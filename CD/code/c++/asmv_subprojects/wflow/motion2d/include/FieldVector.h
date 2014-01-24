/*

  Copyright (c) 1995-2005 by INRIA.
  All Rights Reserved.

  This software was developed at:
  IRISA/INRIA Rennes
  Campus Universitaire de Beaulieu
  35042 Rennes Cedex

  http://www.irisa.fr

*/

#ifndef FieldVector_h
#define FieldVector_h

/*!
  \file FieldVector.h
  \brief Definition of field vectors input/output functions.
*/

#include <stdio.h>
#include <CMotion2DModel.h>
#include <CMotion2DImage.h>

bool WriteFieldVector(CMotion2DModel &model,
		      CMotion2DImage<unsigned char> &S, unsigned char label,
		      const char *filename);

bool WriteFieldVector(CMotion2DModel &model,
		      CMotion2DImage<short> &S, short label,
		      const char *filename);

#endif
