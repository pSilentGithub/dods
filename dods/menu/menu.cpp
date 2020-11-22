#include "../sdk/includes.hpp"

std::vector< item_t > items;
bool open = true;

void menu::initialize( ) {
	items.push_back( item_t( "ESP (F1)", VK_F1, &config::esp::enabled ) );
	items.push_back( item_t( "Name (F2)", VK_F2, &config::esp::name ) );
	items.push_back( item_t( "Box (F3)", VK_F3, &config::esp::box ) );
	items.push_back( item_t( "Health (F4)", VK_F4, &config::esp::health ) );
}

void menu::run( ) {
	if ( GetAsyncKeyState( VK_INSERT ) & 1 )
		open = !open;

	if ( !open )
		return;

	int y_offset = 0;

	render::filled_rect( 5, 5, 100, ( items.size( ) + 1 ) * 15, color( 0, 0, 0, 135 ) );
	render::text( render::fonts::main, "Insert to toggle", 7, 5, false, color( 255, 255, 255, 255 ) );

	for ( auto& item : items ) {
		if ( GetAsyncKeyState( item.m_key ) & 1 )
			*item.m_value = !*item.m_value;

		render::text( render::fonts::main, item.m_title, 7, 20 + y_offset, false, *item.m_value ? color( 0, 255, 0, 255 ) : color( 255, 0, 0, 255 ) );
		y_offset += 15;
	}
}