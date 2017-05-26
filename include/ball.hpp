#pragma once
#include <SFML/Graphics.hpp>
#include "table.hpp"

#define MIN_SPEED 1e-2f
#define FRICTION 35e-5f
#define BORDER_REFLECTION .6f
#define BALL_REFLECTION .83f

class Ball
{
	// movement properties
	sf::Vector2f position;		// the position of the center of the ball
	sf::Vector2f velocity;		// the velocity of the ball

	// material properties
	float radius;				// the radius of the ball

	// graphical variables
	sf::Texture texture;		// the texture (picture) of the ball
	sf::Sprite sprite;
	int style;

	int update( float time, const Table& table );	// moves the ball as if 'time' time units went by
	void draw( sf::RenderWindow &window ); 			// draws the ball

	friend class Table;
	friend class Billiard;

public:
	Ball();
	Ball( const sf::Vector2f& position_, const sf::Vector2f& velocity_, float radius_,
		const std::string& name, int style_ );
	~Ball();
};
