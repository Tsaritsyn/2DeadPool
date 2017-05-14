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
	
	sf::Texture texture;
	sf::Vector2f scale;
	unsigned int style;
	
	// graphics variables go here
	sf::Texture texture;
	sf::Vector2f scale;
	unsigned int style;

public:
	Ball( const sf::Vector2f& position_, const string name, int radius_, const int style_ = 1, const sf::Vector2f& velocity_ = sf::Vector2f (0.0f, 0.0f),  float mass_ = 1.0f, float friction_ = 0.018f );
	~Ball();

	int update( float time, const Table& table );
	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	
	int getRadius() const;
	float getMass() const;

	// graphics functions go here
	void draw(sf::RenderWindow &window);
};
