workspace "oatpp-book"
    configurations {"Debug", "Release"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "Full"

    filter { "action:gmake*" }
        location "./build-gmake"
        buildoptions {"-std=c++14"}

    filter "action:xcode"
        xcodebuildsettings {
            ["CLANG_CXX_LANGUAGE_STANDARD"] = "c++14";
        }

project "oatpp-book"
    kind "ConsoleApp"
    language "C++"

    includedirs {
        "external",
    }

    files {
        "src/**.cpp",
        "src/**.hpp",
    }

    libdirs {
        "external/oatpp/build"
    }

    links {
        "oatpp"
    }
