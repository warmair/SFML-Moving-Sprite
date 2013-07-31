//First steps in SFML, based upon SFML Game Development by Artur Moreira
//Simon Barlow 31/07/13

#include <SFML/Graphics.hpp>
#include <iostream>



class Game : private sf::NonCopyable	//Generate Game Class, could be put in a header but I like dealing with it in one file for 1-class programs
{
public:
			Game();
	   void run();
private:
		void processEvents();
		void update(sf::Time elapsedTime);   
		void render();

		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:

	static const sf::Time TimePerFrame;

	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::RenderWindow mWindow;

	bool mIsMovingUp;
	bool mIsMovingLeft;
	bool mIsMovingRight;
	bool mIsMovingDown;
};

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mIsMovingUp(false)
	, mIsMovingLeft(false)
	, mIsMovingRight(false)
	, mIsMovingDown(false)

{
	if(!mTexture.loadFromFile ("C:/Users/Simon/My Documents/GitHub/SFML-Game-Development-Book/01_intro/Media/Textures/Eagle.png"))
	{
		//panic
	}

	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while(mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
		timeSinceLastUpdate -= TimePerFrame;
		processEvents();
		update(TimePerFrame);
		}
		render();
		
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
		}

	}

}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}


void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= 10.f;
	if (mIsMovingDown)
		movement.y += 10.f;
	if (mIsMovingLeft)
		movement.x -= 10.f;
	if (mIsMovingRight)
		movement.x += 10.f;

	mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}


int main()
{
	Game game;
	game.run();
}
