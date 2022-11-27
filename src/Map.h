#pragma once
#include "Point.h"
#include <vector>
#include <list>
#include <memory>

class Entity;

class Map {
private:
    std::vector<std::vector<std::shared_ptr<Entity>>> map_;
    std::list<std::shared_ptr<Entity>> squads_;

public:
    std::size_t getWidth() const {
        return map_[0].size();
    }

    std::size_t getHeight() const {
        return map_.size();
    }

    void setSizes(Point limits) {
        map_.assign(static_cast<std::size_t>(limits.y), std::vector<std::shared_ptr<Entity>>(static_cast<std::size_t>(limits.x)));
    }

    std::shared_ptr<Entity>& operator[](Point coords) {
        return map_[static_cast<std::size_t>(coords.y)][static_cast<std::size_t>(coords.x)];
    }
    
    void clearCorpses();
    void addSquad(std::shared_ptr<Entity>, Point);

    std::size_t getQuantityOfSquads() const {
        return squads_.size();
    }

    auto begin() {
        return squads_.begin();
    }

    auto end() {
        return squads_.end();
    }
};
