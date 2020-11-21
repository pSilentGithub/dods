#pragma once

class c_base_entity {
public:
    vfunc( get_abs_origin( ), 9, vector& ( __thiscall* )( void* ) );
    vfunc( get_abs_angles( ), 10, vector& ( __thiscall* )( void* ) );
    vfunc( is_alive( ), 63, bool( __thiscall* )( void* ) );
    vfunc( get_max_health( ), 114, int( __thiscall* )( void* ) );

    OFFSET( m_iHealth, int, offsets::DT_BasePlayer::m_iHealth );
    OFFSET( m_fFlags, int, offsets::DT_BasePlayer::m_fFlags );
    OFFSET( m_lifeState, int, offsets::DT_BasePlayer::m_lifeState );
    OFFSET( m_iTeamNum, int, offsets::DT_BaseEntity::m_iTeamNum );

    vector vec_mins( ) {
        return *reinterpret_cast< vector* >( uintptr_t( this ) + offsets::DT_BaseEntity::m_Collision + 0x2C );
    }

    vector vec_maxs( ) {
        return *reinterpret_cast< vector* >( uintptr_t( this ) + offsets::DT_BaseEntity::m_Collision + 0x20 );
    }

    bool is_dormant( ) {
        void* networkable = ( void* )( this + 0x8 );
        typedef bool( __thiscall* vfunc_fn )( void* );
        return util::get_virtual_function<vfunc_fn>( networkable, 8 )( networkable );
    }
};