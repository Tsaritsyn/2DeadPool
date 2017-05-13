#include <SFML\Graphics.hpp>
#include <Table.h>
#include <string>
#include <cmath>

void Table::Set(const std::string &name, const sf::VideoMode &mode)
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
	position = sf::Vector2f(mode.width * 0.1f, mode.height * 0.1f);
	r_corner = 72 * height / 1775 * scale.y;
	r_middle = 82 * height / 1775 * scale.y;

	//determinig field borders for this mode
	//on the texture itself:
	/*borders.resize(24);
	borders[0] = sf::Vector2f(62, 36);
	borders[1] = sf::Vector2f(80, 50);
	borders[2] = sf::Vector2f(442, 50);
	borders[3] = sf::Vector2f(457, 26);
	borders[4] = sf::Vector2f(484, 26);
	borders[5] = sf::Vector2f(500, 50);
	borders[6] = sf::Vector2f(862, 50);
	borders[7] = sf::Vector2f(880, 36);
	borders[8] = sf::Vector2f(907, 67);
	borders[9] = sf::Vector2f(895, 81);
	borders[10] = sf::Vector2f(895, 426);
	borders[11] = sf::Vector2f(910, 440);
	borders[12] = sf::Vector2f(879, 469);
	borders[13] = sf::Vector2f(863, 455);
	borders[14] = sf::Vector2f(499, 455);
	borders[15] = sf::Vector2f(490, 472);
	borders[16] = sf::Vector2f(452, 472);
	borders[17] = sf::Vector2f(442, 455);
	borders[18] = sf::Vector2f(78, 455);
	borders[19] = sf::Vector2f(61, 469);
	borders[20] = sf::Vector2f(34, 439);
	borders[21] = sf::Vector2f(45, 428);
	borders[22] = sf::Vector2f(45, 79);
	borders[23] = sf::Vector2f(33, 67);*/
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
	cout << "normals:\n";
	for (unsigned int i = 0; 2 * i < normals.size(); i++)
	{
		v1 = borders[2 * i];
		v2 = borders[2 * i + 1];
		n = sqrt(pow(v1.y - v2.y, 2) + pow(v2.x - v1.x, 2));
		normals[i] = sf::Vector2f((v2.y - v1.y) / n, (v1.x - v2.x) / n);
		cout << i << " - " << normals[i].x << ' ' << normals[i].y << std::endl;
	}
	 

	//determining pockets' coordinates for this mode
	pockets.push_back(sf::Vector2f(52, 54));		//left top
	pockets.push_back(sf::Vector2f(471, 38));		//middle top
	pockets.push_back(sf::Vector2f(890, 54));		//right top
	pockets.push_back(sf::Vector2f(890, 450));	//right bottom
	pockets.push_back(sf::Vector2f(471, 472));		//middle bottom
	pockets.push_back(sf::Vector2f(52, 450));		//left bottom
	//scaling to the window
	for (int i = 0; i < 6; i++)
	{
		pockets[i].x *= scale.x;
		pockets[i].y *= scale.y;
		pockets[i] += position;
	}
}

void Table::draw(sf::RenderWindow &window) const
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(scale);
	sprite.setPosition(position);
	window.draw(sprite);

	//draw circles pointing pockets centers
	for (int i = 0; i < 6; i++)
	{
		int r;
		if (i == 1 || i == 4) r = r_middle;
		else r = r_corner;
		sf::CircleShape circle(r);
		circle.setFillColor(sf::Color::White);
		circle.setPosition(pockets[i] - sf::Vector2f(r, r));
		window.draw(circle);
	}

	//draw lines showing borders
	sf::Vector2f n1;
	sf::CircleShape c(5);
	float n;
	sf::Vector2f v1, v2;
	for (unsigned int i = 0; 2 * i < borders.size() - 1; i++)
	{
		sf::Vertex line[] = { sf::Vertex(borders[2 * i]), sf::Vertex(borders[2 * i + 1]) };
		window.draw(line, 2, sf::Lines);
		/*v1 = borders[i];
		v2 = borders[i + 1];
		c.setPosition((v1.x + v2.x) / 2 + 10 * normals[i].x - 5, (v1.y + v2.y) / 2 + 10 * normals[i].y - 5);
		window.draw(c);*/
	}
	

}

sf::Vector2f Table::getSize()
{
	return sf::Vector2f(width * scale.x, height * scale.y);
}