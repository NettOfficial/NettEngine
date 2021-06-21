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

#define BIT(x) (1 << x)