#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entities_Facilities.h"
#include "Command.hpp"
#include "Enumerations.hpp"
#include "TextNode.h"

#include <SFML/Graphics/Sprite.hpp>


class Creature : public Entity
{
public:
	enum Type
	{
		Hero,
		Rat,
		TypeCount,
	};


public:
	Creature(Type type, const TextureHolder& textures, const FontHolder& fonts);

	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;
	virtual bool 			isMarkedForRemoval() const;
	bool					isAllied() const;
	float					getMaxSpeed() const;

	void					increaseFireRate();
	void					increaseSpread();
	void					collectMissiles(unsigned int count);

	void 					fire();
	void					launchMissile();


private:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void 			updateCurrent(sf::Time dt, CommandQueue& commands);
	void					updateMovementPattern(sf::Time dt);
	void					guideTowards(sf::Vector2f position);
	void					checkPickupDrop(CommandQueue& commands);
	void					checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

	void					createArrows(SceneNode& node, const TextureHolder& textures) const;
	void					createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;
	void					createPickup(SceneNode& node, const TextureHolder& textures) const;

	void					updateTexts();

	void					collectArrows(unsigned int count);
	void					fireArrow();
	


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

	int						mArrowCount;

	Command 				mDropPickupCommand;
	float					mTravelledDistance;
	std::size_t				mDirectionIndex;
	TextNode*				mHealthDisplay;
	TextNode*				mArrowDisplay;
};

#endif // AIRCRAFT_HPP