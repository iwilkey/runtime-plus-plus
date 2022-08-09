# Kill runtime: ps -A | grep runtime++ | awk '{print $1}' | sudo xargs kill -9 $1
cmake_minimum_required(VERSION 3.10)

project(runtime++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake/;${CMAKE_MODULE_PATH}")

# Group local Runtime++ sources...
set(runtimesources
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
)

# Group local Dear Imgui sources...
set(imguisources
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

# Group local SOIL sources...
set(soilsources
    ../lib/SOIL/src/image_DXT.c
    ../lib/SOIL/src/image_DXT.h
    ../lib/SOIL/src/image_helper.c
    ../lib/SOIL/src/image_helper.h
    ../lib/SOIL/src/SOIL.c
    ../lib/SOIL/src/SOIL.h
    ../lib/SOIL/src/stb_image_aug.c
    ../lib/SOIL/src/stb_image_aug.h
    ../lib/SOIL/src/stbi_DDS_aug_c.h
    ../lib/SOIL/src/stbi_DDS_aug.h
)

# All OS compatable instructions...
# Locate OpenGL...
find_package(OpenGL REQUIRED)

# Locate GLAD and add include dirs...
set(WHERE-IS-GLAD "${CMAKE_SOURCE_DIR}/../lib/glad/src/glad.c")
set(WHERE-IS-GLAD-HEADERS "${CMAKE_SOURCE_DIR}/../lib/glad/include")
add_library("glad" ${WHERE-IS-GLAD})
include_directories(
    "${WHERE-IS-GLAD-HEADERS}"
)

# OS specific instructions...
if(UNIX)

    # Locate SDL and add include dirs...
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})

    # Executable compilation and linking...
    add_executable(${CMAKE_PROJECT_NAME} ${imguisources} ${soilsources} ${runtimesources})

    # Linking GLAD and OpenGL...
    target_link_libraries(${CMAKE_PROJECT_NAME}
        "glad"
        ${OPENGL_gl_LIBRARY}
    )
    # Linking SDL...
    if(APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
            ${SDL2_LIBRARY}
        )
    endif()
    if(UNIX AND NOT APPLE)
        target_link_libraries(${CMAKE_PROJECT_NAME}
            ${SDL2_LIBRARIES}
            ${CMAKE_DL_LIBS}
        )
    endif()

endif()

# Windows machines (UNFINISHED)...
if(WIN32)

    # Locate SDL library...
    set(WHERE-IS-SDL "")
    set(WHERE-IS-SDL-HEADERS "")
    set(WHERE-IS-GLAD "")
    set(WHERE-IS-GLAD-HEADERS "")
    find_library(SDLmain SDL2main PATHS ${WHERE-IS-SDL})
    include_directories(
        "${WHERE-IS-SDL-HEADERS}"
    )

    # Executable compilation and linking...
    # Runtime++...
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${imguisources} ${soilsources} ${runtimesources})
    target_link_libraries(${CMAKE_PROJECT_NAME}
        "glad"
        ${SDL}
        ${SDLmain}
        ${OPENGL_gl_LIBRARY}
    )

endif()
