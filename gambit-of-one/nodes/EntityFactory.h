/*
EntityFactory.h

DateCreated: July 4, 2016

This simple factory produces Creatures and Scenery.  What it makes depends on
the list of spawnpoints fed into it.
*/

#pragma once
#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H


#include "Creature.hpp"
#include "Scenery.h"
#include "DataTables.hpp"

#include <vector>

class EntityFactory
{
public:
	EntityFactory(TextureHolder& textures, FontHolder& fonts);
	~EntityFactory();

	std::vector<Creature*>	getCreatures(std::vector<EnemySpawn> points);
	std::vector<Scenery*>	getScenery(std::vector<ScenerySpawn> points);

private:
	TextureHolder*			mTextures;
	FontHolder*				mFonts;
};


#endif //ENTITY_FACTORY_H
