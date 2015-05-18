#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"
#include "Command.hpp"
#include "ResourceIdentifiers.hpp"
#include "Projectile.hpp"
#include "TextNode.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Creature : public Entity
{
public:
	enum Type
	{
		Rat,
		TypeCount
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
	void					checkPickupDrop(CommandQueue& commands);
	void					checkProjectileLaunch(sf::Time dt, CommandQueue& commands);

	void					createBullets(SceneNode& node, const TextureHolder& textures) const;
	void					createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;
	void					createPickup(SceneNode& node, const TextureHolder& textures) const;

	void					updateTexts();


private:
	Type					mType;
	sf::Sprite				mSprite;
	Command 				mAttackCommand;
	sf::Time				mFireCountdown;
	bool 					mIsAttacking;
	bool 					mIsMarkedForRemoval;

	int						mFireRateLevel;

	Command 				mDropPickupCommand;
	float					mTravelledDistance;
	std::size_t				mDirectionIndex;
	TextNode*				mHealthDisplay;
};

#endif // AIRCRAFT_HPP