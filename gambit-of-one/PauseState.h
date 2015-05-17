#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "States_Facilities.h"
#include "Gui_Facilities.h"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context& context);

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

private:
	sf::Text				mPausedText;
	GUI::Container			mGUIContainer;
};


#endif //PAUSE_STATE_H