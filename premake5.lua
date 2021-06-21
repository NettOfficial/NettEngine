workspace "NettEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	-- Include directiroes relative to root folder (Solution directory)
	IncludeDir = {}
	IncludeDir["GLFW"] = "NettEngine/vendor/GLFW/include"

	include "NettEngine/vendor/GLFW"

project "NettEngine"
	location "NettEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nepch.h"
	pchsource "NettEngine/src/nepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
		 "NE_PLATFORM_WINDOWS;",
		 "NE_BUILD_DLL;",
		 "NETTENGINE_API;",
		 "_WINDLL;"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "NE_DEBUG"
			symbols "On"
			
		filter "configurations:Release"
			defines "NE_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "NE_DIST"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"NettEngine/vendor/spdlog/include",
		"NettEngine/src"
	}

	links
	{
		"NettEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NE_PLATFORM_WINDOWS;",
			"NE_BUILD_DLL;",
			"NETTENGINE_API;",
			"_WINDLL;"
		}

		filter "configurations:Debug"
			defines "NE_DEBUG"
			symbols "On"
			
		filter "configurations:Release"
			defines "NE_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "NE_DIST"
			optimize "On"