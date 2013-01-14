#pragma once


namespace Osprey { namespace Render { namespace Direct3D {


    public enum class RenderType {
        Direct3D11,
    };


    public ref class RenderFactory {
    private:
        RenderFactory() {};


    public:
        static Osprey::Render::IRender ^ CreateRender( RenderType renderType );


    };


} } }
