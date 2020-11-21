#include "../../sdk/includes.hpp"

vmt_hook::vmt_hook( ) {
}

vmt_hook::vmt_hook( void* p_interface ) {
	this->m_interface = reinterpret_cast< uintptr_t** >( p_interface );

	size_t method_count = 0;

	while ( reinterpret_cast< uintptr_t* >( *this->m_interface )[ method_count ] )
		method_count++;

	m_original = *this->m_interface;

	//vmt = new uintptr_t[(sizeof(uintptr_t) * method_count)+ sizeof(uintptr_t)];
	m_vmt = new uintptr_t[ method_count + 1 ];

	memcpy( m_vmt, &m_original[ -1 ], ( sizeof( uintptr_t ) * method_count ) + sizeof( uintptr_t ) );
}

void vmt_hook::hook( void* method, size_t methodIndex ) {
	m_vmt[ methodIndex + 1 ] = reinterpret_cast< uintptr_t >( method );
}

void vmt_hook::apply( ) {
	*this->m_interface = &m_vmt[ 1 ];
}

void vmt_hook::release( ) {
	*this->m_interface = m_original;
	delete[ ] m_vmt;
}