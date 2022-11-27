#include "MoralHealingSquad.h"


void MoralHealingSquad::heal() {
    GeneralHealingSquad::heal();
}

void MoralHealingSquad::update() {
    MoralSquad::update();
}

void MoralHealingSquad::act() {
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

