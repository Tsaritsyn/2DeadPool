#include <SFML\Graphics.hpp>
#include <Table.h>
#include <string>
#include <cmath>
#include <sstream>
#include <Ball.h>

Table::Table(const std::string &name, const sf::VideoMode &mode, const std::string font_name)
{
	texture.loadFromFile(name);
	//determining size and position of the table for this mode
	//getting sizes of texture itself
	width = texture.getSize().x;
	height = texture.getSize().y;
	//scalinig it to 80% of the window 
	scale.x = 0.8f * mode.width / width;
	scale.y = 0.8f * mode.height / height;
	//and moving to 10% from window borders
	position = sf::Vector2f(mode.width * 0.1f, mode.height * 0.15f);
	r_corner = 72 * height / 1775 * scale.y;
	r_middle = 82 * height / 1775 * scale.y;
	//setting count field
	font.loadFromFile(font_name);

	//defining special points
	center_point = position + sf::Vector2f(0.5f * width * scale.x, 0.5f * height * scale.y);
	front_point = position + sf::Vector2f(0.75f * width * scale.x, 0.5f * height * scale.y);
	back_point = position + sf::Vector2f(0.25f * width * scale.x, 0.5f * height * scale.y);

	//determining the ball radius on this table
	R_ball = 68 * height * scale.y / 1775;

	Nmove = 0;
}

void Table::SetParameters()
{
	//determinig field borders for this mode
	//on the texture itself:
	borders.push_back(sf::Vector2f(80, 50));
	borders.push_back(sf::Vector2f(442, 50));
	borders.push_back(sf::Vector2f(500, 50));
	borders.push_back(sf::Vector2f(862, 50));
	borders.push_back(sf::Vector2f(895, 81));
	borders.push_back(sf::Vector2f(895, 426));
	borders.push_back(sf::Vector2f(863, 455));
	borders.push_back(sf::Vector2f(499, 455));
	borders.push_back(sf::Vector2f(442, 455));
	borders.push_back(sf::Vector2f(78, 455));
	borders.push_back(sf::Vector2f(45, 428));
	borders.push_back(sf::Vector2f(45, 79));
	//scaling to the window
	for (unsigned int i = 0; i < borders.size(); i++)
	{
		borders[i].x *= scale.x;
		borders[i].y *= scale.y;
		borders[i] += position;
	}

	//external normals to borders
	normals.resize(12);
	float n;
	sf::Vector2f v1, v2;
	for (unsigned int i = 0; 2 * i < normals.size(); i++)
	{
		v1 = borders[2 * i];
		v2 = borders[2 * i + 1];
		n = sqrt(pow(v1.y - v2.y, 2) + pow(v2.x - v1.x, 2));
		normals[i] = sf::Vector2f((v2.y - v1.y) / n, (v1.x - v2.x) / n);
	}

	//creating set of balls
	//difference between neighbour balls
	float dx = R_ball * sqrt(3);
	float dy = R_ball;
	//file of bals texture
	string name = "BilliardBalls1.png";
	vector < vector <sf::Vector2f> > ball_pos;	//vector of balls positions
	vector <int> ball_skin;						//vector of balls styles
	for (int i = 0; i < 16; i++)
	{
		ball_skin.push_back(i + 1);
	}
	//defining the center ball as 8th, corner balls as different
	ball_skin[0] = 11;
	ball_skin[10] = 1;
	ball_skin[7] = 5;
	ball_skin[4] = 8;

	int k = 0; 
	ball_pos.resize(5);
	ball_pos[0].push_back(back_point - sf::Vector2f(R_ball, R_ball));
	//putting first ball to the back point
	pool.push_back(Ball(ball_pos[0][0], name, R_ball, ball_skin[k++]));
	for (int i = 1; i < 5; i++)
	{
		ball_pos[i].resize(i + 1);
		//shifting ball relatively to neighbours
		for (int j = 0; j < i; j++)
		{
			//to right top neighbour
			ball_pos[i][j] = ball_pos[i - 1][j] + sf::Vector2f(-dx, dy);
			pool.push_back(Ball(ball_pos[i][j], name, R_ball, ball_skin[k++]));
		}
		//to right bottom neighbour
		ball_pos[i][i] = ball_pos[i - 1][i - 1] - sf::Vector2f(dx, dy);
		pool.push_back(Ball(ball_pos[i][i], name, R_ball, ball_skin[k++]));
	}
	//puting the white one to the front point
	pool.push_back(Ball(front_point - sf::Vector2f(R_ball, R_ball), name, R_ball, ball_skin[k]));

	//determining pockets' coordinates for this mode
	pockets.push_back(sf::Vector2f(52, 54));		//left top
	pockets.push_back(sf::Vector2f(471, 38));		//middle top
	pockets.push_back(sf::Vector2f(890, 54));		//right top
	pockets.push_back(sf::Vector2f(890, 450));		//right bottom
	pockets.push_back(sf::Vector2f(471, 472));		//middle bottom
	pockets.push_back(sf::Vector2f(52, 450));		//left bottom
	//scaling to the window
	for (int i = 0; i < 6; i++)
	{
		pockets[i].x *= scale.x;
		pockets[i].y *= scale.y;
		pockets[i] += position;
	}
	
	Player[0] = Player[1] = 0;
}

void Table::countAdd(int Pnum)
{
	Player[Pnum] ++;
}

void Table::draw(sf::RenderWindow &window, const sf::VideoMode &mode) const
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(scale);
	sprite.setPosition(position);
	window.draw(sprite);

	for (unsigned int i = 0; i < pool.size(); i++)
	{
		pool[i].draw(window);
	}

	//draw circles pointing pockets centers
	/*for (int i = 0; i < 6; i++)
	{
		int r;
		if (i == 1 || i == 4) r = r_middle;
		else r = r_corner;
		sf::CircleShape circle(r);
		circle.setFillColor(sf::Color::White);
		circle.setPosition(pockets[i] - sf::Vector2f(r, r));
		window.draw(circle);
	}*/

	//draw lines showing borders
	/*sf::Vector2f n1;
	sf::CircleShape c(5);
	float n;
	sf::Vector2f v1, v2;
	for (unsigned int i = 0; 2 * i < borders.size() - 1; i++)
	{
		sf::Vertex line[] = { sf::Vertex(borders[2 * i]), sf::Vertex(borders[2 * i + 1]) };
		window.draw(line, 2, sf::Lines);
		v1 = borders[i];
		v2 = borders[i + 1];
		c.setPosition((v1.x + v2.x) / 2 + 10 * normals[i].x - 5, (v1.y + v2.y) / 2 + 10 * normals[i].y - 5);
		window.draw(c);
	}*/

	//rendering count
	std::ostringstream PlayerScore;
	PlayerScore << "Player1 - " << Player[0] << " : " << Player[1] << " - Player2\n";
	sf::Text text(PlayerScore.str(), font, 40);
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	sf::FloatRect rect = text.getLocalBounds();
	sf::Vector2f textOrigin = sf::Vector2f(rect.width / 2, rect.height / 2);
	text.setOrigin(textOrigin);
	sf::Vector2f text_pos(mode.width / 2, mode.height * 0.075);
	text.setPosition(text_pos);
	window.draw(text);

	/*sf::CircleShape circle(10);
	circle.setPosition(center_point - sf::Vector2f(10.0f, 10.0f));
	window.draw(circle);
	sf::CircleShape circle1(10);
	circle1.setPosition(front_point - sf::Vector2f(10.0f, 10.0f));
	window.draw(circle1);
	sf::CircleShape circle2(10);
	circle2.setPosition(back_point - sf::Vector2f(10.0f, 10.0f));
	window.draw(circle2);*/
}

sf::Vector2f Table::getSize()
{
	return sf::Vector2f(width * scale.x, height * scale.y);
}