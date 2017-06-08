cmake_minimum_required(VERSION 3.0)

set(SDL_BUILD_FROM_SOURCE ON)

set(FRONTEND_SDL2 main.cpp draw.cpp frontend_sdl2.h)
add_executable(frontend_sdl2 ${FRONTEND_SDL2})

if(${CMAKE_VERSION} VERSION_GREATER 3.7 OR ${CMAKE_VERSION} VERSION_EQUAL 3.7)
    cmake_minimum_required(VERSION 3.7)
    find_package(SDL2)
endif()

if(${SDL2_FOUND})
    include_directories(${SDL2_INCLUDE_DIRS})
elseif(${SDL_BUILD_FROM_SOURCE})
    if(NOT WIN32)
        #Build SDL2 is only for Windows for now. Maybe it will be fixed later.
        message(FATAL_ERROR "Building SDL2 directly is only for Windows!!")
    endif()
    include(ExternalProject)
    set(SDL_ARGS )
    if(WIN32)
        set(SDL_ARGS ${SDL_ARGS} -DVIDEO_OPENGLES=OFF)
    endif()
    message("Downloading and building SDL2 from source")
    ExternalProject_Add(SDL
            CMAKE_ARGS ${SDL_ARGS}
            PREFIX SDL2
            URL https://www.libsdl.org/release/SDL2-2.0.5.tar.gz
            STEP_TARGETS build
            EXCLUDE_FROM_ALL TRUE)
    add_dependencies(frontend_sdl2 SDL-build)
    include_directories(${CMAKE_CURRENT_BINARY_DIR}/SDL2/src/SDL/include)

    add_library(SDL2 IMPORTED STATIC)
    set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/SDL2/src/SDL-build/libSDL2.dll)

    add_library(SDL2main IMPORTED STATIC)
    set_target_properties(SDL2main PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/SDL2/src/SDL-build/${CMAKE_STATIC_LIBRARY_PREFIX}SDL2main${CMAKE_STATIC_LIBRARY_SUFFIX})

    set(SDL2_LIBRARIES mingw32 SDL2 SDL2main)
else()
    set(SDL2_LIBRARIES)
endif()

target_link_libraries(frontend_sdl2 nes_emu_core ${SDL2_LIBRARIES})
