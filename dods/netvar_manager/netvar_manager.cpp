#include "../sdk/includes.hpp"
#include <fstream>

std::unique_ptr<netvar_tree> netvar_manager;

std::ofstream myfile;

netvar_tree::netvar_tree( ) {

	myfile.open( "netvars.txt" );

	const client_class* cc = i::client->get_all_classes( );

	while ( cc != nullptr ) {
		const auto class_info = std::make_shared<node>( 0 );
		recv_table* recv_table = cc->m_recv_table;

		this->populate_nodes( recv_table, &class_info->nodes );
		nodes.emplace( recv_table->m_net_table_name, class_info );

		cc = cc->m_next;
	}

	myfile.close( );
}

void netvar_tree::populate_nodes( recv_table* recvTable, map_type* map_type ) {
	for ( auto i = 0; i < recvTable->m_n_props; i++ ) {
		const recv_prop* prop = &recvTable->m_props[ i ];
		const auto prop_info = std::make_shared<node>( prop->m_offset );

		if ( prop->m_recv_type == 6 )
			this->populate_nodes( prop->m_data_table, &prop_info->nodes );

		if ( prop && prop->m_offset ) {
			char buffer[ 1024 ];
			sprintf_s( buffer, "%s -> 0x%i\n", prop->m_var_name, prop->m_offset );

			myfile << buffer;
		}

		map_type->emplace( prop->m_var_name, prop_info );
	}
}

namespace offsets {
	namespace DT_BasePlayer {
		int m_iHealth;
		int m_fFlags;
		int m_lifeState;
	}

	namespace DT_BaseEntity {
		int m_iTeamNum;
		int m_Collision;
	}

	void setup( ) {
		DT_BasePlayer::m_iHealth = netvar_manager->get_offset( "DT_BasePlayer", "m_iHealth" );
		DT_BasePlayer::m_fFlags = netvar_manager->get_offset( "DT_BasePlayer", "m_fFlags" );
		DT_BasePlayer::m_lifeState = netvar_manager->get_offset( "DT_BasePlayer", "m_lifeState" );

		DT_BaseEntity::m_iTeamNum = netvar_manager->get_offset( "DT_BaseEntity", "m_iTeamNum" );
		DT_BaseEntity::m_Collision = netvar_manager->get_offset( "DT_BaseEntity", "m_Collision" );
	}
}