#include <cmath>
#include "ball.hpp"

#define MIN_SPEED .1
#define REFLECTION .7

float getInterval( const sf::Vector2f& point1, const sf::Vector2f& point2 )
{
	return sqrt( ( point2.x - point1.x ) * ( point2.x - point1.x ) + ( point2.y - point1.y ) * ( point2.y - point1.y ) );
}

float getScalar( const sf::Vector2f& vector1, const sf::Vector2f& vector2 )
{
	return ( vector1.x * vector2.x + vector1.y * vector2.y );
}

float getLength( const sf::Vector2f& vector )
{
	return sqrt( vector.x * vector.x + vector.y * vector.y );
}

Ball::Ball()
{
	position = sf::Vector2f( 0, 0 );
	velocity = sf::Vector2f( 0, 0 );
	radius = 15;
	mass = (float)1;
	friction = (float)0.018;
}

Ball::Ball( const sf::Vector2f& position_, const sf::Vector2f& velocity_, int radius_, float mass_, float friction_ )
{
	position = position_;
	velocity = velocity_;
	radius = radius_;
	mass = mass_;
	friction = friction_;
}

Ball::~Ball() {}

// returns 1 if the ball is still on the table, 0 if got into a pocket
int Ball::update( float time, const Table& table )
{
	// absolute value of the ball's velocity
	float speed = sqrt( velocity.x * velocity.x + velocity.y * velocity.y );
	// velocity normal to a pocket's corner
	sf::Vector2f normal_velocity;
	// a direction from the ball to the corner of a pocket
	sf::Vector2f normal;
	// future position if there were no borders and pockets
	sf::Vector2f future_position;

	// moving the ball as if there were no borders
	if ( speed > MIN_SPEED )
	{
		sf::Vector2f acceleration = -velocity / speed * friction;
		future_position = position + velocity * time + acceleration * time * time / (float)2;

		sf::Vector2f future_velocity = velocity + acceleration * time;
		if ( ( future_velocity.x * velocity.x < 0 ) || ( future_velocity.y * velocity.y < 0 ) )
			velocity = sf::Vector2f( 0, 0 );
		else
			velocity = future_velocity;
		position = future_position;
	}
	else
	{
		velocity = sf::Vector2f( 0, 0 );
		return 1;
	}

	// reflection from the pockets' corners
	for (int i = 0; i < table.borders.size(); ++i)
	{
		if ( getInterval( future_position, table.borders[i] ) < radius )
		{
			normal = table.borders[i] - position;
			float normal_length = getLength( normal );
			normal /= normal_length;
			normal_velocity = normal * getScalar( velocity, normal );
			velocity -= normal_velocity * ( (float)1 + (float)REFLECTION );
			position += velocity * time;
			return 1;
		}
	}

	// reflection from the borders
	if ( ( ( position.y < table.borders[0].y + radius ) && ( position.x >= table.borders[0].x ) && ( position.x <= table.borders[1].x ) ) ||
		( ( position.x >= table.borders[2].x ) && ( position.x <= table.borders[3].x ) ) )
	{
		position.y = ( table.borders[0].y + radius ) * 2 - position.y;
		velocity.y = -velocity.y * (float)REFLECTION;
	}
	if ( ( position.x > table.borders[4].x - radius ) && ( position.y >= table.borders[4].y ) && ( position.y <= table.borders[5].y ) )
	{
		position.x = ( table.borders[5].x - radius ) * 2 - position.x;
		velocity.x = -velocity.x * (float)REFLECTION;
	}
	if ( ( ( position.y > table.borders[6].y - radius ) && ( position.x <= table.borders[6].x ) && ( position.x >= table.borders[7].x ) ) ||
		( ( position.x <= table.borders[8].x ) && ( position.x >= table.borders[9].x ) ) )
	{
		position.y = ( table.borders[7].y - radius ) * 2 - position.y;
		velocity.y = -velocity.y * (float)REFLECTION;
	}
	if ( ( position.x > table.borders[10].x + radius ) && ( position.y >= table.borders[10].y ) && ( position.y <= table.borders[11].y ) )
	{
		position.x = ( table.borders[11].x + radius ) * 2 - position.x;
		velocity.x = -velocity.x * (float)REFLECTION;
	}

	return 1;
}

sf::Vector2f Ball::getPosition() const
{
	return position;
}

sf::Vector2f Ball::getVelocity() const
{
	return velocity;
}

int Ball::getRadius() const
{
	return radius;
}

float Ball::getMass() const
{
	return mass;
}