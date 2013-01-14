using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Osprey.Document {
    public class DocumentFactory {
        public static IDocument CreateDocument() {
            return new Document();
        }
    }
}
