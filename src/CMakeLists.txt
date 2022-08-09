# Kill runtime: ps -A | grep runtime++ | awk '{print $1}' | sudo xargs kill -9 $1
cmake_minimum_required(VERSION 3.12)

project(runtime-project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake/;${CMAKE_MODULE_PATH}")

# Group local Runtime++ sources...
set(runtimesources
    ${CMAKE_SOURCE_DIR}/utils/RuntimeUtilities.h
    ${CMAKE_SOURCE_DIR}/utils/RuntimeUtilities.cc
    ${CMAKE_SOURCE_DIR}/core/RuntimeWindow.h
    ${CMAKE_SOURCE_DIR}/core/RuntimeWindow.cc
    ${CMAKE_SOURCE_DIR}/process/RProcess.h
    ${CMAKE_SOURCE_DIR}/process/RProcess.cc
    ${CMAKE_SOURCE_DIR}/process/RuntimeProcessManager.h
    ${CMAKE_SOURCE_DIR}/process/RuntimeProcessManager.cc
    ${CMAKE_SOURCE_DIR}/core/RuntimeEvents.h
    ${CMAKE_SOURCE_DIR}/core/RuntimeEvents.cc
    ${CMAKE_SOURCE_DIR}/gfx/RuntimeGUI.h
    ${CMAKE_SOURCE_DIR}/gfx/RuntimeGUI.cc
    ${CMAKE_SOURCE_DIR}/gfx/RuntimeRenderer.h
    ${CMAKE_SOURCE_DIR}/gfx/RuntimeRenderer.cc
    ${CMAKE_SOURCE_DIR}/state/RuntimeEngineState.h
    ${CMAKE_SOURCE_DIR}/state/RuntimeEngineState.cc
    ${CMAKE_SOURCE_DIR}/core/RuntimeCore.h
    ${CMAKE_SOURCE_DIR}/core/RuntimeCore.cc
)

# Group local Dear Imgui sources...
set(imguisources
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imconfig.h
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui.h
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui_internal.h
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imstb_rectpack.h
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imstb_textedit.h
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imstb_truetype.h
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui_impl_opengl3.h
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui_impl_sdl.cpp
    ${CMAKE_SOURCE_DIR}/../lib/imgui/imgui_impl_sdl.h
)

# Group local SOIL sources...
set(soilsources
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/image_DXT.c
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/image_DXT.h
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/image_helper.c
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/image_helper.h
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/SOIL.c
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/SOIL.h
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/stb_image_aug.c
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/stb_image_aug.h
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/stbi_DDS_aug_c.h
    ${CMAKE_SOURCE_DIR}/../lib/SOIL/src/stbi_DDS_aug.h
)

# Group all custom project sources...
file(GLOB_RECURSE runtimeprojectsource CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/../project/*.c"
    "${CMAKE_SOURCE_DIR}/../project/*.C"
    "${CMAKE_SOURCE_DIR}/../project/*.c++"
    "${CMAKE_SOURCE_DIR}/../project/*.cc"
    "${CMAKE_SOURCE_DIR}/../project/*.cpp"
    "${CMAKE_SOURCE_DIR}/../project/*.cxx"
    "${CMAKE_SOURCE_DIR}/../project/*.cu"
    "${CMAKE_SOURCE_DIR}/../project/*.mpp"
    "${CMAKE_SOURCE_DIR}/../project/*.m"
    "${CMAKE_SOURCE_DIR}/../project/*.M"
    "${CMAKE_SOURCE_DIR}/../project/*.mm"
    "${CMAKE_SOURCE_DIR}/../project/*.ixx"
    "${CMAKE_SOURCE_DIR}/../project/*.cppm"
    "${CMAKE_SOURCE_DIR}/../project/*.h"
    "${CMAKE_SOURCE_DIR}/../project/*.hh"
    "${CMAKE_SOURCE_DIR}/../project/*.h++"
    "${CMAKE_SOURCE_DIR}/../project/*.hxx"
    "${CMAKE_SOURCE_DIR}/../project/*.in"
    "${CMAKE_SOURCE_DIR}/../project/*.txx"
    "${CMAKE_SOURCE_DIR}/../project/*.f"
    "${CMAKE_SOURCE_DIR}/../project/*.F"
    "${CMAKE_SOURCE_DIR}/../project/*.for"
    "${CMAKE_SOURCE_DIR}/../project/*.f77"
    "${CMAKE_SOURCE_DIR}/../project/*.f90"
    "${CMAKE_SOURCE_DIR}/../project/*.f95"
    "${CMAKE_SOURCE_DIR}/../project/*.f03"
    "${CMAKE_SOURCE_DIR}/../project/*.hip"
    "${CMAKE_SOURCE_DIR}/../project/*.ispc"
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
    add_executable(${CMAKE_PROJECT_NAME} ${imguisources} ${soilsources} ${runtimesources} ${runtimeprojectsource})

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
    set(WHERE-IS-SDL "${CMAKE_SOURCE_DIR}/../lib/native-windows/x86_64-w64-mingw32/")
    set(WHERE-IS-SDL-HEADERS "${CMAKE_SOURCE_DIR}/../lib/native-windows/x86_64-w64-mingw32/include/SDL2")
    find_library(SDLmain SDL2main PATHS ${WHERE-IS-SDL})
    include_directories(
        "${WHERE-IS-SDL-HEADERS}"
    )

    # Executable compilation and linking...
    # Runtime++...
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${imguisources} ${soilsources} ${runtimesources} ${runtimeprojectsource})
    target_link_libraries(${CMAKE_PROJECT_NAME}
        "glad"
        ${SDL}
        ${SDLmain}
        ${OPENGL_gl_LIBRARY}
    )

endif()
