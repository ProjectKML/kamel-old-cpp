//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: HashCode.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_HASHCODE_HPP
#define KMLENGINE_COMMON_UTIL_HASHCODE_HPP

#pragma once

#include "../../Platform/Types.hpp"
#include "../../Platform/Assert/Assert.hpp"
#include "../../Platform/Hints/ForceInline.hpp"
#include "STL/hash.hpp"

namespace KMLEngine {
    namespace HashCode {
        template<typename T>
        KML_FORCEINLINE void CombineWith(usize& hashCode, const T& value) noexcept {
            hashCode ^= std::hash<T>()(value) + 0x9e3779b9 + (hashCode << 6) + (hashCode >> 2); //Boost hash
        }

        namespace Detail {
            template<typename T, typename... TArguments>
            [[nodiscard]] KML_FORCEINLINE usize Combine(const T& first, TArguments&&... arguments) noexcept {
                auto hashCode = std::hash<T>()(first);
                (CombineWith(hashCode, std::forward<TArguments>(arguments)), ...);
                return hashCode;
            }
        }

        template<typename... TArguments>
        [[nodiscard]] KML_FORCEINLINE usize Combine(TArguments&&... arguments) noexcept {
            return Detail::Combine(std::forward<TArguments>(arguments)...);
        }

        template<typename T>
        [[nodiscard]] KML_FORCEINLINE usize CombineAll(usize numObjects, const T* objects) noexcept {
            KML_ASSERT(numObjects);
            KML_ASSERT(objects);

            auto hashCode = std::hash<T>()(objects[0]);

            for(usize ix = 1; ix < numObjects; ix++) CombineWith(hashCode, objects[ix]);
            return hashCode;
        }
    }
}

#endif //KMLENGINE_COMMON_UTIL_HASHCODE_HPP
