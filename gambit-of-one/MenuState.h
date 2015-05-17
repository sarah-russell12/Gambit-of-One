#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "States_Facilities.h"
#include "Gui_Facilities.h"
#include <vector>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context& context);
	
	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

private:
	GUI::Container					mGUIContainer;
	sf::Sprite						mBackgroundSprite;
};


#endif //MENU_STATE_H