//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ObjLoadException.cpp
//------------------------------------------------------------

#include "ObjLoadException.hpp"
#include "../../../../../../Common/Core/Package/PackageLocation.hpp"

namespace KMLEngine {
    ObjLoadException::ObjLoadException(const PackageLocation& location)
        : std::runtime_error(fmt::format("Loading obj model failed: {}", location.ToString())) {}
}