#include "ball.hpp"
#include "table.hpp"
#include "billiard.hpp"
#include "vector_operations.hpp"
#include <cmath>
#include <iostream>
#include <thread>

#define TIME_CONSTANT 2e3

int main(int argc, char const *argv[])
{
    // window initialization
    const sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();    
    // create a fullscreen window
    sf::RenderWindow window( video_mode, "2DeadPool", sf::Style::Fullscreen );

    // initialize a table
    sf::Vector2f screen_center( video_mode.width / 2, video_mode.height / 2 );
    const std::string table_file = "../bin/Table.png";
    const std::string ball_file = "../bin/BilliardBalls.png";
    Table table( screen_center, sf::VideoMode::getDesktopMode(), table_file, ball_file );

    // billiard
    sf::Vector2f billiard_direction( 1, 0 );
    const std::string billiard_file = "../bin/Billiard.png";
    Billiard billiard( table.getBalls()[table.getBalls().size()].getPosition(), billiard_direction,
        billiard_file );

    sf::Vector2f hit_velocity( 0, 0 );

    // clock for the independence from CPU speed
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    int previous_time = time.asMicroseconds();
    int dt = 0.0;

    // run the program as long as the window is open
    while ( window.isOpen() )
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event; 
        while ( window.pollEvent( event ) )
        {
            // close the window if closure was triggered
            if ( event.type == sf::Event::Closed )
                window.close();
        }

        // hit setup
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && ( table.balls_stopped() == 1 ) )
        {
            billiard.setPosition( table.getBalls()[table.getBalls().size() - 1].getPosition() );
            hit_velocity = billiard.setHit( window, table );
            table.getBalls()[table.getBalls().size() - 1].setVelocity( hit_velocity );
        }

        // table update
        time = clock.getElapsedTime();
        dt = time.asMicroseconds() - previous_time;
        previous_time = time.asMicroseconds();
        table.update( dt / TIME_CONSTANT );

        // table display
        window.clear( sf::Color( 0, 100, 0, 0 ) );
        table.draw( window );
        window.display();
    }

	return 0;
}