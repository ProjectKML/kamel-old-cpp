//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: InternalCalls.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_RUNTIME_INTERNALCALLS_HPP
#define KMLENGINE_COMMON_CORE_RUNTIME_INTERNALCALLS_HPP

#pragma once

#include "../../../Platform/Types.hpp"
#include "../../Core/Package/PackageLocation.hpp"
#include <spdlog/spdlog.h>

namespace KMLEngine {
    void Logger_Log(u32 logLevel, const char* message) {
        KML_ASSERT(message);
        spdlog::log(static_cast<spdlog::level::level_enum>(logLevel), message);
    }

    struct Buffer {
        byte* Data;
        usize Size;

        Buffer(byte* data, usize size) : Data(data), Size(size) {}
    };

    Buffer PackageLocation_GetEntry(const char* fileName, const char* entryName) {
        KML_ASSERT(fileName);
        KML_ASSERT(entryName);

        const PackageLocation location(fileName, entryName);
        byte* data;
        usize size;

        location.GetEntry(data, size, *std::pmr::new_delete_resource());
        return Buffer(data, size);
    }

    void PackageLocation_FreeBuffer(byte* buffer, usize size) {
        KML_ASSERT(buffer);

        std::pmr::new_delete_resource()->deallocate(buffer, size);
    }
}

#endif //KMLENGINE_COMMON_CORE_RUNTIME_INTERNALCALLS_HPP