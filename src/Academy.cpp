#include "Academy.h"
#include "Obstacle.h"
#include "GeneralSquad.h"


void Ability::linkSquad() const {
    auto casted = std::static_pointer_cast<Obstacle>(model_);
    casted->setSchoolName(school_name_);
    casted->setAbilityName(name_);
}

std::istream& operator>>(std::istream& is, Ability& ability) {
    is >> ability.name_;
    is >> ability.energy_cost_;
    is >> ability.required_level_of_school_;
    is >> ability.model_;
    ability.linkSquad();
    return is;
}

std::istream& operator>>(std::istream& is, School& school) {
    is >> school.name_;
    std::size_t qty;
    is >> qty;
    while (qty--) {
        Ability ability;
        ability.setSchoolName(school.name_);
        is >> ability;
        school.ability_names_.push_back(ability.getName());
        school[ability.getName()] = std::move(ability);
    } 
    return is;
}

std::istream& operator>>(std::istream& is, Academy& academy) {
    std::size_t qty;
    is >> qty;
    std::cout << qty << std::endl;
    while (qty--) {
        School school;
        is >> school;
        academy.school_names_.push_back(school.getName());
        academy[school.getName()] = std::move(school);
    }
    return is;
}

School& Academy::operator[](const std::string& name) {
    return schools_[name];
}

const School& Academy::operator[](const std::string& name) const {
    auto it = schools_.find(name);
    return it->second;
}

Ability& School::operator[](const std::string& name) {
    return abilities_[name];
}

const Ability& School::operator[](const std::string& name) const {
    auto it = abilities_.find(name);
    return it->second;
}

std::shared_ptr<Entity> Ability::getModel() const {
    return model_->clone();
}

std::shared_ptr<Entity> Ability::getModelWithLevel(int level) const {
    auto model = getModel();
    auto model_casted = std::dynamic_pointer_cast<GeneralSquad>(getModel());
    if (model_casted == nullptr) {
        return model;
    }

    model_casted->setQuantity(static_cast<int>(level * qty_kf_));
    return model_casted;
}   
