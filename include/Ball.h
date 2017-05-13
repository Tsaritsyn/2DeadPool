#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <Table.h>

class Ball
{
	sf::Vector2f position;
	sf::Vector2f vel, accel;
	sf::Vector3f ang_vel, ang_accel;
	float M, R;
	sf::Texture texture;
	sf::Vector2f scale;

public:
	
	Ball(sf::Vector2f pos, const std::string name, float r, sf::Vector2f v = sf::Vector2f(0, 0), sf::Vector2f a = sf::Vector2f(0, 0), sf::Vector3f w = sf::Vector3f(0, 0, 0), sf::Vector3f e = sf::Vector3f(0, 0, 0), float m = 1);
	void draw(sf::RenderWindow &window);
	void move(float dt);
	int ifCloseToBorder(const Table &table);
	void collisionToBorder(const int i, const Table &table);
	bool ifCloseToPocket(const Table &table);
};
