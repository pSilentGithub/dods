#include "../includes.hpp"

void util::console::open( const char* name ) {
	AllocConsole( );
	freopen_s( reinterpret_cast< FILE** >( stdin ), "CONIN$", "r", stdin );
	freopen_s( reinterpret_cast< FILE** >( stdout ), "CONOUT$", "w", stdout );

	SetConsoleTitleA( name );
}

void util::console::close( ) {
	fclose( reinterpret_cast< FILE* >( stdin ) );
	fclose( reinterpret_cast< FILE* >( stdout ) );
	FreeConsole( );
}

void util::console::print( const char* log ) {
	printf_s( "%s\n", log );
}

void* util::capture_interface( const char* mod, const char* iface ) {
	const auto mod_handle = GetModuleHandleA( mod );

	if ( !mod_handle ) {
		printf_s( "invalid module (%s->%s)\n", mod, iface );
		return nullptr;
	}

	const auto create_interface = reinterpret_cast< void* ( * )( const char*, int* ) >( GetProcAddress( mod_handle, "CreateInterface" ) );

	if ( !create_interface ) {
		printf_s( "failed to find CreateInterface (%s->%s)\n", mod, iface );
		return nullptr;
	}

	// todo: traverse through the interface list in the module
	// so we can dynamically grab the interface version

	return create_interface( iface, 0 );
}
