workspace "NettEngine"
	architecture "x64"
	startproject "Sandbox"

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
	IncludeDir["Glad"] = "NettEngine/vendor/Glad/include"
	IncludeDir["Imgui"] = "NettEngine/vendor/imgui"
	IncludeDir["glm"] = "NettEngine/vendor/glm"

group "Dependencies"
	include "NettEngine/vendor/GLFW"
	include "NettEngine/vendor/Glad"
	include "NettEngine/vendor/imgui"

group ""

project "NettEngine"
	location "NettEngine"
	kind "StaticLib"
	language "C++" 
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "nepch.h"
	pchsource "NettEngine/src/nepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NE_PLATFORM_WINDOWS",
			"NE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		filter "configurations:Debug"
			defines "NE_DEBUG"
			runtime "Debug"
			symbols "On"
			
		filter "configurations:Release"
			defines "NE_RELEASE"
			runtime "Release"
			optimize "On"

		filter "configurations:Dist"
			defines "NE_DIST"
			runtime "Release"
			optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"NettEngine/vendor/",
		"NettEngine/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"NettEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NE_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "NE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "NE_DIST"
		runtime "Release"
		optimize "On"