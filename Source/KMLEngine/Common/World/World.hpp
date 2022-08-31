//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: World.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_WORLD_WORLD_HPP
#define KMLENGINE_COMMON_WORLD_WORLD_HPP

#pragma once

#include "../../Platform/Hints/ForceInline.hpp"

namespace KMLEngine {
    class World {
    private:
        bool m_isClient;
    protected:
        World(bool isClient);
        virtual ~World() = default;
    public:
        KML_FORCEINLINE bool IsClient() const { return m_isClient; }
    };
}

#endif //KMLENGINE_COMMON_WORLD_WORLD_HPP