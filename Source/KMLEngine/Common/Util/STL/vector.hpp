//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: vector.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_STL_VECTOR_HPP
#define KMLENGINE_COMMON_UTIL_STL_VECTOR_HPP

#pragma once

#include <vector>
#include <algorithm>

namespace kml_stl {
    template<typename T>
    [[nodiscard]] bool vector_contains(std::vector<T>& v, const T& value) noexcept {
        return std::find(v.begin(), v.end(), value) != v.end();
    }

    template<typename T>
    void remove_from_vector(std::vector<T>& v, const T& value) {
        v.erase(std::find(v.begin(), v.end(), value));
    }

    template<typename T>
    [[nodiscard]] bool try_remove_from_vector(std::vector<T>& v, const T& value) noexcept {
        const auto iterator = std::find(v.begin(), v.end(), value);
        if(iterator == v.end()) return false;
        v.erase(iterator);
        return true;
    }
}

namespace std {
    template<typename T>
    struct hash<std::vector<T>> {
        [[nodiscard]] size_t operator ()(const std::vector<T>& v) const noexcept {
            auto hash_code = v.size();
            for(const auto& i : v) hash_code ^= std::hash<T>()(i) + 0x9e3779b9 + (hash_code << 6) + (hash_code >> 2); //Boost hash
            return hash_code;
        }
    };
}
#endif //KMLENGINE_COMMON_UTIL_STL_VECTOR_HPP
