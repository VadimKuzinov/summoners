#pragma once
#include "InteractiveSquad.h"
#include "Point.h"
#include "Summoner.h"
#include <memory>


class GeneralSquad : public InteractiveSquad {
private:
    double damage_;
    double velocity_;
    int quantity_;
    double xp_for_destroying_;
    double attack_range_;

    bool moving_ = false;
    bool attacking_ = false;

private:
    constexpr static auto properties_ = std::tuple_cat(
        InteractiveSquad::getProperties(),
        std::make_tuple(
            std::make_pair(&GeneralSquad::damage_, "damage"),
            std::make_pair(&GeneralSquad::velocity_, "velocity"),
            std::make_pair(&GeneralSquad::quantity_, "quantity"),
            std::make_pair(&GeneralSquad::xp_for_destroying_, "xp_for_destroying"),
            std::make_pair(&GeneralSquad::attack_range_, "attack_range")
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
    virtual ~GeneralSquad() = default;

    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new GeneralSquad(*this));
    }

    double getDamage() const {
        return damage_;
    }

    double getVelocity() const {
        return velocity_;
    }

    double getQuantity() const {
        return quantity_;
    }

    double getXpForDestroying() const {
        return xp_for_destroying_;
    }

    double getAttackRange() const {
        return attack_range_;
    } 

    void setQuantity(int quantity) {
        quantity_ = quantity;
    }

    void tryToMove() {
        moving_ = true;
        attacking_ = false;
    }

    void tryToAttack() {
        moving_ = false;
        attacking_ = true;
    }

    bool isMoving() const {
        return moving_;
    }

    bool isAttacking() const {
        return attacking_;
    }

    void act() override;
    virtual void update();
    virtual void move();
    virtual void attack();

    virtual void giveDamage();
};

