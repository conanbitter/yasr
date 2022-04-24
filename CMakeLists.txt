cmake_minimum_required(VERSION 3.16)

project(yasr VERSION 0.1 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

add_executable(yasr
    src/main.cpp
    src/gfx/gfx.hpp
    src/gfx/app.cpp
)

if(MSVC)
    find_package(SDL2msvc REQUIRED)
else()
    find_package(SDL2 REQUIRED)
endif()



target_include_directories(yasr
    PUBLIC
        ${SDL2_INCLUDE_DIR_64}
)

target_link_directories(yasr
    PUBLIC
        ${SDL2_LIBRARY_64}
)

target_link_libraries(yasr
    SDL2
    opengl32
)