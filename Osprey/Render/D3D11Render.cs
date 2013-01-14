//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Windows;
//using SlimDX;
//using SlimDX.Direct3D11;
//using SlimDX.Direct3D9;
//using Device = SlimDX.Direct3D11.Device;

//namespace Osprey.Render {
//    class D3D11Render : IRender {
//        private Device mDevice;

//        private SlimDX.DXGI.Factory1 mFactory;

//        private SlimDX.DXGI.Surface mRenderSurface;
//        private Texture2D mRenderTarget;
//        private RenderTargetView mRenderTargetView;

//        private Color4 mBackgroundColor;


//        public System.Windows.Media.Color BackgroundColor {
//            get {
//                return System.Windows.Media.Color.FromArgb(
//                    (byte)(mBackgroundColor.Alpha * 255.0f),
//                    (byte)(mBackgroundColor.Red * 255.0f),
//                    (byte)(mBackgroundColor.Green * 255.0f),
//                    (byte)(mBackgroundColor.Blue * 255.0f));
//            }
//            set {
//                mBackgroundColor = new Color4(value.A * 255.0f, value.R * 255.0f, value.G * 255.0f, value.B * 255.0f);
//            }
//        }


//        public void Create() {
//            try {
//#if DEBUG

//                //var d3d9device = new SlimDX.Direct3D9.DeviceEx(new SlimDX.Direct3D9.Direct3DEx(), 0, DeviceType.Hardware, IntPtr.Zero, CreateFlags.PureDevice, )

//                mFactory = new SlimDX.DXGI.Factory1();
//                var adapter = mFactory.GetAdapter1(0);
//                //var output = adapter.GetOutput(0);
//                //output.

//                //SlimDX.DXGI.Device device = ;

//                mDevice = new Device(adapter, DeviceCreationFlags.Debug, FeatureLevel.Level_11_0, FeatureLevel.Level_10_1, FeatureLevel.Level_10_0);
//#else
//                SlimDX.DXGI.Device device = new Device(DriverType.Hardware, DeviceCreationFlags.Debug);
//                mDevice = new Device(0, DeviceCreationFlags.None, FeatureLevel.Level_11_0, FeatureLevel.Level_10_1, FeatureLevel.Level_10_0);
//#endif
//            } catch (Exception e) {
//                if (mDevice != null) {
//                    mDevice.Dispose();
//                }

//                throw e;
//            }
//        }

//        public void Destroy() {
//            mDevice.Dispose();
//        }


//        public IntPtr GetSurface() {
//            var surface = mRenderTarget.AsSurface();
//            surface.

//            var resource = SlimDX.DXGI.Resource.FromPointer(mRenderTarget.AsSurface().ComPointer);
//            return resource.SharedHandle;
//            //return mRenderTarget.AsSurface().ComPointer;
//        }


//        public void Resize(Size size) {
//            if (mDevice != null) {
//                if (mRenderTarget != null) {
//                    mRenderTarget.Dispose();
//                    mRenderTargetView.Dispose();
//                }

//                //mDevice.Factory.
//                //mRenderSurface = Surface1.;

//                var desc_tex = new Texture2DDescription {
//                    Width = (int)size.Width,
//                    Height = (int)size.Height,
//                    MipLevels = 1,
//                    ArraySize = 1,
//                    Format = SlimDX.DXGI.Format.R8G8B8A8_UNorm,
//                    SampleDescription = new SlimDX.DXGI.SampleDescription(1, 0),
//                    Usage = ResourceUsage.Default,
//                    BindFlags = BindFlags.RenderTarget,
//                    CpuAccessFlags = CpuAccessFlags.None,
//                    OptionFlags = ResourceOptionFlags.None
//                };

//                mRenderTarget = new Texture2D(mDevice, desc_tex);

//                var desc_rtv = new RenderTargetViewDescription {
//                    Format = desc_tex.Format,
//                    Dimension = RenderTargetViewDimension.Texture2D,
//                    MipSlice = 0,
//                };

//                mRenderTargetView = new RenderTargetView(mDevice, mRenderTarget, desc_rtv);
//            }
//        }


//        public void Render() {
//            mDevice.ImmediateContext.ClearRenderTargetView(mRenderTargetView, mBackgroundColor);
//        }
//    }
//}
