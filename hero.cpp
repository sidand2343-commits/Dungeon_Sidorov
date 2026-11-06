#include <iostream>
#include "hero.h"

Hero::Hero(int start_x, int start_y,
           unsigned int hp, unsigned int attack)
    : x_(start_x)
    , y_(start_y)
    , hp_(hp)
    , max_hp_(hp)
    , attack_power_(attack)
    , gold_(0)
    , states_(0)
{
    // Демонстрационный вывод для Практики 10, критерий 90
    std::cout << "[Hero] Constructor called at (" << x_ << ", " << y_ << ")\n";
}

void Hero::set_state(uint32_t mask)   { states_ |= mask; }
void Hero::clear_state(uint32_t mask) { states_ &= ~mask; }

bool Hero::has_state(uint32_t mask) const {
    return (states_ & mask) != 0;
}

void Hero::apply_damage(unsigned int damage) {
    if (damage > hp_) {
        hp_ = 0;
    } else {
        hp_ -= damage;
    }
    std::cout << "You took " << damage << " damage. HP left: " << hp_ << "\n";
}

void Hero::add_gold(unsigned int amount) {
    gold_ += amount;
    std::cout << "You picked up " << amount << " gold!\n";
}

void Hero::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}

void Hero::print_status() const {
    std::cout << "--- Hero Status ---\n";
    std::cout << "HP:         " << hp_ << " / " << max_hp_ << "\n";
    std::cout << "Attack:     " << attack_power_ << "\n";
    std::cout << "Gold:       " << gold_ << "\n";
    std::cout << "Position:   (" << x_ << ", " << y_ << ")\n";

    float hp_percent = static_cast<float>(hp_) / static_cast<float>(max_hp_) * 100.0f;
    std::cout << "HP percent: " << hp_percent << "%\n";

    std::cout << "States: ";
    bool any = false;
    if (has_state(STATE_POISONED))   { std::cout << "poisoned ";   any = true; }
    if (has_state(STATE_BLINDED))    { std::cout << "blinded ";    any = true; }
    if (has_state(STATE_INVISIBLE))  { std::cout << "invisible ";  any = true; }
    if (has_state(STATE_PETRIFIED))  { std::cout << "petrified ";  any = true; }
    if (has_state(STATE_BURNING))    { std::cout << "burning ";    any = true; }
    if (has_state(STATE_SLEEPING))   { std::cout << "sleeping ";   any = true; }
    if (!any) { std::cout << "none"; }
    std::cout << "\n";
}