#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode
{
public:

	enum cDirection
	{
		North,
		South,
		East,
		West,
		TypeCount
	};

	explicit			Entity(int hitpoints);

	void				setVelocity(sf::Vector2f velocity);
	void				setVelocity(float vx, float vy);
	void				accelerate(sf::Vector2f velocity);
	void				accelerate(float vx, float vy);
	void				guideTowards(sf::Vector2f position);
	sf::Vector2f		getVelocity() const;
	
	int					getHitpoints() const;
	void				repair(int points);
	void				damage(int points);
	void				destroy();
	virtual bool		isDestroyed() const;
	bool				isImmune() const;
	
protected:
	virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);

private:
	void				checkImmunity(sf::Time dt);

private:
	sf::Vector2f		mVelocity;
	int					mHitpoints;
	bool				mImmunity;
	sf::Time			mImmunityCountdown;
	//cDirection			mCompass;
};

#endif // ENTITY_HPP