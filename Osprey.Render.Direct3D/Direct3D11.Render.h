#pragma once


namespace Osprey { namespace Render { namespace Direct3D { namespace Direct3D11 {


    public ref class Render
        : public Osprey::Render::IRender
    {
    internal:
        Render();


        ~Render();


    public: // IRender
        virtual void Create();


        virtual void Destroy();


        virtual System::IntPtr GetSurface();


        virtual void Resize( System::Windows::Size size );


        virtual void Draw();


        virtual property System::Windows::Media::Color BackgroundColor {
            System::Windows::Media::Color get();
            void set( System::Windows::Media::Color value );
        }


    private:
        Native::Render * m_render;

        bool m_ready;


    };


} } } }
