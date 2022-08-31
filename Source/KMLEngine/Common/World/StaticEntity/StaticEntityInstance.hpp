//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: StaticEntityInstance.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_WORLD_STATICENTITY_STATICENTITYINSTANCE_HPP
#define KMLENGINE_COMMON_WORLD_STATICENTITY_STATICENTITYINSTANCE_HPP

#pragma once

#include "StaticEntityType.hpp"
#include <glm/glm.hpp>

namespace KMLEngine {
    struct StaticEntityInstance final {
    private:
        u32 m_data;
    public:
        glm::vec3 Position;
        glm::quat Rotation;

        explicit StaticEntityInstance(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
                             const glm::quat& rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f),
                             StaticEntityType type = StaticEntityType::None,
                             u32 metaData = 0) noexcept :
                             Position(position),
                             Rotation(rotation) {
            SetType(type);
            SetMetaData(metaData);
        }

        KML_FORCEINLINE void SetType(StaticEntityType type) noexcept {
            m_data &= 0x1FFFu;
            m_data |= static_cast<u32>(type) << 13u;
        }

        KML_FORCEINLINE void SetMetaData(u32 metaData) noexcept {
            m_data &= 0xFFFFE000u;
            m_data |= metaData;
        }

        [[nodiscard]] StaticEntityType GetType() const noexcept {
            return static_cast<StaticEntityType>(m_data & 0xFFFFE000u >> 13u);
        }

        [[nodiscard]] u32 GetMetaData() const noexcept {
            return m_data & 0x1FFFu;
        }

        [[nodiscard]] KML_FORCEINLINE bool operator ==(const StaticEntityInstance& other) const noexcept  {
            return Position == other.Position && Rotation == other.Rotation && m_data == other.m_data;
        }

        [[nodiscard]] KML_FORCEINLINE bool operator !=(const StaticEntityInstance& other) const noexcept {
            return Position != other.Position || Rotation != other.Rotation || m_data != other.m_data;
        }
    };
}

#endif //KMLENGINE_COMMON_WORLD_STATICENTITY_STATICENTITYINSTANCE_HPP