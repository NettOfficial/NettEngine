#pragma once

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif

#ifdef NE_PLATFORM_WINDOWS
	#ifdef NE_BUILD_DLL
		#define NETTENGINE_API __declspec(dllexport)
	#else
		#define NETTENGINE_API __declspec(dllimport)
	#endif
#else
	#error NettEngine only supports Windows
#endif
