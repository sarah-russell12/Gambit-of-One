/*
DataTable.h

Date Created: August 1, 2016

Date Last Updated: August 2, 2016

This class moves all the data loading for the entities, areas, and resources
into one place.

This class uses the pugixml library (http://pugixml.org) to parse xml documents.
pugixml is Copyright (C) 2006-2015 Arseny Kapoulkine.

Updates: 
	- August 2, 2016: Finished implementing loadResources(). Moved Data 
					  structures to their own file
*/

#pragma once
#ifndef DATA_TABLE_H
#define DATA_TABLE_H

#include "DataStructures.h"
#include "ResourceHolder.hpp"

class DataTable
{
public:
	DataTable();
	~DataTable();

public:
	void										initializeData();

	std::vector<CreatureData>					getCreatureData() const;
	std::vector<ProjectileData>					getProjectileData() const;
	std::vector<PickupData>						getPickupData() const;
	std::vector<SceneryData>					getSceneryData() const;
	std::vector<std::vector<AreaData>>			getAreaData() const;

	TextureHolder*								getTextures();
	FontHolder*									getFonts();

private:
	void										initializeCreatureData();
	void										initializeProjectileData();
	void										initializePickupData();
	void										initializeSceneryData();
	void										initializeAreaData();

	void										loadResources();

private:
	std::vector<CreatureData>					mCreatureData;
	std::vector<ProjectileData>					mProjectileData;
	std::vector<PickupData>						mPickupData;
	std::vector<SceneryData>					mSceneryData;
	std::vector<std::vector<AreaData>>			mAreaData;

	TextureHolder								mTextures;
	FontHolder									mFonts;
};

#endif // DATA_TABLE_H