cmake_minimum_required(VERSION 3.0.0)

set(SDL_BUILD_FROM_SOURCE ON)

set(FRONTEND_SDL2 main.cpp)
add_executable(frontend_sdl2 ${FRONTEND_SDL2})

find_package(SDL 2)

if(${SDL_FOUND})
    include_directories(${SDL_INCLUDE_DIRS})
    set(SDL2_LIBRARIES ${SDL_LIBRARY})
elseif(${SDL_BUILD_FROM_SOURCE})
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
