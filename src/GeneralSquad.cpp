#include "GeneralSquad.h"
#include "Point.h"
#include "Terrain.h"


void GeneralSquad::update() {
    auto captured = getCaptured();
    if (captured && !captured->isAlive()) {
        captured = nullptr;
        setCaptured(captured);
    }

    if (captured) {
        setTargetCoords(captured->getCoords());
    }    
}

void GeneralSquad::move() {
    auto coords = getCoords();
    auto target_coords = getTargetCoords();
    auto terrain = getTerrain();

    double act_velocity = std::min(Point::distance(coords, target_coords), velocity_);
    auto vector_direction = Point::normalized(target_coords - coords) * act_velocity;
    auto target_point = coords + vector_direction;
    auto int_target_point = Point::withIntCfs(target_point);

    auto entityAtTargetPoint = terrain->getSquadWithCoords(int_target_point);
    if (entityAtTargetPoint != nullptr && entityAtTargetPoint != shared_from_this()) {
        moving_ = false;
        return;
    }
    
    terrain->transferSquadToEmptyPlace(shared_from_this(), target_point);

    if (target_coords == coords) {
        moving_ = false;
    }
}

void GeneralSquad::giveDamage() {
    double value = getDamage();
    auto captured = getCaptured();
    captured->receiveDamage(value);
}

void GeneralSquad::attack() {
    auto captured = getCaptured();
    if (captured == nullptr) {
        attacking_ = false;
        return;
    }

    auto distance = Point::distance(getCoords(), captured->getCoords());
    if (distance > attack_range_) {
        return;
    }

    giveDamage();
}

void GeneralSquad::act() {
    update();
    if (isMoving()) {
        move();
    }

    if (isAttacking()) {
        attack();
    }
}

