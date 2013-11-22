#ifndef INITIALIZE_H_
#define INITIALIZE_H_

#include "DenseTrack.h"

void InitTrackerInfo(TrackerInfo* tracker, int track_length, int init_gap)
{
	tracker->trackLength = track_length;
	tracker->initGap = init_gap;
}

DescMat* InitDescMat(int height, int width, int nBins)
{
	DescMat* descMat = (DescMat*)malloc(sizeof(DescMat));
	descMat->height = height;
	descMat->width = width;
	descMat->nBins = nBins;
	descMat->desc = (float*)malloc(height*width*nBins*sizeof(float));
	memset( descMat->desc, 0, height*width*nBins*sizeof(float));
	return descMat;
}

void ReleDescMat( DescMat* descMat)
{
	free(descMat->desc);
	free(descMat);
}

void InitDescInfo(DescInfo* descInfo, int nBins, int flag, int orientation, int size, int nxy_cell, int nt_cell)
{
	descInfo->nBins = nBins;
	descInfo->fullOrientation = orientation;
	descInfo->norm = 2;
	descInfo->threshold = min_flow;
	descInfo->flagThre = flag;
	descInfo->nxCells = nxy_cell;
	descInfo->nyCells = nxy_cell;
	descInfo->ntCells = nt_cell;
	descInfo->dim = descInfo->nBins*descInfo->nxCells*descInfo->nyCells;
	descInfo->blockHeight = size;
	descInfo->blockWidth = size;
}

void usage()
{
	fprintf(stderr, "Extract dense trajectories from a video\n\n");
	fprintf(stderr, "Usage: DenseTrack video_file [options]\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "  -h                        Display this message and exit\n");
	fprintf(stderr, "  -S [start frame]          The start frame to compute feature (default: S=0 frame)\n");
	fprintf(stderr, "  -E [end frame]            The end frame for feature computing (default: E=last frame)\n");
	fprintf(stderr, "  -L [trajectory length]    The length of the trajectory (default: L=15 frames)\n");
	fprintf(stderr, "  -W [sampling stride]      The stride for dense sampling feature points (default: W=5 pixels)\n");
	fprintf(stderr, "  -N [neighborhood size]    The neighborhood size for computing the descriptor (default: N=32 pixels)\n");
	fprintf(stderr, "  -s [spatial cells]        The number of cells in the nxy axis (default: nxy=2 cells)\n");
	fprintf(stderr, "  -t [temporal cells]       The number of cells in the nt axis (default: nt=3 cells)\n");
	fprintf(stderr, "  -T [wFlow]		     0: track optical flow for traj, hog, hof, mbh | 1: track wflow for w-traj, w-hog, w-hof (hof+hofwflow), w-mbh (default 0)\n");
	fprintf(stderr, "  -C [DCS or others]        0: traj hog hof/w-hof mbh | 1: traj curldiv shearC shearD (default 0)\n");
	fprintf(stderr, "  -M [model files] 	     Set 1 to write Affine flow model files using Motion2D (default 0)\n");
}

#if _MSC_VER >= 1600

#include <tchar.h>
TCHAR   *optarg;        // global argument pointer
int     optind = 0;     // global argv index

int getopt(int argc, TCHAR *argv[], TCHAR *optstring) {
    static TCHAR *next = NULL;
    if (optind == 0)
        next = NULL;
    int debugopting = optind;
    optarg = NULL;

    if (next == NULL || *next == _T('\0')) {
        if (optind == 0)
            optind++;

        if (optind >= argc || argv[optind][0] != _T('-') || argv[optind][1] == _T('\0')) {
            optarg = NULL;
            if (optind < argc)
                optarg = argv[optind];
            return EOF;
        }

        if (_tcscmp(argv[optind], _T("--")) == 0) {
            optind++;
            optarg = NULL;
            if (optind < argc)
                optarg = argv[optind];
            return EOF;
        }

        next = argv[optind];
        next++;     // skip past -
        optind++;
    }

    TCHAR c = *next++;
    TCHAR *cp = _tcschr(optstring, c);

    if (cp == NULL || c == _T(':'))
        return _T('?');

    cp++;
    if (*cp == _T(':')) {
        if (*next != _T('\0')) {
            optarg = next;
            next = NULL;
        } else if (optind < argc) {
            optarg = argv[optind];
            optind++;
        } else {
            return _T('?');
        }
    }
    debugopting = optind;
    return c;
}
#endif

void arg_parse(int argc, char** argv)
{
	int c;
    char* executable = argv[0];//basename(argv[0]);
    while((c = getopt (argc, argv, "hS:E:L:W:N:s:t:T:C:M:")) != -1)
    switch(c) {
        case 'S':
        start_frame = atoi(optarg);
        break;
        case 'E':
        end_frame = atoi(optarg);
        break;
        case 'L':
        track_length = atoi(optarg);
        break;
        case 'W':
        min_distance = atoi(optarg);
        break;
        case 'N':
        patch_size = atoi(optarg);
        break;
        case 's':
        nxy_cell = atoi(optarg);
        break;
        case 't':
        nt_cell = atoi(optarg);
        break;

        case 'T':
        wFlow = atoi(optarg);
        break;
        case 'C':
        featComb = atoi(optarg);
        break;
        case 'M':
        compute_models = atoi(optarg);
        break;

        case 'h':
        usage();
        exit(0);
        break;

        default:
        fprintf(stderr, "error parsing arguments at -%c\n  Try '%s -h' for help.", c, executable );
        abort();
    }
}

#endif /*INITIALIZE_H_*/
