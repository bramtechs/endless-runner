cmake_minimum_required(VERSION 3.7)

project(endless-runner-sdl2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS},./src)


add_executable(SDL2Game 
    main.c
    math.c
    player.c
    obstacle.c
    background.c
    particles.c
    gui.c

    endless.h
)
target_link_libraries(SDL2Game ${SDL2_LIBRARIES})