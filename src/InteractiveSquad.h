#pragma once
#include "Obstacle.h"


class InteractiveSquad : public Obstacle {
private:
    std::shared_ptr<Entity> captured_;
    Point target_coords_ = {0, 0};

    std::shared_ptr<Entity> summoner_;
    friend class Summoner;

private:
    constexpr static auto properties_ = std::tuple_cat(
        Obstacle::getProperties(),
        std::make_tuple(
            std::make_pair(&InteractiveSquad::target_coords_, "target_coords")
        )
    );

    void set(const std::string& name, const std::string& value) override {
        setImpl(*this, properties_, name, value);
    }

protected:
    constexpr static auto getProperties() {
        return properties_;
    }

public:
    std::vector<std::pair<std::string, std::string>> serialize() const override {
        return serializeImpl(*this, properties_);
    }

private:
    void setSummoner(std::shared_ptr<Entity> summoner) {
        summoner_ = summoner;
    }

public:
    virtual ~InteractiveSquad() = default;

    std::shared_ptr<Entity> getSummoner() const {
        return summoner_;
    }

    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new InteractiveSquad(*this));
    }

    auto getCaptured() const {
        return captured_;
    }

    void setCaptured(std::shared_ptr<Entity> e) {
        captured_ = e;
    }

    auto getTargetCoords() const {
        return target_coords_;
    }

    void setTargetCoords(Point where) {
        target_coords_ = where;
    }

    double getActingAngle() const;
    void setActingAngle(double);
};

