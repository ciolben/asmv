// Licensed under MIT license; see license.txt.

#include <sbl/math/Geometry.h>
#include <math.h>
namespace sbl {


//-------------------------------------------
// MATRIX 3 CLASS 
//-------------------------------------------


/// create a zero-initialized matrix
Matrix3::Matrix3() {
    data[ 0 ][ 0 ] = 0;
    data[ 0 ][ 1 ] = 0;
    data[ 0 ][ 2 ] = 0;
    data[ 1 ][ 0 ] = 0;
    data[ 1 ][ 1 ] = 0;
    data[ 1 ][ 2 ] = 0;
    data[ 2 ][ 0 ] = 0;
    data[ 2 ][ 1 ] = 0;
    data[ 2 ][ 2 ] = 0;
}


/// set off-diagonal elements to a given value
void Matrix3::setOffDiag( double v ) {
    data[ 0 ][ 1 ] = v;
    data[ 0 ][ 2 ] = v;
    data[ 1 ][ 0 ] = v;
    data[ 1 ][ 2 ] = v;
    data[ 2 ][ 0 ] = v;
    data[ 2 ][ 1 ] = v;
}


/// transform a point using the matrix
Point3 Matrix3::operator*( const Point3 &p ) const {
    return Point3( p.x * data[ 0 ][ 0 ] + p.y * data[ 0 ][ 1 ] + p.z * data[ 0 ][ 2 ],
                   p.x * data[ 1 ][ 0 ] + p.y * data[ 1 ][ 1 ] + p.z * data[ 1 ][ 2 ],
                   p.x * data[ 2 ][ 0 ] + p.y * data[ 2 ][ 1 ] + p.z * data[ 2 ][ 2 ] );
}


//-------------------------------------------
// AFFINE TRANSFORM 3 CLASS
//-------------------------------------------


/// create transform from vector of parameters
AffineTransform3::AffineTransform3( const VectorD &params ) {
    assertAlways( params.length() == 3 || params.length() == 12 );
    b.x = params[ 0 ];
    b.y = params[ 1 ];
    b.z = params[ 2 ];
    if (params.length() == 12) {
        a.data[ 0 ][ 0 ] = params[ 3 ];
        a.data[ 1 ][ 0 ] = params[ 4 ];
        a.data[ 2 ][ 0 ] = params[ 5 ];
        a.data[ 0 ][ 1 ] = params[ 6 ];
        a.data[ 1 ][ 1 ] = params[ 7 ];
        a.data[ 2 ][ 1 ] = params[ 8 ];
        a.data[ 0 ][ 2 ] = params[ 9 ];
        a.data[ 1 ][ 2 ] = params[ 10 ];
        a.data[ 2 ][ 2 ] = params[ 11 ];
    }
}


/// set the matrix elements
void AffineTransform3::setMatrix( double a00, double a01, double a02, double a10, double a11, double a12, double a20, double a21, double a22 ) {
    a.data[ 0 ][ 0 ] = a00;
    a.data[ 0 ][ 1 ] = a01;
    a.data[ 0 ][ 2 ] = a02;
    a.data[ 1 ][ 0 ] = a10;
    a.data[ 1 ][ 1 ] = a11;
    a.data[ 1 ][ 2 ] = a12;
    a.data[ 2 ][ 0 ] = a20;
    a.data[ 2 ][ 1 ] = a21;
    a.data[ 2 ][ 2 ] = a22;
}


/// set rotation matrix
void AffineTransform3::setRotation( double x, double y, double z ) {
    double sx = sin( x );
    double cx = cos( x );
    double sy = sin( y );
    double cy = cos( y );
    double sz = sin( z );
    double cz = cos( z );
    a.data[ 0 ][ 0 ] = cy * cz;
    a.data[ 0 ][ 1 ] = -cx * sz + sx * sy * cz;
    a.data[ 0 ][ 2 ] = sx * sz + cx * sy * cz;
    a.data[ 1 ][ 0 ] = cy * sz;
    a.data[ 1 ][ 1 ] = cx * cz + sx * sy * sz;
    a.data[ 1 ][ 2 ] = -sx * cz + cx * sy * sz;
    a.data[ 2 ][ 0 ] = -sy;
    a.data[ 2 ][ 1 ] = sx * cy;
    a.data[ 2 ][ 2 ] = cx * cy;
}


/// convert the transformation to a vector of parameter values
VectorD AffineTransform3::toVector() const {
    VectorD params( 12 );
    params[ 0 ] = b.x;
    params[ 1 ] = b.y;
    params[ 2 ] = b.z;
    params[ 3 ] = a.data[ 0 ][ 0 ];
    params[ 4 ] = a.data[ 1 ][ 0 ];
    params[ 5 ] = a.data[ 2 ][ 0 ];
    params[ 6 ] = a.data[ 0 ][ 1 ];
    params[ 7 ] = a.data[ 1 ][ 1 ];
    params[ 8 ] = a.data[ 2 ][ 1 ];
    params[ 9 ] = a.data[ 0 ][ 2 ];
    params[ 10 ] = a.data[ 1 ][ 2 ];
    params[ 11 ] = a.data[ 2 ][ 2 ];
    return params;
}


/// compute the inverse transformation
AffineTransform3 AffineTransform3::inverse() const {
    AffineTransform3 inv;


    return inv;
}


} // end namespace sbl

