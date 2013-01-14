using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Interop;
using Osprey.Document;

namespace Osprey {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window {
        private readonly D3DImage mD3DImage;
        private readonly Render.IRender mRender;
        private bool mRenderCreated = false;
        //private IntPtr mBackBuffer;

        private readonly List<Document.IDocument> mDocuments = new List<IDocument>();

        //protected bool CanRender { get { return mBackBuffer != IntPtr.Zero; } }

        public MainWindow() {
            mRender = Render.Direct3D.RenderFactory.CreateRender(Render.Direct3D.RenderType.Direct3D11);
            mRender.BackgroundColor = Colors.BlueViolet;

            mD3DImage = new D3DImage();
            mD3DImage.IsFrontBufferAvailableChanged += OnIsFrontBufferAvailableChanged;

            // Do this before initializing components to make the resouce available to XAML
            Resources["D3DImage"] = new ImageBrush(mD3DImage);

            InitializeComponent();
        }

        protected override void OnClosing(System.ComponentModel.CancelEventArgs e) {
            foreach (var document in mDocuments.Where(d => d.HasUnsavedChanges)) {
                var result = MessageBox.Show(
                    string.Format("Save changes to \"{0}\"?", document.Name),
                    "Save changes?", MessageBoxButton.YesNoCancel, MessageBoxImage.Question, MessageBoxResult.Cancel);
                switch (result) {
                    case MessageBoxResult.Cancel:
                        e.Cancel = true;
                        return;
                    case MessageBoxResult.Yes:
                        document.Save();
                        break;
                }
            }

            base.OnClosing(e);
        }

        protected override void OnClosed(EventArgs e) {
            base.OnClosed(e);

            mRenderCreated = false;
            mRender.Destroy();
        }

        private void OnRendering(object sender, EventArgs eventArgs) {
            if (mD3DImage.IsFrontBufferAvailable /*&& CanRender*/) {
                mD3DImage.Lock();

                // Update back buffer

                mD3DImage.SetBackBuffer(D3DResourceType.IDirect3DSurface9, mRender.GetSurface());
                mD3DImage.AddDirtyRect(new Int32Rect(0, 0, (int)this.ActualWidth, (int)this.ActualHeight));
                mD3DImage.Unlock();
            }
        }

        private void OnIsFrontBufferAvailableChanged(object sender, DependencyPropertyChangedEventArgs dependencyPropertyChangedEventArgs) {
            FrontBufferAvailibilityChanged();
        }

        private void FrontBufferAvailibilityChanged() {
            if (mD3DImage.IsFrontBufferAvailable) {
                mRender.Create();
                //mBackBuffer = mRender.GetSurface();

                mRenderCreated = true;
                CompositionTarget.Rendering += OnRendering;
            } else {
                CompositionTarget.Rendering -= OnRendering;

                mRenderCreated = false;
                //mBackBuffer = IntPtr.Zero;
                mRender.Destroy();
            }
        }

        private void FrameworkElement_OnSizeChanged(object sender, SizeChangedEventArgs e) {
            if (mRender != null && mD3DImage.IsFrontBufferAvailable && mRenderCreated) {
                mRender.Resize(e.NewSize);
            }
        }

        private void MainWindow_OnLoaded(object sender, RoutedEventArgs e) {
            FrontBufferAvailibilityChanged();
            mRender.Resize(new Size(this.RenderTarget.ActualWidth, this.RenderTarget.ActualHeight));
        }
    }
}
