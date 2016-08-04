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
#include "ResourceIdentifiers.hpp"

#include "pugixml.hpp"

using namespace std::placeholders;

DataTable::DataTable()
	: mCreatureData(Creature::TypeCount)
	, mProjectileData(Projectile::TypeCount)
	, mPickupData(Pickup::TypeCount)
	, mSceneryData(Scenery::TypeCount)
	, mAreaData()
	, mTextures()
	, mFonts()
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

TextureHolder* DataTable::getTextures() 
{
	return &mTextures;
}

FontHolder* DataTable::getFonts() 
{
	return &mFonts;
}

void DataTable::initializeCreatureData()
{
	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load_file("xml/CreatureData.xml");

	pugi::xml_node table = doc.child("table");

	for (pugi::xml_node node = table.child("creature"); node; node = node.next_sibling("creature"))
	{
		int id = node.attribute("id").as_int();

		mCreatureData[id].hitpoints = node.child("hitpoints").text().as_int();
		mCreatureData[id].speed = node.child("speed").text().as_float();
		mCreatureData[id].attackDamage = node.child("attackDamage").text().as_int();
		mCreatureData[id].aggroDistance = node.child("aggroDistance").text().as_float();
		mCreatureData[id].attackInterval = sf::seconds(node.child("attackInterval").text().as_float());
		int textureID = node.child("textureID").text().as_int();
		mCreatureData[id].texture = static_cast<Textures::ID>(textureID);

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

	pugi::xml_node table = doc.child("table");

	for (pugi::xml_node node = table.child("projectile"); node; node = node.next_sibling("projectile"))
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

	pugi::xml_node table = doc.child("table");

	for (pugi::xml_node node = table.child("scenery"); node; node = node.next_sibling("scenery"))
	{
		int id = node.attribute("id").as_int();

		mSceneryData[id].texture = static_cast<Textures::ID>(node.child("textureID").text().as_int());
	}
}

void DataTable::initializeAreaData()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/AreaData.xml");
	
	int currentWidth = 0;
	int currentHeight = 0;
	
	pugi::xml_node map = doc.child("map");

	for (pugi::xml_node node = map.child("area"); node; node = node.next_sibling("area"))
	{
		int x = node.child("coordinates").child("x").text().as_int();
		int y = node.child("coordinates").child("y").text().as_int();

		if (x >= currentWidth && x != 0)
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
		else
		{
			mAreaData.push_back(std::vector<AreaData>());
		}
		
		if (y >= currentHeight && y != 0)
		{
			for (int i = 0; i < (y - currentHeight); i++)
			{
				mAreaData[x].push_back(AreaData());
			}
			currentHeight = y + 1;
		}
		else
		{
			mAreaData[x].push_back(AreaData());
		}

		mAreaData[x][y].coordinates = sf::Vector2i(x, y);
		mAreaData[x][y].bgTexture = static_cast<Textures::ID>(node.child("bgTextureID").text().as_int());

		pugi::xml_node enemies = node.child("enemies");

		for (pugi::xml_node spawn = enemies.child("point"); spawn; spawn = spawn.next_sibling("point"))
		{
			int creatureID = spawn.child("creatureID").text().as_int();
			Creature::Type type = static_cast<Creature::Type>(creatureID);
			float spawnX = spawn.child("x").text().as_float();
			float spawnY = spawn.child("y").text().as_float();
			mAreaData[x][y].enemySpawns.push_back(EnemySpawn(type, spawnX, spawnY));
		}

		pugi::xml_node props = node.child("props");

		for (pugi::xml_node spawn = props.child("point"); spawn; spawn = spawn.next_sibling("point"))
		{
			int sceneryID = spawn.child("sceneryID").text().as_int();
			Scenery::Type type = static_cast<Scenery::Type>(sceneryID);
			float spawnX = spawn.child("x").text().as_float();
			float spawnY = spawn.child("y").text().as_float();
			mAreaData[x][y].scenerySpawns.push_back(ScenerySpawn(type, spawnX, spawnY));
		}
	}
}

void DataTable::loadResources()
{
	pugi::xml_document doc;
	doc.load_file("xml/TextureData.xml");

	pugi::xml_node table = doc.child("textures");

	for (pugi::xml_node node = table.child("texture"); node; node = node.next_sibling("texture"))
	{
		Textures::ID id = static_cast<Textures::ID>(node.attribute("id").as_int());
		mTextures.load(id, node.child("file").text().as_string());
	}

	mFonts.load(Fonts::ID::Main, "Media/Sansation.ttf");
}