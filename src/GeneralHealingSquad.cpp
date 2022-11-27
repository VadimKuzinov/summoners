#include "GeneralHealingSquad.h"


void GeneralHealingSquad::heal() {
    auto cur_hp = getCurHp();
    auto max_hp = getMaxHp();
    setCurHp(std::min(max_hp, cur_hp + healing_speed_));
}

void GeneralHealingSquad::update() {
    GeneralSquad::update();
}

void GeneralHealingSquad::act() {
    update();

    if (isMoving()) {
        move();
    }

    if (isAttacking()) {
        attack();
    }

    if (isHealing()) {
        heal();
    }
}

