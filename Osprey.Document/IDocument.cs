using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Osprey.Document {
    public interface IDocument {
        string Name { get; set; }

        bool HasUnsavedChanges { get; }

        void Save();

    }
}
