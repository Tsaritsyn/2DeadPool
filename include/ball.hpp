#pragma once
#include "table.hpp"
#include <SFML/Graphics.hpp>

#define MIN_SPEED 1e-2f
#define FRICTION 4e-4f
#define BORDER_REFLECTION .7f
#define BALL_REFLECTION .8f

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

	// moves the ball as if 'time' time units went by
	int update( float time, const Table& table );

	void draw( sf::RenderWindow &window ); 				// draws the ball

	friend class Table;

public:
	Ball();		// position = velocity = ( 0, 0 ), radius = 1
	Ball( const sf::Vector2f& position_, const sf::Vector2f& velocity_, float radius_,
		const std::string& name, int style_ );
	~Ball();

	sf::Vector2f getPosition() const;					// returns the position
	sf::Vector2f getVelocity() const;					// returns the velocity
	int getRadius() const;								// returns the radius
	int getStyle() const;								// returns the style

	void setVelocity( const sf::Vector2f& velocity_ ); 	// sets the velocity
};
