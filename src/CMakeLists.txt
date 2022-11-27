cmake_minimum_required(VERSION 3.8)

project(game_library)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES Academy.cpp GeneralSquad.cpp InteractiveSquad.cpp Map.cpp MoralHealingSquad.cpp Point.cpp Summoner.cpp Terrain.cpp GeneralHealingSquad.cpp MoralSquad.cpp Entity.cpp)
set(HEADERS Academy.h Concepts.h Entity.h GeneralHealingSquad.h GeneralSquad.h InteractiveSquad.h Map.h MoralHealingSquad.h MoralSquad.h Obstacle.h Point.h Setter.h Squads.h Summoner.h Terrain.h Utils.h toString.h)

add_library(game STATIC ${SOURCES} ${HEADERS})