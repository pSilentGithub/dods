#include "../../sdk/includes.hpp"

c_esp* esp = new c_esp( );

void c_esp::draw( ) {
	if ( !config::esp::enabled )
		return;

	auto local_player = i::entity_list->get_client_entity( i::engine->get_local_player( ) );

	if ( !local_player )
		return;

	this->players( );
}

void c_esp::players( ) {
	auto local_player = i::entity_list->get_client_entity( i::engine->get_local_player( ) );

	for ( int i = 1; i < i::engine->get_max_clients( ); i++ ) {
		const auto entity = i::entity_list->get_client_entity( i );

		if ( !entity || !entity->is_alive( ) || entity->is_dormant( ) || entity->m_iTeamNum( ) == local_player->m_iTeamNum( ) )
			continue;

		s_bounding_box box;

		if ( !this->get_bounding_box( entity, box ) )
			continue;

		player_info_t info;

		if ( !i::engine->get_player_info( i, &info ) )
			continue;


		if ( config::esp::name )
			render::text( render::fonts::main, info.name, box.x + ( box.w / 2 ), box.y - 14, true, color( 255, 255, 255, 255 ) );

		if ( config::esp::box ) {
			render::outlined_rect( box.x - 1, box.y - 1, box.w + 2, box.h + 2, color( 0, 0, 0, 255 ) );
			render::outlined_rect( box.x, box.y, box.w, box.h, color( 255, 0, 0, 255 ) );
			render::outlined_rect( box.x + 1, box.y + 1, box.w - 2, box.h - 2, color( 0, 0, 0, 255 ) );
		}

		if ( config::esp::health ) {
			auto health = entity->m_iHealth( );

			int healthbar_height = ( health * ( box.h + 2 ) ) / 100;
			render::filled_rect( box.x - 5, box.y + 1, 2, box.h - 2, color( 0, 0, 0, 255 ) );
			render::filled_rect( box.x - 5, box.y + 1 + ( ( box.h + 2 ) - healthbar_height ), 2, healthbar_height - 4, color( 0, 255, 0, 255 ) );
			render::outlined_rect( box.x - 6, box.y + 1 - 1, 4, box.h + 2 - 2, color( 0, 0, 0, 255 ) );

			auto text_size = render::text_size( render::fonts::main, std::to_string( health ) + " HP" );

			render::text( render::fonts::main, std::to_string( health ) + " HP", box.x - 7 - text_size.right, box.y, false, color( 255, 255, 255, 255 ) );
		}

	}
}

/*
* (c) dude719
*/
bool c_esp::get_bounding_box( c_base_entity* player, s_bounding_box& bounding_box ) {
	s_bounding_box output{ };

	vector trans = player->get_abs_origin( );

	vector min;
	vector max;

	min = player->vec_mins( );
	max = player->vec_maxs( );

	vector point_list[ ] = {
		vector( min.x, min.y, min.z ),
		vector( min.x, max.y, min.z ),
		vector( max.x, max.y, min.z ),
		vector( max.x, min.y, min.z ),
		vector( max.x, max.y, max.z ),
		vector( min.x, max.y, max.z ),
		vector( min.x, min.y, max.z ),
		vector( max.x, min.y, max.z )
	};

	vector transformed[ 8 ];

	for ( int i = 0; i < 8; i++ ) {
		transformed[ i ].x = point_list[ i ].x + trans.x;
		transformed[ i ].y = point_list[ i ].y + trans.y;
		transformed[ i ].z = point_list[ i ].z + trans.z;
	}

	vector flb, brt{}, blb{}, frt{}, frb{}, brb{}, blt{}, flt{};

	if ( i::debug_overlay->screen_position( transformed[ 3 ], flb ) == 1 ||
		 i::debug_overlay->screen_position( transformed[ 0 ], blb ) == 1 ||
		 i::debug_overlay->screen_position( transformed[ 2 ], frb ) == 1 ||
		 i::debug_overlay->screen_position( transformed[ 6 ], blt ) == 1 ||
		 i::debug_overlay->screen_position( transformed[ 5 ], brt ) == 1 ||
		 i::debug_overlay->screen_position( transformed[ 4 ], frt ) == 1 ||
		 i::debug_overlay->screen_position( transformed[ 1 ], brb ) == 1 ||
		 i::debug_overlay->screen_position( transformed[ 7 ], flt ) == 1 )
		return false;

	vector arr[ ] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for ( int i = 0; i < 8; i++ ) {
		if ( left > arr[ i ].x )
			left = arr[ i ].x;
		if ( top < arr[ i ].y )
			top = arr[ i ].y;
		if ( right < arr[ i ].x )
			right = arr[ i ].x;
		if ( bottom > arr[ i ].y )
			bottom = arr[ i ].y;
	}

	bounding_box.x = left;
	bounding_box.y = bottom;
	bounding_box.w = right - left;
	bounding_box.h = top - bottom;
	return true;
}
