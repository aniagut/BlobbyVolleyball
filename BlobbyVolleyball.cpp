#include "text.cpp"
#include "window.cpp"
#include "textures.cpp"
#include "body.cpp"
#include "wall.cpp"
#include <iostream>
using namespace sf;

int main()
{
	//window
	RenderWindow gameWindow;
	setWindowProperties(gameWindow, 1200, 900, "Blobby Volleyball", 70, 0.8);

	//font
	Font font;
	setFont(font, "Fonts/ugly-byte-free-trial.regular.ttf");

	//score
	unsigned player1Points = 0;
	unsigned player2Points = 0;

	//displaying score
	Text middleText("POINTS", font, 120), points1Text(std::to_string(player1Points), font, 120), points2Text(std::to_string(player2Points), font, 120);
	setTextProperties(middleText, Color::Yellow, 1, gameWindow.getSize().x / 2, gameWindow.getSize().y / 10);
	setTextProperties(points1Text, Color::Yellow, 1, gameWindow.getSize().x / 4, gameWindow.getSize().y / 10);
	setTextProperties(points2Text, Color::Yellow, 1, gameWindow.getSize().x, gameWindow.getSize().y / 10);

	//textures
	Texture textures[4];
	std::string textures_filenames[4] = { "images/bgd.bmp","images/ball.png","images/blobby_red.png","images/blobby_blue.png" };
	loadTextures(textures, textures_filenames, 4);

	//sprites
	Sprite background(textures[0]), ball(textures[1]), player1(textures[2]), player2(textures[3]);

	//define center point for rotation etc.
	ball.setOrigin(textures[1].getSize().x / 2, textures[1].getSize().x / 2);
	player1.setOrigin(textures[2].getSize().x / 2, textures[2].getSize().y / 2);
	player2.setOrigin(textures[3].getSize().x / 2, textures[3].getSize().y / 2);

	//setting walls
	//left
	setWall(0, gameWindow.getSize().y / (2 * 0.8), 10, gameWindow.getSize().y / 0.8);
	//right
	setWall(gameWindow.getSize().x / 0.8, gameWindow.getSize().y / (2 * 0.8), 10, gameWindow.getSize().y / 0.8);
	//down
	setWall(gameWindow.getSize().x / (2 * 0.8), gameWindow.getSize().y / 0.8, gameWindow.getSize().x / 0.8, 100);
	//middle
	setWall(gameWindow.getSize().x / (2 * 0.8), gameWindow.getSize().y / 0.8 - 160, 10, 320);

	//defining players
	b2Body* player1Body = defineDynamicBody(gameWindow.getSize().x / (4 * 0.8 * scale), gameWindow.getSize().y / (0.6 * scale) - 30);
	b2Body* player2Body = defineDynamicBody(gameWindow.getSize().x * 3 / (4 * 0.8 * scale), gameWindow.getSize().y / (0.6 * scale) - 30);

	b2CircleShape circle;
	circle.m_radius = textures[2].getSize().x / (2 * scale);
	player1Body->CreateFixture(&circle, 1);
	player2Body->CreateFixture(&circle, 1);
	player1Body->SetFixedRotation(true);
	player2Body->SetFixedRotation(true);


	//defining ball
	b2Body* ballBody = defineDynamicBody(gameWindow.getSize().x * 3 / (4 * 0.8 * scale), gameWindow.getSize().y / (0.8 * scale) - 30);
	b2FixtureDef fixtureDef;
	circle.m_radius = textures[1].getSize().x / (2 * scale);
	fixtureDef.shape = &circle;
	fixtureDef.restitution = 0.85;
	fixtureDef.density = 0.1;
	ballBody->CreateFixture(&fixtureDef);

	//for points
	bool onGround = 0;

	//simulation step
	while (gameWindow.isOpen()) {
		Event e;
		while (gameWindow.pollEvent(e))
		{
			if (e.type == Event::Closed)
				gameWindow.close();
		}

		for (int n = 0; n < 2; n++) {
			world.Step(1 / 60.0, 8, 3);
		}

		gameWindow.draw(background);

		//player1 move
		b2Vec2 playerPosition = player1Body->GetPosition();
		b2Vec2 playerVelocity = player1Body->GetLinearVelocity();

		if (Keyboard::isKeyPressed(Keyboard::D))  playerVelocity.x = 5;
		if (Keyboard::isKeyPressed(Keyboard::A))   playerVelocity.x = -5;
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			if (playerPosition.y >= gameWindow.getSize().y / (2 * scale * 0.8)) {
				playerVelocity.y = -10;
			}
		}

		if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A)) {
			playerVelocity.x = 0;
		}
		player1Body->SetLinearVelocity(playerVelocity);

		//player2 move
		playerPosition = player2Body->GetPosition();
		playerVelocity = player2Body->GetLinearVelocity();

		if (Keyboard::isKeyPressed(Keyboard::Right))  playerVelocity.x = 5;
		if (Keyboard::isKeyPressed(Keyboard::Left))  playerVelocity.x = -5;
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (playerPosition.y >= gameWindow.getSize().y / (2 * scale * 0.8)) {
				playerVelocity.y = -10;
			}
		}

		if (!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left)) {
			playerVelocity.x = 0;
		}
		player2Body->SetLinearVelocity(playerVelocity);

		//ball move
		playerVelocity = ballBody->GetLinearVelocity();
		if (playerVelocity.Length() > 20) {
			ballBody->SetLinearVelocity(20 / playerVelocity.Length() * playerVelocity);
		}

		//setting position
		b2Vec2 position = player1Body->GetPosition();

		player1.setPosition(position.x * scale, position.y * scale);
		gameWindow.draw(player1);

		position = player2Body->GetPosition();
		player2.setPosition(position.x * scale, position.y * scale);
		gameWindow.draw(player2);

		position = ballBody->GetPosition();
		float angle = ballBody->GetAngle();
		ball.setPosition(position.x * scale, position.y * scale);
		ball.setRotation(angle * 60.f);
		gameWindow.draw(ball);

		//score
		if (onGround && ball.getPosition().y < 400) {
			onGround = 0;
		}
		if (!onGround && ball.getPosition().y > 700) {
			onGround = 1;
			if (ball.getPosition().x < 600) {
				player2Points += 1;
				changeDisplayedText(points2Text, std::to_string(player2Points));
			}
			else {
				player1Points += 1;
				changeDisplayedText(points1Text, std::to_string(player1Points));
			}
		}
		gameWindow.draw(middleText);
		gameWindow.draw(points1Text);
		gameWindow.draw(points2Text);
		gameWindow.display();
	}
	return 0;
}