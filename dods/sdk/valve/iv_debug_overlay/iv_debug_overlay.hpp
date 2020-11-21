#pragma once

class i_debug_overlay {
public:
	vfunc( screen_position( const vector& point, vector& screen ), 10, int( __thiscall* )( void*, const vector&, vector& ), point, screen );

	bool world_to_screen( const vector& point, vector& screen ) {
		return this->screen_position( point, screen ) != 1;
	}
};