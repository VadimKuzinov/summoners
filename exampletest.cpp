#include <gtest/gtest.h>
#include "src/Terrain.h"
#include "src/Summoner.h"
#include "server/Game.h"
#include "src/Map.h"
#include <iostream>


TEST(Summoner, IsActuallySummoning) {
	Game game("../../../cfg/academy", "../../../cfg/map3");
	auto terrain = game.getTerrain();
	auto firstSummoner = terrain->getSummonerFirst();
	auto coords = firstSummoner->getCoords();
	firstSummoner->setTargetCoords({ coords.x + 3, coords.y - 2 });
	firstSummoner->tryToSummon();
	firstSummoner->summon();
	firstSummoner->setSummonedSchool("parallel_universes");
	firstSummoner->setSummonedAbility("kaneki");
	firstSummoner->tryToSummon();
	firstSummoner->act();
	std::shared_ptr<Entity> sth = nullptr;
	sth = terrain->getMap()[Point{ coords.x + 3, coords.y - 2 }];
	ASSERT_TRUE(sth != nullptr && sth->getAbilityName() == "kaneki");
}

TEST(Summoner, IsNotSummoningOutOfRange) {
	Game game("../../../cfg/academy", "../../../cfg/map3");
	auto terrain = game.getTerrain();
	auto firstSummoner = terrain->getSummonerFirst();
	auto coords = firstSummoner->getCoords();
	firstSummoner->setTargetCoords({ coords.x - 20, coords.y - 20 });
	firstSummoner->tryToSummon();
	firstSummoner->summon();
	firstSummoner->setSummonedSchool("parallel_universes");
	firstSummoner->setSummonedAbility("kaneki");
	firstSummoner->tryToSummon();
	firstSummoner->act();
	auto sth = terrain->getMap()[Point{ coords.x - 20, coords.y - 20 }];
	ASSERT_TRUE(sth == nullptr);
}


int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

