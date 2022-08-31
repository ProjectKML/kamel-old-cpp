//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: ConfigParser.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_UTIL_CONFIG_CONFIGPARSER_HPP
#define KMLENGINE_COMMON_UTIL_CONFIG_CONFIGPARSER_HPP

#pragma once

#include "ConfigUtils.hpp"
#include "../../Core/Package/PackageLocation.hpp"
#include <spdlog/spdlog.h>
#include <string>
#include <fstream>
#include <filesystem>

namespace KMLEngine::ConfigParser {
    template<typename T>
    static void SerializeToFile(const T& config) noexcept {
        try {
            const auto path = std::filesystem::path("Configs");
            if(!std::filesystem::exists(path)) std::filesystem::create_directory(path);

            const auto filePath = path / (std::string(T::GetName()) + ".toml");

            toml::table root;
            config.Serialize(root);

            std::ofstream stream(filePath);
            if(!stream.good()) throw std::runtime_error("Failed to open file");
            
            stream << root;
            stream.close();
        } catch(const std::exception& exception) {
            spdlog::warn("Failed to serialize config {}: {}", T::GetName(), exception.what());
        }
    }

    template<typename T>
    static T DeserializeFromFile() noexcept(ConfigUtils::HasRestoreDefaults<T>::Value) {
        T config;
        try {
            const auto path = std::filesystem::path("Configs") / (std::string(T::GetName()) + ".toml");

            const auto root = toml::parse_file(path.string());
            config.Deserialize(root);
        } catch(const std::exception& exception) {
            if constexpr(ConfigUtils::HasRestoreDefaults<T>::Value) {
                config.RestoreDefaults();

                spdlog::warn("Failed to deserialize config {}: {}", T::GetName(), exception.what());
            }
            else throw;
        }

        return config;
    }

    template<typename T>
    static T DeserializeFromPackage(const PackageLocation& location) noexcept(ConfigUtils::HasRestoreDefaults<T>::Value) {
        T config;
        try {
            std::string buffer;
            location.GetEntry(buffer);

            const auto root = toml::parse(buffer);
            config.Deserialize(root);
        } catch(const std::exception& exception) {
            if constexpr(ConfigUtils::HasRestoreDefaults<T>::Value) {
                config.RestoreDefaults();

                spdlog::warn("Failed to deserialize config from location {} : {}", location, exception.what());
            }
            else throw;
        }

        return config;
    }
}

#endif //KMLENGINE_COMMON_UTIL_CONFIG_CONFIGPARSER_HPP
