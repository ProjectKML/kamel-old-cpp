//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ObjLoader.cpp
//------------------------------------------------------------

#include "ObjLoader.hpp"
#include "../../../../../../Common/Core/Package/PackageStream.hpp"
#include "../../../../../../Common/Core/Package/PackageLocation.hpp"
#include "ObjLoadException.hpp"

namespace KMLEngine::ObjLoader {
    static const fastObjCallbacks _OBJ_CALLBACKS = {
            .file_open = [](const char* path, void* userData) -> void* {
                KML_ASSERT(userData);

                return new PackageStream(PackageLocation(*static_cast<const std::string*>(userData), path));
            },
            .file_close = [](void* file, void* userData) {
                KML_ASSERT(file);
                KML_ASSERT(userData);

                delete static_cast<PackageStream*>(file);
            },
            .file_read = [](void* file, void* destination, usize size, void* userData) -> usize {
                KML_ASSERT(file);
                KML_ASSERT(destination);
                KML_ASSERT(size);
                KML_ASSERT(userData);

                return static_cast<PackageStream*>(file)->Fread(destination, size);
            },
            .file_size = [](void* file, void* userData) -> unsigned long {
                KML_ASSERT(file);
                KML_ASSERT(userData);

                return static_cast<PackageStream*>(file)->GetSize();
            }
    };

    fastObjMesh* Load(const PackageLocation& location) {
        auto* mesh = fast_obj_read_with_callbacks(location.GetEntryName().c_str(), &_OBJ_CALLBACKS, (void*)&location.GetFileName());
        if(!mesh) throw ObjLoadException(location);
        return mesh;
    }

    void Unload(fastObjMesh* mesh) noexcept {
        KML_ASSERT(mesh);
        fast_obj_destroy(mesh);
    }
}