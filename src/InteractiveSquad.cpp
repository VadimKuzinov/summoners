#include "InteractiveSquad.h"
#include <cmath>


double InteractiveSquad::getActingAngle() const {
    auto coords = getCoords();
    auto target_coords = getTargetCoords();
    if (coords == target_coords) {
        return std::asin(1);
    }

    auto result = std::acos((target_coords.x - coords.x) / Point::distance(target_coords, coords));
    if (target_coords.y < coords.y) {
        result = Point::pi * 2 - result;
    }
    
    return result;
}

void InteractiveSquad::setActingAngle(double radians) {
    auto coords = getCoords();
    double inf_cf = 100000;
    setTargetCoords({ coords.x + inf_cf * std::cos(radians), coords.y + inf_cf * std::sin(radians) });
}
