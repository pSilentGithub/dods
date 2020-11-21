#pragma once

namespace i {
	extern chl_client* client;
	extern iv_engine_client* engine;
	extern i_surface* surface;
	extern i_input_system* input_system;
	extern c_client_entity_list* entity_list;
	extern i_debug_overlay* debug_overlay;
	extern i_panel* panel;

	void setup( );
}