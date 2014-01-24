/*****************************************************************************
**
**       Copyright (c) 1995-1996-1997-1998 by IRISA/INRIA Rennes.
**       All Rights Reserved.
**
**       IRISA/INRIA Rennes
**       Campus Universitaire de Beaulieu
**       35042 Rennes Cedex
**
*****************************************************************************/

#ifndef __MVECTORS_H
#define __MVECTORS_H


/*
 * PERMET LA COMMUNICATION AVEC LE MODULE DE DECODAGE MPEG
 */

/* Historique: 19/11/98: Pascal SIMONS
 *
 * Ajout des definitions de type pour la matrice de motion vectors et
 * pour le tableau de matrices de motion vectors.
 */

/*
 * Definition d'un type booleen pour valider des macroblocs.
 */
typedef enum {FAUX= 0==1 ,VRAI= 0==0 } BOOLEEN;

/*
 * Type d'image (B, P, I) 
 */
// Type de mouvement contraint
typedef enum {
    ITYPE = 1,
    PTYPE = 2,
    BTYPE = 3,
    DTYPE = 4,
    NBTYPES,
} FrameType;

/*
 * Structure de base pour coder des informations de mouvement sur un
 * Macrobloc.
 */
typedef struct
{
  BOOLEEN valid;  /* Si valid=VRAI, le bloc contient un Motion Vecteur,
		   * sinon, il s'agit d'un bloc INTRA.
		   */
  int x;	   /* mvt en x */
  int y;	   /* mvt en y */
} TVector;

/*
 * Definition d'un type de matrice contenant les informations de mouvement
 * de toute une image.
 */
typedef struct{
  TVector   **vector;
  int	    index;		/* Index de l'image de reference par les vecteurs mvt */
  int	    nbI;		/* Nb de mb intra de l'image */
  int	    nbF;		/* Nb de mb forward de l'image */
  int	    nbB;		/* Nb de mb backward de l'image */
  int	    nbFB;		/* Nb de mb forward et backwardde l'image */
  FrameType type;		/* Type de l'image : I, B, P */
  double    vprec;		/* Precision sur les vecteurs MPEG 1.0 ou 2.0*/
  int	    nbli;
  int	    nbco;
} TVectorTable;



/*
 * ALLOCATION DES MATRICES de motions Vecteurs
 */

 TVectorTable  *VectorTableAlloc(TVectorTable *m, int nbli, int nbco, int nbtables, int force);

/*
 * DESALLOCATION DES MATRICES de motions Vecteurs
 */
 void	VectorTableFree(TVectorTable *m, int nbtables);


/*
 * Mise a jour des indexes des images de references
 */

 void SetReferenceFrame(TVectorTable *forward, TVectorTable *backward, int nbtables);


 void	CopyVectorTable(TVectorTable *vectsrc,TVectorTable *vectdest);
 void	ClearVectorTable(TVectorTable *vect);
#endif
