#include "ball.hpp"
#include "table.hpp"

#define UBUNTU_PANEL_X 62
#define UBUNTU_PANEL_Y 54
#define BALL_RADIUS 15

int main(int argc, char const *argv[])
{
    // store screen size
    unsigned int window_width = sf::VideoMode::getDesktopMode().width;// - UBUNTU_PANEL_X;
    unsigned int window_height = sf::VideoMode::getDesktopMode().height;// - UBUNTU_PANEL_Y;

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
    sf::Vector2f ball_position( center );
    sf::Vector2f ball_velocity( 10, 10 );
    float angular_velocity = (float)0;
    float angular_acceleration = (float)0;
    int radius = BALL_RADIUS;
    float mass = (float)1;
    float friction = (float)0.018;
    Ball ball( ball_position, ball_velocity, angular_velocity, angular_acceleration, radius, mass, friction );

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

        sf::CircleShape shape( BALL_RADIUS );
        shape.setFillColor( sf::Color( 255, 255, 255 ) );
        ball.update( (float)1, table );
        shape.setPosition ( ball.getPosition().x - ball.getRadius(), ball.getPosition().y - ball.getRadius() );

		// display the window each cycle
        window.clear( sf::Color( 0, 100, 0, 0 ) );
        window.draw( table.getSprite() );
        window.draw( shape );
        /*std::vector<sf::CircleShape> pockets_circle( table.pockets.size());
        for (int i = 0; i < pockets_circle.size(); ++i)
        {
            if ( ( i == 1 ) || ( i == 4 ) )
            {
                pockets_circle[i] = sf::CircleShape( table.middle_radius );
                pockets_circle[i].setPosition ( table.pockets[i].x - table.middle_radius, table.pockets[i].y - table.middle_radius + 70 );
            }
            else
            {
                pockets_circle[i] = sf::CircleShape( table.corner_radius );
                pockets_circle[i].setPosition ( table.pockets[i].x - table.corner_radius, table.pockets[i].y - table.corner_radius );
            }
            pockets_circle[i].setFillColor( sf::Color( 255, 0, 0 ) );
            window.draw( pockets_circle[i] );
        }
        std::vector<sf::CircleShape> border_circle( table.borders.size() );
        for (int i = 0; i < border_circle.size(); ++i)
        {
            border_circle[i] = sf::CircleShape( BALL_RADIUS );
            border_circle[i].setFillColor( sf::Color( 0, 255, 0 ) );
            border_circle[i].setPosition ( table.borders[i].x - ball.getRadius(), table.borders[i].y - ball.getRadius() );
            window.draw( border_circle[i] );
        }*/
        window.display();
    }

	return 0;
}