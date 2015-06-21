/*
Creature.hpp

Date Last Updated: June 20, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use "facilities" header files anymore
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


class Creature : public Entity
{
public:
	enum Type
	{
		Hero,
		Rat,
		Thief,
		Archer,
		TypeCount,
	};


public:
	Creature(Type type, const TextureHolder& textures, const FontHolder& fonts);

	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;
	virtual bool 			isMarkedForRemoval() const;
	int						getDamage();
	bool					isAllied() const;
	bool					isRanged() const;
	bool					isGuided() const;
	bool					isAttacking();
	float					getMaxSpeed() const;

	void					increaseFireRate();
	void					increaseSpread();
	void					collectArrows(unsigned int count);

	void					guideTowards(sf::Vector2f position);

	void 					attack();
	void					fireArrow();



private:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void 			updateCurrent(sf::Time dt, CommandQueue& commands);
	void					updateMovementPattern(sf::Time dt);
	
	void					checkPickupDrop(CommandQueue& commands);
	void					checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

	void					createArrows(SceneNode& node, const TextureHolder& textures) const;
	void					createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;
	void					createPickup(SceneNode& node, const TextureHolder& textures) const;

	void					updateTexts();

	
	


private:
	Type					mType;
	sf::Sprite				mSprite;
	Command 				mAttackCommand;
	Command					mFireCommand;
	sf::Time				mFireCountdown;
	bool 					mIsAttacking;
	bool					mIsFiring;
	bool 					mIsMarkedForRemoval;

	bool					mIsGuidedEnemy;
	sf::Vector2f			mTargetDirection;

	int						mDamage;
	int						mArrowCount;

	Command 				mDropPickupCommand;
	float					mTravelledDistance;
	std::size_t				mDirectionIndex;
	TextNode*				mHealthDisplay;
	TextNode*				mArrowDisplay;
};

#endif // CREATURE_HPP