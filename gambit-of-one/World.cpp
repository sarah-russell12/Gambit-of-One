#include "World.h"

World::World(sf::RenderWindow& window)
	: mWindow(window)
{
	mWorldView = sf::View(window.getDefaultView());
	mWorldBounds = sf::FloatRect(
		0.f,					//left x position
		0.f,					//top y position
		mWorldView.getSize().x,	//width
		2000.f					//height
		);
	mSpawnPosition = sf::Vector2f(
		mWorldView.getSize().x / 2.f,
		mWorldBounds.height - mWorldView.getSize().y
		);
	mPlayerAircraft = nullptr;


	loadTextures();
	buildScene();
	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
	mTextures = TextureHolder();
	std ::string eaglePath = "Media/Textures/Eagle.png";
	std::string raptorPath = "Media/Textures/Raptor.png";
	std::string desertPath = "Media/Textures/Desert.png";
	mTextures.load(Textures::Eagle, eaglePath);
	mTextures.load(Textures::Raptor, raptorPath);
	mTextures.load(Textures::Desert, desertPath);
}

void World::buildScene()
{
	//setting up the graph
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	//setting up the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(
		new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(
		mWorldBounds.left,
		mWorldBounds.top);
	mSceneLayers[Background]->attachChild(
		std::move(backgroundSprite));

	//setting up the lead aircraft Eagle
	std::unique_ptr<Aircraft> leader(
		new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	std::unique_ptr<Aircraft> leftEscort(
		new Aircraft(Aircraft::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(
		new Aircraft(Aircraft::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));
}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt)
{
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	mPlayerAircraft->setVelocity(0.f, 0.f);

	//Foward commands to the scene graph
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);
	}

	sf::Vector2f velocity = mPlayerAircraft->getVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f)
	{
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
	}
	mPlayerAircraft->accelerate(sf::Vector2f(0.f, mScrollSpeed));

	//Regular update step
	mSceneGraph.update(dt);

	sf::FloatRect viewBounds(
		mWorldView.getCenter() - mWorldView.getSize() / 2.f,
		mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}

CommandQueue World::getCommandQueue()
{
	return mCommandQueue;
}