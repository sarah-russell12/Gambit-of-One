#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "States_Facilities.h"
#include "World.h"
#include "Player.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	World				mWorld;
	Player&				mPlayer;
};

#endif //GAMESTATE_H