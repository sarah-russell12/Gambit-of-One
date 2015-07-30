/*
SceneNode.h

Date Last Updated: July 30, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- July 30, 2015: Copied over a version from the textbook code that was
				 written while following the textbook and then edited
				 to fit what was needed of it.
*/

#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <cassert>
#include <memory>
#include <set>
#include <vector>

#include "Foreach.hpp"
#include "Enumerations.hpp"

struct Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode>			Ptr;
	typedef std::pair<SceneNode*, SceneNode*>	Pair;

public:
	explicit				SceneNode(Category::Type category = Category::None);
	
	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);

	void					update(sf::Time dt, CommandQueue& commands);

	sf::Transform			getWorldTransform() const;
	sf::Vector2f			getWorldPosition() const;

	virtual unsigned int	getCategory() const;
	void					onCommand(const Command& command, sf::Time dt);

	virtual sf::FloatRect	getBoundingRect() const;
	virtual bool			isDestroyed() const;
	virtual bool			isMarkedForRemoval() const;

	void					checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	void					checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void					removeWrecks();

private:
	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);
	void				updateChildren(sf::Time dt, CommandQueue& commands);

private:
	std::vector<Ptr>	mChildren;
	SceneNode*			mParent;
	Category::Type		mDefaultCategory;
};

bool collision(const SceneNode& lhs, const SceneNode& rhs);
float distance(const SceneNode& lhs, const SceneNode& rhs);

#endif //SCENE_NODE_H