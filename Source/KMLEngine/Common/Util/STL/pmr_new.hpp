//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: pmr_new.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STL_PMR_NEW_HPP
#define KMLENGINE_COMMON_UTIL_STL_PMR_NEW_HPP

#pragma once

#include "../../../Platform/Assert/Assert.hpp"
#include <memory_resource>

namespace kml_stl {
    template<typename T, typename... Arguments>
    inline T* pmr_new(std::pmr::memory_resource& memoryResource, Arguments&&... arguments) {
        auto* object = static_cast<T*>(memoryResource.allocate(sizeof(T), alignof(T)));
        new (object) T(std::forward<Arguments>(arguments)...);
        return object;
    }

    template<typename T, typename... Arguments>
    inline T* pmr_new(std::pmr::memory_resource* memoryResource, Arguments&&... arguments) {
        KML_ASSERT(memoryResource);

        auto* object = static_cast<T*>(memoryResource->allocate(sizeof(T), alignof(T)));
        new (object) T(std::forward<Arguments>(arguments)...);
        return object;
    }

    template<typename T, typename... Arguments>
    inline T* pmr_new_arr(std::pmr::memory_resource& memoryResource, size_t numObjects, Arguments&&... arguments) {
        KML_ASSERT(numObjects);

        auto* objects = static_cast<T*>(memoryResource.allocate(sizeof(T) * numObjects, alignof(T)));
        for(auto i = 0; i < numObjects; i++) new (objects[i]) T(std::forward<Arguments>(arguments)...);
        return objects;
    }

    template<typename T, typename... Arguments>
    inline T* pmr_new_arr(std::pmr::memory_resource* memoryResource, size_t numObjects, Arguments&&... arguments) {
        KML_ASSERT(memoryResource);
        KML_ASSERT(numObjects);

        auto* objects = static_cast<T*>(memoryResource->allocate(sizeof(T) * numObjects, alignof(T)));
        for(auto i = 0; i < numObjects; i++) new (objects[i]) T(std::forward<Arguments>(arguments)...);
        return objects;
    }

    template<typename T>
    inline void pmr_delete(std::pmr::memory_resource& memoryResource, T* object) {
        KML_ASSERT(object);

        object->~T();
        memoryResource.deallocate(object, sizeof(T), alignof(T));
    }

    template<typename T>
    inline void pmr_delete(std::pmr::memory_resource* memoryResource, T* object) {
        KML_ASSERT(memoryResource);
        KML_ASSERT(object);

        object->~T();
        memoryResource->deallocate(object, sizeof(T), alignof(T));
    }

    template<typename T>
    inline void pmr_delete_arr(std::pmr::memory_resource& memoryResource, T* object, size_t numObjects) {
        KML_ASSERT(object);
        KML_ASSERT(numObjects);

        for(auto i = 0; i < numObjects; i++) object[i].Dispose();
        memoryResource.deallocate(object, sizeof(T) * numObjects, alignof(T));
    }

    template<typename T>
    inline void pmr_delete_arr(std::pmr::memory_resource* memoryResource, T* object, size_t numObjects) {
        KML_ASSERT(memoryResource);
        KML_ASSERT(object);
        KML_ASSERT(numObjects);

        for(auto i = 0; i < numObjects; i++) object[i].Dispose();
        memoryResource->deallocate(object, sizeof(T) * numObjects, alignof(T));
    }
}

#endif //KMLENGINE_COMMON_UTIL_STL_PMR_NEW_HPP