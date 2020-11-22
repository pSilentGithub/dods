#pragma once

struct item_t {
	const char* m_title;
	int m_key;
	bool* m_value;

	item_t( const char* title, int key, bool* value ) {
		this->m_title = title;
		this->m_key = key;
		this->m_value = value;
	}
};

namespace menu {
	void initialize( );
	void run( );
}