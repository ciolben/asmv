/*

  Copyright (c) 1995-2005 by INRIA.
  All Rights Reserved.

  This software was developed at:
  IRISA/INRIA Rennes
  Campus Universitaire de Beaulieu
  35042 Rennes Cedex

  http://www.irisa.fr

*/

#ifndef Motion2DImage_PNG_h
#define Motion2DImage_PNG_h

#ifndef __NO_IMAGEIO_PNG_

#include <CMotion2DImage.h>

using namespace std;

#if defined (WIN32)
#  if defined MOTION2D_DLL_EXPORTS
#     define MOTION2D_API __declspec( dllexport )
#  elif defined MOTION2D_DLL_IMPORTS
#     define MOTION2D_API __declspec( dllimport )
#  else
#     define MOTION2D_API
#  endif
#else
#     define MOTION2D_API
#endif

/*!
  \file Motion2DImage_PNG.h
  \brief Definition of PNG image format input/output functions.
*/

/*!

  Read the contents of the PNG filename, allocate memory for the corresponding
  gray level image, convert the data in gray level, and set the bitmap whith
  the gray level data. That means that the image \e I is a "black and white"
  rendering of the original image in \e filename, as in a black and white
  photograph.

  \return false if an error occurs, or true otherwise.

  If the image has been already initialized, memory allocation is done
  only if the new image size is different, else we re-use the same
  memory space.

  \sa ReadPGM(), ReadPPM(), WritePNG()

*/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
MOTION2D_API
#endif
int ReadPNG(CMotion2DImage<unsigned char> &I, const char *filename);
/*!

  Read the contents of the PNG filename, allocate memory for the corresponding
  gray level image, convert the data in gray level, and set the bitmap whith
  the gray level data. That means that the image \e I is a "black and white"
  rendering of the original image in \e filename, as in a black and white
  photograph.

  \return false if an error occurs, or true otherwise.

  If the image has been already initialized, memory allocation is done
  only if the new image size is different, else we re-use the same
  memory space.

  \sa ReadPGM(), ReadPPM(), WritePNG()

*/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
MOTION2D_API
#endif
int ReadPNG(CMotion2DImage<short> &I, const char *filename);
/*!

  Write the content of the bitmap in the file which name is given by \e
  filename. This function writes a PNG file.

  \warning The resulted PNG image is a gray level image.

  \return false if an error occurs, or true otherwise.

  \sa ReadPNG(), WritePGM(), WritePPM()

*/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
MOTION2D_API
#endif
int WritePNG(CMotion2DImage<unsigned char> &I, const char *filename);

/*!

  Write the content of the bitmap in the file which name is given by \e
  filename. This function writes a PNG file.

  \warning The resulted PNG image is a gray level image.

  \return false if an error occurs, or true otherwise.

  \sa ReadPNG(), WritePGM(), WritePPM()

*/
#ifndef DOXYGEN_SHOULD_SKIP_THIS
MOTION2D_API
#endif
int WritePNG(CMotion2DImage<short> &I, const char *filename);
#endif

#endif
