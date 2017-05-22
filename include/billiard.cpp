#include "billiard.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

#define HIT_DISTANCE 100
#define SCALE .5
#define PI 3.1415926
#define MAX_POWER 50

float getLength1( const sf::Vector2f& vector )
{
	return sqrt( vector.x * vector.x + vector.y * vector.y );
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

void Billiard::setHit( sf::RenderWindow& window, const sf::Sprite& table_sprite )
{
	int mouseDelta = 0;
	sf::Vector2f mousePosition;
	sf::RectangleShape powerBar( sf::Vector2f( window.getSize().x / 20, window.getSize().y / 3 ) );
	powerBar.setPosition( sf::Vector2f( window.getSize().x * .925, window.getSize().y * .5 ) );
	sf::RectangleShape powerBar_color;
	powerBar_color.setFillColor( sf::Color( 255, 0, 0 ) );

	while ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
	{
		// mouseWheel control
		sf::Event event;
		while ( window.pollEvent( event ) )
       		if ( event.type == sf::Event::MouseWheelMoved )
        		mouseDelta += 2 * event.mouseWheel.delta;
        if ( mouseDelta < 0)
        	mouseDelta = 0;

       	// power bar
        if ( mouseDelta > MAX_POWER )
        	mouseDelta = MAX_POWER;
		powerBar_color.setSize( sf::Vector2f( powerBar.getSize().x,	powerBar.getSize().y * mouseDelta / MAX_POWER ) );
		powerBar_color.setPosition( sf::Vector2f( window.getSize().x * .925, 
			window.getSize().y * 5 / 6 - powerBar.getSize().y * mouseDelta / MAX_POWER ) );

        // billiard rotation
        mousePosition = sf::Vector2f( sf::Mouse::getPosition( window ) );
        setRotation( mousePosition );

        // displaying everything
        window.clear( sf::Color( 0, 100, 0, 0 ) );
        window.draw( table_sprite );
        window.draw( sprite );
        window.draw( powerBar );
        window.draw( powerBar_color );
        window.display();
	}
	std::cout << mouseDelta << std::endl;
}

/*void Billiard::hitAnimation( const sf::RenderWindow& window )
{
	sf::Vector2f temp_position = ball_to_hit - direction / getLength1( direction ) * (float)HIT_DISTANCE;
}*/