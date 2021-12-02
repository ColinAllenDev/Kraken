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

project "Kraken"
    location "Kraken" -- Engine subfolder
    kind "SharedLib" -- Dynamic Library
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    pchheader "krpch.h"
    pchsource "Kraken/src/krpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs {
	    "%{prj.name}/src",    
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows" -- WINDOWS
        cppdialect "C++17"
        staticruntime "On" -- Link runtime libraries statically
        systemversion "latest" -- Windows SDK

        defines {
            "KR_PLATFORM_WINDOWS",
            "KR_BUILD_DLL"
        }

        postbuildcommands { -- Copy Kraken.dll to Sandbox enviornment
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }
    
    filter "configurations:Debug"
        defines "KR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "KR_DIST"
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
        "Kraken/vendor/spdlog/include",
        "Kraken/src"
    }

    links {
        "Kraken"
    }

    filter "system:windows" -- WINDOWS
        cppdialect "C++17"
        staticruntime "On" -- Link runtime libraries statically
        systemversion "latest" -- Windows SDK

    defines {
        "KR_PLATFORM_WINDOWS"
    }

    filter "configurations:Debug"
        defines "KR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "KR_DIST"
        optimize "On"
