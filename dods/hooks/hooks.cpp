#include "../sdk/includes.hpp"

vmt_hook* panel_hook;

void __fastcall paint_traverse( std::uintptr_t ecx, std::uintptr_t edx, unsigned int panel, bool force_repaint, bool allow_force );

void h::setup( ) {
	panel_hook = new vmt_hook( i::panel );
	panel_hook->hook( paint_traverse, 41 );
	panel_hook->apply( );
}

void h::release( ) {
	panel_hook->release( );

	Sleep( 500 );
}

void __fastcall paint_traverse( std::uintptr_t ecx, std::uintptr_t edx, unsigned int panel, bool force_repaint, bool allow_force ) {
	static auto original_fn = panel_hook->get_original< decltype( &paint_traverse ) >( 41 );

	original_fn( ecx, edx, panel, force_repaint, allow_force );

	auto panel_name = i::panel->get_name( panel );

	static auto wanted_panel_id = 0;

	if ( !wanted_panel_id && !strcmp( panel_name, "FocusOverlayPanel" ) ) {
		wanted_panel_id = panel;
	} else if ( wanted_panel_id == panel ) {

		for ( auto& feature : base_feature::features ) {
			if ( feature )
				feature->draw( );
		}

		menu::run( );
	}
}