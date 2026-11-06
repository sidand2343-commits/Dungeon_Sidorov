#ifndef GAME_H
#define GAME_H

#include <string>
#include "map.h"
#include "hero.h"

enum class CommandResult {
    CONTINUE_NO_MOVE,
    CONTINUE_MOVE,
    QUIT
};

class Game {
public:
    // Конструктор загрузки уровня из файла
    explicit Game(const std::string& map_filename);

    // Конструктор с размерами (для тестов)
    Game(int map_width, int map_height);

    // Деструктор по умолчанию — RAII сам освободит Map и Hero
    ~Game() = default;

    // Запрет копирования
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    // Главный цикл
    void run();

private:
    CommandResult process_command(const std::string& command);
    void print_welcome() const;
    void print_help() const;

    Map  map_;
    Hero hero_;
    int  move_counter_;
    bool is_playing_;
};

#endif