#pragma once
#include "InteractiveSquad.h"
#include <memory>
#include <string>
#include <unordered_map>


class Summoner: public InteractiveSquad {
private:
    double summon_range_;
    double max_energy_;
    double cur_energy_;
    double xp_ = 0;
    double energy_regen_speed_;

    bool accumulating_ = true;
    bool summoning_ = false;
    bool upgrading_ = false;

    std::string summoned_school_;
    std::string summoned_ability_;
    std::unordered_map<std::string, int> levels_of_schools_;

private:
    constexpr static auto properties_ = std::tuple_cat(
        InteractiveSquad::getProperties(), 
        std::make_tuple(
            std::make_pair(&Summoner::summon_range_, "summon_range"),
            std::make_pair(&Summoner::max_energy_, "max_energy"),
            std::make_pair(&Summoner::cur_energy_, "cur_energy"),
            std::make_pair(&Summoner::xp_, "xp"),
            std::make_pair(&Summoner::energy_regen_speed_, "energy_regen_speed"),
            std::make_pair(&Summoner::summoned_school_, "summoned_school"),
            std::make_pair(&Summoner::summoned_ability_, "summoned_ability")
        )
    );

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value);
    }

protected:
    constexpr static auto getProperties() {
        return properties_;
    }

public:
    std::vector<std::pair<std::string, std::string>> serialize() const override {
        return serializeImpl(*this, properties_);
    }

public:
    virtual ~Summoner() = default;

    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new Summoner(*this));
    }  

    void tryToAccumulate() {
        accumulating_ = true; summoning_ = false; upgrading_ = false;
    }

    void tryToSummon() {
        summoning_ = true; accumulating_ = false; upgrading_ = false;
    }

    void tryToUpgrade() {
        summoning_ = false; accumulating_ = false; upgrading_ = true; 
    }

    bool isAccumulating() const {
        return accumulating_;
    }

    bool isSummoning() const {
        return summoning_;
    }

    bool isUpgrading() const {
        return upgrading_;
    }

    void setSummonedSchool(const std::string& summoned_school) {
        summoned_school_ = summoned_school;
    }

    void setSummonedAbility(const std::string& summoned_ability) {
        summoned_ability_ = summoned_ability;
    }

    auto& getLevelsOfSchools() {
        return levels_of_schools_;
    }

    void summon();
    void accumulateEnergy();
    void upgradeSchool();
    void act() override;
};

