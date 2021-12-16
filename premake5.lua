-- Kraken Premake Build System
workspace "Kraken"
    architecture "x64"
    startproject "Sandbox"
    
    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
    kind "StaticLib" -- Static Library
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    pchheader "kepch.h"
    pchsource "Kraken/src/kepch.cpp"

    -- All source (.cpp) and header (.h) files
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    -- Exclude platform folders, not all platforms need all of them
    removefiles { "%{prj.name}/src/Platform/**"}

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
        "imgui"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows" -- WINDOWS
        -- Windows specific platform files
        files {
            "%{prj.name}/src/Platform/Windows/**.h",
            "%{prj.name}/src/Platform/Windows/**.cpp"
        }

        defines {
            "KE_PLATFORM_WINDOWS",
            "KE_BUILD_DLL"
        }

        postbuildcommands { -- Copy Kraken.dll to Sandbox enviornment
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }
    
    filter "system:linux" -- LINUX
        pic "On"   

        -- Linux specific platform files
        files {
            "%{prj.name}/src/Platform/Linux/**.h",
            "%{prj.name}/src/Platform/Linux/**.cpp"
        }

        links {
            "GLFW",
            "Xrandr",
            "Xi",
            "GLEW",
            "GLU",
            "GL",
            "X11"
        }

        defines {
            "KE_PLATFORM_LINUX",
            "KE_BUILD_DLL"
        }

        -- 'premake5 clean' command in linux, cleans solution binaries
        newaction {
            trigger = "clean",
            description = "clean build",
            execute = function ()
                print("Cleaning build...")
                os.rmdir("./bin")
                os.rmdir("./int")
                os.rmdir("./Kraken/vendor/GLFW/bin") -- this method seems hacky, might change in future
                os.rmdir("./Kraken/vendor/GLFW/int")
                os.rmdir("./Kraken/vendor/imgui/bin") 
                os.rmdir("./Kraken/vendor/imgui/int")
                os.rmdir("./Kraken/vendor/glad/bin")
                os.rmdir("./Kraken/vendor/glad/int")
                os.rmdir("./Sandbox/obj")
                print("Done cleaning build!")
            end    
        }

    filter "configurations:Debug"
        defines "KE_DEBUG"
        runtime "Debug"
        symbols "on"
    filter {"system:windows", "configurations:Debug"}
        buildoptions "/MTd"   

    filter "configurations:Release"
        defines "KE_RELEASE"
        runtime "Release"
        optimize "on"
    filter {"system:windows", "configurations:Release"}
        buildoptions "/MD"    

    filter "configurations:Dist"
        defines "KE_DIST"
        runtime "Release"
        optimize "on"
    filter {"system:windows", "configurations:Dist"}
        buildoptions "/MD"   


project "Sandbox"
    location "Sandbox" -- Sandbox subfolder
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"
    systemversion "latest"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Kraken/src",    
        "Kraken/vendor",
        "Kraken/vendor/GLFW/include",
        "Kraken/vendor/spdlog/include",
        "%{IncludeDir.glm}"
    }

    links {
        "Kraken"
    }

    filter "system:windows" -- WINDOWS        
        defines {
            "KE_PLATFORM_WINDOWS"
        }

    filter "system:linux" -- LINUX
        pic "On"
        
        links {
            "GLFW",
            "Glad",
            "imgui",
            "Xrandr",
            "Xi",
            "GLU",
            "GL",
            "X11",
            "dl",
            "pthread",
            --"stdc++fs"
        }

        defines {
            "KE_PLATFORM_LINUX"
        }     

    filter "configurations:Debug"
        defines "KE_DEBUG"
        runtime "Debug"
        symbols "on"
    filter { "system:windows", "configurations:Debug" }
        buildoptions "/MTd"

    filter "configurations:Release"
        defines "KE_RELEASE"
        runtime "Release"
        optimize "on"
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MD"

    filter "configurations:Dist"
        defines "KE_DIST"
        runtime "Release"
        optimize "on"
