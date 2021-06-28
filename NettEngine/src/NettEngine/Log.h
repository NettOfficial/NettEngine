#pragma once

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace NettEngine {

	class NETTENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};

}


//Core log macros
#define NE_CORE_TRACE(...)      ::NettEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NE_CORE_INFO(...)       ::NettEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NE_CORE_WARN(...)       ::NettEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NE_CORE_ERROR(...)      ::NettEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
//#define NE_CORE_FATAL(...)      ::NettEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define NE_TRACE(...)      ::NettEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NE_INFO(...)       ::NettEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define NE_WARN(...)       ::NettEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NE_ERROR(...)      ::NettEngine::Log::GetClientLogger()->error(__VA_ARGS__)
//#define NE_FATAL(...)      ::NettEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)