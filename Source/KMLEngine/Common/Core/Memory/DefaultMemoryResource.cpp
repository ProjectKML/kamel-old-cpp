//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: DefaultMemoryResource.cpp
//------------------------------------------------------------

#include "DefaultMemoryResource.hpp"

namespace KMLEngine {
    template<> DefaultMemoryResource* Singleton<DefaultMemoryResource>::_INSTANCE = nullptr;

    DefaultMemoryResource::DefaultMemoryResource() { AttachSingleton(); }
    DefaultMemoryResource::~DefaultMemoryResource() { DetachSingleton(); }
}