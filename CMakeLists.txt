cmake_minimum_required(VERSION 3.16)
project(game C)

set(CMAKE_C_STANDARD 99)

unset(game CACHE)

# Шлях до SDL2
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/SDL2-2.30.10")
set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/SDL2_ttf-2.20.2")




if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SDL2_LIB_PATH "${SDL2_PATH}/lib/x64")
else()
    set(SDL2_LIB_PATH "${SDL2_PATH}/lib/x86")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(SDL2_TTF_LIB_PATH "${SDL2_TTF_PATH}/lib/x64")
else()
    set(SDL2_TTF_LIB_PATH "${SDL2_TTF_PATH}/lib/x86")
endif()

add_executable(${PROJECT_NAME}
        main.c
        )

# Додаємо шляхи до заголовочних файлів
include_directories(
        "${SDL2_PATH}/include"
        "${SDL2_TTF_PATH}/include"
)

# Лінкуємо бібліотеки (x64 версія, оскільки бачу що у вас є папка x64)
#target_link_libraries(${PROJECT_NAME}
#        "${SDL2_PATH}/lib/x86/SDL2.lib"
#        "${SDL2_PATH}/lib/x86/SDL2main.lib"
#        )
target_link_libraries(${PROJECT_NAME}
        "${SDL2_LIB_PATH}/SDL2.lib"
        "${SDL2_LIB_PATH}/SDL2main.lib"
        "${SDL2_TTF_LIB_PATH}/SDL2_ttf.lib"


        )



# Копіюємо DLL
#if(EXISTS "${SDL2_PATH}/lib/x86/SDL2.dll")
#    file(COPY "${SDL2_PATH}/lib/x86/SDL2.dll"
#            DESTINATION ${CMAKE_BINARY_DIR})
#endif()

if(EXISTS "${SDL2_LIB_PATH}/SDL2.dll")
    file(COPY "${SDL2_LIB_PATH}/SDL2.dll"
            DESTINATION ${CMAKE_BINARY_DIR})
endif()

if(EXISTS "${SDL2_TTF_LIB_PATH}/SDL2_ttf.dll")
    file(COPY "${SDL2_TTF_LIB_PATH}/SDL2_ttf.dll"
            DESTINATION ${CMAKE_BINARY_DIR})
endif()