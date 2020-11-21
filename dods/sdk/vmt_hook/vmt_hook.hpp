#pragma once

/*
* forgot the original credit for this class,
* sorry
*/

class vmt_hook {
private:
	uintptr_t* m_vmt;
public:
	uintptr_t** m_interface = nullptr;
	uintptr_t* m_original = nullptr;
	uint32_t m_method_count = 0;

	vmt_hook( );
	vmt_hook( void* p_interface );
	void hook( void* method, size_t methodIndex );
	void apply( );
	void release( );

	template<typename Fn>
	Fn get_original( size_t methodIndex ) {
		return reinterpret_cast< Fn >( m_original[ methodIndex ] );
	}
};