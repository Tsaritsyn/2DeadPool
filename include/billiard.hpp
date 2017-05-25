#pragma once
#include "ball.hpp"
#include "table.hpp"
#include <SFML/Graphics.hpp>

#define BILLIARD_SCALE .5f
#define PI 3.1415926f
#define MAX_POWER 7
#define PULL_BACK 10.0f

class Billiard
{
	sf::Vector2f position; 		// specifies the position of the ball to hit
	sf::Vector2f direction;		// the direction of the hit, amplitude of this vector is the strength of the hit

	sf::Texture texture;
	sf::Sprite sprite;

	void draw( sf::RenderWindow& window, float ball_radius );

public:
	Billiard();
	Billiard( const sf::Vector2f& position_, const sf::Vector2f& direction_, const std::string& filename );
	~Billiard();

	const sf::Vector2f& getPosition() const;
	const sf::Sprite& getSprite() const;

	void setPosition( const sf::Vector2f& position_ );
	void setDirection( const sf::Vector2f& direction_ );
	void setRotation( const sf::Vector2f& mousePosition_ );

	sf::Vector2f setHit( sf::RenderWindow& window, Table& table );
};