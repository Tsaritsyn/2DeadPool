#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <Vector2.h>

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

public: 
	//setting texture and scale of table to draw it in any window equally
	void Set(const std::string &name, const sf::VideoMode &mode);
	//rendering the table
	void draw(sf::RenderWindow &window) const;
	sf::Vector2f getSize();
};