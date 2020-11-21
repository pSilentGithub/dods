#pragma once

#include <Windows.h>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <d3d9.h>

#include "util/util.hpp"

#include "vmt_hook/vmt_hook.hpp"

#include "valve/vector/vector.hpp"
#include "valve/matrix/matrix.hpp"
#include "valve/recv_prop/recv_prop.hpp"
#include "../netvar_manager/netvar_manager.h"
#include "valve/chl_client/chl_client.hpp"
#include "valve/iv_engine_client/iv_engine_client.hpp"
#include "valve/color/color.hpp"
#include "valve/i_surface/i_surface.hpp"
#include "valve/i_input_system/i_input_system.hpp"
#include "valve/c_base_entity/c_base_entity.hpp"
#include "valve/c_client_entity_list/c_client_entity_list.hpp"
#include "valve/iv_debug_overlay/iv_debug_overlay.hpp"
#include "valve/i_panel/i_panel.hpp"

#include "../render/render.hpp"

#include "../interfaces/interfaces.hpp"
#include "../hooks/hooks.hpp"

#include "../features/feature.hpp"
#include "../features/esp/esp.hpp"