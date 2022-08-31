//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageStream.cpp
//------------------------------------------------------------

#include "PackageStream.hpp"
#include "PackageLocation.hpp"
#include "../../../Platform/PlatformMemory.hpp"

namespace KMLEngine {
    PackageStream::PackageStream(const PackageLocation& location, std::pmr::memory_resource& memoryResource) {
        location.GetEntry(m_buffer, memoryResource);
    }

    usize PackageStream::Fread(void* buffer, usize size) noexcept {
        if(!buffer || !size) return 0;

        const auto remainingSize = m_buffer.size() - m_offset;
        if(size > remainingSize) size = remainingSize;

        if(!size) return 0;
        PlatformMemory::Copy(buffer, m_buffer.data() + m_offset, size);

        m_offset += size;
        return size;
    }

    i32 PackageStream::Fseek(usize size, SeekMode seekMode) noexcept {
        switch(seekMode) {
            case SeekMode::Begin:
                if(size > m_buffer.size()) return -1;
                m_offset = size;
                break;
            case SeekMode::Current:
                if(size + m_offset > m_buffer.size()) return -1;
                m_offset += size;
                break;
            case SeekMode::End:
                if(size > m_buffer.size()) return -1;
                m_offset = m_buffer.size() - size;
                break;
            default:
                return -1;
        }

        return 0;
    }
}