/*
Creature.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Creature is one of the main Entities of the game.  They fight with each
other using varied behaviors including ranged attacks and melee attacks.
Some move can move in patterns, some stand still, while others will
converge on the player when they are within a certain distance.
*/

#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "Entity.hpp"
#include "..\Command.hpp"
#include "..\ResourceIdentifiers.hpp"
#include "Projectile.hpp"
#include "TextNode.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Creature : public Entity
{
public:
	enum Type
	{
		Hero,
		Guide,
		Rat,
		Archer,
		Bandit,
		TypeCount
	};


public:
	Creature(Type type, const TextureHolder& textures, const FontHolder& fonts);

	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;
	int						getDamage() const;
	virtual bool 			isMarkedForRemoval() const;
	bool					isAllied() const;
	bool					isAggroed() const;
	bool					isGuided() const;
	bool					isRanged() const;
	bool					isMelee() const;
	bool					isAttacking() const;
	bool					isBlocked() const;
	float					getMaxSpeed() const;
	Entity::cDirection		getCompass() const;
	float					getAggroDistance() const;

	void					checkAggro(sf::Vector2f position);
	void					increaseFireRate();
	void					increaseSpread();

	void					attack();
	void 					fire();

	void					guideTowards(sf::Vector2f position);
	void					block();
	
private:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void 			updateCurrent(sf::Time dt, CommandQueue& commands);
	void					updateMovementPattern(sf::Time dt);
	void					checkPickupDrop(CommandQueue& commands);
	void					checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
	void					checkAttacks(sf::Time dt, CommandQueue& commands);
	
	Entity::cDirection		checkCompass() const;

	void					createArrows(SceneNode& node, const TextureHolder& textures) const;
	void					createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;
	void					createPickup(SceneNode& node, const TextureHolder& textures) const;

	void					updateSprite();
	void					updateCompass();
	void					updateCreatureDirection();
	void					updateTexts();
	void					turn();

private:
	Type					mType;
	sf::Sprite				mSprite;
	
	Command 				mFireCommand;

	sf::Time				mFireCountdown;
	sf::Time				mAttackCountdown;

	bool 					mIsFiring;
	bool					mIsAttacking;
	bool 					mIsMarkedForRemoval;
	bool					mIsAggroed;
	bool					mIsBlocked;					// Attempt to fix movement

	cDirection				mCompass;
	TextureHolder			mHeroTextures;

	int						mFireRateLevel;
	int						mSpreadLevel;

	Command 				mDropPickupCommand;
	float					mTravelledDistance;
	std::size_t				mDirectionIndex;
	TextNode*				mHealthDisplay;

	sf::Texture				mNormalTexture;
	sf::Texture				mAttackTexture;
	sf::Texture				mFiringTexture;

	sf::Vector2f			mTargetDirection;
	float					mAggroDistance;
};

#endif // CREATURE_HPP