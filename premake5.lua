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
	include "NettEngine/vendor/glm"

group ""

project "NettEngine"
	location "NettEngine"
	kind "SharedLib"
	language "C++" 
	staticruntime "off"

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
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
		 "NE_PLATFORM_WINDOWS",
		 "NE_BUILD_DLL",
		 "GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
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
	staticruntime "off"

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
		"NettEngine/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"NettEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
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