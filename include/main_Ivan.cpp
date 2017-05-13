#include "ball.hpp"
#include "table.hpp"
#include <cmath>

#define BALL_RADIUS 15

int main(int argc, char const *argv[])
{
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
    Table table( center, width, height );

    // create a test ball
    sf::Vector2f ball_position( sf::Vector2f( 210, 500 ) );
    sf::Vector2f ball_velocity( .2, -5 );
    int radius = BALL_RADIUS;
    float mass = (float)1;
    float friction = (float)0.018;
    Ball ball( ball_position, ball_velocity, radius, mass, friction );

    // set table type
    const std::string table_file = "../bin/Table.png";
    table.setType( table_file );

    // run the program as long as the window is open
    while ( window.isOpen() )
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event; 
        while ( window.pollEvent( event ) )
        {
            // "close requested" event: we close the window
            if ( event.type == sf::Event::Closed )
                window.close();
        }

        // testing ball appearance
        sf::CircleShape shape( BALL_RADIUS );
        shape.setFillColor( sf::Color( 255, 255, 255 ) );
        ball.update( (float)1, table );
        shape.setPosition ( ball.getPosition().x - ball.getRadius(), ball.getPosition().y - ball.getRadius() );

		// display the window each cycle
        window.clear( sf::Color( 0, 100, 0, 0 ) );
        window.draw( table.getSprite() );
        window.draw( shape );
        window.display();
    }

	return 0;
}