#include "table.hpp"
#include "ball.hpp"
#include <new>
#include <iostream>
#include <cmath>

#define BALL_COUNT 16
#define TABLE_WIDTH .8
#define TABLE_HEIGHT .8
#define SCALE_X	1.16047
#define SCALE_Y 1.22555

Table::Table( const sf::Vector2f& position_, const sf::VideoMode& video_mode,
	const std::string& table_file, const std::string& ball_file )
{
	// general initialization
	position = position_;
	width = video_mode.width * TABLE_WIDTH;
	height = video_mode.height * TABLE_HEIGHT;

	// determining the scale factor
	texture.loadFromFile( table_file );
	sf::Vector2f texture_size( texture.getSize() );
	sf::Vector2f scale( width / texture_size.x, height / texture_size.y );
	std::cout << scale.x << ' ' << scale.y << std::endl;

	// pockets' radii setup
	corner_radius = 90 * height / 1775 * scale.y;
	middle_radius = 75 * height / 1775 * scale.y;

	// borders setup
	borders.push_back(sf::Vector2f(79, 50));
	borders.push_back(sf::Vector2f(442, 50));
	borders.push_back(sf::Vector2f(500, 50));
	borders.push_back(sf::Vector2f(862, 50));
	borders.push_back(sf::Vector2f(896, 79));
	borders.push_back(sf::Vector2f(896, 428));
	borders.push_back(sf::Vector2f(862, 455));
	borders.push_back(sf::Vector2f(500, 455));
	borders.push_back(sf::Vector2f(442, 455));
	borders.push_back(sf::Vector2f(79, 455));
	borders.push_back(sf::Vector2f(45, 428));
	borders.push_back(sf::Vector2f(45, 79));
	//scaling to the window
	for (unsigned int i = 0; i < borders.size(); i++)
	{
		borders[i].x *= scale.x;
		borders[i].y *= scale.y;
		borders[i] += position - sf::Vector2f( width / 2, height / 2 );
	}

	// pockets setup
	pockets.push_back(sf::Vector2f(36, 41));		//left top
	pockets.push_back(sf::Vector2f(471, 30));		//middle top
	pockets.push_back(sf::Vector2f(906, 41));		//right top
	pockets.push_back(sf::Vector2f(906, 463));		//right bottom
	pockets.push_back(sf::Vector2f(471, 480));		//middle bottom
	pockets.push_back(sf::Vector2f(36, 463));		//left bottom
	//scaling to the window
	for (int i = 0; i < pockets.size(); i++)
	{
		pockets[i].x *= scale.x;
		pockets[i].y *= scale.y;
		pockets[i] += position - sf::Vector2f( width / 2, height / 2 );
	}

	// balls initialization
	balls = new Ball[BALL_COUNT];
	float ball_radius = 47 * height * scale.y / 1775;
	sf::Vector2f null_velocity( 0, 0 );
	std::vector<sf::Vector2f> ball_positions( BALL_COUNT ); // relatively to the table's center
	ball_positions[0] = sf::Vector2f( ball_radius * 2 * sqrt(3), -ball_radius * 2 );
	ball_positions[1] = sf::Vector2f( ball_radius * 4 * sqrt(3), ball_radius * 2 );
	ball_positions[2] = sf::Vector2f( ball_radius * 3 * sqrt(3), -ball_radius );
	ball_positions[3] = sf::Vector2f( ball_radius * 4 * sqrt(3), -ball_radius * 2 );
	ball_positions[4] = sf::Vector2f( ball_radius * 4 * sqrt(3), -ball_radius * 4 );
	ball_positions[5] = sf::Vector2f( ball_radius * 3 * sqrt(3), ball_radius * 3 );
	ball_positions[6] = sf::Vector2f( ball_radius * sqrt(3), ball_radius );
	ball_positions[7] = sf::Vector2f( ball_radius * 2 * sqrt(3), 0 );
	ball_positions[8] = sf::Vector2f( 0, 0 );
	ball_positions[9] = sf::Vector2f( ball_radius * 3 * sqrt(3), ball_radius );
	ball_positions[10] = sf::Vector2f( ball_radius * 4 * sqrt(3), ball_radius * 4 );
	ball_positions[11] = sf::Vector2f( ball_radius * sqrt(3), -ball_radius );
	ball_positions[12] = sf::Vector2f( ball_radius * 4 * sqrt(3), 0 );
	ball_positions[13] = sf::Vector2f( ball_radius * 3 * sqrt(3), -ball_radius * 3 );
	ball_positions[14] = sf::Vector2f( ball_radius * 2 * sqrt(3), ball_radius * 2 );
	ball_positions[15] = sf::Vector2f( width * (-.5), 0 );
	for (int i = 0; i < BALL_COUNT; ++i)
		balls[i] = Ball( sf::Vector2f( ball_positions[i].x * scale.x / SCALE_X, ball_positions[i].y * scale.y / SCALE_Y )
			+ position + sf::Vector2f( width / 4 * scale.x / SCALE_X, 0 ), null_velocity, ball_radius, ball_file, i );

	// graphical initialization
	sprite.setTexture( texture );
	sprite.setScale( scale );
	sprite.setPosition( position - sf::Vector2f( width / 2, height / 2 ) );
}

Table::~Table()
{
	delete[] balls;
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

void Table::draw( sf::RenderWindow& window )
{
    window.draw( sprite );
    for (int i = 0; i < BALL_COUNT; ++i)
		balls[i].draw( window );
}