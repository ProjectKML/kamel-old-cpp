//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageLocation.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_PACKAGE_PACKAGELOCATION_HPP
#define KMLENGINE_COMMON_CORE_PACKAGE_PACKAGELOCATION_HPP

#pragma once

#include "../../Util/HashCode.hpp"
#include <fmt/format.h>
#include <vector>
#include <memory_resource>

namespace KMLEngine {
	class PackageLocation {
	private:
		std::string m_fileName, m_entryName;
	public:
		PackageLocation() = default;
		PackageLocation(std::string fileName, std::string entryName) noexcept : m_fileName(std::move(fileName)), m_entryName(std::move(entryName)) {}
		PackageLocation(const std::string_view& fullName);

		PackageLocation GetPrefixed(const std::string_view& prefix) const;
		PackageLocation GetSuffixed(const std::string_view& suffix) const;
		PackageLocation GetRelativeToCurrent(const std::string_view& relativePath) const;

		bool Exists() const noexcept;
		
		void GetEntry(std::vector<byte>& buffer) const;
		void GetEntry(std::pmr::vector<byte>& buffer, std::pmr::memory_resource& memoryResource) const;
		void GetEntry(std::string& buffer) const;
		void GetEntry(std::pmr::string& buffer, std::pmr::memory_resource& memoryResource) const;

        void GetEntry(byte*& data, usize& size, std::pmr::memory_resource& memoryResources) const;
		
		template<typename OStream>
		KML_FORCEINLINE friend OStream& operator <<(OStream& stream, const PackageLocation& location) noexcept {
			return stream << location.m_fileName << ':' << location.m_fileName;
		}

		[[nodiscard]] std::string ToString() const noexcept {
			return fmt::format("{}:{}", m_fileName, m_entryName);
		}

		[[nodiscard]] KML_FORCEINLINE const std::string& GetFileName() const noexcept { return m_fileName; }
		[[nodiscard]] KML_FORCEINLINE const std::string& GetEntryName() const noexcept { return m_entryName; }

		[[nodiscard]] KML_FORCEINLINE operator bool () const noexcept { return m_fileName.size() > 0 && m_entryName.size() > 0; }
		[[nodiscard]] KML_FORCEINLINE bool operator ==(const PackageLocation& location) const noexcept { return m_fileName == location.m_fileName && m_entryName == location.m_entryName; }
		[[nodiscard]] KML_FORCEINLINE bool operator !=(const PackageLocation& location) const noexcept { return m_fileName != location.m_fileName || m_entryName != location.m_entryName; }
	};
}

#endif //KMLENGINE_COMMON_CORE_PACKAGE_PACKAGELOCATION_HPP
