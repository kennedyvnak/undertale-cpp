-- Include conan gennerate script
include("conanbuildinfo.premake.lua")
imgui_bindings_path = conan_rootpath_imgui .. "/res/bindings"
imgui_bindings_files = { imgui_bindings_path .. "/imgui_impl_glfw.*", imgui_bindings_path .. "/imgui_impl_opengl3.*" }

-- Main Workspace
workspace "UndertaleCpp"
    -- Import conan gennerate config
    conan_basic_setup()

    -- Project
    project "UnderC64"
        kind "ConsoleApp"
        language "C++"
        targetdir "bin/%{cfg.buildcfg}"
		objdir "bin/%{cfg.buildcfg}/obj/"
		location "src"
        debugdir "app"

        defines { "GLFW_INCLUDE_NONE", "GLEW_STATIC", "STB_IMAGE_IMPLEMENTATION" }
        includedirs { "src", imgui_bindings_path }
        linkoptions { conan_exelinkflags }

        files { "src/**.h", "src/**.cpp", imgui_bindings_files, conan_rootpath_stb .."/include/stb_image.h", "res/**" }

        filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

		filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"