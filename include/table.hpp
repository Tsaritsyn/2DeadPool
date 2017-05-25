#pragma once
#include <SFML/Graphics.hpp>

#define BALL_COUNT 16
#define TABLE_WIDTH .8
#define TABLE_HEIGHT .8
#define SCALE_X	1.16047
#define SCALE_Y 1.22555

class Ball;

class Table
{
	// geometrical properties
	sf::Vector2f position;							// geometrical center of the table
	unsigned int width, height;						// dimensions of the table
	float corner_radius, middle_radius;				// pockets' properties

	// special origin points for balls, borders, pockets 
	std::vector <sf::Vector2f> pockets, borders;

	// the balls of the game
	std::vector<Ball> balls;

	// graphical properties
	sf::Texture texture;
	sf::Sprite sprite;

	friend class Ball;

public:
	// position_ is the center of the table, width and height are the dimensions in pixels, name picture filename
	Table( const sf::Vector2f& position_, const sf::VideoMode& video_mode,
		const std::string& table_file, const std::string& ball_file );
	~Table();

	int update( float time ); 			// calculates the positions and the velocities of the balls
	int balls_stopped() const;  		// stop_flag == 1 when all balls' velocities are null
	//void setHit( sf::RenderWindow& window, Billiard& billiard );

	sf::Vector2f getPosition() const;			// returns the position
	unsigned int getWidth() const;				// returns width
	unsigned int getHeight() const;				// returns height
	std::vector<Ball>& getBalls();				// returns the balls

	void draw( sf::RenderWindow& window );		// draws the table
};