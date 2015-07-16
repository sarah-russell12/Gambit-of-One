/*
SceneNode.h

Date Last Updated: June 21, 2015

This header file was made during the Spring 2015 SFML Game Development
Tutorial at New College of Florida.  This code follows the code from the
textbook "SFML Game Development" by Artur Moreira, Henrick Vogelius
Hansson, and Jan Haller.

Updates:
- June 20, 2015:
	- Moved to "Headers" folder
	- Opted to not use most of "facilities" header files anymore
- June 25, 2015:
	- Moved the distance and collision methods, which had to do with
	  SceneNodes, to here.
	- Changed the distance method to reflect textbook's code
*/

#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "Enumerations.hpp"
#include "SFML_facilities.h"
#include "UtilityFunctions.hpp"

#include <vector>
#include <set>
#include <memory>
#include <utility>

struct Command;
class CommandQueue;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
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

	void					checkSceneCollision(SceneNode& sceneGraph,
												std::set<Pair>& collisionPairs);
	void					checkNodeCollision(SceneNode& node,
												std::set<Pair>& collisionPairs);
	void					removeWrecks();
	virtual sf::FloatRect	getBoundingRect() const;
	virtual bool			isMarkedForRemoval() const;
	virtual bool			isDestroyed() const;


private:
	virtual void		draw(sf::RenderTarget& target,
							sf::RenderStates states) const;
	virtual void		drawCurrent(sf::RenderTarget& target,
							sf::RenderStates states) const;
	void				drawChildren(sf::RenderTarget& target,
							sf::RenderStates states) const;
	void				drawBoundingRect(sf::RenderTarget& target,
							sf::RenderStates states) const;

	virtual void		updateCurrent(sf::Time dt, CommandQueue& commands);
	void				updateChildren(sf::Time dt, CommandQueue& commands);
	

private:
	std::vector<Ptr>	mChildren;
	SceneNode*			mParent;
	Category::Type		mDefaultCategory;
};

bool			collision(const SceneNode& lhs, const SceneNode& rhs);
float			distance(const SceneNode& e2, const SceneNode& e1);

#endif //SCENE_NODE_H