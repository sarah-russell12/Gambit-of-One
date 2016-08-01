/*
DataTable.cpp

Date Created: August 1, 2016

Date Last Updated: August 1, 2016

Defines all the methods declared in DataTable.h

This class uses the pugixml library (http://pugixml.org) to parse xml documents.
pugixml is Copyright (C) 2006-2015 Arseny Kapoulkine.
*/

#include "DataTable.h"
#include "Creature.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"
#include "Scenery.h"

#include "pugixml.hpp"

using namespace std::placeholders;

DataTable::DataTable()
	: mCreatureData(Creature::TypeCount)
	, mProjectileData(Projectile::TypeCount)
	, mPickupData(Pickup::TypeCount)
	, mSceneryData(Scenery::TypeCount)
	, mAreaData()
{}

DataTable::~DataTable() {}

void DataTable::initializeData()
{
	initializeCreatureData();
	initializeProjectileData();
	initializePickupData();
	initializeSceneryData();
	initializeAreaData();

	loadResources();
}

std::vector<CreatureData> DataTable::getCreatureData() const
{
	return mCreatureData;
}

std::vector<ProjectileData> DataTable::getProjectileData() const
{
	return mProjectileData;
}

std::vector<PickupData> DataTable::getPickupData() const
{
	return mPickupData;
}

std::vector<SceneryData> DataTable::getSceneryData() const
{
	return mSceneryData;
}

std::vector<std::vector<AreaData>> DataTable::getAreaData() const
{
	return mAreaData;
}

TextureHolder DataTable::getTextures() const
{
	return mTextures;
}

FontHolder DataTable::getFonts() const
{
	return mFonts;
}

void DataTable::initializeCreatureData()
{
	pugi::xml_document creatureDoc;
	creatureDoc.load_file("xml/CreatureData.xml");

	for (pugi::xml_node node : creatureDoc.children("creature"))
	{
		int id = node.attribute("id").as_int();

		mCreatureData[id].hitpoints = node.child("hitpoints").text().as_int();
		mCreatureData[id].speed = node.child("speed").text().as_float();
		mCreatureData[id].attackDamage = node.child("attackDamage").text().as_int();
		mCreatureData[id].aggroDistance = node.child("aggroDistance").text().as_float();
		mCreatureData[id].attackInterval = sf::seconds(node.child("attackInterval").text().as_float());
		mCreatureData[id].texture = static_cast<Textures::ID>(node.child("TextureID").text().as_int());

		int width = node.child("textureRect").child("width").text().as_int();
		int height = node.child("textureRect").child("height").text().as_int();

		mCreatureData[id].textureRect = sf::IntRect(0, 0, width, height);

		if (node.child("directions").first_child())
		{
			for (pugi::xml_node direction : node.child("directions").children("direction"))
			{
				float angle = direction.child("angle").text().as_float();
				float distance = direction.child("distance").text().as_float();
				float sign = direction.child("sign").text().as_float();

				mCreatureData[id].directions.push_back(Direction(angle, distance, sign));
			}
		}

		if (node.child("teleports").first_child())
		{
			for (pugi::xml_node point : node.child("teleports").children("point"))
			{
				float x = point.child("x").text().as_float();
				float y = point.child("y").text().as_float();
				Compass comp = static_cast<Compass>(point.child("compass").text().as_int());
				mCreatureData[id].teleportPoints.push_back(TeleportPoint(x, y, comp));
			}
		}
	}
}

void DataTable::initializeProjectileData()
{
	pugi::xml_document doc;
	doc.load_file("xml/ProjectileData.xml");

	for (pugi::xml_node node : doc.children("projectile"))
	{
		int id = node.attribute("id").as_int();

		mProjectileData[id].speed = node.child("speed").text().as_float();
		mProjectileData[id].damage = node.child("damage").text().as_int();
		mProjectileData[id].texture = static_cast<Textures::ID>(node.child("textureID").text().as_int());
	}
}

void DataTable::initializePickupData()
{
	// This is something that requires hand doing since the action requires 
	// a function
	mPickupData[Pickup::HealthRefill].texture = Textures::HealthRefill;
	mPickupData[Pickup::HealthRefill].action = [](Creature& a) { a.repair(25); };
}

void DataTable::initializeSceneryData()
{
	pugi::xml_document doc;
	doc.load_file("xml/SceneryData.xml");

	for (pugi::xml_node node : doc.children("scenery"))
	{
		int id = node.attribute("id").as_int();

		mSceneryData[id].texture = static_cast<Textures::ID>(node.child("textureID").text().as_int());
	}
}

void DataTable::initializeAreaData()
{
	pugi::xml_document doc;
	doc.load_file("xml/AreaData.xml");
	
	int currentWidth = 0;
	int currentHeight = 0;
	
	for (pugi::xml_node node : doc.children("area"))
	{
		int x = node.child("coordinates").child("x").text().as_int();
		int y = node.child("coordinates").child("x").text().as_int();

		if (x >= currentWidth)
		{
			for (int i = 0; i < (x - currentWidth); i++)
			{
				std::vector<AreaData> newRow;
				for (int j = 0; j < currentHeight; j++)
				{
					newRow.push_back(AreaData());
				}
				mAreaData.push_back(newRow);
			}
			currentWidth = x + 1;
		}
		if (y >= currentHeight)
		{
			for (int i = 0; i < (y - currentHeight); i++)
			{
				mAreaData[x].push_back(AreaData());
			}
			currentHeight = y + 1;
		}

		mAreaData[x][y].coordinates = sf::Vector2i(x, y);
		mAreaData[x][y].bgTexture = static_cast<Textures::ID>(node.child("bgTextureID").text().as_int());

		if (node.child("enemies").first_child())
		{
			for (pugi::xml_node spawn : node.child("enemies").children("spawnpoint"))
			{
				Creature::Type type = static_cast<Creature::Type>(spawn.child("creatureID").text().as_int());
				float spawnX = spawn.child("spawnX").text().as_float();
				float spawnY = spawn.child("spawnY").text().as_float();
				mAreaData[x][y].enemySpawns.push_back(EnemySpawn(type, x, y));
			}
		}

		if (node.child("props").first_child())
		{
			for (pugi::xml_node spawn : node.child("props").children("spawnpoint"))
			{
				Scenery::Type type = static_cast<Scenery::Type>(spawn.child("sceneryID").text().as_int());
				float spawnX = spawn.child("spawnX").text().as_float();
				float spawnY = spawn.child("spawnY").text().as_float();
				mAreaData[x][y].scenerySpawns.push_back(ScenerySpawn(type, x, y));
			}
		}
	}
}