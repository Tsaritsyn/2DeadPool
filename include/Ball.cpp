#include <Ball.h>
#include <string>
#include <iostream>
#include <cmath>

Ball::Ball(sf::Vector2f pos, const std::string name, float r, sf::Vector2f v, sf::Vector2f a , sf::Vector3f w, sf::Vector3f e, float m)
{
	position = pos;
	vel = v;
	R = r;
	accel = a;
	ang_vel = w;
	ang_accel = e;
	M = m;
	sf::Image image;
	image.loadFromFile("Ball.png");
	image.createMaskFromColor(sf::Color::White);
	texture.loadFromImage(image);
	scale.x = 2 * R / texture.getSize().x;
	scale.y = 2 * R / texture.getSize().y;
}

void Ball::draw(sf::RenderWindow &window)
{
	sf::Sprite sprite;
	sprite.setScale(scale);
	sprite.setPosition(position);
	sprite.setTexture(texture);
	window.draw(sprite);
}

void Ball::move(float dt)
{
	position += dt * vel;
}

//distance between two points
int len(sf::Vector2f a, sf::Vector2f b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int Ball::ifCloseToBorder(const Table &table)
{
	sf::Vector2f v1, v2;
	float x0 = position.x + R;
	float y0 = position.y + R;
	for (unsigned int i = 0; 2 * i < table.borders.size() - 1; i++)
	{
			v1 = table.borders[2 * i];
			v2 = table.borders[2 * i + 1];
			float dist = abs((v2.y - v1.y) * x0 - (v2.x - v1.x) * y0 + v2.x * v1.y - v2.y * v1.x) / sqrt(pow(v2.y - v1.y, 2) + pow(v2.x - v1.x, 2));
			float sqal = (vel.x * table.normals[i].x + vel.y * table.normals[i].y);
			float c = len(position + sf::Vector2f(R, R), v1);
			float b = len(position + sf::Vector2f(R, R), v2);
			float a = len(v1, v2);
			float cosa = (b * b + c * c - a * a) / (2 * b * c);
			float cos0 = a / sqrt(a * a + R * R);
			if (dist < R && cosa < cos0 && sqal > 0)
			{
				//cout << i << std::endl;
				return i;
			}
	}
	return -1;
}

void Ball::collisionToBorder(const int i, const Table &table)
{
	sf::Vector2f n;
	if (i >= 0 && !(position.x + R > table.borders[1].x && position.x + R < table.borders[2].x))
	{
		float sqal = (vel.x * table.normals[i].x + vel.y * table.normals[i].y);
		n = table.normals[i] * sqal;
		vel -= n * 2.0f;
		//std::cout << i << std::endl;
	}
	//else if (i == -1) cout << "Error!\n";
	//else cout << "i = 0\n";
}

bool Ball::ifCloseToPocket(const Table &table)
{
	float dist;
	for (int i = 0; i < 6; i++)
	{
		float r;
		if (i == 1 || i == 4) r = table.r_middle;
		else r = table.r_corner;
		dist = (table.pockets[i].x - position.x - R) * (table.pockets[i].x - position.x - R) + (table.pockets[i].y - position.y - R) * (table.pockets[i].y - position.y - R);
		if (dist < r * r) return true;
	};
	return false;
}
