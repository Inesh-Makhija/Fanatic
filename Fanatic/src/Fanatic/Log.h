#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Fanatic {

	class FANATIC_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core Log Macros
#define FNC_CORE_TRACE(...)    ::Fanatic::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FNC_CORE_INFO(...)     ::Fanatic::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FNC_CORE_WARN(...)     ::Fanatic::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FNC_CORE_ERROR(...)    ::Fanatic::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FNC_CORE_FATAL(...)    ::Fanatic::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros
#define FNC_TRACE(...)         ::Fanatic::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FNC_INFO(...)          ::Fanatic::Log::GetClientLogger()->info(__VA_ARGS__)
#define FNC_WARN(...)          ::Fanatic::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FNC_ERROR(...)         ::Fanatic::Log::GetClientLogger()->error(__VA_ARGS__)
#define FNC_FATAL(...)         ::Fanatic::Log::GetClientLogger()->fatal(__VA_ARGS__)