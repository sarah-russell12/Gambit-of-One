#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP
#include "SFML_facilities.h"
#include "States_Facilities.h"
#include <assert.h>
#include <vector>
#include <map>
#include <functional>

class StateStack : private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit			StateStack(State::Context context);
	template<typename T>
	void				registerState(States::ID stateID);
	void				update(sf::Time dt);
	void				draw();
	void				pushState(States::ID stateID);
	void				popState();
	void				clearStates();
	void				handleEvent(const sf::Event& event);

	bool				isEmpty() const;

private:
	State::Ptr			createState(States::ID stateID);
	void				applyPendingChanges();

private:
	struct PendingChange
	{
		Action			action;
		States::ID		stateID;
	};

private:
	std::vector<State::Ptr>				mStack;
	std::vector<PendingChange>			mPendingList;
	State::Context						mContext;
	std::map < States::ID,
		std::function < State::Ptr() >> mFactories;
};

#endif //STATE_STACK_HPP