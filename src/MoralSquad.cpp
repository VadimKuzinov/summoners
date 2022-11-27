#include "MoralSquad.h"
#include <iostream>
#include <cmath>


void MoralSquad::stabilizeMorality() {
    if (morality_ < 0) {
        morality_ += stabilization_speed_;
    }
    else {
        morality_ -= stabilization_speed_;
    }

    if (morality_ >= -stabilization_speed_ && morality_ <= stabilization_speed_) {
        morality_ = 0;
    }
}

double MoralSquad::getMakingDamageCf() const {
    return 1 + std::atan(getMorality());
}

void MoralSquad::update() {
    GeneralSquad::update();
    
    stabilizeMorality();
}

void MoralSquad::giveDamage() {
    double value = getDamage();
    value *= getMakingDamageCf();
    auto captured = getCaptured();
    captured->receiveDamage(value);
}

void MoralSquad::attack() {
    auto captured = getCaptured();
    if (captured == nullptr) {
        return;
    }

    auto distance = Point::distance(getCoords(), captured->getCoords());
    if (distance > getAttackRange()) {
        return;
    }

    giveDamage();
}

void MoralSquad::act() {
    update();

    if (isMoving()) {
        move();
    }

    if (isAttacking()) {
        attack();
    }
}

