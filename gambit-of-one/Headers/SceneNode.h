#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include "SFML_facilities.h"
#include "Enumerations.hpp"
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

#endif //SCENE_NODE_H