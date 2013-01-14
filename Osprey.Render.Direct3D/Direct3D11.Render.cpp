#include "Stdafx.h"
#include "Direct3D11.Render.h"


using namespace System;


namespace Osprey { namespace Render { namespace Direct3D { namespace Direct3D11 {


    Render::Render() 
        : m_render( new Native::Render() )
        , m_ready( false )
    {}


    Render::~Render() {
        delete m_render;
    }


    void Render::Create() {
        try {
            m_render->create();

            m_ready = true;
        } catch( std::runtime_error const& e ) {
            throw gcnew Exception( gcnew String( e.what() ) );
        }
    }


    void Render::Destroy() {
        m_ready = false;
        m_render->destroy();
    }


    System::IntPtr Render::GetSurface() {
        return IntPtr( m_render->get_render_target() );
    }


    void Render::Resize( System::Windows::Size size ) {
        assert( m_render );

        if( !m_ready ) {
            throw gcnew Exception( gcnew String( L"Attempt to resize render before it has been created" ) );
        }
        
        try {
            m_render->resize( (UINT)size.Width, (UINT)size.Height );
        } catch( std::runtime_error const& e ) {
            throw gcnew Exception( gcnew String( e.what() ) );
        }
    }


    void Render::Draw() {
    }


    System::Windows::Media::Color Render::BackgroundColor::get() {
        //D3DXVECTOR4 color = m_render->get_background_color();
        float color[4];
        m_render->get_background_color( color );

        return System::Windows::Media::Color::FromArgb( (unsigned char)( color[3] * 255.0f ), (unsigned char)( color[0] * 255.0f ), (unsigned char)( color[1] * 255.0f ), (unsigned char)( color[2] * 255.0f ) );
    }


    void Render::BackgroundColor::set( System::Windows::Media::Color value ) {
        float color[4] = { (float)value.R / 255.0f, (float)value.G / 255.0f, (float)value.B / 255.0f, (float)value.A / 255.0f };
        m_render->set_background_color( color );
    }


} } } }
