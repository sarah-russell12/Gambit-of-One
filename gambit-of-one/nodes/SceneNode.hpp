/*
SceneNode.hpp

Date Last Updated: August 16, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

SceneNodes are the structure in which all Entity interaction and transformation
is built on.  SceneNodes have a tree structure to them: All SceneNodes, except
for the root node will have parent SceneNodes, and all ScenNodes can have any
number of children SceneNodes.  The children SceneNodes will have positions and
transformations that are relative to their parent.  When their parent
transforms, all the children transform relative to their parent.
*/

#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include "..\Category.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <set>
#include <memory>
#include <utility>

struct Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	// This might need this adjustment if I want to carry the PlayerCreature across areas
	typedef std::shared_ptr<SceneNode> Ptr;
	typedef std::pair<SceneNode*, SceneNode*> Pair;


public:
	explicit				SceneNode(Category::Type category = Category::None);

	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);

	void					update(sf::Time dt, CommandQueue& commands);

	sf::Vector2f			getWorldPosition() const;
	sf::Transform			getWorldTransform() const;

	void					onCommand(const Command& command, sf::Time dt);
	virtual unsigned int	getCategory() const;

	void					checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
	void					checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
	void					removeWrecks();
	virtual sf::FloatRect	getBoundingRect() const;
	virtual bool			isMarkedForRemoval() const;
	virtual bool			isDestroyed() const;


private:
	virtual void			updateCurrent(sf::Time dt, CommandQueue& commands);
	void					updateChildren(sf::Time dt, CommandQueue& commands);

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
	void					drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	std::vector<Ptr>		mChildren;
	SceneNode*				mParent;
	Category::Type			mDefaultCategory;
};

bool	collision(const SceneNode& lhs, const SceneNode& rhs);
float	distance(const SceneNode& lhs, const SceneNode& rhs);

#endif // SCENENODE_HPP