/*
Component.cpp

Date Last Updated: August 16, 2015

This source file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.
*/

#include "Component.hpp"

namespace GUI
{

	Component::Component()
		: mIsSelected(false)
		, mIsActive(false)
	{
	}

	Component::~Component()
	{
	}

	bool Component::isSelected() const
	{
		return mIsSelected;
	}

	void Component::select()
	{
		mIsSelected = true;
	}

	void Component::deselect()
	{
		mIsSelected = false;
	}

	bool Component::isActive() const
	{
		return mIsActive;
	}

	void Component::activate()
	{
		mIsActive = true;
	}

	void Component::deactivate()
	{
		mIsActive = false;
	}

}