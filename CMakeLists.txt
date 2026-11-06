cmake_minimum_required(VERSION 3.16)
project(Dungeon_Sidorov CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Dungeon_Sidorov
        main.cpp
        game.cpp
        map.cpp
        hero.cpp
        error_codes.cpp
)

# Копировать level.txt в папку сборки после сборки
add_custom_command(TARGET Dungeon_Sidorov POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/level.txt"
        "$<TARGET_FILE_DIR:Dungeon_Sidorov>/level.txt"
)