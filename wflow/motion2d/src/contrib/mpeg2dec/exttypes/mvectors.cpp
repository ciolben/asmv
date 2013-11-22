/*****************************************************************************
**
**       Copyright (c) 1999-2001 by IRISA/INRIA Rennes.
**       All Rights Reserved.
**
**       IRISA/INRIA Rennes
**       Campus Universitaire de Beaulieu
**       35042 Rennes Cedex
**
*****************************************************************************/
#include  <stdlib.h> 

// Nombre de tables de vecteurs alouees 
// a linitialisation (4 pour la suite d'image PBBP)
#define NB_VECTOR_TABLES_MIN	4
#include "mvectors.h"
/*
 * Allocation d'un tableau de matrice de MV.
 *
 * Arguments :
 * int nbtables : Nombre de matrices
 * int nbli      : Nombre de macroblocs en horizontal dans chaque matrice.
 * int nbco      : Nombre de macroblocs en vertical dans chaque matrice.
*/

TVectorTable  *VectorTableAlloc(TVectorTable *m, int nbli, int nbco, int nbtables, int force)
{
  int i, j;
  if (force == 1){
    
    m = (TVectorTable *) calloc(nbtables, sizeof(TVectorTable));
    if (m == NULL){	
	return(m);
    }

    for(i = 0 ; i < nbtables; i++)  {
      m[i].nbli = nbli;
      m[i].nbco = nbco;
      m[i].vector = (TVector **) malloc(nbli*sizeof(TVector *));
      if (m[i].vector == NULL){
	  return(m);
      }
      for (j = 0 ; j < nbli ; j ++){
	m[i].vector[j] = (TVector *) malloc(nbco*sizeof(TVector));
        if (m[i].vector[j] == NULL){
	    return(m);
	}
      }
    }
    
    return m;
  }
  
  m = (TVectorTable *) realloc((TVectorTable *) m, nbtables*sizeof( TVectorTable));
  if (m == NULL){
    return(m);
  }      
  for(i = 0 ; i < nbtables ; i++)  {
    m[i].nbli = nbli;
    m[i].nbco = nbco;
    m[i].vector = (TVector **) realloc((TVector **) m[i].vector, nbli*sizeof(TVector *));
    if (m[i].vector == NULL){
	return(m);
    }
    for (j = 0 ; j < nbli ; j ++){
       m[i].vector[j] = (TVector *) realloc((TVector *) m[i].vector[j],nbco*sizeof( TVector));
       if (m[i].vector[j] == NULL){
	   return(m);
       }

    }
  }
  return(m);

}



void	VectorTableFree(TVectorTable *m, int nbtables)
{

  int i, j;
  for(i = 0 ; i < nbtables ; i++)  {
    for (j = 0 ; j < m[i].nbli ; j ++){
      free(m[i].vector[j]);
      
    }

    free(m[i].vector);    
  }

  if (nbtables > 2){
    free(m);    
  }  
}




void	CopyVectorTable(TVectorTable *vectsrc,TVectorTable *vectdest)
{
  int x, y;
  for (x = 0; x < vectsrc->nbli; x++)
    for (y = 0; y < vectsrc->nbco; y++){
      vectdest->vector[x][y].valid = vectsrc->vector[x][y].valid;
      vectdest->vector[x][y].x = vectsrc->vector[x][y].x;
      vectdest->vector[x][y].y = vectsrc->vector[x][y].y;
    }
  vectdest->type = vectsrc->type;
  vectdest->nbI = vectsrc->nbI;
  vectdest->nbF = vectsrc->nbF;
  vectdest->nbB = vectsrc->nbB;
  vectdest->nbFB = vectsrc->nbFB;
  vectdest->index = vectsrc->index;
  vectdest->vprec = vectsrc->vprec;
  vectdest->nbli = vectsrc->nbli;
  vectdest->nbco = vectsrc->nbco;

}

void	ClearVectorTable(TVectorTable *vect)
{
  int x, y;
  for (x = 0; x < vect->nbli; x++)
    for (y = 0; y < vect->nbco; y++){
      vect[0].vector[x][y].valid = FAUX;
      vect[0].vector[x][y].x = 0;
      vect[0].vector[x][y].y = 0;
    }

}
