#include "stdafx.h"
#include "direct3d11.render.h"


namespace Osprey { namespace Render { namespace Direct3D { namespace Direct3D11 { namespace Native {


    Render::Render()
        : m_factory( nullptr )
        , m_adapter( nullptr )
        , m_render_target_mutex( nullptr )
        , m_render_target_surface( nullptr )
        , m_device( nullptr )
        , m_immediate_context( nullptr )
        , m_render_target( nullptr )
        , m_render_target_view( nullptr )
    {
    }


    void Render::create() {
        HRESULT hr;

        hr = CreateDXGIFactory1( __uuidof( IDXGIFactory1 ), reinterpret_cast< void ** >( &m_factory ) );
        if( FAILED( hr ) ) {
            throw std::runtime_error( "Could not create DXGI factory" );
        }

        enumerate_adapters();
        assert( m_adapter );

        UINT flags = 0;
#ifdef _DEBUG
        flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };

        hr = D3D11CreateDevice
            ( m_adapter
            , D3D_DRIVER_TYPE_UNKNOWN
            , nullptr
            , flags
            , feature_levels
            , sizeof( feature_levels ) / sizeof( feature_levels[0] )
            , D3D11_SDK_VERSION
            , &m_device
            , &m_feature_level
            , &m_immediate_context
            );
        if( FAILED( hr ) ) {
            throw std::runtime_error( "Could not create Direct3D 11 device" );
        }
    }


    void Render::destroy() {
        if( m_render_target_view ) {
            m_render_target_view->Release();
            m_render_target_view = nullptr;
        }

        if( m_render_target ) {
            m_render_target->Release();
            m_render_target = nullptr;
        }

        if( m_render_target_mutex ) {
            m_render_target_mutex->Release();
            m_render_target_mutex = nullptr;
        }

        if( m_immediate_context ) {
            m_immediate_context->Release();
            m_immediate_context = nullptr;
        }

        if( m_device ) {
            m_device->Release();
            m_device = nullptr;
        }

        if( m_adapter ) {
            m_adapter->Release();
            m_adapter = nullptr;
        }

        if( m_factory ) {
            m_factory->Release();
            m_factory = nullptr;
        }
    }


    void Render::resize( UINT width, UINT height ) {
        assert( m_device );

        HRESULT hr;

        if( m_render_target_view ) {
            m_render_target_view->Release();
            m_render_target_view = nullptr;
        }

        if( m_render_target ) {
            m_render_target->Release();
            m_render_target = nullptr;
        }

        if( m_render_target_mutex ) {
            m_render_target_mutex->Release();
            m_render_target_mutex = nullptr;
        }

        if( m_render_target_surface ) {
            m_render_target_surface->Release();
            m_render_target_surface = nullptr;
        }

        {
            D3D11_TEXTURE2D_DESC desc = {};
            desc.Width = width;
            desc.Height = height;
            desc.MipLevels = 1;
            desc.ArraySize = 1;
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.SampleDesc.Count = 1;
            desc.SampleDesc.Quality = 0;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_RENDER_TARGET;
            desc.CPUAccessFlags = 0;
            desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;

            hr = m_device->CreateTexture2D( &desc, nullptr, &m_render_target );
            if( FAILED( hr ) ) {
                throw std::runtime_error( "Could not create render target texture" );
            }
        }

        {
            D3D11_RENDER_TARGET_VIEW_DESC desc = {};
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
            desc.Texture2D.MipSlice = 0;

            hr = m_device->CreateRenderTargetView( m_render_target, &desc, &m_render_target_view );
            if( FAILED( hr ) ) {
                throw std::runtime_error( "Could not create render target view" );
            }
        }

        hr = m_render_target->QueryInterface( __uuidof( IDXGISurface ), reinterpret_cast< void ** >( &m_render_target_surface ) );
        if( FAILED( hr ) ) {
            throw std::runtime_error( "Could not get resource interface from render target" );
        }

        //IDXGIResource * surface = nullptr;
        //hr = m_render_target->QueryInterface( __uuidof( IDXGISurface ), reinterpret_cast< void ** >( &surface ) );
        //if( FAILED( hr ) ) {
        //    throw std::runtime_error( "Could not get resource interface from render target" );
        //}

        //try {
        //    hr = surface->GetSharedHandle( &m_shared_render_target_handle );
        //    if( FAILED( hr ) ) {
        //        throw std::runtime_error( "Could not get shared handle from resource" );
        //    }

        //    surface->Release();
        //} catch( ... ) {
        //    surface->Release();
        //    throw;
        //}

        hr = m_render_target->QueryInterface( __uuidof( IDXGIKeyedMutex ), reinterpret_cast< void ** >( &m_render_target_mutex ) );
        if( FAILED( hr ) ) {
            throw std::runtime_error( "Could not get keyed mutex interface from render target" );
        }
    }


    void Render::enumerate_adapters() {
        IDXGIAdapter * adapter = nullptr;
        std::vector< IDXGIAdapter * > adapters;
        for( UINT i = 0; m_factory->EnumAdapters( i, &adapter ) != DXGI_ERROR_NOT_FOUND; ++i ) {
            DXGI_ADAPTER_DESC desc = {};
            HRESULT hr = adapter->GetDesc( &desc );
            if( FAILED( hr ) ) {
                throw std::runtime_error( "Could not get adapter description" );
            }

            adapters.push_back( adapter );
        }

        m_adapter = adapters.front();
        m_adapter->AddRef();

        std::for_each( adapters.begin(), adapters.end(), [&]( IDXGIAdapter * a ) { a->Release(); } );
    }


} } } } }
