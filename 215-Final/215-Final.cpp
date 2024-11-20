// 215-Final.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

const float KB_SPEED = 0.2;
void LoadTex(Texture& tex, string filename) {
	if (!tex.loadFromFile(filename)) {
		cout << "Could not load" << filename << endl;
	}
}

void MovePaddle(PhysicsSprite & paddle, unsigned int elapsedMS) {
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		Vector2f newPos(paddle.getCenter());
		newPos.x = newPos.x + (KB_SPEED * elapsedMS);
		//constrain y movement
		newPos.y = 393; 
		paddle.setCenter(newPos);
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		Vector2f newPos(paddle.getCenter());
		newPos.x = newPos.x - (KB_SPEED * elapsedMS);
		//constrain y movement
		newPos.y = 393;
		paddle.setCenter(newPos);
	}
}

int main()
{
	// Create our window and world with gravity 0
	RenderWindow window(VideoMode(800, 600), "Breakout");
	World world(Vector2f(0,0));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(200, 300));
	ball.setRadius(10);
	ball.applyImpulse(Vector2f(0.1, -0.4));
	world.AddPhysicsBody(ball);

	/*Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(760, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);*/

	//Create a wall
	PhysicsRectangle rightwall;
	rightwall.setSize(Vector2f(20, 560));
	rightwall.setCenter(Vector2f(790, 300));
	rightwall.setStatic(true);
	world.AddPhysicsBody(rightwall);

	//Create another wall
	PhysicsRectangle leftwall;
	leftwall.setSize(Vector2f(20, 560));
	leftwall.setCenter(Vector2f(10, 300));
	leftwall.setStatic(true);
	world.AddPhysicsBody(leftwall);

	//Create a ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(760, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	/*//Create a center block
	PhysicsRectangle block;
	block.setSize(Vector2f(50, 50));
	block.setCenter(Vector2f(400, 300));
	block.setStatic(true);
	world.AddPhysicsBody(block);*/

	//create paddle
	PhysicsSprite& paddle = *new PhysicsSprite();
	Texture paddleTex;
	paddle.setStatic(true);
	LoadTex(paddleTex, "images/paddle.png");
	paddle.setTexture(paddleTex);
	Vector2f sz = paddle.getSize();
	paddle.setCenter(Vector2f(400,
		400 - (sz.y / 2)));
	world.AddPhysicsBody(paddle);
	

	
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	Time currentTime(lastTime);

	while (true) {
		// calculate MS since last frame
		currentTime = clock.getElapsedTime();
		Time deltaTime = (currentTime - lastTime);
		long deltaTimeMS = deltaTime.asMilliseconds();
		if (deltaTimeMS > 0.2) {
			lastTime = currentTime;
			world.UpdatePhysics(deltaTimeMS);
			MovePaddle(paddle, deltaTimeMS);
		}
		window.clear();
		window.draw(paddle);
		window.draw(ball);
		window.draw(rightwall);
		window.draw(leftwall);
		window.draw(ceiling);
		window.display();
		}
		
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
