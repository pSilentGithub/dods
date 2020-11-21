#pragma once

enum font_flags_t {
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

class vertex_t {
public:
	vector_2d m_pos;
	vector_2d m_coord;

public:
	__forceinline vertex_t( ) { }

	__forceinline vertex_t( float x, float y ) : m_pos{ x, y }, m_coord{ 0.f, 0.f } {}
	__forceinline vertex_t( const vector_2d& pos ) : m_pos{ pos }, m_coord{ 0.f, 0.f } {}
	__forceinline vertex_t( const vector_2d& pos, const vector_2d& coord ) : m_pos{ pos }, m_coord{ coord } {}

	__forceinline void init( const vector_2d& pos, const vector_2d& coord = { 0, 0 } ) {
		m_pos = pos;
		m_coord = coord;
	}
};

class i_surface {
public:
	vfunc( draw_set_color( int r, int g, int b, int a = 255 ), 11, void( __thiscall* )( void*, int, int, int, int ), r, g, b, a );
	vfunc( draw_filled_rect( int x, int y, int w, int h ), 12, void( __thiscall* )( void*, int, int, int, int ), x, y, w, h );
	vfunc( draw_outlined_rect( int x, int y, int w, int h ), 14, void( __thiscall* )( void*, int, int, int, int ), x, y, w, h );
	vfunc( draw_line( int x, int y, int x2, int y2 ), 15, void( __thiscall* )( void*, int, int, int, int ), x, y, x2, y2 );
	vfunc( draw_set_text_font( unsigned long font ), 17, void( __thiscall* )( void*, unsigned long ), font );
	vfunc( draw_set_text_color( color col ), 18, void( __thiscall* )( void*, color ), col );
	vfunc( draw_set_text_pos( int x, int y ), 20, void( __thiscall* )( void*, int, int ), x, y );
	vfunc( draw_print_text( const wchar_t* text, int text_length ), 22, void( __thiscall* )( void*, const wchar_t*, int, int ), text, text_length, 0 );
	vfunc( draw_set_texture_rgb( int id, color* rgba, int w, int h ), 31, void( __thiscall* )( void*, int, color*, int, int ), id, rgba, w, h );
	vfunc( draw_set_texture( int id ), 32, void( __thiscall* )( void*, int ), id );
	vfunc( create_new_texture_id( bool procedural = false ), 37, int( __thiscall* )( void*, bool ), procedural );
	vfunc( unlock_cursor( ), 61, void( __thiscall* )( void* ) );
	vfunc( lock_cursor( ), 62, void( __thiscall* )( void* ) );
	vfunc( create_font( ), 66, unsigned long( __thiscall* )( void* ) );
	vfunc( set_font_glyph_set( unsigned long font, const char* name, int size, int weight, int blur, int scan_lines, int flags, int min_range, int max_range ), 67, bool( __thiscall* )( void*, DWORD, const char*, int, int, int, int, int, int, int ), font, name, size, weight, blur, scan_lines, flags, min_range, max_range );
	vfunc( get_font_tall( ), 69, int( __thiscall* )( void* ) );
	vfunc( get_text_size( unsigned long font, const wchar_t* text, int& wide, int& tall ), 75, void( __thiscall* )( void*, unsigned long, const wchar_t*, int&, int& ), font, text, wide, tall );
	vfunc( play_sound( const char* file_name ), 78, void( __thiscall* )( void*, const char* ), file_name );
	vfunc( draw_outlined_circle( int x, int y, int radius, int segments ), 99, void( __thiscall* )( void*, int, int, int, int ), x, y, radius, segments );
	vfunc( draw_textured_polyline( int count, vertex_t* verts ), 100, void( __thiscall* )( void*, vertex_t*, int ), verts, count );
	vfunc( draw_textured_polygon( int count, vertex_t* verts, bool unk = false ), 102, void( __thiscall* )( void*, int, vertex_t*, bool ), count, verts, unk );
	vfunc( draw_filled_rect_fade( int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool horizontal ), 118, void( __thiscall* )( void*, int, int, int, int, unsigned int, unsigned int, bool ), x0, y0, x1, y1, alpha0, alpha1, horizontal );
	vfunc( draw_color_circle( int x, int y, float radius, int r, int g, int b, int a = 255 ), 161, void( __thiscall* )( void*, int, int, int, int, int, int, int ), x, y, radius, r, g, b, a );
	vfunc( draw_color_text( unsigned long font, int x, int y, int r, int g, int b, int a, const char* fmt, ... ), 162, void( __thiscall* )( void*, unsigned long, int, int, int, int, int, int, char const* ), font, x, y, r, g, b, a, fmt );
};