#include "table.hpp"
#include "ball.hpp"
#include "billiard.hpp"
#include "vector_operations.hpp"
#include <iostream>
#include <cmath>

Table::Table( const sf::Vector2f& position_, const sf::VideoMode& video_mode,
	const std::string& table_file, const std::string& ball_file, const std::string& billiard_file )
{
	// general initialization
	position = position_;
	width = video_mode.width * TABLE_WIDTH;
	height = video_mode.height * TABLE_HEIGHT;

	// determining the scale factor
	texture.loadFromFile( table_file );
	sf::Vector2f texture_size( texture.getSize() );
	sf::Vector2f scale( width / texture_size.x, height / texture_size.y );

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
	float ball_radius = 44 * height * scale.y / 1775;
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
		balls.push_back( Ball( sf::Vector2f( ball_positions[i].x * scale.x / SCALE_X, ball_positions[i].y * scale.y / SCALE_Y )
			+ position + sf::Vector2f( width / 4 * scale.x / SCALE_X, 0 ), null_velocity, ball_radius, ball_file, i ) );

	// graphical initialization
	sprite.setTexture( texture );
	sprite.setScale( scale );
	sprite.setPosition( position - sf::Vector2f( width / 2, height / 2 ) );

	//billiard setup
	sf::Vector2f null_vector( 0, 0 );
	billiard.push_back( Billiard( null_vector, null_vector, billiard_file ) );
}

Table::~Table()	{}

int Table::update( float time )
{
	int result = -1;
    sf::Vector2f rel_distance( 0, 0 );
    sf::Vector2f vel_difference( 0, 0 );
    sf::Vector2f delta_velocity( 0, 0 );

	// balls' positions update
    for (int i = 0; i < balls.size(); ++i)
    {
        for (int j = i + 1; j < balls.size(); ++j)
        {
            rel_distance = balls[j].position - balls[i].position;
            vel_difference = balls[j].velocity - balls[i].velocity;
            if ( ( balls[i].radius + balls[j].radius
                - getLength( rel_distance ) > 0.0 ) && ( getScalar( vel_difference, rel_distance ) < 0.0 ) )
            {
                delta_velocity = getNorm( rel_distance ) * getScalar( vel_difference, getNorm( rel_distance ) );
                balls[i].velocity += delta_velocity * BALL_REFLECTION;
                balls[j].velocity -= delta_velocity * BALL_REFLECTION;
            }
        }

        if ( balls[i].update( 1.0f, *this ) == 0 )
        {
        	result = balls[i].style;
        	balls.erase( balls.begin() + i );
        }
    }

    return result;
}

int Table::balls_stopped() const
{
	int stop_flag = 1;
	sf::Vector2f null_vector( 0, 0 );
	for (int i = 0; i < balls.size(); ++i)
		if ( balls[i].velocity != null_vector )
			stop_flag = 0;

	return stop_flag;
}

void Table::setHit( sf::RenderWindow& window )
{
    sf::Vector2f hit_velocity( 0, 0 );

	/*sf::Vector2f null_vector( 0, 0 );
	if ( balls[balls.size() - 1].style != CUE_STYLE )
		balls.push_back( position + sf::Vector2f( width / 4, height / 2 ),
			null_vector, balls[balls.size() - 1].radius, , CUE_STYLE );*/
	// hit setup
    if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && ( this->balls_stopped() == 1 ) )
    {
        billiard[0].position = balls[balls.size() - 1].position;
        hit_velocity = billiard[0].setHit( window, *this );
        balls[balls.size() - 1].velocity = hit_velocity;
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

std::vector<Ball>& Table::getBalls()
{
	return balls;
}

void Table::draw( sf::RenderWindow& window )
{
    window.draw( sprite );
    for (int i = 0; i < balls.size(); ++i)
		balls[i].draw( window );
}