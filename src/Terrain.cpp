#include "Terrain.h"
#include "Point.h"
#include "Summoner.h"
#include <fstream>


void Terrain::init(const std::string& file_academy, const std::string& file_terrain) {
    std::ifstream ifs(file_academy);
    ifs >> academy_;

    ifs = std::ifstream(file_terrain);
    ifs >> *this;
}

void Terrain::goToTheNextIteration() {
    map_.clearCorpses();
    for (auto&& squad : map_) {
        squad->act();
    }
}

void Terrain::linkSquad(std::shared_ptr<Entity> e, Point where) {
    auto casted = std::static_pointer_cast<Obstacle>(e);
    casted->coords_ = where;
    casted->terrain_ = shared_from_this();
}

void Terrain::addSummoner(std::shared_ptr<Entity> e) {
    if (summoners_.first == nullptr) {
        summoners_.first = std::dynamic_pointer_cast<Summoner>(e);
    }
    else {
        summoners_.second = std::dynamic_pointer_cast<Summoner>(e);
    }
}

void Terrain::loadSchoolsToSummoner(std::shared_ptr<Summoner> summoner) {
    for (auto&& [name, school] : academy_.getSchools()) {
        summoner->getLevelsOfSchools()[name] = 1;
    }
}

void Terrain::addSquad(std::shared_ptr<Entity> new_squad, Point where) {
    linkSquad(new_squad, where);
    if (typeid(*new_squad) == typeid(Summoner)) {
        addSummoner(new_squad);
    }

    map_.addSquad(new_squad, where);
}

std::istream& operator>>(std::istream& is, Terrain& terrain) {
    Point limits;
    is >> limits;
    terrain.map_.setSizes(limits);

    std::size_t qty;
    is >> qty;
    Point coords;
    std::string school, ability;
    while (qty--) {
        is >> coords >> school >> ability;
        std::cout << coords << school << ability << std::endl;
        terrain.addSquad(terrain.academy_[school][ability].getModel(), coords);
    }

    return is;
}


void Terrain::transferSquadToEmptyPlace(std::shared_ptr<Entity> squad, Point target_coords) {
    auto cur_coords = Point::withIntCfs(squad->getCoords());
    auto int_target_coords = Point::withIntCfs(target_coords);
    map_[cur_coords] = nullptr;
    map_[int_target_coords] = squad;
    std::static_pointer_cast<Obstacle>(squad)->setCoords(target_coords);
}
