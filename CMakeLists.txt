cmake_minimum_required(VERSION 3.16)
project(CoasterBuilder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(CoasterBuilder ${SOURCES})

target_include_directories(CoasterBuilder PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

target_precompile_headers(CoasterBuilder PRIVATE src/pch.h)

# Link with GLFW
add_subdirectory(libs/glfw)
target_link_libraries(CoasterBuilder PRIVATE glfw)

# Define DEBUG symbol for Debug builds
target_compile_definitions(CoasterBuilder PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

# Define Release symbol for Debug builds
target_compile_definitions(CoasterBuilder PRIVATE
    $<$<CONFIG:Release>:RELEASE>
)

if (WIN32)
    target_link_libraries(CoasterBuilder PRIVATE opengl32)

    if (MINGW)
        target_link_options(CoasterBuilder PRIVATE
            $<$<CONFIG:Release>:-mwindows>
        )
    elseif (MSVC)
        target_link_options(CoasterBuilder PRIVATE
            $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup>
        )
    endif()
endif()
