cmake_minimum_required(VERSION 3.7)

project(endless-runner-sdl2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS},./src)


add_executable(SDL2Game 
    src/main.c
    src/math.c
    src/platform.c
    src/player.c
    src/obstacle.c
    src/background.c
    src/particles.c
    src/gui.c

    src/endless.h
)
target_link_libraries(SDL2Game ${SDL2_LIBRARIES})
