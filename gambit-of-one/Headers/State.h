#ifndef STATE_H
#define STATE_H
#include "SFML_facilities.h"
#include <memory>
//#include "StateStack.hpp"
#include "Enumerations.hpp"
#include "ResourceHolder.hpp"
#include "Player.h"

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;
	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures,
			FontHolder& fonts, Player& player);
		sf::RenderWindow*	window;
		TextureHolder*		textures;
		FontHolder*			fonts;
		Player*				player;
	};

public:
						State(StateStack& stack, Context context);
	virtual				~State();
	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;

protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStackClear();

	Context				getContext() const;

private:
	StateStack*			mStack;
	Context				mContext;

};

#endif //STATE_H