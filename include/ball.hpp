#pragma once
#include <SFML/Graphics.hpp>
#include "table.hpp"

class Ball
{
	// movement properties
	sf::Vector2f position;
	sf::Vector2f velocity;

	// material properties
	int radius;
	float mass;
	float friction;

	// graphics variables go here

public:
	Ball();
	Ball( const sf::Vector2f& position_, const sf::Vector2f& velocity_, int radius_, float mass_, float friction_ );
	~Ball();

	int update( float time, const Table& table );
	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;

	int getRadius() const;
	float getMass() const;

	// graphics functions go here
};