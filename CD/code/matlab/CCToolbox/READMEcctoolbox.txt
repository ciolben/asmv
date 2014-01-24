Create input for cc toolbox from particleVideoAnalyzer.exe ("Dump to Matlab format").
	name.sps file -> curve.txt
In Matlab, go into CCToolbox folder, and write
	setcctpath;
Now, read curves data with handmade function that converts data points to cells array :
	curvedata = readcsv("curve.txt");
Get clustering algorithm options (for linear regression e.g) :
	ops = listmodels("lrm");
If you want to change the number of clusters for example, do :
	ops.K = 10;
Compute now the clusters :
	resdata = curve_clust(curvedata, ops);
Finally, print the result (might take a while) :
	showmodel(resdata, curvedata);
