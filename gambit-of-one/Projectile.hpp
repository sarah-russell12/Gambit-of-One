#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Projectile : public Entity
{
public:
	enum Type
	{
		AlliedBullet,
		EnemyBullet,
		Missile,
		TypeCount
	};


public:
	Projectile(Type type, const TextureHolder& textures, const Entity::cDirection& direction);

	void					guideTowards(sf::Vector2f position);
	bool					isGuided() const;

	virtual unsigned int	getCategory() const;
	virtual sf::FloatRect	getBoundingRect() const;
	float					getMaxSpeed() const;
	int						getDamage() const;
	void					updateSprite();

	//void					setSprite();

private:
	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::Sprite				leftArrow;
	sf::Sprite				rightArrow;
	sf::Sprite				downArrow;
	sf::Sprite				upArrow;

	Type					mType;
	sf::Sprite				mSprite;
	sf::Sprite				OriginSprite;
	sf::Vector2f			mTargetDirection;
	cDirection				mCDirection;
};

#endif // PROJECTILE_HPP