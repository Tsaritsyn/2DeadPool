#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <Vector2.h>

class Ball;

class Table
{
	unsigned int width, height;
	sf::Vector2f scale;
	sf::Texture texture;
	std::vector <sf::Vector2f> pockets, borders, normals;
	sf::Vector2f position;
	float r_corner;
	float r_middle;
	friend class Ball;
	unsigned int Player[2];
	//sf::Text text(std::string str, sf::Font font, int size);
	//sf::Text text;
	sf::Font font;
	sf::Vector2f center_point, front_point, back_point;
	float R_ball;
	

public: 
	unsigned int Nmove;
	std::vector <Ball> pool;
	//setting texture and scale of table to draw it in any window equally
	Table(const std::string &name, const sf::VideoMode &mode, const std::string font_name);
	//setting pockets and borders, creating count
	void SetParameters();
	//rendering the table
	void draw(sf::RenderWindow &window, const sf::VideoMode &mode) const;
	sf::Vector2f getSize();
	//increasing count
	void countAdd(int Pnum);
};