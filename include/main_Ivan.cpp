#include "ball.hpp"
#include "table.hpp"
#include "billiard.hpp"
#include "score.hpp"
#include "vector_operations.hpp"
#include <cmath>
#include <iostream>
#include <thread>

#define TIME_CONSTANT 2.5e3f

int game( sf::RenderWindow& window, Table& table, Score& score );

int main(int argc, char const *argv[])
{
    // window initialization
    const sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();    
    // create a fullscreen window
    sf::RenderWindow window( video_mode, "2DeadPool", sf::Style::Fullscreen );

    // initialize a table
    sf::Vector2f screen_center( video_mode.width / 2, video_mode.height / 2 );
    const std::string table_file = "../bin/Table.png";
    const std::string ball_file = "../bin/Balls.png";
    const std::string billiard_file = "../bin/Billiard.png";
    Table table( screen_center, sf::VideoMode::getDesktopMode(), table_file, ball_file, billiard_file );

    // initialize a scoreboard
    sf::Vector2f left_score( video_mode.width / 20, video_mode.height / 10 );
    sf::Vector2f right_score( video_mode.width * 19 / 20, video_mode.height / 10 );
    Score score( left_score, right_score );

    int game_result = game( window, table, score );

    std::cout << "Player" << game_result << " won! Congrats!" << std::endl;

	return 0;
}

int game( sf::RenderWindow& window, Table& table, Score& score )
{
    // clock for the independence from CPU speed
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    float previous_time = time.asMicroseconds();
    float dt = 0.0;

    // specifies whose turn it is
    int player_number = 2;

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

        // set hit
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && ( table.balls_stopped() == 1 ) )
            table.setHit( window );

        // table update
        time = clock.getElapsedTime();
        dt = time.asMicroseconds() - previous_time;
        previous_time = time.asMicroseconds();
        table.update( 1.0f, score, player_number );

        // table display
        window.clear( sf::Color( 0, 100, 0, 0 ) );
        table.draw( window );
        window.display();
    }

    return 1;
}