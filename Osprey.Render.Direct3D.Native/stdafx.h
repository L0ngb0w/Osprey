#pragma once

#include "targetver.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

#include <cassert>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>


#include <DXGI.h>
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10math.h>
