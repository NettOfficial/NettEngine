#pragma once

#ifdef NE_PLATFORM_WINDOWS
	#ifdef NE_BUILD_DLL
		#define NETTENGINE_API __declspec(dllexport)
	#else
		#define NETTENGINE_API __declspec(dllimport)
	#endif
#else
	#error NettEngine only supports Windows
#endif

#ifdef HZ_ENABLE_ASSERTS
	#define NE_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NE_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NE_ASSERT(x, ...)
	#define NE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)