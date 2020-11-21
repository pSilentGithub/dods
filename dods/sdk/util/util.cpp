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

std::uint8_t* util::get_signature( const char* module_name, const char* signature ) {
	const auto module_handle = GetModuleHandleA( module_name );

	if ( !module_handle )
		return nullptr;

	static auto pattern_to_byte = [ ]( const char* pattern ) {
		auto bytes = std::vector< int >{ };
		auto start = const_cast< char* >( pattern );
		auto end = const_cast< char* >( pattern ) + std::strlen( pattern );

		for ( auto current = start; current < end; ++current ) {
			if ( *current == '?' ) {
				++current;

				if ( *current == '?' )
					++current;

				bytes.push_back( -1 );
			} else {
				bytes.push_back( std::strtoul( current, &current, 16 ) );
			}
		}
		return bytes;
	};

	auto dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( module_handle );
	auto nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< std::uint8_t* >( module_handle ) + dos_header->e_lfanew );

	auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	auto pattern_bytes = pattern_to_byte( signature );
	auto scan_bytes = reinterpret_cast< std::uint8_t* >( module_handle );

	auto s = pattern_bytes.size( );
	auto d = pattern_bytes.data( );

	for ( auto i = 0ul; i < size_of_image - s; ++i ) {
		bool found = true;

		for ( auto j = 0ul; j < s; ++j ) {
			if ( scan_bytes[ i + j ] != d[ j ] && d[ j ] != -1 ) {
				found = false;
				break;
			}
		}

		if ( found )
			return &scan_bytes[ i ];
	}

	return nullptr;
}