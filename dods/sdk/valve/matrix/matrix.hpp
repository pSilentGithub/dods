#pragma once

struct matrix3x4_t {
	matrix3x4_t( ) { }
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23 ) {
		matrix_value[ 0 ][ 0 ] = m00;	matrix_value[ 0 ][ 1 ] = m01; matrix_value[ 0 ][ 2 ] = m02; matrix_value[ 0 ][ 3 ] = m03;
		matrix_value[ 1 ][ 0 ] = m10;	matrix_value[ 1 ][ 1 ] = m11; matrix_value[ 1 ][ 2 ] = m12; matrix_value[ 1 ][ 3 ] = m13;
		matrix_value[ 2 ][ 0 ] = m20;	matrix_value[ 2 ][ 1 ] = m21; matrix_value[ 2 ][ 2 ] = m22; matrix_value[ 2 ][ 3 ] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void init( const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector& vecOrigin ) {
		matrix_value[ 0 ][ 0 ] = xAxis.x; matrix_value[ 0 ][ 1 ] = yAxis.x; matrix_value[ 0 ][ 2 ] = zAxis.x; matrix_value[ 0 ][ 3 ] = vecOrigin.x;
		matrix_value[ 1 ][ 0 ] = xAxis.y; matrix_value[ 1 ][ 1 ] = yAxis.y; matrix_value[ 1 ][ 2 ] = zAxis.y; matrix_value[ 1 ][ 3 ] = vecOrigin.y;
		matrix_value[ 2 ][ 0 ] = xAxis.z; matrix_value[ 2 ][ 1 ] = yAxis.z; matrix_value[ 2 ][ 2 ] = zAxis.z; matrix_value[ 2 ][ 3 ] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t( const vector& xAxis, const vector& yAxis, const vector& zAxis, const vector& vecOrigin ) {
		init( xAxis, yAxis, zAxis, vecOrigin );
	}

	inline void set_origin( vector const& p ) {
		matrix_value[ 0 ][ 3 ] = p.x;
		matrix_value[ 1 ][ 3 ] = p.y;
		matrix_value[ 2 ][ 3 ] = p.z;
	}

	inline vector get_origin( ) {
		return vector( matrix_value[ 0 ][ 3 ], matrix_value[ 1 ][ 3 ], matrix_value[ 2 ][ 3 ] );
	}

	inline void invalidate( void ) {
		for ( int i = 0; i < 3; i++ ) {
			for ( int j = 0; j < 4; j++ ) {
				matrix_value[ i ][ j ] = 0;
			}
		}
	}

	float* operator[]( int i ) { return matrix_value[ i ]; }
	const float* operator[]( int i ) const { return matrix_value[ i ]; }
	float* Base( ) { return &matrix_value[ 0 ][ 0 ]; }
	const float* Base( ) const { return &matrix_value[ 0 ][ 0 ]; }

	float matrix_value[ 3 ][ 4 ];
};