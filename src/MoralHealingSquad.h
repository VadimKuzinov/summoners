#pragma once
#include "MoralSquad.h"
#include "GeneralHealingSquad.h"


class MoralHealingSquad : public MoralSquad, public GeneralHealingSquad {
private:
    constexpr static auto properties_ = std::tuple_cat(MoralSquad::getProperties(), GeneralHealingSquad::getUniqueProperties());

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
    virtual ~MoralHealingSquad() = default;

    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new MoralHealingSquad(*this));
    }

public:
    void act() override;

protected:
    void heal() override;
    void update() override;
};

