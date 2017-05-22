#pragma once
#include <SFML/Graphics.hpp>

class Billiard
{
	sf::Vector2f position; 		// specifies the position of the ball to hit
	sf::Vector2f direction;		// the direction of the hit, amplitude of this vector is the strength of the hit

	sf::Texture texture;
	sf::Sprite sprite;

public:
	Billiard( const sf::Vector2f& position_, const sf::Vector2f& direction_, const std::string& filename );
	~Billiard();
	const sf::Vector2f& getPosition() const;
	const sf::Sprite& getSprite() const;
	void setPosition( const sf::Vector2f& position_ );
	void setDirection( const sf::Vector2f& direction_ );
	void setRotation( const sf::Vector2f& mousePosition_ );
	void setHit( sf::RenderWindow& window, const sf::Sprite& table_sprite );
	//void hitAnimation( const sf::RenderWindow& window );
};