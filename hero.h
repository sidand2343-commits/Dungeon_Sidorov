#ifndef HERO_H
#define HERO_H

#include <cstdint>
#include <string>

// Маски состояний (те же, что в C-версии)
#define STATE_POISONED   (1U << 0)
#define STATE_BLINDED    (1U << 1)
#define STATE_INVISIBLE  (1U << 2)
#define STATE_PETRIFIED  (1U << 3)
#define STATE_BURNING    (1U << 4)
#define STATE_SLEEPING   (1U << 5)

class Hero {
public:
    // Конструктор с параметрами (Практика 10, критерий 80)
    Hero(int start_x, int start_y,
         unsigned int hp = 100,
         unsigned int attack = 10);

    // Геттеры (инкапсуляция, Практика 11 — задел на будущее)
    int  get_x() const { return x_; }
    int  get_y() const { return y_; }
    unsigned int get_hp() const { return hp_; }
    unsigned int get_max_hp() const { return max_hp_; }
    unsigned int get_gold() const { return gold_; }
    uint32_t     get_states() const { return states_; }

    // Изменение состояния
    void set_state(uint32_t mask);
    void clear_state(uint32_t mask);
    bool has_state(uint32_t mask) const;

    // Урон: здоровье не уходит ниже нуля
    void apply_damage(unsigned int damage);

    // Подбор золота
    void add_gold(unsigned int amount);

    // Вывод статуса
    void print_status() const;

    // Перемещение (координаты меняет сам объект через this)
    void move(int dx, int dy);

private:
    int  x_;
    int  y_;
    unsigned int hp_;
    unsigned int max_hp_;
    unsigned int attack_power_;
    unsigned int gold_;
    uint32_t     states_;
};

#endif