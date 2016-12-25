/*
DataTables.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

This file uses the pugixml library (http://pugixml.org) to parse xml documents.
pugixml is Copyright (C) 2006-2015 Arseny Kapoulkine.
*/

#include "DataTables.hpp"
#include "Creature.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"
#include "Scenery.h"

#include "pugixml.hpp"


// For std::bind() placeholders _1, _2, ...
using namespace std::placeholders;

std::vector<CreatureData> Tables::initializeCreatureData()
{
	std::vector<CreatureData> data = std::vector<CreatureData>();

	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load_file("xml/CreatureData.xml");

	pugi::xml_node table = doc.child("table");

	for (pugi::xml_node node = table.child("creature"); node; node = node.next_sibling("creature"))
	{
		CreatureData newdata = CreatureData();
		
		newdata.type			= node.attribute("id").as_uint();
		newdata.combatID		= node.child("cID").text().as_uint();
		newdata.movementID		= node.child("mID").text().as_uint();
		newdata.texture			= node.child("textureID").text().as_uint();
		newdata.constitution	= node.child("con").text().as_int();
		newdata.strength		= node.child("str").text().as_int();
		newdata.dexterity		= node.child("dex").text().as_int();
		newdata.intelligence	= node.child("int").text().as_int();
		newdata.charisma		= node.child("cha").text().as_int();
		newdata.experience		= node.child("exp").text().as_int();
		newdata.level			= node.child("lvl").text().as_int();
		newdata.speed			= node.child("speed").text().as_float();
		newdata.aggroDistance	= node.child("aggroDistance").text().as_float();

		int width = node.child("textureRect").child("width").text().as_int();
		int height = node.child("textureRect").child("height").text().as_int();

		newdata.textureRect = sf::IntRect(0, 0, width, height);

		if (node.child("directions").first_child())
		{
			for (pugi::xml_node direction : node.child("directions").children("direction"))
			{
				float angle = direction.child("angle").text().as_float();
				float distance = direction.child("distance").text().as_float();
				float sign = direction.child("sign").text().as_float();

				newdata.directions.push_back(Direction(angle, distance, sign));
			}
		}

		if (node.child("teleports").first_child())
		{
			for (pugi::xml_node point : node.child("teleports").children("point"))
			{
				float x = point.child("x").text().as_float();
				float y = point.child("y").text().as_float();
				Compass comp = static_cast<Compass>(point.child("compass").text().as_int());
				newdata.teleportPoints.push_back(TeleportPoint(x, y, comp));
			}
		}

		data.push_back(newdata);
	}


	return data;
}

std::vector<ProjectileData> Tables::initializeProjectileData()
{
	std::vector<ProjectileData> data = std::vector<ProjectileData>();

	pugi::xml_document doc;
	doc.load_file("xml/ProjectileData.xml");

	pugi::xml_node table = doc.child("table");

	for (pugi::xml_node node = table.child("projectile"); node; node = node.next_sibling("projectile"))
	{
		ProjectileData newdata = ProjectileData();

		newdata.type = node.attribute("id").as_uint();
		newdata.texture = node.child("textureID").text().as_uint();

		data.push_back(newdata);
	}

	return data;
}

std::vector<PickupData> Tables::initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);

	data[Pickup::HealthRefill].texture = Textures::HealthRefill;
	data[Pickup::HealthRefill].action = [](Creature& a) { a.repair(25); };

	return data;
}

std::vector<SceneryData> Tables::initializeSceneryData()
{
	std::vector<SceneryData> data = std::vector<SceneryData>();

	pugi::xml_document doc;
	doc.load_file("xml/SceneryData.xml");

	pugi::xml_node table = doc.child("table");

	for (pugi::xml_node node = table.child("scenery"); node; node = node.next_sibling("scenery"))
	{
		SceneryData newdata = SceneryData();

		newdata.type = node.attribute("id").as_uint();
		newdata.texture = node.child("textureID").text().as_uint();

		data.push_back(newdata);
	}

	return data;
}

std::vector<std::vector<AreaData>> Tables::initializeAreaData()
{
	std::vector<std::vector<AreaData>> map{};
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("xml/AreaData.xml");

	int currentWidth = 0;
	int currentHeight = 0;

	pugi::xml_node data = doc.child("map");

	for (pugi::xml_node node = data.child("area"); node; node = node.next_sibling("area"))
	{
		int x = node.child("coordinates").child("x").text().as_int();
		int y = node.child("coordinates").child("y").text().as_int();

		if (x == currentWidth)
		{
			std::vector<AreaData> newRow;
			for (int j = 0; j < currentHeight; j++)
			{
				newRow.push_back(AreaData());
			}
			map.push_back(newRow);
			currentWidth = x + 1;
		}

		if (y == currentHeight)
		{
			map[x].push_back(AreaData());
			currentHeight = y + 1;
		}

		map[x][y].coordinates = sf::Vector2i(x, y);
		map[x][y].bgTexture = node.child("bgTextureID").text().as_uint();

		pugi::xml_node enemies = node.child("enemies");

		for (pugi::xml_node spawn = enemies.child("point"); spawn; spawn = spawn.next_sibling("point"))
		{
			unsigned int creatureType = spawn.child("creatureID").text().as_uint();
			float spawnX = spawn.child("x").text().as_float();
			float spawnY = spawn.child("y").text().as_float();
			map[x][y].enemySpawns.push_back(EnemySpawn(creatureType, spawnX, spawnY));
		}

		pugi::xml_node props = node.child("props");

		for (pugi::xml_node spawn = props.child("point"); spawn; spawn = spawn.next_sibling("point"))
		{
			unsigned int sceneryType = spawn.child("sceneryID").text().as_uint();
			float spawnX = spawn.child("x").text().as_float();
			float spawnY = spawn.child("y").text().as_float();
			map[x][y].scenerySpawns.push_back(ScenerySpawn(sceneryType, spawnX, spawnY));
		}
	}

	return map;
}

namespace Tables
{
	// Putting this here so that the global methods are only called once, hopefully
	const std::vector<CreatureData> Creatures = initializeCreatureData();
	const std::vector<ProjectileData> Projectiles = initializeProjectileData();
	const std::vector<PickupData> Pickups = initializePickupData();
	const std::vector<SceneryData> Props = initializeSceneryData();
	const std::vector<std::vector<AreaData>> Areas = initializeAreaData();
}