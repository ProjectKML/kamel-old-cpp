//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: EventBus.cpp
//------------------------------------------------------------

#include "EventBus.hpp"

namespace KMLEngine {
    template<> EventBus* Singleton<EventBus>::_INSTANCE = nullptr;

    EventBus::EventBus() { AttachSingleton(); }
    EventBus::~EventBus() { DetachSingleton(); }
}
