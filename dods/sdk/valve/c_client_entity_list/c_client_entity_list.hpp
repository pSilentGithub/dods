#pragma once

class c_client_entity_list {
public:
	virtual void* get_client_networkable( int entnum ) = 0;
	virtual void* get_client_networkable_from_handle( HANDLE entity_handle ) = 0;
	virtual void* get_client_unknown_from_handle( HANDLE entity_handle ) = 0;
	virtual c_base_entity* get_client_entity( int entnum ) = 0;
	virtual c_base_entity* get_client_entity_from_handle( HANDLE entity_handle ) = 0;
	virtual int number_of_entities( bool include_non_networkable ) = 0;
	virtual int get_highest_entity_index( void ) = 0;
	virtual void set_max_entites( int maxents ) = 0;
	virtual int get_max_entities( ) = 0;
};