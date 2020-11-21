#include "../sdk/includes.hpp"

vmt_hook* panel_hook;
vmt_hook* device_hook;

void __fastcall paint_traverse( std::uintptr_t ecx, std::uintptr_t edx, unsigned int panel, bool force_repaint, bool allow_force );
long __fastcall end_scene( std::uintptr_t ecx, std::uintptr_t edx, const LPDIRECT3DDEVICE9 device );

void h::setup( ) {
	panel_hook = new vmt_hook( i::panel );
	panel_hook->hook( paint_traverse, 41 );
	panel_hook->apply( );

	device_hook = new vmt_hook( reinterpret_cast<DWORD*>( i::device ) );
	device_hook->hook( end_scene, 42 );
	device_hook->apply( );
}

void h::release( ) {
	panel_hook->release( );
	device_hook->release( );

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

		render::text( render::fonts::main, "dods hack", 5, 8, false, color( 255, 255, 255, 255 ) );
	}
}

long __fastcall end_scene( std::uintptr_t ecx, std::uintptr_t edx, const LPDIRECT3DDEVICE9 device ) {
	static auto original_fn = device_hook->get_original< decltype( &end_scene ) >( 42 );

	return original_fn( ecx, edx, device );
}