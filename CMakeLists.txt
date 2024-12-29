cmake_minimum_required(VERSION 3.16)
project(game C)

set(CMAKE_C_STANDARD 99)

unset(game CACHE)

# Шлях до SDL2
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/SDL2-2.30.10")

add_executable(${PROJECT_NAME}
        main.c
        )

# Додаємо шляхи до заголовочних файлів
include_directories(
        "${SDL2_PATH}/include"
)

# Лінкуємо бібліотеки (x64 версія, оскільки бачу що у вас є папка x64)
target_link_libraries(${PROJECT_NAME}
        "${SDL2_PATH}/lib/x86/SDL2.lib"
        "${SDL2_PATH}/lib/x86/SDL2main.lib"
        )

# Копіюємо DLL
if(EXISTS "${SDL2_PATH}/lib/x86/SDL2.dll")
    file(COPY "${SDL2_PATH}/lib/x86/SDL2.dll"
            DESTINATION ${CMAKE_BINARY_DIR})
endif()

