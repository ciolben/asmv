#include "DenseTrack.h"
#include "Descriptors.h"
#include "Initialize.h"

#include <string>
using std::string;

IplImageWrapper image, prev_image, grey, prev_grey;
IplImagePyramid grey_pyramid, prev_grey_pyramid, eig_pyramid;

CvCapture* capture = 0;
float* fscales = 0; 					// float scale values
int show_track = 0; 					// set show_track = 1, if you want to visualize the trajectories
char motion2D_path[] = "Motion2D";	// set the appropriate path

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
                result += buffer;
    }
    pclose(pipe);
    return result;
}

void computeFlowAff(float *modAff, IplImage* flowAff) {
    double co_c,li_c;
    int height, width;
    height = flowAff->height;
    width = flowAff->width;
    co_c = (double)width/2;
    li_c = (double)height/2;
    for(int row=0; row<height; row++){
      float* f = (float*)(flowAff->imageData + flowAff->widthStep*row);
      for(int col=0; col<width; col++)  {
        double x_xg = (double)col - co_c;
        double y_yg = (double)row - li_c;
        f[2*col] = modAff[2] + modAff[4] * x_xg + modAff[5] * y_yg;
        f[2*col+1] = modAff[3] + modAff[6] * x_xg + modAff[7] * y_yg;
      }
    }
}

void diffFlow(IplImage* flow, IplImage* flowAff, IplImage* flowDiff)	{
    int height, width;
    height = flow->height;
    width = flow->width;
    for(int row=0; row<height; row++){
      float* f = (float*)(flow->imageData + flow->widthStep*row);
      float* fa = (float*)(flowAff->imageData + flowAff->widthStep*row);
      float* fd = (float*)(flowDiff->imageData + flowDiff->widthStep*row);
      for(int col=0; col<width; col++)  {
	fd[2*col] = f[2*col] - fa[2*col];
	fd[2*col+1] = f[2*col+1] - fa[2*col+1];
      }
    }
}

//////////////////////////////------------------------------------------------------------------////////////////////////////////
#if _MSC_VER >= 1600
//#include <direct.h>
//#include <Windows.h>
#endif
void write_motionModels(char *video, char *model_path, char *mod)
{
	int frameNum = 0;
	CvCapture* capture = 0;

	printf("%s %s \n",video,model_path);
    capture = cvCreateFileCapture(video);
	if( !capture ) {
		printf( "Could not initialize capturing..\n" );
		return;
	}

	char cmd[300];
    string result;
    #if _MSC_VER >= 1600
        {
        //Nothing to do, will never work. Tried EVERYTHING.
//            wchar_t mpath[64];
//            char* framespath = "frames"; wchar_t fpath[128];
//            MultiByteToWideChar(CP_ACP, 0, model_path, -1, mpath, 64); //convert to LPCWSTR
//            MultiByteToWideChar(CP_ACP, 0, framespath, -1, fpath, 128);
//            int res = CreateDirectory(mpath,NULL);
//            _chdir(model_path);
//            res += CreateDirectory(fpath,NULL);
//            _chdir("..");
//            printf("mkdir : %d\n", res);
        //So bruteforce after hours... (not sure if every win OS has natively mkdir, but well,
        //it's driving me crazy)
            sprintf(cmd,"mkdir \".\\%s\\Frames\"",model_path);
            result = exec(cmd);
        }

        //result = "";
    #else
        sprintf(cmd,"\"mkdir -p \"%s/Frames\"\"",model_path);
        printf("mkdir cmd= %s\n",cmd);
        string result = exec(cmd);
        printf("%s \n",result.c_str());
    #endif
	while(true) {
	    char framepath[300];
	    IplImage* frame = 0;
	    frame = cvQueryFrame( capture );
	    if( !frame ) {
		break;
	    }

	    image = IplImageWrapper( cvGetSize(frame), 8, 3 );
	    image->origin = frame->origin;
	    cvCopy( frame, image, 0 );
	    grey = IplImageWrapper( cvGetSize(frame), 8, 1 );
	    cvCvtColor( image, grey, CV_BGR2GRAY );

	    sprintf(framepath,"%s/Frames/%05d.png",model_path,frameNum);

	    if( !cvSaveImage(framepath, grey) )
		fprintf(stderr, "failed to write image file\n");

	    frameNum++;
	}

	// Compute motion model
	sprintf(cmd,"%s -m %s  -p \"%s/Frames/%%05d.png\" -f 0 -i %d -r \"%s/%s.mod\"",motion2D_path,mod,model_path,frameNum-1,model_path,mod);
	printf("cmd= %s\n",cmd);
    result = exec(cmd); _exec("");
	sprintf(cmd,"rm -rf %s/Frames",model_path);
	result = exec(cmd);				// delete the frames
	
	return;
}


//////////////////////////////------------------------------------------------------------------////////////////////////////////

        
int main( int argc, char** argv )
{
	int frameNum = 0;
	TrackerInfo tracker;
	DescInfo hogInfo;
	DescInfo hofInfo;
	DescInfo mbhInfo;
	DescInfo curldivInfo;
	DescInfo shearCDInfo;

	char* video = argv[1];
	char* model_path = argv[2];				// to save or access the Affine motion model files
    arg_parse(argc - 2, argv + 2);

	if(compute_models) {
		printf("%s \n",model_path);
		if(model_path[0]=='-') {
		    printf("With -M 1, second argument should be the path for model file! \n");
		    return 0; }
		write_motionModels(video,model_path,"AC");	// compute and write Affine model using Motion2D
		return 0;					// then return
	}

	char modelfile[300];
	sprintf(modelfile,"%s/AC.mod",model_path);
	std::ifstream streamfile(modelfile);
	if(!streamfile) {
		printf("Model file does not exists, please create model file first and then pass the path!\n");
		printf("./release/DenseTrack <video>  < model_path> -T ... \n");
		return 0;
	}

	if(wFlow) {						//  Affine flow will be used
		string dummyLine;
		for(int f=0; f<43+start_frame; f++) {		// skip comment/info lines
		    getline(streamfile, dummyLine);
		}
	}

	InitTrackerInfo(&tracker, track_length, init_gap);
	InitDescInfo(&hogInfo, 8, 0, 1, patch_size, nxy_cell, nt_cell);
	InitDescInfo(&hofInfo, 9, 1, 1, patch_size, nxy_cell, nt_cell);
	InitDescInfo(&mbhInfo, 8, 0, 1, patch_size, nxy_cell, nt_cell);
	InitDescInfo(&curldivInfo, 8, 0, 1, patch_size, nxy_cell, nt_cell);
	InitDescInfo(&shearCDInfo, 8, 0, 0, patch_size, nxy_cell, nt_cell);

	capture = cvCreateFileCapture(video);

	if( !capture ) { 
		printf( "Could not initialize capturing..\n" );
		return -1;
	}

	if( show_track == 1 )
		cvNamedWindow( "DenseTrack", 0 );


	std::vector<std::list<Track> > xyScaleTracks;
	int init_counter = 0; // indicate when to detect new feature points
	while( true ) {
		IplImage* frame = 0;
		int i, c;

		// get a new frame
		frame = cvQueryFrame( capture );
		if( !frame ) {
			break;
		}
		if( frameNum >= start_frame && frameNum <= end_frame ) {
		if( !image ) {
			// initailize all the buffers
			image = IplImageWrapper( cvGetSize(frame), 8, 3 );
			image->origin = frame->origin;
			prev_image= IplImageWrapper( cvGetSize(frame), 8, 3 );
			prev_image->origin = frame->origin;
			grey = IplImageWrapper( cvGetSize(frame), 8, 1 );
			grey_pyramid = IplImagePyramid( cvGetSize(frame), 8, 1, scale_stride );
			prev_grey = IplImageWrapper( cvGetSize(frame), 8, 1 );
			prev_grey_pyramid = IplImagePyramid( cvGetSize(frame), 8, 1, scale_stride );
			eig_pyramid = IplImagePyramid( cvGetSize(frame), 32, 1, scale_stride );

			cvCopy( frame, image, 0 );
			cvCvtColor( image, grey, CV_BGR2GRAY );
			grey_pyramid.rebuild( grey );

			// how many scale we can have
			scale_num = std::min<std::size_t>(scale_num, grey_pyramid.numOfLevels());
			fscales = (float*)cvAlloc(scale_num*sizeof(float));
			xyScaleTracks.resize(scale_num);

			for( int ixyScale = 0; ixyScale < scale_num; ++ixyScale ) {
				std::list<Track>& tracks = xyScaleTracks[ixyScale];
				fscales[ixyScale] = pow(scale_stride, ixyScale);

				// find good features at each scale separately
				IplImage *grey_temp = 0, *eig_temp = 0;
				std::size_t temp_level = (std::size_t)ixyScale;
				grey_temp = cvCloneImage(grey_pyramid.getImage(temp_level));
				eig_temp = cvCloneImage(eig_pyramid.getImage(temp_level));
				std::vector<CvPoint2D32f> points(0);
				cvDenseSample(grey_temp, eig_temp, points, quality, min_distance);

				// save the feature points
				for( i = 0; i < points.size(); i++ ) {
					Track track(tracker.trackLength);
					if(featComb) {
					    PointDesc point(curldivInfo, shearCDInfo, points[i]);
					    track.addPointDesc(point); }
					else {
						if (wFlow) {
						    PointDesc point(0, hogInfo, hofInfo, mbhInfo, points[i]); 
						    track.addPointDesc(point); }
						else {
						    PointDesc point(hogInfo, hofInfo, mbhInfo, points[i]);
						    track.addPointDesc(point); }
					}
					tracks.push_back(track);
				}

				cvReleaseImage( &grey_temp );
				cvReleaseImage( &eig_temp );
			}
		}

		// build the image pyramid for the current frame
		cvCopy( frame, image, 0 );
		cvCvtColor( image, grey, CV_BGR2GRAY );
		grey_pyramid.rebuild(grey);

		if( frameNum > 0 ) {
		init_counter++;

		float modAff[8];		// for affine model parameters

        for( int ixyScale = 0; ixyScale < scale_num; ++ixyScale ) {
			// track feature points in each scale separately
			std::vector<CvPoint2D32f> points_in(0);
			std::list<Track>& tracks = xyScaleTracks[ixyScale];
			for (std::list<Track>::iterator iTrack = tracks.begin(); iTrack != tracks.end(); ++iTrack) {
				CvPoint2D32f point = iTrack->pointDescs.back().point;
				points_in.push_back(point); // collect all the feature points at scale ixyScale
			}
			int count = points_in.size();
			IplImage *prev_grey_temp = 0, *grey_temp = 0;
			std::size_t temp_level = ixyScale;
			prev_grey_temp = cvCloneImage(prev_grey_pyramid.getImage(temp_level));
			grey_temp = cvCloneImage(grey_pyramid.getImage(temp_level));

			cv::Mat prev_grey_mat = cv::cvarrToMat(prev_grey_temp);
			cv::Mat grey_mat = cv::cvarrToMat(grey_temp);

			std::vector<int> status(count);
			std::vector<CvPoint2D32f> points_out(count);

		      // read affine motion model parameters
		      if(wFlow) {
  			if(ixyScale==0) {
			    if (frameNum > start_frame)   {
				float dummyval;
				for(int f=0; f<17; f++)	{
				    if(f>=1 && f<=8)
					streamfile >> modAff[f-1];
				    else
					streamfile >> dummyval;
				}
			    }
			    else
				for(int f = 0; f<8; f++)
					modAff[f] = 0;
                	}
			else {
                modAff[2] /= sqrt(2.f);	// c1 c2 updated for scale change
                modAff[3] /= sqrt(2.f);
			}
		      }

			// compute the affine flow using the motion model
			IplImage* flowAff = cvCreateImage(cvGetSize(grey_temp), IPL_DEPTH_32F, 2);
			if(wFlow)
			  computeFlowAff(modAff,flowAff);

			// compute the optical flow
			IplImage* flow = cvCreateImage(cvGetSize(grey_temp), IPL_DEPTH_32F, 2);
			cv::Mat flow_mat = cv::cvarrToMat(flow);
			cv::calcOpticalFlowFarneback( prev_grey_mat, grey_mat, flow_mat,
                            sqrt(2.f)/2.0, 5, 10, 2, 7, 1.5, cv::OPTFLOW_FARNEBACK_GAUSSIAN );

			// compute wFlow
			IplImage* flowDiff = cvCreateImage(cvGetSize(grey_temp), IPL_DEPTH_32F, 2);
			if(wFlow) 
			    diffFlow(flow,flowAff,flowDiff);         // flowDiff = flow-flowAff

			// track feature points by median filtering
			if(wFlow)
				OpticalFlowTracker(flowDiff, points_in, points_out, status);
			else
				OpticalFlowTracker(flow, points_in, points_out, status);



			int width = grey_temp->width;
			int height = grey_temp->height;
			// compute the integral histograms
			DescMat* hogMat;
			DescMat* hofMat;
			DescMat* mbhMatX;
			DescMat* mbhMatY;
			DescMat* hofMat_wFlow;
			DescMat* curldivMat;
			DescMat* shearCMat;
			DescMat* shearDMat;

			if(featComb) {
				curldivMat = InitDescMat(height, width, curldivInfo.nBins);
				shearCMat = InitDescMat(height, width, shearCDInfo.nBins);
				shearDMat = InitDescMat(height, width, shearCDInfo.nBins);
				if(wFlow==1)
				    KinemComp(flowDiff, curldivMat, shearCMat, shearDMat, curldivInfo, shearCDInfo);
				else
				    KinemComp(flow, curldivMat, shearCMat, shearDMat, curldivInfo, shearCDInfo);
			}
			else {
				hogMat = InitDescMat(height, width, hogInfo.nBins);
				hofMat = InitDescMat(height, width, hofInfo.nBins);
				mbhMatX = InitDescMat(height, width, mbhInfo.nBins);
				mbhMatY = InitDescMat(height, width, mbhInfo.nBins);
				
                                HogComp(prev_grey_temp, hogMat, hogInfo);
				HofComp(flow, hofMat, hofInfo);

				if(wFlow) {
					hofMat_wFlow = InitDescMat(height, width, hofInfo.nBins);
					HofComp(flowDiff, hofMat_wFlow, hofInfo);
					MbhComp(flowDiff, mbhMatX, mbhMatY, mbhInfo);
				}
				else 
					MbhComp(flow, mbhMatX, mbhMatY, mbhInfo);
			}

			i = 0;
			for (std::list<Track>::iterator iTrack = tracks.begin(); iTrack != tracks.end(); ++i) {
			if( status[i] == 1 ) { // if the feature point is successfully tracked
				PointDesc& pointDesc = iTrack->pointDescs.back();
				CvPoint2D32f prev_point = points_in[i];
				// get the descriptors for the feature point
				CvScalar rect = getRect(prev_point, cvSize(width, height), hogInfo);
				
				if(featComb) {
				    pointDesc.curldiv = getDesc(curldivMat, rect, curldivInfo);
				    pointDesc.shearC = getDesc(shearCMat, rect, shearCDInfo);
				    pointDesc.shearD = getDesc(shearDMat, rect, shearCDInfo);
				    PointDesc point(curldivInfo, shearCDInfo, points_out[i]);
				    iTrack->addPointDesc(point); }
				else {
				    pointDesc.hog = getDesc(hogMat, rect, hogInfo);
				    pointDesc.hof = getDesc(hofMat, rect, hofInfo);
				    pointDesc.mbhX = getDesc(mbhMatX, rect, mbhInfo);
				    pointDesc.mbhY = getDesc(mbhMatY, rect, mbhInfo);
				    if(wFlow) {
					pointDesc.hof_wFlow = getDesc(hofMat_wFlow, rect, hofInfo);
					PointDesc point(0, hogInfo, hofInfo, mbhInfo, points_out[i]);
					iTrack->addPointDesc(point); }
				    else {
					PointDesc point(hogInfo, hofInfo, mbhInfo, points_out[i]);
					iTrack->addPointDesc(point); }
				}

				// draw this track
				if( show_track == 1 ) {
					std::list<PointDesc>& descs = iTrack->pointDescs;
					std::list<PointDesc>::iterator iDesc = descs.begin();
					float length = descs.size();
					CvPoint2D32f point0 = iDesc->point;
					point0.x *= fscales[ixyScale]; // map the point to first scale
					point0.y *= fscales[ixyScale];

					float j = 0;
					for (iDesc++; iDesc != descs.end(); ++iDesc, ++j) {
						CvPoint2D32f point1 = iDesc->point;
						point1.x *= fscales[ixyScale];
						point1.y *= fscales[ixyScale];

						cvLine(image, cvPointFrom32f(point0), cvPointFrom32f(point1),
							   CV_RGB(0,cvFloor(255.0*(j+1.0)/length),0), 2, 8,0);
						point0 = point1;
					}
					cvCircle(image, cvPointFrom32f(point0), 2, CV_RGB(255,0,0), -1, 8,0);
				}
				++iTrack;
			}
			else // remove the track, if we lose feature point
				iTrack = tracks.erase(iTrack);
			}

			// Release
			if(featComb) {
				ReleDescMat(curldivMat);
				ReleDescMat(shearCMat);
				ReleDescMat(shearDMat);	}
			else{
			    if(wFlow)
				ReleDescMat(hofMat_wFlow);
			    ReleDescMat(hogMat);
			    ReleDescMat(hofMat);
			    ReleDescMat(mbhMatX);
			    ReleDescMat(mbhMatY);
			}

			cvReleaseImage( &prev_grey_temp );
			cvReleaseImage( &grey_temp );
            cvReleaseImage( &flow ); //*********************************************************
			cvReleaseImage( &flowAff );
            //cvReleaseImage( &flowDiff );

            //save wflow
            if (ixyScale == 0) {
                char buff[256];
                sprintf(buff, "%s/wflow%d.yml.gz", model_path, frameNum);
                cv::FileStorage file(buff, cv::FileStorage::WRITE);
                file << "wflow" << flowDiff;
                file.release();
            }

            cvReleaseImage( &flowDiff );
		}

//skeep features
if (false) {

		for( int ixyScale = 0; ixyScale < scale_num; ++ixyScale ) {
		std::list<Track>& tracks = xyScaleTracks[ixyScale]; // output the features for each scale
		for( std::list<Track>::iterator iTrack = tracks.begin(); iTrack != tracks.end(); ) {
			if( iTrack->pointDescs.size() >= tracker.trackLength+1 ) { // if the trajectory achieves the length we want
				std::vector<CvPoint2D32f> trajectory(tracker.trackLength+1);
				std::list<PointDesc>& descs = iTrack->pointDescs;
				std::list<PointDesc>::iterator iDesc = descs.begin();

				for (int count = 0; count <= tracker.trackLength; ++iDesc, ++count) {
					trajectory[count].x = iDesc->point.x*fscales[ixyScale];
					trajectory[count].y = iDesc->point.y*fscales[ixyScale];
				}
				float mean_x(0), mean_y(0), var_x(0), var_y(0), length(0);
				if( isValid(trajectory, mean_x, mean_y, var_x, var_y, length) == 1 ) {
					printf("%d\t", frameNum);
					printf("%f\t%f\t", mean_x, mean_y);
					printf("%f\t%f\t", var_x, var_y);
					printf("%f\t", length);
					printf("%f\t", fscales[ixyScale]);

					for (int count = 0; count < tracker.trackLength; ++count)
						printf("%f\t%f\t", trajectory[count].x,trajectory[count].y );

					int t_stride;
					if(!featComb) {									// HOG
					    iDesc = descs.begin();
					    t_stride = cvFloor(tracker.trackLength/hogInfo.ntCells);
					    for( int n = 0; n < hogInfo.ntCells; n++ ) {
						std::vector<float> vec(hogInfo.dim);
						for( int t = 0; t < t_stride; t++, iDesc++ )
							for( int m = 0; m < hogInfo.dim; m++ )
								vec[m] += iDesc->hog[m];
						for( int m = 0; m < hogInfo.dim; m++ )
							printf("%f\t", vec[m]/float(t_stride)); }
					    }

					if(!featComb) {									// HOF
					    iDesc = descs.begin();
					    t_stride = cvFloor(tracker.trackLength/hofInfo.ntCells);
					    for( int n = 0; n < hofInfo.ntCells; n++ ) {
						std::vector<float> vec(hofInfo.dim);
						for( int t = 0; t < t_stride; t++, iDesc++ )
							for( int m = 0; m < hofInfo.dim; m++ )
								vec[m] += iDesc->hof[m];
						for( int m = 0; m < hofInfo.dim; m++ )
							printf("%f\t", vec[m]/float(t_stride)); }
					    }

					if(!featComb && wFlow) {							// HOF_wFlow
					    iDesc = descs.begin();
                                            t_stride = cvFloor(tracker.trackLength/hofInfo.ntCells);
                                            for( int n = 0; n < hofInfo.ntCells; n++ ) {
                                                std::vector<float> vec(hofInfo.dim);
                                                for( int t = 0; t < t_stride; t++, iDesc++ )
                                                        for( int m = 0; m < hofInfo.dim; m++ )
                                                                vec[m] += iDesc->hof_wFlow[m];
                                                for( int m = 0; m < hofInfo.dim; m++ )
							printf("%f\t", vec[m]/float(t_stride)); }
                                            }

					if(!featComb) {									// MBH
					    iDesc = descs.begin();
					    t_stride = cvFloor(tracker.trackLength/mbhInfo.ntCells);
					    for( int n = 0; n < mbhInfo.ntCells; n++ ) {
						std::vector<float> vec(mbhInfo.dim);
						for( int t = 0; t < t_stride; t++, iDesc++ )
							for( int m = 0; m < mbhInfo.dim; m++ )
								vec[m] += iDesc->mbhX[m];
						for( int m = 0; m < mbhInfo.dim; m++ )
							printf("%f\t", vec[m]/float(t_stride)); }
					    
					    iDesc = descs.begin();
					    t_stride = cvFloor(tracker.trackLength/mbhInfo.ntCells);
					    for( int n = 0; n < mbhInfo.ntCells; n++ ) {
						std::vector<float> vec(mbhInfo.dim);
						for( int t = 0; t < t_stride; t++, iDesc++ )
							for( int m = 0; m < mbhInfo.dim; m++ )
								vec[m] += iDesc->mbhY[m];
						for( int m = 0; m < mbhInfo.dim; m++ )
							printf("%f\t", vec[m]/float(t_stride)); }
					    }

					if(featComb) {
					    iDesc = descs.begin();
					    t_stride = cvFloor(tracker.trackLength/curldivInfo.ntCells);
					    for( int n = 0; n < curldivInfo.ntCells; n++ ) {
                                                std::vector<float> vec(curldivInfo.dim);
                                                for( int t = 0; t < t_stride; t++, iDesc++ )
                                                        for( int m = 0; m < curldivInfo.dim; m++ )
                                                                vec[m] += iDesc->curldiv[m];
                                                for( int m = 0; m < curldivInfo.dim; m++ )
							printf("%f\t", vec[m]/float(t_stride)); }

					    iDesc = descs.begin();
                                            t_stride = cvFloor(tracker.trackLength/shearCDInfo.ntCells);
                                            for( int n = 0; n < shearCDInfo.ntCells; n++ ) {
                                                std::vector<float> vec(shearCDInfo.dim);
                                                for( int t = 0; t < t_stride; t++, iDesc++ )
                                                        for( int m = 0; m < shearCDInfo.dim; m++ )
                                                                vec[m] += iDesc->shearC[m];
                                                for( int m = 0; m < shearCDInfo.dim; m++ )
							printf("%f\t", vec[m]/float(t_stride)); }

					    iDesc = descs.begin();
                                            t_stride = cvFloor(tracker.trackLength/shearCDInfo.ntCells);
                                            for( int n = 0; n < shearCDInfo.ntCells; n++ ) {
                                                std::vector<float> vec(shearCDInfo.dim);
                                                for( int t = 0; t < t_stride; t++, iDesc++ )
                                                        for( int m = 0; m < shearCDInfo.dim; m++ )
                                                                vec[m] += iDesc->shearD[m];
                                                for( int m = 0; m < shearCDInfo.dim; m++ )
							printf("%f\t", vec[m]/float(t_stride)); }
					}
				
					printf("\n");
				}
				iTrack = tracks.erase(iTrack);
			}
			else
				iTrack++;
		    }
		}

}  else {
    //minimal
    for( int ixyScale = 0; ixyScale < scale_num; ++ixyScale ) {
        std::list<Track>& tracks = xyScaleTracks[ixyScale]; // output the features for each scale
        for( std::list<Track>::iterator iTrack = tracks.begin(); iTrack != tracks.end(); ) {
            if( iTrack->pointDescs.size() >= tracker.trackLength+1 ) {
                iTrack = tracks.erase(iTrack);
            }
            else {
                iTrack++;
            }
        }
    }
}
//end skeep features

		if( init_counter == tracker.initGap ) { // detect new feature points every initGap frames
		init_counter = 0;
		for (int ixyScale = 0; ixyScale < scale_num; ++ixyScale) {
			std::list<Track>& tracks = xyScaleTracks[ixyScale];
			std::vector<CvPoint2D32f> points_in(0);
			std::vector<CvPoint2D32f> points_out(0);
			for(std::list<Track>::iterator iTrack = tracks.begin(); iTrack != tracks.end(); iTrack++, i++) {
				std::list<PointDesc>& descs = iTrack->pointDescs;
				CvPoint2D32f point = descs.back().point; // the last point in the track
				points_in.push_back(point);
			}

			IplImage *grey_temp = 0, *eig_temp = 0;
			std::size_t temp_level = (std::size_t)ixyScale;
			grey_temp = cvCloneImage(grey_pyramid.getImage(temp_level));
			eig_temp = cvCloneImage(eig_pyramid.getImage(temp_level));

			cvDenseSample(grey_temp, eig_temp, points_in, points_out, quality, min_distance);
			// save the new feature points
			for( i = 0; i < points_out.size(); i++) {
				Track track(tracker.trackLength);
				if(featComb) {
				    PointDesc point(curldivInfo, shearCDInfo, points_out[i]);
				    track.addPointDesc(point); }
				else {
				    if(wFlow) {
					PointDesc point(0, hogInfo, hofInfo, mbhInfo, points_out[i]);
					track.addPointDesc(point); }
				    else {
					PointDesc point(hogInfo, hofInfo, mbhInfo, points_out[i]);
					track.addPointDesc(point); }
				}
				tracks.push_back(track);
			}
			cvReleaseImage( &grey_temp );
			cvReleaseImage( &eig_temp );
		}
		}
		}

		cvCopy( frame, prev_image, 0 );
		cvCvtColor( prev_image, prev_grey, CV_BGR2GRAY );
		prev_grey_pyramid.rebuild(prev_grey);
		}


		if( show_track == 1 ) {
			cvShowImage( "DenseTrack", image);
			c = cvWaitKey(-1);
			if((char)c == 27) break;
		}
		// get the next frame
		frameNum++;

	}

	if( show_track == 1 )
		cvDestroyWindow("DenseTrack");

	return 0;
}
