#include "Stdafx.h"
#include "RenderFactory.h"
#include "Direct3D11.Render.h"


using namespace System;

using namespace Osprey::Render;


namespace Osprey { namespace Render { namespace Direct3D {


    IRender ^ RenderFactory::CreateRender( RenderType renderType ) {
        switch( renderType ) {
        case RenderType::Direct3D11:
            return gcnew Direct3D11::Render();
        default:
            throw gcnew Exception();
        }
    }


} } }
