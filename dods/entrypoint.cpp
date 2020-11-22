/*
* entrypoint.cpp
* dods cheat
* (c) Luna Wilburn 2020
*/

#include "sdk/includes.hpp"

unsigned long __stdcall initialize( _In_ LPVOID reserved ) {
	util::console::open( );

	i::setup( );
	netvar_manager = std::make_unique<netvar_tree>( );
	offsets::setup( );
	render::setup( );
	menu::initialize( );
	h::setup( );


	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

	FreeLibraryAndExitThread( reinterpret_cast< HMODULE >( reserved ), 0 );

	return 0;
}

BOOL WINAPI DllMain( _In_ HINSTANCE instance, _In_ DWORD reason, _In_ LPVOID reserved ) {

	switch ( reason ) {
	case DLL_PROCESS_ATTACH: {
		if ( const auto thread_handle = CreateThread( 0, 0, initialize, instance, 0, 0 ) )
			CloseHandle( thread_handle );
		break;
	}
	case DLL_PROCESS_DETACH: {
		h::release( );
		util::console::close( );
		break;
	}
	}

	return TRUE;
}