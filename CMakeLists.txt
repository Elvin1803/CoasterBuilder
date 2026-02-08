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
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui
    )

target_precompile_headers(CoasterBuilder PRIVATE src/pch.h)

# Link with GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)
target_link_libraries(CoasterBuilder PRIVATE glfw)

# Link with GLAD
add_subdirectory(libs/glad)
target_link_libraries(CoasterBuilder PRIVATE glad)

# Link with GLM
add_subdirectory(libs/glm)
target_link_libraries(CoasterBuilder PRIVATE glm)

# Compile IMGUI and link with it
file(GLOB IMGUI_SOURCES "libs/imgui/imgui*.cpp"
                        "libs/imgui/imgui*.h"
                        "libs/imgui/backends/imgui_impl_glfw.cpp"
                        "libs/imgui/backends/imgui_impl_glfw.h"
                        "libs/imgui/backends/imgui_impl_opengl3.cpp"
                        "libs/imgui/backends/imgui_impl_opengl3.h")
add_library(imgui_lib STATIC ${IMGUI_SOURCES})
target_include_directories(imgui_lib PRIVATE libs/imgui)
target_link_libraries(imgui_lib PRIVATE glfw)
target_link_libraries(CoasterBuilder PRIVATE imgui_lib)

# Define DEBUG symbol for Debug builds
target_compile_definitions(CoasterBuilder PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)

# Define Release symbol for Debug builds
target_compile_definitions(CoasterBuilder PRIVATE
    $<$<CONFIG:Release>:RELEASE>
)

if(MSVC)
  target_compile_options(CoasterBuilder PRIVATE /W4 /WX)
else()
  target_compile_options(CoasterBuilder PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

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
