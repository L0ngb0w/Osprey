#pragma once

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

#include <cassert>
#include <stdexcept>


#include <direct3d11.render.h>


#ifdef _DEBUG

#pragma comment( lib, "Osprey.Render.Direct3D.Native_d.lib" )

#else

#pragma comment( lib, "Osprey.Render.Direct3D.Native.lib" )

#endif