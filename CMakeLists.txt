cmake_minimum_required(VERSION 3.7)

project(endless-runner-sdl2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS},./src)


add_executable(SDL2Game 
    src/defs.h

    src/main.c
    src/main.h
    
    src/math.c
    src/math.h

    src/player.c
    src/player.h

    src/obstacle.c
    src/obstacle.h

    src/background.c
    src/background.h

    src/particles.c
    src/particles.h

    src/gui.c
    src/gui.h
)
target_link_libraries(SDL2Game ${SDL2_LIBRARIES})
