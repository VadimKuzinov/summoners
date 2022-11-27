#pragma once
#include "../src/Point.h"
#include "../src/Squads.h"
#include "Player.h"
#include "../src/Utils.h"
#include <vector>
#include <thread>
#include <string>
#include <sstream>
#include <iostream>


class Game {
    std::shared_ptr<Terrain> terrain_;
    std::pair<std::shared_ptr<Player>, std::shared_ptr<Player>> players_;

public:
    Game(const std::string& academy_cfg, const std::string& map_cfg) : terrain_(new Terrain) {
        terrain_->init(academy_cfg, map_cfg);
        players_ = {std::shared_ptr<Player>(new Player(terrain_->getSummonerFirst())), 
                    std::shared_ptr<Player>(new Player(terrain_->getSummonerSecond()))};
    }

    std::shared_ptr<Player> getFirstPlayer() const {
        return players_.first;
    }

    std::shared_ptr<Player> getSecondPlayer() const {
        return players_.second;
    }

    std::shared_ptr<Terrain> getTerrain() const {
        return terrain_;
    }

    std::vector<char> getSerializedGameState(std::shared_ptr<Player>) const;
};

