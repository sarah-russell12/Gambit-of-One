/*
EntityFactory.cpp

Date Created: July 4, 2016

Defines all the methods declared in EntityFactory.h
*/

#include "EntityFactory.h"
#include "Utility.hpp"

EntityFactory::EntityFactory()
	: mTextures(), mFonts()
{
	loadResources();
}

EntityFactory::~EntityFactory() {}

std::vector<Creature*>	EntityFactory::getCreatures(std::vector<EnemySpawn> points)
{
	std::vector<Creature*> creatures{};

	for (std::size_t i = 0; i < points.size(); i++)
	{
		EnemySpawn point = points[i];
		auto enemy = new Creature(point.type, mTextures, mFonts);
		enemy->setPosition(point.x, point.y);
		creatures.push_back(enemy);
	}
	
	return creatures;
}

std::vector<Scenery*> EntityFactory::getScenery(std::vector<ScenerySpawn> points)
{
	std::vector<Scenery*> props{};

	for (std::size_t i = 0; i < points.size(); i++)
	{
		ScenerySpawn point = points[i];
		Scenery* prop = new Scenery(point.type, mTextures);
		prop->setPosition(point.x, point.y);
		props.push_back(prop);
	}

	return props;
}

void EntityFactory::loadResources()
{
	mTextures.load(Textures::Hero, "Media/Textures/HeroSpriteSheet.png");
	mTextures.load(Textures::Rat, "Media/Textures/RatSpriteSheet.png");
	mTextures.load(Textures::Archer, "Media/Textures/ArcherSpriteSheet.png");
	mTextures.load(Textures::Bandit, "Media/Textures/BanditSpriteSheet.png");
	mTextures.load(Textures::Rock, "Media/Textures/Rock.png");
	mTextures.load(Textures::Arrow, "Media/Textures/Arrow.png");
	mTextures.load(Textures::HealthRefill, "Media/Textures/HealthPotion.png");

	mFonts.load(Fonts::Main, "Media/Sansation.ttf");
}