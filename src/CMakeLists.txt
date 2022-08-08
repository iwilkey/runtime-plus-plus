cmake_minimum_required(VERSION 3.10)

project(runtime++)

# for filesystem functionality from C++17
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

if (WIN32)
    set(WHERE-IS-SDL "...")
    set(WHERE-IS-SDL-HEADERS "...")
    set(WHERE-IS-GLAD "...")
    set(WHERE-IS-GLAD-HEADERS "...")
endif()

if (UNIX)
    set(WHERE-IS-GLAD "/Users/ianwilkey/Desktop/runtime++/lib/glad/src/glad.c")
    set(WHERE-IS-GLAD-HEADERS "/Users/ianwilkey/Desktop/runtime++/lib/glad/include")

    if (APPLE)
        set(WHERE-IS-SDL "${CMAKE_SOURCE_DIR}/lib")
        set(WHERE-IS-SDL-HEADERS "${CMAKE_SOURCE_DIR}/lib/SDL2.framework/Versions/Current/Headers")
    endif()

    if(NOT APPLE)
        find_package(SDL2 REQUIRED)
        include_directories(${SDL2_INCLUDE_DIRS})
    endif()
endif()

#message(${WHERE-IS-SDL})
#message(${WHERE-IS-SDL-HEADERS})
#message(${WHERE-IS-GLAD})
#message(${WHERE-IS-GLAD-HEADERS})

if (WIN32 OR APPLE)
    find_library(SDL SDL2 PATHS ${WHERE-IS-SDL})
    if (WIN32)
        find_library(SDLmain SDL2main PATHS ${WHERE-IS-SDL})
    endif()

    include_directories(
        "${WHERE-IS-SDL-HEADERS}"
    )
endif()

add_library("glad" ${WHERE-IS-GLAD})
include_directories(
        "${WHERE-IS-GLAD-HEADERS}"
    )

# your sources
set(sources
    utils/RuntimeUtilities.h
    utils/RuntimeUtilities.cc
    core/RuntimeWindow.h
    core/RuntimeWindow.cc
    process/RProcess.h
    process/RProcess.cc
    process/RuntimeProcessManager.h
    process/RuntimeProcessManager.cc
    core/RuntimeEvents.h
    core/RuntimeEvents.cc
    gfx/RuntimeGUI.h
    gfx/RuntimeGUI.cc
    gfx/RuntimeRenderer.h
    gfx/RuntimeRenderer.cc
    state/RuntimeEngineState.h
    state/RuntimeEngineState.cc
    state/implementation/DebugState.h
    state/implementation/DebugState.cc
    core/RuntimeCore.h
    core/RuntimeCore.cc
    ../lib/imgui/imconfig.h
    ../lib/imgui/imgui.cpp
    ../lib/imgui/imgui.h
    ../lib/imgui/imgui_demo.cpp
    ../lib/imgui/imgui_draw.cpp
    ../lib/imgui/imgui_internal.h
    ../lib/imgui/imgui_widgets.cpp
    ../lib/imgui/imstb_rectpack.h
    ../lib/imgui/imstb_textedit.h
    ../lib/imgui/imstb_truetype.h
    ../lib/imgui/imgui_impl_opengl3.cpp
    ../lib/imgui/imgui_impl_opengl3.h
    ../lib/imgui/imgui_impl_sdl.cpp
    ../lib/imgui/imgui_impl_sdl.h
)

if (WIN32)
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${sources})
    target_link_libraries(${CMAKE_PROJECT_NAME}
        "glad"
        ${SDL}
        ${SDLmain}
        ${OPENGL_gl_LIBRARY}
        )
else()
    add_executable(${CMAKE_PROJECT_NAME} ${sources})
    target_link_libraries(${CMAKE_PROJECT_NAME}
            "glad"
            ${OPENGL_gl_LIBRARY}
            )
    if (APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
            ${SDL}
            )
    endif()
    if (UNIX AND NOT APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
            ${SDL2_LIBRARIES}
            ${CMAKE_DL_LIBS}
            )
    endif()
endif()
