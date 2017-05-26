#pragma once
#include <SFML/Graphics.hpp>
#include "ball.hpp"

class Score
{
	// the scores of the players
	int score1, score2;

	// scores' positions
	sf::Vector2f left_score, right_score;

	/* player names variables*/

	// puts the balls got into a pocket to the appropriate score
	void add_ball( Ball& ball, int player_number );

	friend class Table;

public:
	Score( const sf::Vector2f& left_score_, const sf::Vector2f& right_score_ );
	~Score();
};