using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Osprey.Render {
    public interface IRender {
        #region Properties

        System.Windows.Media.Color BackgroundColor { get; set; }

        #endregion
        #region Methods

        void Create();


        void Destroy();


        IntPtr GetSurface();


        void Resize(System.Windows.Size size);


        void Draw();

        #endregion
    }
}
