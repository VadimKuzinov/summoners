#pragma once
#include "../src/Summoner.h"
#include "../src/Terrain.h"
#include <memory>
#include <iostream>
#include <string>
#include <vector>


class Player {
private:
    std::shared_ptr<Summoner> summoner_;
    std::shared_ptr<Terrain> terrain_;
    std::shared_ptr<Entity> active_ = nullptr;
    std::string chosen_school_ = "";

public:
    explicit Player(const std::shared_ptr<Summoner>& summoner) : summoner_(summoner), terrain_(summoner->getTerrain()) {
    }

    void setActive(Point where) {
        active_ = terrain_->getMap()[where];
    }

    void resetActive() {
        active_ = nullptr;
    }

    std::shared_ptr<Entity> getActive() const {
        return active_;
    }

    void catchClick(std::string type, Point where);

    std::shared_ptr<Summoner> getSummoner() const {
        return summoner_;
    }

    decltype(auto) getSchoolNames() const {
        return terrain_->getAcademy().getSchoolNames();
    }

    decltype(auto) getAbilityNames(const std::string& school_name) const {
        return terrain_->getAcademy()[school_name].getAbilityNames();
    }

    std::vector<std::string> getMenuOptions() const;
};

