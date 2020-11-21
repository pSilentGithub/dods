#pragma once

namespace render {
	void setup( );
	void filled_rect( const int x, const int y, const int w, const int h, color col );
	void outlined_rect( const int x, const int y, const int w, const int h, color col );
	void line( const int x, const int y, const int w, const int h, color col );
	RECT text_size( const DWORD& font, std::string text );
	void text( const DWORD& font, std::string text, const int x, const int y, const bool centered, color col );

	namespace fonts {
		extern DWORD main;
	}
}