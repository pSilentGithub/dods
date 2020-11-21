#pragma once

// credits to the valve sdk

#define FastSqrt(x)			(sqrt)(x)
#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)

class vector {
public:
	float x, y, z;
	vector( void );
	vector( float X, float Y, float Z );
	vector CrossProduct( const vector& a, const vector& b );
	vector Cross( const vector& vOther );
	void Init( float ix = 0.0f, float iy = 0.0f, float iz = 0.0f );
	bool IsValid( ) const;
	float operator[]( int i ) const;
	float& operator[]( int i );
	inline void Zero( );
	bool operator==( const vector& v ) const;
	bool operator!=( const vector& v ) const;
	inline vector& operator+=( const vector& v );
	inline vector& operator-=( const vector& v );
	inline vector& operator*=( const vector& v );
	inline vector& operator*=( float s );
	inline vector& operator/=( const vector& v );
	inline vector& operator/=( float s );
	inline vector& operator+=( float fl );
	inline vector& operator-=( float fl );
	inline float	Length( ) const;
	inline float LengthSqr( void ) const {
		CHECK_VALID( *this );
		return ( x * x + y * y + z * z );
	}
	bool IsZero( float tolerance = 0.01f ) const {
		return ( x > -tolerance && x < tolerance&&
				 y > -tolerance && y < tolerance&&
				 z > -tolerance && z < tolerance );
	}
	auto Dot( float* other ) const -> float {
		return x * other[ 0 ] + y * other[ 1 ] + z * other[ 2 ];
	}
	vector	Normalize( );
	float	NormalizeInPlace( );
	inline float	DistTo( const vector& vOther ) const;
	inline float	DistToSqr( const vector& vOther ) const;
	float	Dot( const vector& vOther ) const;
	float	Length2D( void ) const;
	float	Length2DSqr( void ) const;
	vector& operator=( const vector& vOther );
	vector	operator-( void ) const;
	vector	operator+( const vector& v ) const;
	vector	operator-( const vector& v ) const;
	vector	operator*( const vector& v ) const;
	vector	operator/( const vector& v ) const;
	vector	operator*( float fl ) const;
	vector	operator/( float fl ) const;
	// Base address...
	float* Base( );
	float const* Base( ) const;
};

//===============================================
inline void vector::Init( float ix, float iy, float iz ) {
	x = ix; y = iy; z = iz;
	CHECK_VALID( *this );
}
//===============================================
inline vector::vector( float X, float Y, float Z ) {
	x = X; y = Y; z = Z;
	CHECK_VALID( *this );
}

inline vector vector::CrossProduct( const vector& a, const vector& b ) {
	return vector( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x );
}
//===============================================
inline vector vector::Cross( const vector& vOther ) {
	return CrossProduct( *this, vOther );
}

//===============================================
inline vector::vector( void ) { }
//===============================================
inline void vector::Zero( ) {
	x = y = z = 0.0f;
}
//===============================================
inline void vectorClear( vector& a ) {
	a.x = a.y = a.z = 0.0f;
}
//===============================================
inline vector& vector::operator=( const vector& vOther ) {
	CHECK_VALID( vOther );
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}
//===============================================
inline float& vector::operator[]( int i ) {
	Assert( ( i >= 0 ) && ( i < 3 ) );
	return ( ( float* )this )[ i ];
}
//===============================================
inline float vector::operator[]( int i ) const {
	Assert( ( i >= 0 ) && ( i < 3 ) );
	return ( ( float* )this )[ i ];
}
//===============================================
inline bool vector::operator==( const vector& src ) const {
	CHECK_VALID( src );
	CHECK_VALID( *this );
	return ( src.x == x ) && ( src.y == y ) && ( src.z == z );
}
//===============================================
inline bool vector::operator!=( const vector& src ) const {
	CHECK_VALID( src );
	CHECK_VALID( *this );
	return ( src.x != x ) || ( src.y != y ) || ( src.z != z );
}
//===============================================
inline void vectorCopy( const vector& src, vector& dst ) {
	CHECK_VALID( src );
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
//===============================================
inline  vector& vector::operator+=( const vector& v ) {
	CHECK_VALID( *this );
	CHECK_VALID( v );
	x += v.x; y += v.y; z += v.z;
	return *this;
}
//===============================================
inline  vector& vector::operator-=( const vector& v ) {
	CHECK_VALID( *this );
	CHECK_VALID( v );
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
//===============================================
inline  vector& vector::operator*=( float fl ) {
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID( *this );
	return *this;
}
//===============================================
inline  vector& vector::operator*=( const vector& v ) {
	CHECK_VALID( v );
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID( *this );
	return *this;
}
//===============================================
inline vector& vector::operator+=( float fl ) {
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID( *this );
	return *this;
}
//===============================================
inline vector& vector::operator-=( float fl ) {
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID( *this );
	return *this;
}
//===============================================
inline  vector& vector::operator/=( float fl ) {
	Assert( fl != 0.0f );
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID( *this );
	return *this;
}
//===============================================
inline  vector& vector::operator/=( const vector& v ) {
	CHECK_VALID( v );
	Assert( v.x != 0.0f && v.y != 0.0f && v.z != 0.0f );
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID( *this );
	return *this;
}
//===============================================
inline float vector::Length( void ) const {
	CHECK_VALID( *this );

	float root = 0.0f;

	float sqsr = x * x + y * y + z * z;

	root = sqrt( sqsr );

	return root;
}
//===============================================
inline float vector::Length2D( void ) const {
	CHECK_VALID( *this );

	float root = 0.0f;

	float sqst = x * x + y * y;

	root = sqrt( sqst );

	return root;
}
//===============================================
inline float vector::Length2DSqr( void ) const {
	return ( x * x + y * y );
}
//===============================================
inline vector CrossProduct( const vector& a, const vector& b ) {
	return vector( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x );
}
//===============================================
float vector::DistTo( const vector& vOther ) const {
	vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length( );
}
float vector::DistToSqr( const vector& vOther ) const {
	vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr( );
}
//===============================================
inline vector vector::Normalize( ) {
	vector vector;
	float length = this->Length( );

	if ( length != 0 ) {
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	} else {
		vector.x = vector.y = 0.0f; vector.z = 1.0f;
	}

	return vector;
}
//===============================================
inline float vector::NormalizeInPlace( ) {
	vector& v = *this;

	float iradius = 1.f / ( this->Length( ) + 1.192092896e-07F ); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;

	return iradius;
}
//===============================================
inline float vectorNormalize( vector& v ) {
	Assert( v.IsValid( ) );
	float l = v.Length( );
	if ( l != 0.0f ) {
		v /= l;
	} else {
		// FIXME:
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}
//===============================================
inline float vectorNormalize( float* v ) {
	return vectorNormalize( *( reinterpret_cast< vector* >( v ) ) );
}
//===============================================
inline vector vector::operator+( const vector& v ) const {
	vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline vector vector::operator-( const vector& v ) const {
	vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
//===============================================
inline vector vector::operator*( float fl ) const {
	vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
//===============================================
inline vector vector::operator*( const vector& v ) const {
	vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
//===============================================
inline vector vector::operator/( float fl ) const {
	vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
//===============================================
inline vector vector::operator/( const vector& v ) const {
	vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}
inline float vector::Dot( const vector& vOther ) const {
	const vector& a = *this;

	return( a.x * vOther.x + a.y * vOther.y + a.z * vOther.z );
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline float vectorLength( const vector& v ) {
	CHECK_VALID( v );
	return ( float )FastSqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

//VECTOR SUBTRAC
inline void vectorSubtract( const vector& a, const vector& b, vector& c ) {
	CHECK_VALID( a );
	CHECK_VALID( b );
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//VECTORADD
inline void vectorAdd( const vector& a, const vector& b, vector& c ) {
	CHECK_VALID( a );
	CHECK_VALID( b );
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* vector::Base( ) {
	return ( float* )this;
}

inline float const* vector::Base( ) const {
	return ( float const* )this;
}

inline void vectorMAInline( const float* start, float scale, const float* direction, float* dest ) {
	dest[ 0 ] = start[ 0 ] + direction[ 0 ] * scale;
	dest[ 1 ] = start[ 1 ] + direction[ 1 ] * scale;
	dest[ 2 ] = start[ 2 ] + direction[ 2 ] * scale;
}

inline void vectorMAInline( const vector& start, float scale, const vector& direction, vector& dest ) {
	dest.x = start.x + direction.x * scale;
	dest.y = start.y + direction.y * scale;
	dest.z = start.z + direction.z * scale;
}

inline void vectorMA( const vector& start, float scale, const vector& direction, vector& dest ) {
	vectorMAInline( start, scale, direction, dest );
}

inline void vectorMA( const float* start, float scale, const float* direction, float* dest ) {
	vectorMAInline( start, scale, direction, dest );
}


class __declspec( align( 16 ) )vectorAligned : public vector {
public:
	inline vectorAligned( void ) { };

	inline vectorAligned( float X, float Y, float Z ) {
		Init( X, Y, Z );
	}

	explicit vectorAligned( const vector& vOther ) {
		Init( vOther.x, vOther.y, vOther.z );
	}

	vectorAligned& operator=( const vector& vOther ) {
		Init( vOther.x, vOther.y, vOther.z );
		return *this;
	}

	float w;
};


inline unsigned long& FloatBits( float& f ) {
	return *reinterpret_cast< unsigned long* >( &f );
}

inline bool IsFinite( float f ) {
	return ( ( FloatBits( f ) & 0x7F800000 ) != 0x7F800000 );
}

//=========================================================
// 2D vector_2d
//=========================================================

class vector_2d {
public:
	// Members
	float x, y;

	// Construction/destruction
	vector_2d( void );
	vector_2d( float X, float Y );
	vector_2d( const float* pFloat );

	// Initialization
	void Init( float ix = 0.0f, float iy = 0.0f );

	// Got any nasty NAN's?
	bool IsValid( ) const;

	// array access...
	float operator[]( int i ) const;
	float& operator[]( int i );

	// Base address...
	float* Base( );
	float const* Base( ) const;

	// Initialization methods
	void Random( float minVal, float maxVal );

	// equality
	bool operator==( const vector_2d& v ) const;
	bool operator!=( const vector_2d& v ) const;

	// arithmetic operations
	vector_2d& operator+=( const vector_2d& v );
	vector_2d& operator-=( const vector_2d& v );
	vector_2d& operator*=( const vector_2d& v );
	vector_2d& operator*=( float s );
	vector_2d& operator/=( const vector_2d& v );
	vector_2d& operator/=( float s );

	// negate the vector_2d components
	void	Negate( );

	// Get the vector_2d's magnitude.
	float	Length( ) const;

	// Get the vector_2d's magnitude squared.
	float	LengthSqr( void ) const;

	// return true if this vector is (0,0) within tolerance
	bool IsZero( float tolerance = 0.01f ) const {
		return ( x > -tolerance && x < tolerance&&
				 y > -tolerance && y < tolerance );
	}

	float	Normalize( );

	// Normalize in place and return the old length.
	float	NormalizeInPlace( );

	// Compare length.
	bool	IsLengthGreaterThan( float val ) const;
	bool	IsLengthLessThan( float val ) const;

	// Get the distance from this vector_2d to the other one.
	float	DistTo( const vector_2d& vOther ) const;

	// Get the distance from this vector_2d to the other one squared.
	float	DistToSqr( const vector_2d& vOther ) const;

	// Copy
	void	CopyToArray( float* rgfl ) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector_2d equation (because it's done per-component
	// rather than per-vector_2d).
	void	MulAdd( const vector_2d& a, const vector_2d& b, float scalar );

	// Dot product.
	float	Dot( const vector_2d& vOther ) const;

	// assignment
	vector_2d& operator=( const vector_2d& vOther );

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors
	vector_2d( const vector_2d& vOther );

	// arithmetic operations
	vector_2d	operator-( void ) const;

	vector_2d	operator+( const vector_2d& v ) const;
	vector_2d	operator-( const vector_2d& v ) const;
	vector_2d	operator*( const vector_2d& v ) const;
	vector_2d	operator/( const vector_2d& v ) const;
	vector_2d	operator*( float fl ) const;
	vector_2d	operator/( float fl ) const;

	// Cross product between two vectors.
	vector_2d	Cross( const vector_2d& vOther ) const;

	// Returns a vector_2d with the min or max in X, Y, and Z.
	vector_2d	Min( const vector_2d& vOther ) const;
	vector_2d	Max( const vector_2d& vOther ) const;

#else

private:
	// No copy constructors allowed if we're in optimal mode
	vector_2d( const vector_2d& vOther );
#endif
};

//-----------------------------------------------------------------------------

const vector_2d vec2_origin( 0, 0 );

//-----------------------------------------------------------------------------
// vector_2d related operations
//-----------------------------------------------------------------------------

// vector_2d clear
void vector_2dClear( vector_2d& a );

// Copy
void vector_2dCopy( const vector_2d& src, vector_2d& dst );

// vector_2d arithmetic
void vector_2dAdd( const vector_2d& a, const vector_2d& b, vector_2d& result );
void vector_2dSubtract( const vector_2d& a, const vector_2d& b, vector_2d& result );
void vector_2dMultiply( const vector_2d& a, float b, vector_2d& result );
void vector_2dMultiply( const vector_2d& a, const vector_2d& b, vector_2d& result );
void vector_2dDivide( const vector_2d& a, float b, vector_2d& result );
void vector_2dDivide( const vector_2d& a, const vector_2d& b, vector_2d& result );
void vector_2dMA( const vector_2d& start, float s, const vector_2d& dir, vector_2d& result );

// Store the min or max of each of x, y, and z into the result.
void vector_2dMin( const vector_2d& a, const vector_2d& b, vector_2d& result );
void vector_2dMax( const vector_2d& a, const vector_2d& b, vector_2d& result );

#define vector_2dExpand( v ) (v).x, (v).y

// Normalization
float vector_2dNormalize( vector_2d& v );

// Length
float vector_2dLength( const vector_2d& v );

// Dot Product
float DotProduct2D( const vector_2d& a, const vector_2d& b );

// Linearly interpolate between two vectors
void vector_2dLerp( const vector_2d& src1, const vector_2d& src2, float t, vector_2d& dest );


//-----------------------------------------------------------------------------
//
// Inlined vector_2d methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------

inline vector_2d::vector_2d( void ) {
#ifdef _DEBUG
	// Initialize to NAN to catch errors
	//x = y = float_NAN;
#endif
		}

inline vector_2d::vector_2d( float X, float Y ) {
	x = X; y = Y;
	Assert( IsValid( ) );
}

inline vector_2d::vector_2d( const float* pFloat ) {
	Assert( pFloat );
	x = pFloat[ 0 ]; y = pFloat[ 1 ];
	Assert( IsValid( ) );
}


//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline vector_2d::vector_2d( const vector_2d& vOther ) {
	Assert( vOther.IsValid( ) );
	x = vOther.x; y = vOther.y;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

inline void vector_2d::Init( float ix, float iy ) {
	x = ix; y = iy;
	Assert( IsValid( ) );
}

inline void vector_2d::Random( float minVal, float maxVal ) {
	x = minVal + ( ( float )rand( ) / 0x7fff ) * ( maxVal - minVal );
	y = minVal + ( ( float )rand( ) / 0x7fff ) * ( maxVal - minVal );
}

inline void vector_2dClear( vector_2d& a ) {
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline vector_2d& vector_2d::operator=( const vector_2d& vOther ) {
	Assert( vOther.IsValid( ) );
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline float& vector_2d::operator[]( int i ) {
	Assert( ( i >= 0 ) && ( i < 2 ) );
	return ( ( float* )this )[ i ];
}

inline float vector_2d::operator[]( int i ) const {
	Assert( ( i >= 0 ) && ( i < 2 ) );
	return ( ( float* )this )[ i ];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline float* vector_2d::Base( ) {
	return ( float* )this;
}

inline float const* vector_2d::Base( ) const {
	return ( float const* )this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

inline bool vector_2d::IsValid( ) const {
	return IsFinite( x ) && IsFinite( y );
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool vector_2d::operator==( const vector_2d& src ) const {
	Assert( src.IsValid( ) && IsValid( ) );
	return ( src.x == x ) && ( src.y == y );
}

inline bool vector_2d::operator!=( const vector_2d& src ) const {
	Assert( src.IsValid( ) && IsValid( ) );
	return ( src.x != x ) || ( src.y != y );
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void vector_2dCopy( const vector_2d& src, vector_2d& dst ) {
	Assert( src.IsValid( ) );
	dst.x = src.x;
	dst.y = src.y;
}

inline void	vector_2d::CopyToArray( float* rgfl ) const {
	Assert( IsValid( ) );
	Assert( rgfl );
	rgfl[ 0 ] = x; rgfl[ 1 ] = y;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

inline void vector_2d::Negate( ) {
	Assert( IsValid( ) );
	x = -x; y = -y;
}

inline vector_2d& vector_2d::operator+=( const vector_2d& v ) {
	Assert( IsValid( ) && v.IsValid( ) );
	x += v.x; y += v.y;
	return *this;
}

inline vector_2d& vector_2d::operator-=( const vector_2d& v ) {
	Assert( IsValid( ) && v.IsValid( ) );
	x -= v.x; y -= v.y;
	return *this;
}

inline vector_2d& vector_2d::operator*=( float fl ) {
	x *= fl;
	y *= fl;
	Assert( IsValid( ) );
	return *this;
}

inline vector_2d& vector_2d::operator*=( const vector_2d& v ) {
	x *= v.x;
	y *= v.y;
	Assert( IsValid( ) );
	return *this;
}

inline vector_2d& vector_2d::operator/=( float fl ) {
	Assert( fl != 0.0f );
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	Assert( IsValid( ) );
	return *this;
}

inline vector_2d& vector_2d::operator/=( const vector_2d& v ) {
	Assert( v.x != 0.0f && v.y != 0.0f );
	x /= v.x;
	y /= v.y;
	Assert( IsValid( ) );
	return *this;
}

inline void vector_2dAdd( const vector_2d& a, const vector_2d& b, vector_2d& c ) {
	Assert( a.IsValid( ) && b.IsValid( ) );
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

inline void vector_2dSubtract( const vector_2d& a, const vector_2d& b, vector_2d& c ) {
	Assert( a.IsValid( ) && b.IsValid( ) );
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

inline void vector_2dMultiply( const vector_2d& a, float b, vector_2d& c ) {
	Assert( a.IsValid( ) && IsFinite( b ) );
	c.x = a.x * b;
	c.y = a.y * b;
}

inline void vector_2dMultiply( const vector_2d& a, const vector_2d& b, vector_2d& c ) {
	Assert( a.IsValid( ) && b.IsValid( ) );
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


inline void vector_2dDivide( const vector_2d& a, float b, vector_2d& c ) {
	Assert( a.IsValid( ) );
	Assert( b != 0.0f );
	float oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

inline void vector_2dDivide( const vector_2d& a, const vector_2d& b, vector_2d& c ) {
	Assert( a.IsValid( ) );
	Assert( ( b.x != 0.0f ) && ( b.y != 0.0f ) );
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

inline void vector_2dMA( const vector_2d& start, float s, const vector_2d& dir, vector_2d& result ) {
	Assert( start.IsValid( ) && IsFinite( s ) && dir.IsValid( ) );
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
inline void	vector_2d::MulAdd( const vector_2d& a, const vector_2d& b, float scalar ) {
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

inline void vector_2dLerp( const vector_2d& src1, const vector_2d& src2, float t, vector_2d& dest ) {
	dest[ 0 ] = src1[ 0 ] + ( src2[ 0 ] - src1[ 0 ] ) * t;
	dest[ 1 ] = src1[ 1 ] + ( src2[ 1 ] - src1[ 1 ] ) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
inline float DotProduct2D( const vector_2d& a, const vector_2d& b ) {
	Assert( a.IsValid( ) && b.IsValid( ) );
	return( a.x * b.x + a.y * b.y );
}

// for backwards compatability
inline float vector_2d::Dot( const vector_2d& vOther ) const {
	return DotProduct2D( *this, vOther );
}


//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float vector_2dLength( const vector_2d& v ) {
	Assert( v.IsValid( ) );
	return ( float )FastSqrt( v.x * v.x + v.y * v.y );
}

inline float vector_2d::LengthSqr( void ) const {
	Assert( IsValid( ) );
	return ( x * x + y * y );
}

inline float vector_2d::NormalizeInPlace( ) {
	return vector_2dNormalize( *this );
}

inline bool vector_2d::IsLengthGreaterThan( float val ) const {
	return LengthSqr( ) > val * val;
}

inline bool vector_2d::IsLengthLessThan( float val ) const {
	return LengthSqr( ) < val * val;
}

inline float vector_2d::Length( void ) const {
	return vector_2dLength( *this );
}


inline void vector_2dMin( const vector_2d& a, const vector_2d& b, vector_2d& result ) {
	result.x = ( a.x < b.x ) ? a.x : b.x;
	result.y = ( a.y < b.y ) ? a.y : b.y;
}


inline void vector_2dMax( const vector_2d& a, const vector_2d& b, vector_2d& result ) {
	result.x = ( a.x > b.x ) ? a.x : b.x;
	result.y = ( a.y > b.y ) ? a.y : b.y;
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------
inline float vector_2dNormalize( vector_2d& v ) {
	Assert( v.IsValid( ) );
	float l = v.Length( );
	if ( l != 0.0f ) {
		v /= l;
	} else {
		v.x = v.y = 0.0f;
	}
	return l;
}


//-----------------------------------------------------------------------------
// Get the distance from this vector_2d to the other one
//-----------------------------------------------------------------------------
inline float vector_2d::DistTo( const vector_2d& vOther ) const {
	vector_2d delta;
	vector_2dSubtract( *this, vOther, delta );
	return delta.Length( );
}

inline float vector_2d::DistToSqr( const vector_2d& vOther ) const {
	vector_2d delta;
	vector_2dSubtract( *this, vOther, delta );
	return delta.LengthSqr( );
}


//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
inline void ComputeClosestPoint2D( const vector_2d& vecStart, float flMaxDist, const vector_2d& vecTarget, vector_2d* pResult ) {
	vector_2d vecDelta;
	vector_2dSubtract( vecTarget, vecStart, vecDelta );
	float flDistSqr = vecDelta.LengthSqr( );
	if ( flDistSqr <= flMaxDist * flMaxDist ) {
		*pResult = vecTarget;
	} else {
		vecDelta /= FastSqrt( flDistSqr );
		vector_2dMA( vecStart, flMaxDist, vecDelta, *pResult );
	}
}



//-----------------------------------------------------------------------------
//
// Slow methods
//
//-----------------------------------------------------------------------------

#ifndef VECTOR_NO_SLOW_OPERATIONS
#endif
//-----------------------------------------------------------------------------
// Returns a vector_2d with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

inline vector_2d vector_2d::Min( const vector_2d& vOther ) const {
	return vector_2d( x < vOther.x ? x : vOther.x,
					  y < vOther.y ? y : vOther.y );
}

inline vector_2d vector_2d::Max( const vector_2d& vOther ) const {
	return vector_2d( x > vOther.x ? x : vOther.x,
					  y > vOther.y ? y : vOther.y );
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

inline vector_2d vector_2d::operator-( void ) const {
	return vector_2d( -x, -y );
}

inline vector_2d vector_2d::operator+( const vector_2d& v ) const {
	vector_2d res;
	vector_2dAdd( *this, v, res );
	return res;
}

inline vector_2d vector_2d::operator-( const vector_2d& v ) const {
	vector_2d res;
	vector_2dSubtract( *this, v, res );
	return res;
}

inline vector_2d vector_2d::operator*( float fl ) const {
	vector_2d res;
	vector_2dMultiply( *this, fl, res );
	return res;
}

inline vector_2d vector_2d::operator*( const vector_2d& v ) const {
	vector_2d res;
	vector_2dMultiply( *this, v, res );
	return res;
}

inline vector_2d vector_2d::operator/( float fl ) const {
	vector_2d res;
	vector_2dDivide( *this, fl, res );
	return res;
}

inline vector_2d vector_2d::operator/( const vector_2d& v ) const {
	vector_2d res;
	vector_2dDivide( *this, v, res );
	return res;
}

inline vector_2d operator*( float fl, const vector_2d& v ) {
	return v * fl;
}