#include "Game.h"

template <typename T>
void pushVarAsChars(std::vector<char>& v, const T& var, char sep = '\n') {
    std::string s = toString(var);
    for (char c : s) {
        v.push_back(c);
    }
    v.push_back(sep);
}

std::vector<char> Game::getSerializedGameState(std::shared_ptr<Player> player) const {
    std::string type;
    std::vector<char> result = {};
    auto terrain = player->getSummoner()->getTerrain();
    auto qty = terrain->getMap().getQuantityOfSquads() + 1;
    pushVarAsChars(result, qty);

    for (auto&& squad : terrain->getMap()) {
        pushVarAsChars(result, squad->getSchoolName(), ' ');
        pushVarAsChars(result, squad->getAbilityName(), ' ');
        pushVarAsChars(result, squad->getCoords(), ' ');
        pushVarAsChars(result, typeid(*squad) == typeid(Obstacle) ? 1 : std::static_pointer_cast<InteractiveSquad>(squad)->getActingAngle(), ' ');
        pushVarAsChars(result, applyFunctionToCasted(typeid(*squad), ActingStatus{}, squad), ' ');
        pushVarAsChars(result, std::static_pointer_cast<Obstacle>(squad)->getCurHp() / std::static_pointer_cast<Obstacle>(squad)->getMaxHp(), ' ');
        pushVarAsChars(result, typeid(*squad) == typeid(Obstacle) ? 1 : (int)(squad != player->getSummoner() &&
            std::static_pointer_cast<InteractiveSquad>(squad)->getSummoner() != player->getSummoner()));
    }

    auto active = player->getActive();
    if (active && !active->isAlive()) {
        player->resetActive();
        active = nullptr;
    }

    if (active == nullptr) {
        pushVarAsChars(result, Point{ -1, -1 });
    }
    else {
        pushVarAsChars(result, active->getCoords());
    }

    std::shared_ptr<Entity> e = (active == nullptr ? player->getSummoner() : active);
    auto serialized = e->serialize();

    auto choices = player->getMenuOptions();
    pushVarAsChars(result, choices.size());
    for (auto&& option_name : choices) {
        pushVarAsChars(result, option_name);
    }

    pushVarAsChars(result, serialized.size());

    for (auto&& pair : serialized) {
        pushVarAsChars(result, pair.second, ' ');
        pushVarAsChars(result, pair.first);
    }
    result.push_back('\0');

    return result;
}

