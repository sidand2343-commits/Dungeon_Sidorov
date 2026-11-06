#include <iostream>
#include <string>
#include "game.h"

int main(int argc, char* argv[]) {
    try {
        // Критерий 91: объект на стеке — деструктор вызовется автоматически
        Game game(argc > 1 ? std::string(argv[1]) : std::string("level.txt"));
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "[main] Exiting normally\n";
    return 0;
}