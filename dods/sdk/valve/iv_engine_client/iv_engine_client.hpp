#pragma once

struct player_info_t {
	char name[ 32 ];
	int user_id;
	char guid[ 33 ];
	unsigned long friends_id;
	char friends_name[ 32 ];
	bool fake_player;
	bool is_hltv;
	unsigned long custom_files[ 4 ];
	unsigned char files_downloaded;
};

class iv_engine_client {
public:
	vfunc( get_screen_size( int& width, int& height ), 5, void( __thiscall* )( void*, int&, int& ), width, height );
	vfunc( get_player_info( int ent_num, player_info_t* info ), 8, bool( __thiscall* )( void*, int, void* ), ent_num, info );
	vfunc( get_player_for_user_id( int user_id ), 9, int( __thiscall* )( void*, int ), user_id );
	vfunc( console_is_visible( ), 11, bool( __thiscall* )( void* ) );
	vfunc( get_local_player( ), 12, int( __thiscall* )( void* ) );
	vfunc( get_last_time_stamp( ), 15, float( __thiscall* )( void* ) );
	vfunc( get_view_angles( vector& angles ), 19, void( __thiscall* )( void*, vector& ), angles );
	vfunc( set_view_angles( vector& angles ), 20, void( __thiscall* )( void*, vector& ), angles );
	vfunc( get_max_clients( ), 21, int( __thiscall* )( void* ) );
	vfunc( is_in_game( ), 26, bool( __thiscall* )( void* ) );
	vfunc( is_connected( ), 27, bool( __thiscall* )( void* ) );
	vfunc( is_drawing_loading_message( ), 28, bool( __thiscall* )( void* ) );
	vfunc( is_box_visible( const vector& mins, const vector& maxs ), 31, int( __thiscall* )( void*, const vector&, const vector& ), mins, maxs );
	vfunc( get_game_directory( ), 35, const char* ( __thiscall* )( void* ) );
	vfunc( world_to_screen_matrix( ), 36, const matrix3x4_t& ( __thiscall* )( void* ) );
	vfunc( get_level_name( ), 51, const char* ( __thiscall* )( void* ) );
	vfunc( is_level_main_menu_background( ), 87, bool( __thiscall* )( void* ) );
	vfunc( get_screen_aspect_ratio( ), 95, float( __thiscall* )( void* ) );
	vfunc( get_engine_build_number( ), 98, unsigned int( __thiscall* )( void* ) );
	vfunc( get_app_id( ), 104, int( __thiscall* )( void* ) );
	vfunc( client_cmd_urestricted( const char* cmd_string ), 106, void( __thiscall* )( void*, const char* ), cmd_string );
	vfunc( is_loading_demo( ), 130, bool( __thiscall* )( void* ) );
	vfunc( is_playing_demo( ), 131, bool( __thiscall* )( void* ) );
	vfunc( flash_window( ), 136, void( __thiscall* )( void* ) );
	vfunc( is_active_app( ), 138, bool( __thiscall* )( void* ) );
};