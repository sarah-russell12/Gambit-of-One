#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "States_Facilities.h"
#include "SFML_facilities.h"

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void				draw();
	virtual bool				update(sf::Time dt);
	virtual bool				handleEvent(const sf::Event& event);

private:
	sf::Sprite					mBackgroundSprite;
	sf::Text					mText;

	bool						mShowText;
	sf::Time					mTextEffectTime;
};


#endif //TITLE_STATE_H