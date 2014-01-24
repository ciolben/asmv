/*****************************************************************************
**
**       Copyright (c) 2000 by IRISA/INRIA Rennes.
**       All Rights Reserved.
**
**       IRISA/INRIA Rennes
**       Campus Universitaire de Beaulieu
**       35042 Rennes Cedex
**
*****************************************************************************/


/*
 * structure d'un block dct0.
 */
typedef struct
{
  BOOLEEN valid;  /* Si valid=VRAI, le bloc contient un Motion Vecteur,
		   * sinon, il s'agit d'un bloc INTRA.
		   */
  unsigned char g; /* niveau de gris du block */
} Tdct;

/*
 * Definition d'un type de matrice contenant les informations de mouvement
 * de toute une image.
 */
typedef struct{
  Tdct   **block;
  int	    nbli;
  int	    nbco;
} TdctTable;

// Fonction d'allocation et de desallocation pour le type dct
TdctTable  *dctTableAlloc(TdctTable *m, int nbli, int nbco, int nbtables, int force);
void	dctTableFree(TdctTable *m, int nbtables);

void	CopydctTable(TdctTable *vectsrc,TdctTable *vectdest);
void	CleardctTable(TdctTable *vect);

