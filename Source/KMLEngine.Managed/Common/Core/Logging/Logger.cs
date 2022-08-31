//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Logger.cs
//------------------------------------------------------------

using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using KMLEngine.Managed.Common.Core.Loader;

namespace KMLEngine.Managed.Common.Core.Logging {
    public static class Logger {
        internal static unsafe delegate* unmanaged<LogLevel, byte*, void> _LOG = null;
        
        public static unsafe void Log(LogLevel logLevel, string message) {
            var nativeMessage = Encoding.UTF8.GetBytes(message);
            fixed (byte* address = nativeMessage) {
                _LOG(logLevel, address);
            }
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void Trace(string message) {
            Log(LogLevel.Trace, message);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void Debug(string message) {
            Log(LogLevel.Debug, message);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void Info(string message) {
            Log(LogLevel.Info, message);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void Warn(string message) {
            Log(LogLevel.Warn, message);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void Error(string message) {
            Log(LogLevel.Error, message);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void Critical(string message) {
            Log(LogLevel.Critical, message);
        }
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void Off(string message) {
            Log(LogLevel.Off, message);
        }
    }
}