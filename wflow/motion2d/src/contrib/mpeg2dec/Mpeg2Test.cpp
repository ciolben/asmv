// principal.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>

#include <iostream.h>
#include"Mpeg2Irisa.h"
#include"Image.h"
int main(int argc, char  *argv[])
{
  Image image;
  unsigned char* imageRaw;
  int moreframes;
  unsigned long int ima = 0;
  Mpeg2Irisa mpeg;

  mpeg.openStream(argv[1]);
  cout << "Taille des images : " << mpeg.getWidth() << " " << mpeg.getHeight() << endl;
  mpeg.initStream();

  //  image = (unsigned char *) malloc ( height * width* sizeof(unsigned char));

   //Allocation memoire pour img1 et img2 avant lecture
  do {
    moreframes = mpeg.skipFrame( );

    cout << "ima: " << ima <<" " << moreframes<< endl;

    ima ++;
  } while ( (ima < 10 ) && (moreframes) );



  do {
    moreframes = mpeg.getFrame( &imageRaw);

    image.fromDataRaw(imageRaw,mpeg.getWidth(),mpeg.getHeight(),3);
    char name[255];
    
    sprintf(name,"toto%06d.png",ima);

image.write(name);

 cout << "ima: " << ima << " " << moreframes<< " " << name<<endl;
 ima++;
  } while ( (ima < 20 ) && (moreframes) );


  cout <<" test\n";
  mpeg.closeStream();



  cout << "fin" << endl;
  return(0);
}

