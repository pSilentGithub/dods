#pragma once

/*
* forgot who originally made this, but i *borrowed* this
* netvar manager awhile ago and it has worked perfectly
* fine for me, if anyone knows the original author
* please make a pull request replacing this text
* with this format:
* 
* (c) author name
* link:
*/

class recv_table;

class netvar_tree {
	struct node;
	using map_type = std::unordered_map<std::string, std::shared_ptr<node>>;

	struct node {
		node( int offset ) : offset( offset ) { }
		map_type nodes;
		int offset;
	};

	map_type nodes;

public:
	netvar_tree( );

private:
	void populate_nodes( recv_table* recv_table, map_type* map );

	static int get_offset_recursive( map_type& map, int acc, const char* name ) {
		return acc + map[ name ]->offset;
	}

	template<typename ...args_t>
	int get_offset_recursive( map_type& map, int acc, const char* name, args_t ...args ) {
		const auto& node = map[ name ];
		return this->get_offset_recursive( node->nodes, acc + node->offset, args... );
	}

public:

	template<typename ...args_t>
	int get_offset( const char* name, args_t ...args ) {
		const auto& node = nodes[ name ];
		return this->get_offset_recursive( node->nodes, node->offset, args... );
	}
}; extern std::unique_ptr<netvar_tree> netvar_manager;

namespace offsets {
	namespace DT_BasePlayer {
		extern int m_iHealth;
		extern int m_fFlags;
		extern int m_lifeState;
	}

	namespace DT_BaseEntity {
		extern int m_iTeamNum;
		extern int m_Collision;
	}

	void setup( );
}

#define OFFSET( name, type, offset )\
	type &name( )\
	{\
		return *( type * )( (uintptr_t)this + offset );\
	}