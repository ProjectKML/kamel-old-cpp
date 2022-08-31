//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: PackageManager.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_PACKAGE_PACKAGEMANAGER_HPP
#define KMLENGINE_COMMON_CORE_PACKAGE_PACKAGEMANAGER_HPP

#pragma once

#include "../../Util/Traits/Disposable.hpp"
#include "../../Util/Traits/Singleton.hpp"
#include "../../Util/STL/flat_hash_map.hpp"
#include <string_view>
#include <mutex>

namespace KMLEngine {
	class PackageFile;
	class PackageManager final : public Uncopyable, public Singleton<PackageManager> {
	private:
		kml_stl::flat_hash_map<std::string_view, PackageFile*> m_packages;
		std::mutex m_mutex;

	public:
		PackageManager();
		~PackageManager();

		[[nodiscard]] PackageFile* Get(const std::string_view& name);
	};
}

#endif //KMLENGINE_COMMON_CORE_PACKAGE_PACKAGEMANAGER_HPP
