#include <cmath>
#include "ball.hpp"

#define MIN_SPEED .1
#define REFLECTION .7

Ball::Ball()
{
	position = sf::Vector2f( 0, 0 );
	velocity = sf::Vector2f( 0, 0 );
	angular_velocity = (float)0;
	angular_acceleration = (float)0;
	radius = 15;
	mass = (float)1;
	friction = (float)0.018;
}

Ball::Ball( const sf::Vector2f& position_, const sf::Vector2f& velocity_, float angular_velocity_,
		float angular_acceleration_, int radius_, float mass_, float friction_ )
{
	position = position_;
	velocity = velocity_;
	angular_velocity = angular_velocity_;
	angular_acceleration = angular_acceleration_;
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

	// moving the ball as if there were no borders
	if ( speed > MIN_SPEED )
	{
		sf::Vector2f acceleration = -velocity / speed * friction;
		position += velocity * time + acceleration * time * time / (float)2;

		sf::Vector2f future_velocity = velocity + acceleration * time;
		if ( ( future_velocity.x * velocity.x < 0 ) || ( future_velocity.y * velocity.y < 0 ) )
			velocity = sf::Vector2f( 0, 0 );
		else
			velocity = future_velocity;
	}
	else
		velocity = sf::Vector2f( 0, 0 );

	// reflection from the borders
	if (position.y < table.borders[0].y + radius)
	{
		position.y = ( table.borders[0].y + radius ) * 2 - position.y;
		velocity.y = -velocity.y * (float)REFLECTION;
	}
	if (position.x > table.borders[5].x - radius)
	{
		position.x = ( table.borders[5].x - radius ) * 2 - position.x;
		velocity.x = -velocity.x * (float)REFLECTION;
	}
	if (position.y > table.borders[7].y - radius)
	{
		position.y = ( table.borders[7].y - radius ) * 2 - position.y;
		velocity.y = -velocity.y * (float)REFLECTION;
	}
	if (position.x < table.borders[11].x + radius)
	{
		position.x = ( table.borders[11].x + radius ) * 2 - position.x;
		velocity.x = -velocity.x * (float)REFLECTION;
	}
}

sf::Vector2f Ball::getPosition() const
{
	return position;
}

sf::Vector2f Ball::getVelocity() const
{
	return velocity;
}

float Ball::getAngVelocity() const
{
	return angular_velocity;
}

float Ball::getAngAcceleration() const
{
	return angular_acceleration;
}

int Ball::getRadius() const
{
	return radius;
}

float Ball::getMass() const
{
	return mass;
}