#ifndef GAME_H
#define GAME_H
#include "SFML_Facilities.h"
#include "World.h"
#include "Player.h"

class Game {
public:
	Game();
	void	run();

private:
	void	processEvents();
	void	update(sf::Time deltaTime);
	void	render();
	void	processInput();

	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	Player mPlayer;
	World mWorld;
	bool mIsPaused;

	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	const float PlayerSpeed = 20;
};

#endif //GAME_H