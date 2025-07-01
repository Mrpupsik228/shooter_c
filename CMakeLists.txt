cmake_minimum_required(VERSION 3.10)
project(game VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)

include(FetchContent)

# SDL2
find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
    message(STATUS "SDL2 not found, fetching from source...")
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.32.8
    )
    FetchContent_MakeAvailable(SDL2)
endif()

# SDL2_ttf
find_package(SDL2_ttf QUIET)
if(NOT SDL2_TTF_FOUND)
    message(STATUS "SDL2_ttf not found, fetching from source...")
    FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-2.22.0
    )
    FetchContent_MakeAvailable(SDL2_ttf)
endif()

# Create the executable
add_executable(${PROJECT_NAME}
    src/main.c
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2_ttf::SDL2_ttf
    SDL2::SDL2
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# copy assets folder to build directory
if(NOT EXISTS "${CMAKE_BINARY_DIR}/assets")
   file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION ${CMAKE_BINARY_DIR}) 
endif()
