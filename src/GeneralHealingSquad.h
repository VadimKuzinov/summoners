#pragma once
#include "GeneralSquad.h"


class GeneralHealingSquad : virtual public GeneralSquad {
protected:
    double healing_speed_;

    bool healing_ = false;

private:
    constexpr static auto unique_properties_ = std::make_tuple(
        std::make_pair(&GeneralHealingSquad::healing_speed_, "healing_speed")
    );

    constexpr static auto properties_ = std::tuple_cat(GeneralSquad::getProperties(), unique_properties_);

    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value);
    } 

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
    virtual ~GeneralHealingSquad() = default;    

    std::shared_ptr<Entity> clone() const {
        return std::shared_ptr<Entity>(new GeneralHealingSquad(*this));
    }  

    void tryToHeal() {
        healing_ = true;
    }
  
    bool isHealing() const {
        return healing_;
    }

    virtual void heal();
    void act() override;
    void update() override;
};

