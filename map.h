#ifndef MAP_H
#define MAP_H

#include <string>
#include "error_codes.h"
#include "hero.h"

class Map {
public:
    // Конструктор по размерам (Практика 10)
    Map(int width, int height);

    // Конструктор загрузки из файла (Практика 8 + 10)
    // При ошибке бросает исключение — RAII гарантирует, что память не утечёт
    explicit Map(const std::string& filename);

    // Деструктор — единственное место освобождения памяти (критерий 89)
    ~Map();

    // Запрет копирования (критерий 94 методички):
    // если скопировать объект, два деструктора освободят один блок — UB
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    // Разрешаем перемещение (move semantics) — полезно для RAII
    Map(Map&& other) noexcept;
    Map& operator=(Map&& other) noexcept;

    // Доступ к клетке
    char get_cell(int x, int y) const;
    void set_cell(int x, int y, char c);

    bool is_inside(int x, int y) const;
    bool is_passable(int x, int y) const;

    // Отрисовка: подставляет символ героя, не меняя карту
    void print(const Hero& hero) const;

    // Рекурсивная проверка достижимости
    bool check_reachable(int start_x, int start_y, char target) const;

    int get_width() const  { return width_; }
    int get_height() const { return height_; }

private:
    int   width_;
    int   height_;
    char* cells_;  // Один непрерывный блок: index = y * width_ + x

    // Вспомогательный метод для рекурсии
    bool dfs_reachable(int x, int y, char target, bool* visited) const;
};

#endif