StateStack::StateStack(State::Context context)
	: mStack()
	, mPendingList()
	, mContext(context)
	, mFactories() {}

template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::update(sf::Time dt)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			return;
	}
}void StateStack::draw()
{
	for (State::Ptr& state : mStack)
	{
		state->draw();
	}
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = mStack.begin(); itr != mStack.end(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			return;
	}

	applyPendingChanges();
}



void StateStack::pushState(States::ID stateID)
{
	PendingChange change;
	change.stateID = stateID;
	change.action = Push;
	mPendingList.push_back(change);
}

void StateStack::popState()
{
	PendingChange change;
	change.action = Pop;
	mPendingList.push_back(change);
}

void StateStack::clearStates()
{
	PendingChange change;
	change.action = Clear;
	mPendingList.push_back(change);
}

void StateStack::applyPendingChanges()
{
	for (PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateID));
			break;
		case Pop:
			mStack.pop_back();
			break;
		case Clear:
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}