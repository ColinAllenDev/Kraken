-- Kraken Premake Build System
workspace "Kraken"
    architecture "x64"
    startproject "Sandbox"
    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- "Debug-Windows-x64"

-- Include directories relative to root (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Kraken/vendor/GLFW/include"
IncludeDir["glad"] = "Kraken/vendor/glad/include"
IncludeDir["ImGui"] = "Kraken/vendor/imgui/"
IncludeDir["glm"] = "Kraken/vendor/glm"

include "Kraken/vendor/GLFW"
include "Kraken/vendor/glad"
include "Kraken/vendor/imgui"

project "Kraken"
    location "Kraken" -- Engine subfolder
    kind "SharedLib" -- Dynamic Library
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    pchheader "kepch.h"
    pchsource "Kraken/src/kepch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs {
	    "%{prj.name}/src",    
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links {
        "GLFW",
        "glad",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows" -- WINDOWS
        cppdialect "C++17"
        staticruntime "On" -- Link runtime libraries statically
        systemversion "latest" -- Windows SDK

        defines {
            "KE_PLATFORM_WINDOWS",
            "KE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands { -- Copy Kraken.dll to Sandbox enviornment
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }
    
    filter "configurations:Debug"
        defines "KE_DEBUG"
        buildoptions "/MDd" -- multithreaded dll
        symbols "On"

    filter "configurations:Release"
        defines "KE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "KE_DIST"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox" -- Sandbox subfolder
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Kraken/src",    
        "Kraken/vendor/spdlog/include",
        "%{IncludeDir.glm}"
    }

    links {
        "Kraken"
    }

    filter "system:windows" -- WINDOWS
        cppdialect "C++17"
        staticruntime "On" -- Link runtime libraries statically
        systemversion "latest" -- Windows SDK

    defines {
        "KE_PLATFORM_WINDOWS"
    }

    filter "configurations:Debug"
        defines "KE_DEBUG"
        buildoptions "/MDd" -- multithreaded dll
        symbols "On"

    filter "configurations:Release"
        defines "KE_RELEASE"
        buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines "KE_DIST"
        buildoptions "/MD"
        optimize "On"
