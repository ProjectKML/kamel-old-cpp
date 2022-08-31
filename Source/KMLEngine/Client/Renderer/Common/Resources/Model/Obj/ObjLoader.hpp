//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ObjLoader.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_OBJLOADER_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_OBJLOADER_HPP

#pragma once

#include <fast_obj/fast_obj.h>

namespace KMLEngine {
    class PackageLocation;

    namespace ObjLoader {
        fastObjMesh* Load(const PackageLocation& location);
        void Unload(fastObjMesh* mesh) noexcept;
    }
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_OBJLOADER_HPP