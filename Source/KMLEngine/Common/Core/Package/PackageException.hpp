//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageException.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_PACKAGE_PACKAGEEXCEPTION_HPP
#define KMLENGINE_COMMON_CORE_PACKAGE_PACKAGEEXCEPTION_HPP

#pragma once

#include <stdexcept>

namespace KMLEngine {
	class PackageException final : public std::runtime_error {
	public:
		explicit PackageException(const std::string& message) noexcept : std::runtime_error(message) {}
	};
}

#endif //KMLENGINE_COMMON_CORE_PACKAGE_PACKAGEEXCEPTION_HPP
