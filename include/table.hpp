#pragma once
#include <SFML/Graphics.hpp>

class Table
{
public:
	sf::Vector2f position;	// geometrical center of the table
	unsigned int width, height;
	float corner_radius, middle_radius;

	std::vector <sf::Vector2f> pockets, borders;
	//std::vector<Ball> balls;

	sf::Texture texture;
	sf::Sprite sprite;

	friend class Ball;

	// graphics variables go here

public:
	Table( const sf::Vector2f& position_, unsigned int width_, unsigned int height_, const std::string& name );
	~Table();

	sf::Vector2f getPosition() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	sf::Sprite getSprite() const;

	// graphics functions go here
};