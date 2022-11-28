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

    /**Allows to set member field of any type using only strings therefore object can be easily
     * deserialized.
     * Function must be called only during the initialization of instance of this class
     * in corresponding initialization function of friend class.
     * 
     * @param name name of field
     * @param value value to set converted to std::string
     */
    void set(const std::string& name, const std::string& value) override {
        return setImpl(*this, properties_, name, value);
    }

protected:
    /**Function can be used in derived classes to reach base class properties
     * and add own ones. The main purpose of function is too provide convenient
     * interface for serialization or deserialization.
     * @returns 
     * Tuple of pairs, where first element represents pointer to
     * member field and second one is the string represantation of
     * corresponding field.
     */
    constexpr static auto getProperties() {
        return properties_;
    }

public:
    /**@returns
     * Vector of pairs with field name and corresponding value converted to std::string.
     */
    std::vector<std::pair<std::string, std::string>> serialize() const override {
        return serializeImpl(*this, properties_);
    }

public:
    virtual ~GeneralSquad() = default;
    
    /**@returns
     * Base pointer to cloned instance of this class.
     */
    std::shared_ptr<Entity> clone() const override {
        return std::shared_ptr<Entity>(new GeneralSquad(*this));
    }

    /**@returns
     * Basic damage squad can apply to the other squad.
     */
    double getDamage() const {
        return damage_;
    }

    /**@returns
     * Max relative velocity the instance can pass per
     * one iteration of the game.
     */
    double getVelocity() const {
        return velocity_;
    }

    /**@returns 
     * XP that enemy's summoner will receive
     * for destroying this squad.
     */
    double getXpForDestroying() const {
        return xp_for_destroying_;
    }

    /**@returns
     * Max reachable distance between this squad and 
     * other one so that this squad can actually
     * give damage to other squad.
     */
    double getAttackRange() const {
        return attack_range_;
    } 

    void setQuantity(int quantity) {
        quantity_ = quantity;
    }

    /**Notify game class that squad is going to move at the next iteration. 
     */
    void tryToMove() {
        moving_ = true;
        attacking_ = false;
    }

    /**Notify game class that squad is going to attack at the next iteration.
     */
    void tryToAttack() {
        moving_ = false;
        attacking_ = true;
    }

    /**@returns 
     * Moving status.
     */
    bool isMoving() const {
        return moving_;
    }

    /**@returns 
     * Attacking status.
     */
    bool isAttacking() const {
        return attacking_;
    }

public:
    /**Function that should be called every iteration of the game.
     * It calls corresponding acting methods depending on flags received from 
     * functions isMoving(), isAttacking(), etc.
     */
    void act() override;

protected:
    /**Update target point is captured is not nullptr or 
     * set captured to nullptr if it was destroyed.
     */
    virtual void update();

    /**The necessary condition for this function to be called is 
     * true value of isMoving(). 
     * Implements moving of this squad towards target point.
     */
    virtual void move();

    /**The necessary condition for this functuion to be called is
     * true value of isAttacking().
     * Implements attack of this squad directed to captured squad.
     */
    virtual void attack();

    /**Apply attack towards captured to wit give corrected basic damage.
     */
    virtual void giveDamage();
};

/*! \class GeneralSquad GeneralSquad.h "src/GeneralSquad.h"
 *  \brief This is a GeneralSquad class.
 *
 *  Squad is inherited from Obstacle and unlike base can move and attack.
 */