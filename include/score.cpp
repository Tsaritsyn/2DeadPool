#include "score.hpp"

Score::Score( const sf::Vector2f& left_score_, const sf::Vector2f& right_score_ )
{
	score1 = score2 = 0;
	left_score = left_score_;
	right_score = right_score_;
}

Score::~Score() {}

void Score::add_ball( Ball& ball, int player_number )
{
	if ( player_number == 1 )
	{
		ball.position = left_score + sf::Vector2f( 0, ball.radius * 2.5f * score1 );
		score1++;
	}
	else
	{
		ball.position = right_score + sf::Vector2f( 0, ball.radius * 2.5f * score2 );
		score2++;
	}
}