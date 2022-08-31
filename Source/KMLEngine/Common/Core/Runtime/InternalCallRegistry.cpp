//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: InternalCallRegistry.cpp
//------------------------------------------------------------

#include "InternalCallRegistry.hpp"
#include "InternalCalls.hpp"

namespace KMLEngine {
    void InternalCallRegistry::RegisterInternalCalls() {
        Add("Logger_Log", (void*)Logger_Log);
        Add("PackageLocation_GetEntry", (void*)PackageLocation_GetEntry);
        Add("PackageLocation_FreeBuffer", (void*)PackageLocation_FreeBuffer); //TODO: check here
    }
}
