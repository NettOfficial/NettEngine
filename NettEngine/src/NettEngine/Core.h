#pragma once

#include <memory>

#ifdef NE_PLATFORM_WINDOWS
#if NE_DYNAMIC_LINK
	#ifdef NE_BUILD_DLL
		#define NETTENGINE_API __declspec(dllexport)
	#else
		#define NETTENGINE_API __declspec(dllimport)
	#endif
#else
	#define NETTENGINE_API
#endif
#else 
	#error NettEngine only supports Windows
#endif

#ifdef NE_DEBUG
	#define NE_ENABLE_ASSERTS
#endif

#ifdef NE_ENABLE_ASSERTS
	#define NE_ASSERT(x, ...) { if(!(x)) { NE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NE_CORE_ASSERT(x, ...) { if(!(x)) { NE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NE_ASSERT(x, ...)
	#define NE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace NettEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}