#include "ball.hpp"
#include "table.hpp"
#include "billiard.hpp"
#include "score.hpp"
#include "vector_operations.hpp"
#include <cmath>
#include <iostream>
#include <thread>

#define TIME_CONSTANT 2.5e3f
#define EARLY_END 3

int game( sf::RenderWindow& window, Table& table, Score& score );

int main(int argc, char const *argv[])
{
    // window initialization
    const sf::VideoMode video_mode = sf::VideoMode::getDesktopMode();

    // initialize a table
    sf::Vector2f screen_center( video_mode.width / 2, video_mode.height * 11 / 20 );
    const std::string table_file = "../bin/Table.png";
    const std::string ball_file = "../bin/Balls.png";
    const std::string billiard_file = "../bin/Billiard.png";
    Table table( screen_center, sf::VideoMode::getDesktopMode(), table_file, ball_file, billiard_file );

    // initialize a scoreboard
    std::vector<std::string> player_names(2);
    std::cout << "Input the name of the first player." << std::endl;
    std::cin >> player_names[0];
    std::cout << "Input the name of the second player." << std::endl;
    std::cin >> player_names[1];
    
    const std::string font_file = "../bin/Lithograph-Bold.ttf";
    Score score( video_mode, player_names[0], player_names[1], font_file );

    // create a fullscreen window
    sf::RenderWindow window( video_mode, "2DeadPool", sf::Style::Fullscreen );
    int game_result = game( window, table, score );

    if ( game_result == EARLY_END )
        std::cout << "See ya later" << std::endl;
    else
        std::cout << player_names[game_result - 1] << " is the winner for today! Congrats!" << std::endl;

	return 0;
}

int game( sf::RenderWindow& window, Table& table, Score& score )
{
    // clock for the independence from CPU speed
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    float previous_time = time.asMicroseconds();
    float dt = 0.0;

    // deisgnates the end of the turn
    int turn_flag = 0;
    // specifies whose turn it is
    int player_number = 0;
    int cue_flag = 0;
    int game_flag = 0;

    // needed for changing turns
    std::vector<int> previous_score( 2 );
    previous_score[0] = 0;
    previous_score[1] = 0;
    std::vector<int> current_score( 2 );
    current_score[0] = 0;
    current_score[1] = 0;

    // == 0 when player1 wins, ==1 otherwise
    int update_result = 0;

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

        if ( ( ( turn_flag != 0 ) || ( game_flag != 0 ) ) && ( table.balls_stopped() ) )
        {
            if ( game_flag != 0 )
                return game_flag;
            if ( cue_flag )
            {
                player_number = 1 - player_number;
                cue_flag = 0;
            }
            else
            {
                current_score = score.getScore();
                if ( previous_score[player_number] == current_score[player_number] )
                    player_number = 1 - player_number; 
                previous_score = current_score;
            }
            turn_flag = 0;
        }

        // set hit
        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && ( table.balls_stopped() == 1 ) )
        {
            table.setHit( window, score, player_number );
            turn_flag = 1;
        }

        // table update
        time = clock.getElapsedTime();
        dt = time.asMicroseconds() - previous_time;
        previous_time = time.asMicroseconds();
        update_result = table.update( 1.0f, score, player_number );
        switch ( update_result )
        {
            case GAME_LOST:
                update_result = 1 - player_number;
                turn_flag = GAME_LOST;
                game_flag = 2 - player_number;
                break;
            case GAME_WON:
                update_result = player_number;
                turn_flag = GAME_WON;
                game_flag = 1 + player_number;
                break;
            case CUE_BALL_FOUL:
                turn_flag = CUE_BALL_FOUL;
                cue_flag = 1;
                break;        
        }

        // table display
        window.clear( sf::Color( 0, 100, 0, 0 ) );
        table.draw( window );
        score.draw( window, player_number );
        window.display();
    }

    return EARLY_END;
}

/*
// hint line setup
sf::Vertex line[] =
{
    position,
    position + getNorm( direction ) * HINT;
};
window.draw(line, 2, sf::Lines);
*/