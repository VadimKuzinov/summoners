#pragma once
#include "Setter.h"
#include "Entity.h"
#include "Point.h"
#include <memory>


class Obstacle : public Entity {
private:
    std::weak_ptr<Terrain> terrain_;
    Point coords_ = {0, 0};
    friend class Terrain;

private:
    std::string school_name_;
    std::string ability_name_;
    friend class Ability;

private:
    double max_hp_;
    double cur_hp_;
    int priority_;

private:
    constexpr static auto properties_ = std::make_tuple(
        std::make_pair(&Obstacle::max_hp_, "max_hp"),
        std::make_pair(&Obstacle::cur_hp_, "cur_hp"),
        std::make_pair(&Obstacle::priority_, "priority"),
        std::make_pair(&Obstacle::coords_, "coords"),
        std::make_pair(&Obstacle::school_name_, "school_name"),
        std::make_pair(&Obstacle::ability_name_, "ability_name")
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
    virtual ~Obstacle() = default;

    std::shared_ptr<Entity> clone() const override {
        return std::shared_ptr<Entity>(new Obstacle(*this));
    }

private:
    void setSchoolName(const std::string& school_name) {
        school_name_ = school_name;
    }

    void setAbilityName(const std::string& ability_name) {
        ability_name_ = ability_name;
    }

public:
    const std::string& getSchoolName() const final {
        return school_name_;
    }

    const std::string& getAbilityName() const final {
        return ability_name_;
    }

protected:
    void setCoords(Point new_coords) {
        coords_ = new_coords;
    }

    void setCurHp(double cur_hp) {
        cur_hp_ = cur_hp;
    }

public:
    std::shared_ptr<Terrain> getTerrain() const {
        return std::shared_ptr(terrain_);
    }

    Point getCoords() const final {
        return coords_;
    }

    void receiveDamage(double dmg_value) override {
        cur_hp_ -= dmg_value;
    }

    double getMaxHp() const {
        return max_hp_;
    }

    void act() override {
    }

    bool isAlive() const final {
        return cur_hp_ > 0;
    }

    int getPriority() const final {
        return priority_;
    }

    double getCurHp() const {
        return cur_hp_;
    }
};

