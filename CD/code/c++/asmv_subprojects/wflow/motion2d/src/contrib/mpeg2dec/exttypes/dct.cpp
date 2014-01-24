/*****************************************************************************
**
**       Copyright (c) 2001 by IRISA/INRIA Rennes.
**       All Rights Reserved.
**
**       IRISA/INRIA Rennes
**       Campus Universitaire de Beaulieu
**       35042 Rennes Cedex
**
*****************************************************************************/
#include <stdlib.h>

typedef enum {FAUX= 0==1 ,VRAI= 0==0 } BOOLEEN;

#include "dct.h"
/*
 * Allocation d'un tableau de matrice de dc-dct.
 *
 * Arguments :
 * int nbtables : Nombre de matrices
 * int nbli      : Nombre de macroblocs en horizontal dans chaque matrice.
 * int nbco      : Nombre de macroblocs en vertical dans chaque matrice.
*/

TdctTable  *dctTableAlloc(TdctTable *m, int nbli, int nbco, int nbtables, int force)
{
  int i, j;

  if (force == 1){
    
    m = (TdctTable *) calloc(nbtables, sizeof(TdctTable));
    if (m == NULL){	
	return(m);
    }

    for(i = 0 ; i < nbtables; i++)  {
      m[i].nbli = nbli;
      m[i].nbco = nbco;
      m[i].block = (Tdct **) malloc(nbli*sizeof(Tdct *));
      if (m[i].block == NULL){
	  return(m);
      }
      for (j = 0 ; j < nbli ; j ++){
	m[i].block[j] = (Tdct *) malloc(nbco*sizeof(Tdct));
        if (m[i].block[j] == NULL){
	    return(m);
	}
      }
    }
    
    return m;
  }
  
  m = (TdctTable *) realloc((TdctTable *) m, nbtables*sizeof( TdctTable));
  if (m == NULL){
    return(m);
  }      
  for(i = 0 ; i < nbtables ; i++)  {
    m[i].nbli = nbli;
    m[i].nbco = nbco;
    m[i].block = (Tdct **) realloc((Tdct **) m[i].block, nbli*sizeof(Tdct *));
    if (m[i].block == NULL){
	return(m);
    }
    for (j = 0 ; j < nbli ; j ++){
       m[i].block[j] = (Tdct *) realloc((Tdct *) m[i].block[j],nbco*sizeof( Tdct));
       if (m[i].block[j] == NULL){
	   return(m);
       }

    }
  }
  return(m);

}

void	dctTableFree(TdctTable *m, int nbtables)
{
  int i, j;

  for(i = 0 ; i < nbtables ; i++)  {
    for (j = 0 ; j < m[i].nbli ; j ++){
      free(m[i].block[j]);
      
    }

    free(m[i].block);    
  }

  if (nbtables > 2){
    free(m);    
  }  
}

void	CopydctTable(TdctTable *dctsrc,TdctTable *dctdest)
{
  int x, y;
  for (x = 0; x < dctsrc->nbli; x++)
    for (y = 0; y < dctsrc->nbco; y++){
      dctdest->block[x][y].valid = dctsrc->block[x][y].valid;
      dctdest->block[x][y].g = dctsrc->block[x][y].g;
  }
  dctdest->nbli = dctsrc->nbli;
  dctdest->nbco = dctsrc->nbco;

}

void	CleardctTable(TdctTable *vect)
{
  int x, y;
  for (x = 0; x < vect->nbli; x++)
    for (y = 0; y < vect->nbco; y++){
      vect[0].block[x][y].valid = FAUX;
      vect[0].block[x][y].g = 0;      
    }

}
