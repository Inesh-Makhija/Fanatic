workspace "Fanatic"
	architecture "x64"
	startproject "Vixen"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Fanatic/vendor/GLFW/include"
IncludeDir["Glad"] = "Fanatic/vendor/Glad/include"
IncludeDir["ImGui"] = "Fanatic/vendor/imgui"
IncludeDir["ImGuibackend"] = "Fanatic/vendor/imgui/backends"
IncludeDir["glm"] = "Fanatic/vendor/glm"
IncludeDir["stb_image"] = "Fanatic/vendor/stb_image"

include "Fanatic/vendor/GLFW"
include "Fanatic/vendor/Glad"
include "Fanatic/vendor/imgui"

project "Fanatic"
	location "Fanatic"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fncpch.h"
	pchsource "Fanatic/src/fncpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGuibackend}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
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
			"FNC_PLATFORM_WINDOWS",
			"FNC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FNC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FNC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FNC_DIST"
		runtime "Release"
		optimize "on"

project "Vixen"
	location "Vixen"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
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
		"Fanatic/vendor/spdlog/include",
		"Fanatic/src",
		"Fanatic/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Fanatic"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"FNC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FNC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FNC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FNC_DIST"
		runtime "Release"
		optimize "on"
