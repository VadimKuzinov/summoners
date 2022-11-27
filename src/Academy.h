#pragma once
#include "Entity.h"
#include <typeinfo>
#include <unordered_map>
#include <iostream>
#include <memory>


class Ability;
class School;
class Academy;

std::istream& operator>>(std::istream&, Ability&);
std::istream& operator>>(std::istream&, School&);
std::istream& operator>>(std::istream&, Academy&);


class Ability {
private:
    std::string name_;
    std::string school_name_;

    double energy_cost_;
    int required_level_of_school_;
    std::shared_ptr<Entity> model_;
    double qty_kf_ = 1.0;
    friend std::istream& operator>>(std::istream&, Ability&);

private:
    void linkSquad() const;

public:
    void setSchoolName(const std::string school_name) {
        school_name_ = school_name;
    }

    const std::string& getName() const {
        return name_;
    }

    std::shared_ptr<Entity> getModel() const;

    double getEnergyCost() const {
        return energy_cost_;
    }

    double getRequiredLevelOfSchool() const {
        return required_level_of_school_;
    }

    std::shared_ptr<Entity> getModelWithLevel(int level) const;
};

class School {
private:
    std::string name_;
    std::vector<std::string> ability_names_;
    std::unordered_map<std::string, Ability> abilities_;
    double required_xp_for_upgrading_ = 15;
    friend std::istream& operator>>(std::istream&, School&);

public:
    const std::string& getName() const {
        return name_;
    }

    Ability& operator[](const std::string&);

    const std::vector<std::string>& getAbilityNames() const {
        return ability_names_;
    }

    auto& getAbilities() {
        return abilities_;
    }

    double getRequiredXpForUpgrading() const {
        return required_xp_for_upgrading_;
    }
};

class Academy { 
private:
    std::vector<std::string> school_names_;
    std::unordered_map<std::string, School> schools_;
    friend std::istream& operator>>(std::istream&, Academy&);

public:
    School& operator[](const std::string&);

    const std::vector<std::string>& getSchoolNames() const {
        return school_names_;
    }

    auto& getSchools() {
        return schools_;
    }
};

