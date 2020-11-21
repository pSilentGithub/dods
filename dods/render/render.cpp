#include "../sdk/includes.hpp"

DWORD render::fonts::main;

void render::setup( ) {
	fonts::main = i::surface->create_font( );
	i::surface->set_font_glyph_set( fonts::main, "Tahoma", 12, 700, 0, 0, FONTFLAG_DROPSHADOW, 0, 0 );
}

void render::filled_rect( const int x, const int y, const int w, const int h, color col ) {
	i::surface->draw_set_color( col.m_r, col.m_g, col.m_b, col.m_a );
	i::surface->draw_filled_rect( x, y, x + w, y + h );
}

void render::outlined_rect( const int x, const int y, const int w, const int h, color col ) {
	i::surface->draw_set_color( col.m_r, col.m_g, col.m_b, col.m_a );
	i::surface->draw_outlined_rect( x, y, x + w, y + h );
}

void render::line( const int x, const int y, const int w, const int h, color col ) {
	i::surface->draw_set_color( col.m_r, col.m_g, col.m_b, col.m_a );
	i::surface->draw_line( x, y, w, h );
}

RECT render::text_size( const DWORD& font, std::string text ) {
	RECT output;

	wchar_t buf[ 2056 ];

	if ( MultiByteToWideChar( CP_UTF8, 0, text.c_str( ), -1, buf, 128 ) > 0 ) {
		int width, height;
		i::surface->get_text_size( font, buf, width, height );
		output.right = width;
		output.bottom = height;
	}

	return output;
}

void render::text( const DWORD& font, std::string text, const int x, const int y, const bool centered, color col ) {
	int _x = x, _y = y;

	wchar_t buf[ 2056 ];

	if ( MultiByteToWideChar( CP_UTF8, 0, text.c_str( ), -1, buf, 128 ) > 0 ) {
		int width, height;
		i::surface->get_text_size( font, buf, width, height );

		if ( centered )
			_x -= width / 2;


		i::surface->draw_set_text_font( font );
		i::surface->draw_set_text_color( col );
		i::surface->draw_set_text_pos( _x, _y );
		i::surface->draw_print_text( buf, wcslen( buf ) );
	}
}