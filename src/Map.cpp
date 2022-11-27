#include "Map.h"
#include "Entity.h"
#include <algorithm>


void Map::addSquad(std::shared_ptr<Entity> new_squad, Point where) {
    map_[static_cast<std::size_t>(where.y)][static_cast<std::size_t>(where.x)] = new_squad;
    auto it_low = std::lower_bound(begin(), end(), new_squad->getPriority(),
            [](std::shared_ptr<Entity> squad, int priority) { 
                return squad->getPriority() < priority;
            });

    squads_.insert(it_low, new_squad);
}

void Map::clearCorpses() {
    auto it = squads_.begin();
    Point coords;
    while (it != squads_.end()) {
        if (!(*it)->isAlive()) {
            coords = Point::withIntCfs((*it)->getCoords());
            map_[static_cast<std::size_t>(coords.y)][static_cast<std::size_t>(coords.x)] = nullptr;
            squads_.erase(it++);
        }
        else {
            ++it;
        }
    }
}

