//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: NativeLoader.cs
//------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Reflection;
using System.Runtime.InteropServices;
using KMLEngine.Managed.Common.Core.Logging;
using KMLEngine.Managed.Common.Core.Package;

namespace KMLEngine.Managed.Common.Core.Loader {
    internal class NativeLoader {
        internal struct InternalCall {
            public IntPtr Name;
            public IntPtr Address;
        }
        
        private static Dictionary<string, IntPtr> _INTERNAL_CALLS = new();
        public static Dictionary<string, IntPtr> InternalCalls => _INTERNAL_CALLS;
        
        [UnmanagedCallersOnly]
        private static unsafe byte Initialize(uint numInternalCalls, InternalCall* internalCalls, IntPtr managedFunctions) {
            var functionList = (IntPtr*)managedFunctions;
            if (functionList == null) return 0;
            
            functionList[0] = GetMethodInternal("KMLEngine.Managed.Common.Core.Loader.NativeLoader", "GetMethod",
                typeof(IntPtr), typeof(IntPtr));
            if(functionList[0] == IntPtr.Zero) return 0;

            functionList[1] = GetMethodInternal("KMLEngine.Managed.Common.Core.Loader.NativeLoader", "GetMethod",
                typeof(IntPtr), typeof(IntPtr), typeof(uint), typeof(IntPtr));

            for (var ix = 0; ix < numInternalCalls; ix++) {
                var internalCall = internalCalls[ix];
                var name = Marshal.PtrToStringUTF8(internalCall.Name) ?? throw new ArgumentNullException(nameof(internalCall.Name));
                _INTERNAL_CALLS.Add(name, internalCall.Address);
            }
    
            Logger._LOG = (delegate* unmanaged<LogLevel, byte*, void>) NativeLoader.InternalCalls["Logger_Log"];
            PackageLocation._GET_ENTRY = (delegate* unmanaged<byte*, byte*, PackageLocation.Buffer>) NativeLoader.InternalCalls["PackageLocation_GetEntry"];
            PackageLocation._FREE_BUFFER = (delegate* unmanaged<byte*, ulong, void>) NativeLoader.InternalCalls["PackageLocation_FreeBuffer"];
            
            return functionList[1] == null ? (byte) 0 : (byte) 1;
        }
        
        [UnmanagedCallersOnly]
        internal static IntPtr GetMethod(IntPtr typeName, IntPtr methodName) {
            var sTypeName = Marshal.PtrToStringUTF8(typeName);
            if(sTypeName == null) return IntPtr.Zero;

            var sMethodName = Marshal.PtrToStringUTF8(methodName);
            if(sMethodName == null) return IntPtr.Zero;

            var type = Type.GetType(sTypeName);
            if(type == null) return IntPtr.Zero;

            var method = type.GetMethod(sMethodName, BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
            if(method == null) return IntPtr.Zero;
            return method.GetCustomAttribute<UnmanagedCallersOnlyAttribute>() == null ? IntPtr.Zero : method.MethodHandle.GetFunctionPointer();
        }

        internal static IntPtr GetMethodInternal(string typeName, string methodName, params Type[] parameterTypes) {
            if(typeName == null) return IntPtr.Zero;
            if(methodName == null) return IntPtr.Zero;
            if(parameterTypes == null) return IntPtr.Zero;
            
            var type = Type.GetType(typeName);
            if(type == null) return IntPtr.Zero;
            
            var method = type.GetMethod(methodName, BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic, parameterTypes);
            if(method == null) return IntPtr.Zero;
            return method.GetCustomAttribute<UnmanagedCallersOnlyAttribute>() == null ? IntPtr.Zero : method.MethodHandle.GetFunctionPointer();
        }
        [UnmanagedCallersOnly]
        internal static IntPtr GetMethod(IntPtr typeName, IntPtr methodName, uint numParameters, IntPtr parameters) {
            var sTypeName = Marshal.PtrToStringUTF8(typeName);
            if(sTypeName == null) return IntPtr.Zero;

            var sMethodName = Marshal.PtrToStringUTF8(methodName);
            if(sMethodName == null) return IntPtr.Zero;
            
            var type = Type.GetType(sTypeName);
            if(type == null) return IntPtr.Zero;
            
            if(numParameters > 0 && parameters == IntPtr.Zero) return IntPtr.Zero;

            var parameterTypes = new Type[numParameters];
            for(var ix = 0; ix < numParameters; ix++) {
                unsafe {
                    var sParameterName = Marshal.PtrToStringUTF8(((IntPtr*) parameters)[0]);
                    if(sParameterName == null) return IntPtr.Zero;

                    var parameterType = Type.GetType(sParameterName);
                    if (parameterType == null) return IntPtr.Zero;
                    parameterTypes[ix] = parameterType;
                }
            }

            var method = type.GetMethod(sMethodName, BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic,
                parameterTypes);
            if(method == null) return IntPtr.Zero;
            return method.GetCustomAttribute<UnmanagedCallersOnlyAttribute>() == null ? IntPtr.Zero : method.MethodHandle.GetFunctionPointer();
        }
    }
}
