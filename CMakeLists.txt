cmake_minimum_required(VERSION 3.10)
project (Dungeon_Sidorov)
set (CMAKE_C_STANDARD 99)
add_executable(
${PROJECT_NAME}
main.c
game.c
game.h
)