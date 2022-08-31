//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: Guid.cpp
//------------------------------------------------------------

#include "Guid.hpp"
#include "../../Platform/PlatformMemory.hpp"
#include "String/Character.hpp"
#ifdef KML_PLATFORM_WINDOWS
#include "../../Platform/Windows/WindowsHelper.hpp"
#include <Windows.h>
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS)
#include <CoreFoundation/CFUUID.h>
#elif defined(KML_PLATFORM_LINUX)
#include <uuid/uuid.h>
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
#include <fmt/format.h>

namespace KMLEngine {
    Guid Guid::NewGuid() {
        Guid guid;
#ifdef KML_PLATFORM_WINDOWS
        if (FAILED(CoCreateGuid(reinterpret_cast<GUID*>(guid.U8.data())))) {
            throw std::runtime_error(fmt::format("CoCreateGuid failed: {}", WindowsHelper::GetLastErrorAsString()));
        }
#elif defined(KML_PLATFORM_MACOS) || defined(KML_PLATFORM_IOS)
        const auto newId = CFUUIDCreate(nullptr);
        const auto bytes = CFUUIDGetUUIDBytes(newId);
        CFRelease(newId);

        PlatformMemory::Copy(guid.U8.data(), &bytes, guid.U8.size());
#elif defined(KML_PLATFORM_LINUX)
        uuid_generate((unsigned char*)&guid);
#else
#error KML_UNSUPPORTED_PLATFORM
#endif
        return guid;
    }

    Guid Guid::FromString(const std::string_view& str) {
        if (str.size() != 36) throw std::runtime_error("Invalid Guid");

        Guid guid;
        if (!Character::TryToHexInt(str[0], str[1], guid.U8[0])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[2], str[3], guid.U8[1])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[4], str[5], guid.U8[2])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[6], str[7], guid.U8[3])) throw std::runtime_error("Invalid Guid");

        if (str[8] != '-') throw std::runtime_error("Invalid Guid");

        if (!Character::TryToHexInt(str[9], str[10], guid.U8[4])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[11], str[12], guid.U8[5])) throw std::runtime_error("Invalid Guid");

        if (str[13] != '-') throw std::runtime_error("Invalid Guid");

        if (!Character::TryToHexInt(str[14], str[15], guid.U8[6])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[16], str[17], guid.U8[7])) throw std::runtime_error("Invalid Guid");

        if (str[18] != '-') throw std::runtime_error("Invalid Guid");

        if (!Character::TryToHexInt(str[19], str[20], guid.U8[8])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[21], str[22], guid.U8[9])) throw std::runtime_error("Invalid Guid");

        if (str[23] != '-') throw std::runtime_error("Invalid Guid");

        if (!Character::TryToHexInt(str[24], str[25], guid.U8[10])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[26], str[27], guid.U8[11])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[28], str[29], guid.U8[12])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[30], str[31], guid.U8[13])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[32], str[33], guid.U8[14])) throw std::runtime_error("Invalid Guid");
        if (!Character::TryToHexInt(str[34], str[35], guid.U8[15])) throw std::runtime_error("Invalid Guid");

        return guid;
    }

    Guid::Guid() {
        PlatformMemory::Zero(U8.data(), U8.size());
    }

    std::ostream& operator<<(std::ostream& stream, const Guid& guid) {
        stream << Character::FromHexInt((guid.U8[0] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[0] & 0xF);

        stream << Character::FromHexInt((guid.U8[1] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[1] & 0xF);

        stream << Character::FromHexInt((guid.U8[2] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[2] & 0xF);

        stream << Character::FromHexInt((guid.U8[3] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[3] & 0xF);

        stream << '-';

        stream << Character::FromHexInt((guid.U8[4] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[4] & 0xF);

        stream << Character::FromHexInt((guid.U8[5] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[5] & 0xF);

        stream << '-';

        stream << Character::FromHexInt((guid.U8[6] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[6] & 0xF);

        stream << Character::FromHexInt((guid.U8[7] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[7] & 0xF);

        stream << '-';

        stream << Character::FromHexInt((guid.U8[8] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[8] & 0xF);

        stream << Character::FromHexInt((guid.U8[9] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[9] & 0xF);

        stream << '-';

        stream << Character::FromHexInt((guid.U8[10] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[10] & 0xF);

        stream << Character::FromHexInt((guid.U8[11] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[11] & 0xF);

        stream << Character::FromHexInt((guid.U8[12] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[12] & 0xF);

        stream << Character::FromHexInt((guid.U8[13] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[13] & 0xF);

        stream << Character::FromHexInt((guid.U8[14] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[14] & 0xF);

        stream << Character::FromHexInt((guid.U8[15] & 0xF0) >> 4);
        stream << Character::FromHexInt(guid.U8[15] & 0xF);

        return stream;
    }


    std::string Guid::ToString() const noexcept {
        std::string result;
        result.resize(36);

        result[0] = Character::FromHexInt((U8[0] & 0xF0) >> 4);
        result[1] = Character::FromHexInt(U8[0] & 0xF);

        result[2] = Character::FromHexInt((U8[1] & 0xF0) >> 4);
        result[3] = Character::FromHexInt(U8[1] & 0xF);

        result[4] = Character::FromHexInt((U8[2] & 0xF0) >> 4);
        result[5] = Character::FromHexInt(U8[2] & 0xF);

        result[6] = Character::FromHexInt((U8[3] & 0xF0) >> 4);
        result[7] = Character::FromHexInt(U8[3] & 0xF);

        result[8] = '-';

        result[9] = Character::FromHexInt((U8[4] & 0xF0) >> 4);
        result[10] = Character::FromHexInt(U8[4] & 0xF);

        result[11] = Character::FromHexInt((U8[5] & 0xF0) >> 4);
        result[12] = Character::FromHexInt(U8[5] & 0xF);

        result[13] = '-';

        result[14] = Character::FromHexInt((U8[6] & 0xF0) >> 4);
        result[15] = Character::FromHexInt(U8[6] & 0xF);

        result[16] = Character::FromHexInt((U8[7] & 0xF0) >> 4);
        result[17] = Character::FromHexInt(U8[7] & 0xF);

        result[18] = '-';

        result[19] = Character::FromHexInt((U8[8] & 0xF0) >> 4);
        result[20] = Character::FromHexInt(U8[8] & 0xF);

        result[21] = Character::FromHexInt((U8[9] & 0xF0) >> 4);
        result[22] = Character::FromHexInt(U8[9] & 0xF);

        result[23] = '-';

        result[24] = Character::FromHexInt((U8[10] & 0xF0) >> 4);
        result[25] = Character::FromHexInt(U8[10] & 0xF);

        result[26] = Character::FromHexInt((U8[11] & 0xF0) >> 4);
        result[27] = Character::FromHexInt(U8[11] & 0xF);

        result[28] = Character::FromHexInt((U8[12] & 0xF0) >> 4);
        result[29] = Character::FromHexInt(U8[12] & 0xF);

        result[30] = Character::FromHexInt((U8[13] & 0xF0) >> 4);
        result[31] = Character::FromHexInt(U8[13] & 0xF);

        result[32] = Character::FromHexInt((U8[14] & 0xF0) >> 4);
        result[33] = Character::FromHexInt(U8[14] & 0xF);

        result[34] = Character::FromHexInt((U8[15] & 0xF0) >> 4);
        result[35] = Character::FromHexInt(U8[15] & 0xF);

        return result;
    }
}
