#include "ball.hpp"
#include "table.hpp"
#include "billiard.hpp"
#include <cmath>
#include <iostream>

#define BALL_RADIUS 15

int main(int argc, char const *argv[])
{
    // window initialization
    // store screen size
    unsigned int window_width = sf::VideoMode::getDesktopMode().width;
    unsigned int window_height = sf::VideoMode::getDesktopMode().height;
    // create a fullscreen window
    sf::RenderWindow window( sf::VideoMode( window_width, window_height ), "2DeadPool", sf::Style::Fullscreen );
	// set vertical synhronization with the monitors display rate
	window.setVerticalSyncEnabled( true );
	// change the title of the window
	window.setTitle( "2DeadPool" );

    // initialize a table
    sf::Vector2f center( window_width / 2, window_height / 2 );
    unsigned int width = window_width * 4 / 5;
    unsigned int height = window_height * 4 / 5;
    const std::string table_file = "../bin/Table.png";
    Table table( center, width, height, table_file );

    // create a test ball
    sf::Vector2f ball_position( center );
    sf::Vector2f ball_velocity( 0, 0 );
    int radius = BALL_RADIUS;
    Ball ball( ball_position, ball_velocity, radius );

    // create a test billiard
    const std::string billiard_file = "../bin/Billiard.png";
    Billiard billiard( center, center, billiard_file );
    sf::Vector2f mousePosition;

    // run the program as long as the window is open
    while ( window.isOpen() )
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event; 
        while ( window.pollEvent( event ) )
        {
            // close window if closure was triggered
            if ( event.type == sf::Event::Closed )
                window.close();
        }

        // testing ball appearance
        sf::CircleShape ball_shape( BALL_RADIUS );
        ball_shape.setFillColor( sf::Color( 255, 255, 255 ) );
        ball.update( (float)1, table );
        ball_shape.setPosition ( ball.getPosition().x - ball.getRadius(), ball.getPosition().y - ball.getRadius() );

        // setting a hit with the billiard
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
            billiard.setHit( window, table.getSprite() );

        // testing billiard appearance
        mousePosition = sf::Vector2f( sf::Mouse::getPosition( window ) );
        billiard.setRotation( mousePosition );

		// display the window each cycle
        window.clear( sf::Color( 0, 100, 0, 0 ) );
        window.draw( table.getSprite() );
        window.draw( ball_shape );
        window.draw( billiard.getSprite() );
        window.display();
    }

	return 0;
}