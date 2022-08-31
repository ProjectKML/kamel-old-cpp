//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageLocation.cs
//------------------------------------------------------------

using System;
using System.Runtime.InteropServices;
using System.Text;

namespace KMLEngine.Managed.Common.Core.Package {
    public struct PackageLocation {
        [StructLayout(LayoutKind.Sequential)]
        internal unsafe struct Buffer {
            public readonly byte* Data;
            public readonly ulong Size;
        }

        internal static unsafe delegate* unmanaged<byte*, byte*, Buffer> _GET_ENTRY = null;
        internal static unsafe delegate* unmanaged<byte*, ulong, void> _FREE_BUFFER = null;

        public readonly string FileName;
        public readonly string EntryName;

        public PackageLocation(string fileName, string entryName) {
            FileName = fileName;
            EntryName = entryName;
        }

        public unsafe byte[] GetBytes() {
            var nativeFileName = Encoding.UTF8.GetBytes(FileName);
            var nativeEntryName = Encoding.UTF8.GetBytes(EntryName);

            byte[] content;
            
            fixed(byte* fileNameAddress = nativeFileName, entryNameAddress = nativeEntryName) {
                var buffer = _GET_ENTRY(fileNameAddress, entryNameAddress);
                content = new byte[buffer.Size];
                Marshal.Copy(new IntPtr(buffer.Data), content, 0, (int)buffer.Size);
                _FREE_BUFFER(buffer.Data, (ulong)content.Length);
            }

            return content;
        }

        public unsafe string GetString() {
            var nativeFileName = Encoding.UTF8.GetBytes(FileName);
            var nativeEntryName = Encoding.UTF8.GetBytes(EntryName);

            string content;
            
            fixed(byte* fileNameAddress = nativeFileName, entryNameAddress = nativeEntryName) {
                var buffer = _GET_ENTRY(fileNameAddress, entryNameAddress);
                content = Marshal.PtrToStringUTF8(new IntPtr(buffer.Data), (int)buffer.Size);
                _FREE_BUFFER(buffer.Data, buffer.Size);
            }

            return content;
        }
    }
}