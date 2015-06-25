/*
ResourceHolder.hpp

Date Last Updated: June 21, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
*/

#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include "Enumerations.hpp"
#include "SFML_Facilities.h"

#include <map>
#include <memory>
#include <functional>
#include <assert.h>


template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void			load(Identifier id, const std::string& filename);
	Resource&		get(Identifier id);
	const Resource&	get(Identifier id) const;
	template <typename Parameter>
	void			load(Identifier id, const std::string& filename,
		const Parameter& secondParam);

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};


typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#include "ResourceHolder.inl"

#endif //RESOUCE_HOLDER_HPP