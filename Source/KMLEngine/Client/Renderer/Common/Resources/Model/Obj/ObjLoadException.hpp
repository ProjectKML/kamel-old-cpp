//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ObjLoadException.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_OBJLOADEXCEPTION_HPP
#define KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_OBJLOADEXCEPTION_HPP

#pragma once

#include <stdexcept>

namespace KMLEngine {
    class PackageLocation;

    class ObjLoadException final : public std::runtime_error {
    public:
        explicit ObjLoadException(const PackageLocation& location);
    };
}

#endif //KMLENGINE_CLIENT_RENDERER_COMMON_RESOURCES_MODEL_OBJ_OBJLOADEXCEPTION_HPP