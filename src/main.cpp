#include <SFML\Graphics.hpp>
#include <Table.h>
#include <Ball.h>
#include <string>
#include <iostream>

int main()
{
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	int width = mode.width;
	int height = mode.height;
	sf::RenderWindow window(mode, "My window", sf::Style::Fullscreen);
	bool fullscreen = true;
	sf::Event event;

	Table table;
	//setting parameters of the table to this window and mode
	table.Set("Table.png", mode);
	//radius of pool ball for this table
	float R = 60 * table.getSize().y / 1775;

	//preparing to work with time
	sf::Clock clock;
	float prevtime = 0.0;		//time of previous frame
	float ball_time = 0.0;		//time when the last ball was created
	float time = 0.0;			//time of current frame

	std::vector < Ball > queue;
	
	while (window.isOpen())
	{
		//determinig living time of the frame
		time = clock.getElapsedTime().asSeconds();
		float dt = time - prevtime;
		prevtime = time;

		while (window.pollEvent(event))
		{
			//closing window
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//exit from fullscreen mode
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && fullscreen)
		{
			window.create(mode, "My window");
			fullscreen = false;
		}

		window.clear(sf::Color::Green);

		//rendering table
		table.draw(window);

		//creating new ball
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && ((ball_time - time) < -0.2))
		{
			//взятие координат курсора
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
			
			//задание случайной скорости
			int k = rand() % 100 + 100;
			int a = rand() % 360 + 1;
			sf::Vector2f v(k * cos(3.14159f * a / 180), k * sin(3.14159f * a / 180));
			//sf::Vector2f v(0, -200);
			sf::Vector2f pos(mouse_pos.x, mouse_pos.y);
			Ball newp(pos, "Ball.png", R, v);
			//std::cout << pos.x << ' ' << pos.y << " - " << newp.center.x << ' ' << newp.center.y << std::endl;
			queue.push_back(newp);

			//запоминание времени создания частицы
			ball_time = clock.getElapsedTime().asSeconds();
		}

		//просчёт столкновений
		for (unsigned int i = 0; i < queue.size(); i++)
		{
			//с другими частицами
			/*for (unsigned int j = i + 1; j < queue.size(); j++)
			{
				if (queue[i].ifCollision(queue[j]))
				{
					collision(queue[i], queue[j]);
				}
			}*/
			//со стенками
			queue[i].collisionToBorder(queue[i].ifCloseToBorder(table), table);

			//hitting in pocket
			if (queue[i].ifCloseToPocket(table))
			{
				queue.erase(queue.begin() + i);
			}

			//отрисовка и передвижение частиц
			queue[i].draw(window);
			queue[i].move(dt);
		}

		window.display();
		
	}

	

	return 0;
}