#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "game.h"

Game::Game(const std::string& map_filename)
    : map_(map_filename)  // RAII: если конструктор Map бросит исключение,
                          // Game не создастся, и утечек не будет (критерий 92)
    , hero_(4, 3)
    , move_counter_(1)
    , is_playing_(true)
{
    std::cout << "[Game] Constructor called\n";
}

Game::Game(int map_width, int map_height)
    : map_(map_width, map_height)
    , hero_(map_width / 2, map_height / 2)
    , move_counter_(1)
    , is_playing_(true)
{
    std::cout << "[Game] Constructor called (generated map)\n";
}

void Game::print_welcome() const {
    std::cout << "Welcome to the Dungeon!!!\n";
    std::cout << "Commands: north/south/east/west (n/s/e/w), look (l), "
              << "status (st), check (c), hit N, quit (q), help (h)\n\n";
}

void Game::print_help() const {
    std::cout << "Commands:\n";
    std::cout << "  north/n, south/s, east/e, west/w - move\n";
    std::cout << "  look/l    - look around\n";
    std::cout << "  status/st - show hero stats\n";
    std::cout << "  check/c   - is exit reachable?\n";
    std::cout << "  hit N     - take N damage\n";
    std::cout << "  quit/q    - quit\n";
}

static std::string to_lower_copy(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

CommandResult Game::process_command(const std::string& raw) {
    std::string cmd = to_lower_copy(raw);

    // Обрезаем trailing whitespace
    while (!cmd.empty() && (cmd.back() == '\n' || cmd.back() == ' ')) {
        cmd.pop_back();
    }

    // Движение
    auto try_move = [this](int dx, int dy, const char* dir) -> CommandResult {
        int nx = hero_.get_x() + dx;
        int ny = hero_.get_y() + dy;
        if (!map_.is_passable(nx, ny)) {
            std::cout << "You can't go there.\n";
            return CommandResult::CONTINUE_NO_MOVE;
        }
        hero_.move(dx, dy);

        // Подбор золота
        if (map_.get_cell(nx, ny) == 'G') {
            hero_.add_gold(10);
            map_.set_cell(nx, ny, '.');
        }

        std::cout << "You went " << dir << ".\n";
        return CommandResult::CONTINUE_MOVE;
    };

    if (cmd == "north" || cmd == "n") return try_move(0, -1, "north");
    if (cmd == "south" || cmd == "s") return try_move(0,  1, "south");
    if (cmd == "east"  || cmd == "e") return try_move(1,  0, "east");
    if (cmd == "west"  || cmd == "w") return try_move(-1, 0, "west");

    if (cmd == "look" || cmd == "l") {
        std::cout << "You looked around.\n";
        map_.print(hero_);
        return CommandResult::CONTINUE_NO_MOVE;
    }

    if (cmd == "status" || cmd == "st") {
        hero_.print_status();
        return CommandResult::CONTINUE_NO_MOVE;
    }

    if (cmd == "check" || cmd == "c") {
        if (map_.check_reachable(hero_.get_x(), hero_.get_y(), 'E')) {
            std::cout << "The exit is reachable.\n";
        } else {
            std::cout << "The exit is NOT reachable from here.\n";
        }
        return CommandResult::CONTINUE_NO_MOVE;
    }

    if (cmd == "help" || cmd == "h") {
        print_help();
        return CommandResult::CONTINUE_NO_MOVE;
    }

    if (cmd == "quit" || cmd == "q") {
        std::cout << "The game is over.\n";
        return CommandResult::QUIT;
    }

    // hit N — ручной парсинг (Практика 6)
    if (cmd.rfind("hit ", 0) == 0) {
        std::string arg = cmd.substr(4);
        unsigned int damage = 0;
        bool ok = true;
        for (char c : arg) {
            if (c < '0' || c > '9') { ok = false; break; }
            damage = damage * 10 + (c - '0');
        }
        if (ok && !arg.empty()) {
            hero_.apply_damage(damage);
            return CommandResult::CONTINUE_NO_MOVE;
        }
        std::cout << "Usage: hit N (N — целое неотрицательное число)\n";
        return CommandResult::CONTINUE_NO_MOVE;
    }

    std::cout << "Unknown command '" << cmd << "'.\n";
    print_help();
    return CommandResult::CONTINUE_NO_MOVE;
}

void Game::run() {
    print_welcome();
    map_.print(hero_);

    while (is_playing_) {
        std::cout << "\n[Move " << move_counter_ << "] Enter the command: ";

        std::string command;
        if (!std::getline(std::cin, command)) {
            // EOF
            break;
        }

        CommandResult result = process_command(command);

        if (result == CommandResult::QUIT) {
            is_playing_ = false;
        } else if (result == CommandResult::CONTINUE_MOVE) {
            ++move_counter_;
            map_.print(hero_);
        }
    }
}