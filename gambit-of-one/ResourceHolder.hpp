/*
ResourceHolder.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

A ResourceHolder is a mapping of Resource::ID enum values to Standard Library
unique pointers to the Resource.  This makes sure that in the code, we are not
repeatedly calling on Resources in different areas in the game, which would take
up not only memory, but would cause us to have to change many lines of code if
the location of resources change.  This allows the program to access the same
set of resources without taking up memory.
*/

#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>



template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;


private:
	void insertResource(Identifier id, std::unique_ptr<Resource> resource);


private:
	std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "ResourceHolder.inl"

#endif // RESOURCEHOLDER_HPP