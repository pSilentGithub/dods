#include "../sdk/includes.hpp"

namespace i {
	chl_client* client;
	iv_engine_client* engine;
	i_surface* surface;
	i_input_system* input_system;
	c_client_entity_list* entity_list;
	i_debug_overlay* debug_overlay;
	i_panel* panel;
	std::uint8_t* device;
}

void i::setup( ) {
	//__cstring:004B695A 0000000B C VClient017
	iface( client, chl_client, "client.dll", "VClient017" );

	//__cstring:004B699F 00000011 C VEngineClient014
	iface( engine, iv_engine_client, "engine.dll", "VEngineClient014" );

	//__cstring:004DA121 00000010 C VGUI_Surface030
	iface( surface, i_surface, "vguimatsurface.dll", "VGUI_Surface030" );

	//__cstring:004B6B14 00000016 C InputSystemVersion001
	iface( input_system, i_input_system, "inputsystem.dll", "InputSystemVersion001" );

	//__cstring:004B6FD2 00000015 C VClientEntityList003
	iface( entity_list, c_client_entity_list, "client.dll", "VClientEntityList003" );

	//__cstring:004B69FC 00000011 C VDebugOverlay003
	iface( debug_overlay, i_debug_overlay, "engine.dll", "VDebugOverlay003" );

	//__cstring:004DA113 0000000E C VGUI_Panel009
	iface( panel, i_panel, "vgui2.dll", "VGUI_Panel009" );

	device = util::get_signature( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 1;
}