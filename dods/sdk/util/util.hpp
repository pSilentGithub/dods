#pragma once

namespace util {
	namespace console {
		void open( const char* name = "" );
		void close( );
		void print( const char* log );
	}

	void* capture_interface( const char* mod, const char* iface );

	template < typename T > static T get_virtual_function( void* base, const std::uint16_t index ) {
		return ( *reinterpret_cast< T** >( base ) )[ index ];
	}
}

#define iface( pointer, iface_class, mod, iface ) \
	pointer = reinterpret_cast< iface_class* >( util::capture_interface( mod, iface ) );

#define vfunc( function_name, index, type, ... ) \
	auto function_name { \
		return util::get_virtual_function< type >( this, index )( this, __VA_ARGS__ ); \
	};