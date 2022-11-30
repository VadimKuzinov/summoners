#include "Player.h"
#include "../src/GeneralSquad.h"
#include "../src/Utils.h"


void Player::catchClick(std::string type, Point where) {
    if (type == "map") {
        if (where.y >= terrain_->getMap().getHeight() || where.x >= terrain_->getMap().getWidth()) {
            return;
        }

        if (active_ == nullptr) {
            setActive(where);
        }
        else if (active_ == terrain_->getMap()[where]) {
            resetActive();
        }
        else {
            auto casted = std::dynamic_pointer_cast<InteractiveSquad>(active_);
            if (casted == nullptr || (casted != getSummoner() && casted->getSummoner() != summoner_)) {
                return;
            }

            casted->setTargetCoords(where);
            casted->setCaptured(terrain_->getMap()[where]);
        }
    }
    else if (type == "menu") {
        auto number_of_option = static_cast<unsigned int>(where.y);
        if (active_ != nullptr) {
            auto choices = applyFunctionToCasted(typeid(*active_), MenuCaller{}, active_);
            if (number_of_option >= choices.size()) {
                return;
            }

            auto&& func = choices[number_of_option].first;
            func(active_);
        }
        else {
            if (chosen_school_ == "") {
                auto school_names = getSchoolNames();
                if (number_of_option >= school_names.size()) {
                    return;
                }

                chosen_school_ = school_names[number_of_option];
                summoner_->setSummonedSchool(chosen_school_);
            }
            else {
                auto ability_names = getAbilityNames(chosen_school_);
                if (number_of_option >= ability_names.size()) {
                    return;
                }

                summoner_->setSummonedAbility(ability_names[number_of_option]);
                chosen_school_ = "";
            }
        }
    }
    else if (type == "reset_active") {
        resetActive();
    }
    else if (type == "active") {
        if (active_ == nullptr || typeid(*active_) == typeid(Obstacle)) {
            return;
        }

        double delta = Point::pi / 8;
        auto max_w = terrain_->getMap().getWidth();
        auto max_h = terrain_->getMap().getHeight();

        auto coords = active_->getCoords();
        auto casted = std::static_pointer_cast<InteractiveSquad>(active_);
        auto acting_angle = casted->getActingAngle();

        if (where.x == -1) {
            casted->setActingAngle(acting_angle - delta);
        }
        else if (where.x == 1) {
            casted->setActingAngle(acting_angle + delta);
        }

        if (where.y == -1) {
            casted->setActingAngle(-Point::pi / 2);
        }
        else if (where.y == 1) {
            casted->setActingAngle(Point::pi / 2);
        }
    }
}

std::vector<std::string> Player::getMenuOptions() const {
    if (active_ == nullptr) {
        if (chosen_school_ == "") {
            return getSchoolNames();
        }
        else {
            return getAbilityNames(chosen_school_);
        }
    }
    else {
        if (typeid(*active_) == typeid(Obstacle) || (active_ != summoner_ && std::static_pointer_cast<InteractiveSquad>(active_)->getSummoner() != summoner_)) {
            return {};
        }
        auto choices = applyFunctionToCasted(typeid(*active_), MenuCaller{}, active_);
        std::vector<std::string> result;
        for (auto&& pair : choices) {
            result.push_back(pair.second);
        }
        return result;
    }
}


