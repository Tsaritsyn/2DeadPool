#include "table.hpp"

#define DEFAULT_CENTER_X 600
#define DEFAULT_CENTER_Y 350
#define DEFAULT_LENGTH 800
#define DEFAULT_WIDTH 500
#define DEFAULT_FRICTION 1

Table::Table( const sf::Vector2f& position_, unsigned int width_, unsigned int height_ )
{
	position = position_;
	width = width_;
	height = height_;
}

Table::~Table() {}

void Table::setType( const std::string& name )
{
	texture.loadFromFile( name );
	sprite.setTexture( texture );

	sf::Vector2f texture_size( texture.getSize() );
	sf::Vector2f scale( width / texture_size.x, height / texture_size.y );
	sprite.setScale( scale );
	sprite.setPosition( position - sf::Vector2f( width / 2, height / 2 ) );// sf::Vector2f( width / 10, height / 10 ) );

	corner_radius = 72 * height / 1775 * scale.y;
	middle_radius = 82 * height / 1775 * scale.y;

	borders.push_back(sf::Vector2f(80, 50));
	borders.push_back(sf::Vector2f(442, 50));
	borders.push_back(sf::Vector2f(500, 50));
	borders.push_back(sf::Vector2f(862, 50));
	borders.push_back(sf::Vector2f(895, 81));
	borders.push_back(sf::Vector2f(895, 426));
	borders.push_back(sf::Vector2f(863, 455));
	borders.push_back(sf::Vector2f(499, 455));
	borders.push_back(sf::Vector2f(442, 455));
	borders.push_back(sf::Vector2f(78, 455));
	borders.push_back(sf::Vector2f(45, 428));
	borders.push_back(sf::Vector2f(45, 79));
	//scaling to the window
	for (unsigned int i = 0; i < borders.size(); i++)
	{
		borders[i].x *= scale.x;
		borders[i].y *= scale.y;
		borders[i] += position - sf::Vector2f( width / 2, height / 2 );
	}

	//determining pockets' coordinates for this mode
	pockets.push_back(sf::Vector2f(52, 54));		//left top
	pockets.push_back(sf::Vector2f(471, 38));		//middle top
	pockets.push_back(sf::Vector2f(890, 54));		//right top
	pockets.push_back(sf::Vector2f(890, 450));	//right bottom
	pockets.push_back(sf::Vector2f(471, 472));		//middle bottom
	pockets.push_back(sf::Vector2f(52, 450));		//left bottom
	//scaling to the window
	for (int i = 0; i < pockets.size(); i++)
	{
		pockets[i].x *= scale.x;
		pockets[i].y *= scale.y;
		pockets[i] += position - sf::Vector2f( width / 2, height / 2 );
	}
}

sf::Vector2f Table::getPosition() const
{
	return position;
}

unsigned int Table::getWidth() const
{
	return width;
}

unsigned int Table::getHeight() const
{
	return height;
}

sf::Sprite Table::getSprite() const
{
	return sprite;
}