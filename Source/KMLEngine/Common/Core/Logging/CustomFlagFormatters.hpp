//------------------------------------------------------------
// This file is part of KMLEngine by zmarlon & BeastLe9enD
// File name: CustomFlagFormatters.hpp
//------------------------------------------------------------

#ifndef KMLENGINE_COMMON_CORE_LOGGING_CUSTOMFLAGFORMATTERS_HPP
#define KMLENGINE_COMMON_CORE_LOGGING_CUSTOMFLAGFORMATTERS_HPP

#pragma once

#include <spdlog/pattern_formatter.h>
#include <array>

namespace KMLEngine {
	class LogLevelFlagFormatter final : public spdlog::custom_flag_formatter {
	private:
		static std::string_view GetLevelName(spdlog::level::level_enum level) noexcept {
			using namespace std::string_view_literals;
			static constexpr std::array names = { "TRACE"sv, "DEBUG"sv, "INFO"sv, "WARN"sv, "ERR"sv, "CRITICAL"sv, "OFF"sv };
			return names[level];
		}
	public:
		void format(const spdlog::details::log_msg& message, const std::tm&, spdlog::memory_buf_t& buffer) final {
			const auto& name = GetLevelName(message.level);
			buffer.append(name.data(), name.data() + name.size());
		}

		[[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const final {
			return spdlog::details::make_unique<LogLevelFlagFormatter>();
		}
	};

	class LogThreadNameFormatter final : public spdlog::custom_flag_formatter {
	public:
		void format(const spdlog::details::log_msg& message, const std::tm&, spdlog::memory_buf_t& buffer) final;

		[[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const final {
			return spdlog::details::make_unique<LogThreadNameFormatter>();
		}
	};
}

#endif //KMLENGINE_COMMON_CORE_LOGGING_CUSTOMFLAGFORMATTERS_HPP