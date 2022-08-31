//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: DefaultMemoryResource.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_MEMORY_DEFAULTMEMORYRESOURCE_HPP
#define KMLENGINE_COMMON_CORE_MEMORY_DEFAULTMEMORYRESOURCE_HPP

#pragma once

#include "../../Util/Traits/Uncopyable.hpp"
#include "../../Util/Traits/Singleton.hpp"
#include <memory_resource>

namespace KMLEngine {
    class DefaultMemoryResource final : public std::pmr::memory_resource, public Uncopyable, public Singleton<DefaultMemoryResource> {
    private:
        [[nodiscard]] void* do_allocate(size_t bytes, size_t alignment) final {
            return std::pmr::new_delete_resource()->allocate(bytes, alignment);
        }

        void do_deallocate(void* p, size_t bytes, size_t alignment) final {
            std::pmr::new_delete_resource()->deallocate(p, bytes, alignment);
        }

        [[nodiscard]] bool do_is_equal(const memory_resource& other) const noexcept final {
            return std::pmr::new_delete_resource()->is_equal(other);
        }
    public:
        DefaultMemoryResource();
        ~DefaultMemoryResource();
    };
}

#endif //KMLENGINE_COMMON_CORE_MEMORY_DEFAULTMEMORYRESOURCE_HPP