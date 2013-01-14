#pragma once


#include <DXGI.h>
#include <D3D11.h>


namespace Osprey { namespace Render { namespace Direct3D { namespace Direct3D11 { namespace Native {


    class Render {
    public:
        Render();


        void create();


        void destroy();


        void resize( UINT width, UINT height );


        IDXGIResource * get_render_target() const { return m_render_target_surface; }


        void set_background_color( float const* color ) {
            memcpy( m_background_color, color, 4 * sizeof( float ) );
        }


        void get_background_color( float * color ) const {
            memcpy( color, m_background_color, 4 * sizeof( float ) );
        }


    private:
        void enumerate_adapters();


    private:
        IDXGIFactory1          * m_factory;
        IDXGIAdapter           * m_adapter;
        IDXGIKeyedMutex        * m_render_target_mutex;
        IDXGIResource          * m_render_target_surface;
        ID3D11Device           * m_device;
        ID3D11DeviceContext    * m_immediate_context;
        ID3D11Texture2D        * m_render_target;
        ID3D11RenderTargetView * m_render_target_view;

        D3D_FEATURE_LEVEL m_feature_level;
        float m_background_color[4];


    };


} } } } }
