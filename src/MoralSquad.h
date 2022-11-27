#pragma once
#include "GeneralSquad.h"


class MoralSquad : virtual public GeneralSquad {
private:
    double morality_ = 0;
    double stabilization_speed_;

private:
    constexpr static auto unique_properties_ = std::make_tuple(
        std::make_pair(&MoralSquad::morality_, "morality"),
        std::make_pair(&MoralSquad::stabilization_speed_, "stabilization_speed")
    );

    constexpr static auto properties_ = std::tuple_cat(GeneralSquad::getProperties(), unique_properties_);

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value);
    }

protected:
    double getMakingDamageCf() const;

protected:
    constexpr static auto getUniqueProperties() {
        return unique_properties_;
    }

    constexpr static auto getProperties() {
        return properties_;
    }

public:
    std::vector<std::pair<std::string, std::string>> serialize() const override {
        return serializeImpl(*this, properties_);
    }

public:
    virtual ~MoralSquad() = default;

    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new MoralSquad(*this));
    }

    double getMorality() const {
        return morality_;
    }

    double getStabilizationSpeed() const {
        return stabilization_speed_;
    }

    void stabilizeMorality();

    void act() override;
    void update() override;
    void attack() override;
    void giveDamage() override;
};

