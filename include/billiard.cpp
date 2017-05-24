#include "billiard.hpp"
#include "vector_operations.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

#define HIT_DISTANCE 100
#define SCALE .5
#define PI 3.1415926
#define MAX_POWER 50
#define PULL_BACK 2.0f

Billiard::Billiard()
{
	position = direction = sf::Vector2f( 0, 0 );
}

Billiard::Billiard( const sf::Vector2f& position_, const sf::Vector2f& direction_, const std::string& filename )
{
	position = position_;
	direction = direction_;

	// graphical initialization
	texture.loadFromFile( filename );
	sf::Vector2f size( texture.getSize() );
	sprite.setScale( sf::Vector2f( SCALE, SCALE ) );
	sprite.setTexture( texture );
	sprite.setPosition( position );
	sprite.setRotation( 90 + atan2f( direction.x, direction.y ) * 180 / PI );
}

Billiard::~Billiard() {}

const sf::Vector2f& Billiard::getPosition() const
{
	return position;
}

const sf::Sprite& Billiard::getSprite() const
{
	return sprite;
}

void Billiard::setPosition( const sf::Vector2f& position_ )
{
	position = position_;
}

void Billiard::setDirection( const sf::Vector2f& direction_ )
{
	direction = direction_;
}

void Billiard::setRotation( const sf::Vector2f& mousePosition_ )
{
	direction = position - mousePosition_;
	sprite.setRotation( 142 + atan2f( direction.y, direction.x ) * 180 / PI );
}

sf::Vector2f Billiard::setHit( sf::RenderWindow* window, const sf::Vector2f& cue_ball, float ball_radius )
{
	// specify the position of the hit
	position = cue_ball;

	// hit power
	float power = 0.0;
	sf::Vector2f mouse_position = sf::Vector2f( sf::Mouse::getPosition( *window ) );
	float initial_power = getLength( mouse_position - position );			// zero hit power level

	// power bar
	sf::RectangleShape powerBar( sf::Vector2f( window->getSize().x / 20, window->getSize().y / 3 ) );
	powerBar.setPosition( sf::Vector2f( window->getSize().x * .925, window->getSize().y * .5 ) );
	sf::RectangleShape powerBar_color;
	powerBar_color.setFillColor( sf::Color( 255, 0, 0 ) );

	while ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
	{
		// retrieving the hit power
		mouse_position = sf::Vector2f( sf::Mouse::getPosition( *window ) );
		power = ( getLength( mouse_position - position ) - initial_power ) / 5;
		if ( power > MAX_POWER )
        	power = MAX_POWER;
        if ( power < 0 )
        	power = 0;

       	// power bar setup
		powerBar_color.setSize( sf::Vector2f( powerBar.getSize().x,	powerBar.getSize().y * power / MAX_POWER ) );
		powerBar_color.setPosition( sf::Vector2f( window->getSize().x * .925, 
			window->getSize().y * 5 / 6 - powerBar.getSize().y * power / MAX_POWER ) );

        // billiard texture displacement
        mouse_position = sf::Vector2f( sf::Mouse::getPosition( *window ) );
        setRotation( mouse_position );
        sprite.setPosition( position - getNorm( direction ) * ( power * PULL_BACK + ball_radius ) );

        // displaying everything
        window->clear( sf::Color( 0, 100, 0, 0 ) );
        //window.draw( table_sprite );
       	window->draw( sprite );
        window->draw( powerBar );
        window->draw( powerBar_color );
        window->display();
	}

	return getNorm( direction ) * power;
}

void Billiard::draw( sf::RenderWindow& window, float ball_radius )
{
	setRotation( sf::Vector2f( sf::Mouse::getPosition( window ) ) );
	sprite.setPosition( position - getNorm( direction ) * ball_radius );
	window.draw( sprite );
}