#pragma once
#include "table.hpp"
#include <SFML/Graphics.hpp>

class Ball
{
	// movement properties
	sf::Vector2f position;
	sf::Vector2f velocity;

	// material properties
	int radius;

	// graphics	variables
	sf::Texture texture;
	sf::Vector2f scale;
	unsigned int style;

public:
	Ball( const sf::Vector2f& position_, const sf::Vector2f& velocity_, int radius_ );
	~Ball();

	int update( float time, const Table& table );
	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	
	int getRadius() const;

	// graphics functions go here
	void draw( sf::RenderWindow &window );
};
