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
	firstSummoner->setSummonedSchool("parallel_universes");
	firstSummoner->setSummonedAbility("kaneki");
	firstSummoner->tryToSummon();
	firstSummoner->act();
	auto sth = terrain->getMap()[Point{ coords.x - 20, coords.y - 20 }];
	ASSERT_TRUE(sth == nullptr);
}

TEST(GeneralSquad, MovingOnEmptyRoad) {
	Game game("../../../cfg/academy", "../../../cfg/map3");
	auto terrain = game.getTerrain();
	auto firstSummoner = terrain->getSummonerFirst();
	auto coords = firstSummoner->getCoords();
	firstSummoner->setTargetCoords({ coords.x + 3, coords.y - 2 });
	firstSummoner->setSummonedSchool("parallel_universes");
	firstSummoner->setSummonedAbility("kaneki");
	firstSummoner->tryToSummon();
	firstSummoner->act();
	auto sth = terrain->getMap()[Point{ coords.x + 3, coords.y - 2 }];
	auto casted = std::static_pointer_cast<GeneralSquad>(sth);
	casted->setTargetCoords(Point{ coords.x + 2, coords.y - 10 });
	casted->tryToMove();
	while (casted->isMoving()) {
		casted->act();
	}

	auto act_coords = casted->getCoords();
	auto exp_coords = Point{ coords.x + 2, coords.y - 10 };
	EXPECT_EQ(act_coords, exp_coords);
}


int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

