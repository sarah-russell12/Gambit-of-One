/*
Creature.hpp

Date Last Updated: June 30, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use "facilities" header files anymore
- June 30, 2015: Built a new Creature class that better follows the
				 structure of the textbook code.
*/

#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "Command.hpp"
#include "CommandQueue.h"
#include "DataTables.hpp"
#include "Entity.h"
#include "Enumerations.hpp"
#include "Pickup.h"
#include "Projectile.h"
#include "SFML_facilities.h"
#include "TextNode.h"
#include "UtilityFunctions.hpp"

#include <SFML/Graphics/Sprite.hpp>

class Entity;

class Creature : public Entity
{
public:
	enum Type
	{
		Hero,
		Guide,
		Rat,
		Archer,
		Theif,
		TypeCount,
	};

public:
	Creature(Type type, const TextureHolder& textures, const FontHolder& fonts);

	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;
	virtual bool			isMarkedForRemoval() const;
	bool					isAllied() const;
	bool					isGuided() const;
	bool					isRanged() const;
	bool					isAttacking() const;
	float					getMaxSpeed() const;

	void					collectArrows(unsigned int count);

	void					attack();
	void					fireArrow();

	void					guideTowards(sf::Vector2f position);

//	For later: See if we can make the direction that the ranged creature is
//	firing depend on the position of the player
//	void					checkRotation(sf::Vector2f positon);

private:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);

	void					updateMovementPattern(sf::Time dt);

	void					checkAttacks(sf::Time dt, CommandQueue& commands);
	void					checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
	void					checkPickupDrop(CommandQueue& commands);
	void					checkAggro(sf::Vector2f position);

	void					createArrows(SceneNode& node, const TextureHolder& textures) const;
	void					createPickup(SceneNode& node, const TextureHolder& textures) const;
	void					createProjectile(SceneNode& node, Projectile::Type type,
									float xOffset, float yOffset,
									const TextureHolder& textures) const;

	void					updateTexts();

private:
	Type				mType;
	sf::Sprite			mSprite;

	TextNode*			mHealthDisplay;
	TextNode*			mArrowDisplay;

	sf::Time			mAttackCountdown;
	sf::Time			mFireCountdown;

	Command				mFireCommand;
	Command				mDropPickupCommand;

	bool				mIsFiring;
	bool				mIsAttacking;
	bool				mIsMarkedForRemoval;

	sf::Texture			mNormalTexture;
	sf::Texture			mAttackTexture;
	sf::Texture			mFiringTexture;

	int					mArrowAmmo;

	float				mTravelledDistance;
	std::size_t			mDirectionIndex;

	// For guided creatures, aggro (short for 'aggrovation', or the act of a
	// non-player entity wanting to attack a player entity) is set off when the
	// player is in within the aggro distance.
	sf::Vector2f		mTargetDirection;
	bool				mIsAggroed;
};

#endif // CREATURE_HPP