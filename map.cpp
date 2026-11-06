#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <vector>
#include "map.h"



// ---------- Конструктор по размерам ----------
Map::Map(int width, int height)
    : width_(width)
    , height_(height)
    , cells_(nullptr)
{
    std::cout << "[Map] Constructor called: " << width << "x" << height << "\n";

    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Map size must be positive");
    }

    // Выделяем один непрерывный блок (Практика 7, критерий 63)
    cells_ = new (std::nothrow) char[width * height];
    if (!cells_) {
        // Критерий 61: результат выделения проверяется до использования
        throw std::bad_alloc();
    }

    // Заполняем стенами
    std::memset(cells_, '#', width * height);

    // Вырезаем комнату (строки 1..height-2, столбцы 1..width-2)
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            cells_[y * width + x] = '.';
        }
    }

    // Золото и выход
    if (width > 4 && height > 4) {
        cells_[2 * width + 3] = 'G';
        cells_[2 * width + 5] = 'G';
        cells_[(height - 3) * width + (width - 3)] = 'E';
    }
}

// ---------- Конструктор загрузки из файла ----------
Map::Map(const std::string& filename)
    : width_(0)
    , height_(0)
    , cells_(nullptr)
{
    std::cout << "[Map] Loading from file: " << filename << "\n";

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    // Считываем все строки
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        // Обрезаем \r (Windows) — критерий 75 методички
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(line);
    }

    if (lines.empty()) {
        throw std::runtime_error("Empty file");
    }

    height_ = static_cast<int>(lines.size());
    width_  = static_cast<int>(lines[0].size());

    if (width_ <= 0 || height_ <= 0) {
        throw std::runtime_error("Invalid map dimensions");
    }

    // Проверяем, что все строки одной длины (критерий 71)
    for (const auto& l : lines) {
        if (static_cast<int>(l.size()) != width_) {
            throw std::runtime_error("Inconsistent row lengths");
        }
    }

    // Выделяем память
    cells_ = new (std::nothrow) char[width_ * height_];
    if (!cells_) {
        throw std::bad_alloc();
    }

    // Копируем данные
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            cells_[y * width_ + x] = lines[y][x];
        }
    }

    std::cout << "[Map] Loaded: " << width_ << "x" << height_ << "\n";
}

// ---------- Деструктор (RAII, критерий 89) ----------
Map::~Map() {
    std::cout << "[Map] Destructor called\n";
    delete[] cells_;  // Единственное место освобождения памяти
    cells_ = nullptr; // Критерий 62: после освобождения указатель обнуляется
}

// ---------- Перемещение (move semantics) ----------
Map::Map(Map&& other) noexcept
    : width_(other.width_)
    , height_(other.height_)
    , cells_(other.cells_)
{
    other.width_  = 0;
    other.height_ = 0;
    other.cells_  = nullptr;  // Чтобы деструктор other не освободил наш блок
}

Map& Map::operator=(Map&& other) noexcept {
    if (this != &other) {
        delete[] cells_;  // Освобождаем старый блок
        width_  = other.width_;
        height_ = other.height_;
        cells_  = other.cells_;
        other.width_  = 0;
        other.height_ = 0;
        other.cells_  = nullptr;
    }
    return *this;
}

// ---------- Доступ к клеткам ----------
bool Map::is_inside(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

char Map::get_cell(int x, int y) const {
    if (!is_inside(x, y)) return '#';
    return cells_[y * width_ + x];
}

void Map::set_cell(int x, int y, char c) {
    if (is_inside(x, y)) {
        cells_[y * width_ + x] = c;
    }
}

bool Map::is_passable(int x, int y) const {
    if (!is_inside(x, y)) return false;
    char c = cells_[y * width_ + x];
    return c != '#';
}

// ---------- Отрисовка ----------
void Map::print(const Hero& hero) const {
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (x == hero.get_x() && y == hero.get_y()) {
                std::cout << '@';
            } else {
                std::cout << cells_[y * width_ + x];
            }
        }
        std::cout << '\n';
    }
}

// ---------- Рекурсивная проверка достижимости ----------
bool Map::dfs_reachable(int x, int y, char target, bool* visited) const {
    // Базовые случаи — ДО обращения к массивам
    if (!is_inside(x, y)) return false;
    if (!is_passable(x, y)) return false;
    if (visited[y * width_ + x]) return false;
    if (cells_[y * width_ + x] == target) return true;

    visited[y * width_ + x] = true;

    if (dfs_reachable(x + 1, y, target, visited)) return true;
    if (dfs_reachable(x - 1, y, target, visited)) return true;
    if (dfs_reachable(x, y + 1, target, visited)) return true;
    if (dfs_reachable(x, y - 1, target, visited)) return true;

    return false;
}

bool Map::check_reachable(int start_x, int start_y, char target) const {
    bool* visited = new (std::nothrow) bool[width_ * height_];
    if (!visited) return false;

    std::memset(visited, 0, width_ * height_);

    bool result = dfs_reachable(start_x, start_y, target, visited);

    delete[] visited;  // RAII: здесь тоже можно было бы использовать unique_ptr
    return result;
}