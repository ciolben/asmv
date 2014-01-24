opticalflowCV
	Compute the optical flow and compute the interpolation of two frames.
		In the .pro file, change the config in "app" instead of "lib" if lib cannot be loaded when used (OpenCV libs are hudge)
		Put the bin/lib in the same folder as ASMV.exe.

wflow
	Compute the Omega-flow. Sources are modified in several ways (Windows compatibility, speed improvements (skip writing of descriptors), matrices writing (affine + wflow), added options)
		Contains the dependent sub-project Motion2D, which has also been fixed for Windows (...no effort was done to make it easy from the developers...). The bin is under windows_builds.
		Put wflow.exe and motion2d.exe in the same folder as ASMV.exe.