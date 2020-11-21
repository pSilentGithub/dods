#pragma once

class i_input_system {
public:
	vfunc( enable_input( bool enabled ), 7, void* ( __thiscall* )( void*, bool ), enabled );
	vfunc( reset_input_state( ), 25, void* ( __thiscall* )( void* ) );
};