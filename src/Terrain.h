#pragma once
#include "Map.h"
#include "Academy.h"
#include <iostream>
#include <memory>


class Terrain;
class Summoner;
class Entity;
class School;

std::istream& operator>>(std::istream& is, Terrain& terrain);

class Terrain : public std::enable_shared_from_this<Terrain> {
private:
    std::pair<std::shared_ptr<Summoner>, std::shared_ptr<Summoner>> summoners_;
    Map map_;
    Academy academy_;
    friend std::istream& operator>>(std::istream& is, Terrain& terrain);

    void linkSquad(std::shared_ptr<Entity>, Point);
    void addSummoner(std::shared_ptr<Entity>);
    void loadSchoolsToSummoner(std::shared_ptr<Summoner>);

public:
    Terrain() = default;

    void init(const std::string& academy_cfg, const std::string& map_cfg);

    void addSquad(std::shared_ptr<Entity>, Point);

    std::shared_ptr<Summoner> getSummonerFirst() {
        return summoners_.first;
    }

    std::shared_ptr<Summoner> getSummonerSecond() {
        return summoners_.second;
    }

    Academy& getAcademy() {
        return academy_;
    }

    Map& getMap() {
        return map_;
    }

    std::shared_ptr<const Entity> getSquadWithCoords(Point coords) {
        return std::const_pointer_cast<const Entity>(map_[coords]);
    }

    void transferSquadToEmptyPlace(std::shared_ptr<Entity> squad, Point target_coords);
    void goToTheNextIteration();
};

