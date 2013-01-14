using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Osprey.Document {
    public class Document : IDocument {
        public string Name { get; set; }


        public bool HasUnsavedChanges { get { return false; } }


        public void Save() {
            throw new NotImplementedException();
        }
    }
}
