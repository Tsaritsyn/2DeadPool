#include <SFML\Graphics.hpp>
#include <Table.h>
#include <Ball.h>
#include <string>
#include <iostream>
#include <sstream>

int raw(int player, Table& table, sf::RenderWindow& window, sf::Clock& clock, sf::Event& event, sf::VideoMode& mode, bool& fullscreen)
{
	float prevtime = 0.0;		//time of previous frame
	float time = 0.0;

	table.Nmove = 0;
	for (unsigned int i = 0; i < table.pool.size(); i++)
	{
		int k = rand() % 100 + 100;
		int a = rand() % 360 + 1;
		table.pool[i].setVelocity(sf::Vector2f(k * cos(3.14159f * a / 180), k * sin(3.14159f * a / 180)));
		table.Nmove++;
	}

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
		table.draw(window, mode);

		//accounting for interactions
		for (unsigned int i = 0; i < table.pool.size(); i++)
		{
			//collision to borders
			table.pool[i].collisionToBorder(table.pool[i].ifCloseToBorder(table), table);

			//hitting in pocket
			if (table.pool[i].ifCloseToPocket(table))
			{
				int Pnum = 0;
				if (table.pool[i].getStyle() < 8) Pnum = 0;
				else if (table.pool[i].getStyle() > 8 && table.pool[i].getStyle() < 16) Pnum = 1;
				table.countAdd(Pnum);
				table.pool.erase(table.pool.begin() + i);
				table.Nmove--;
				//Player[Pnum]++;
				//Pnum = 1 - Pnum;
			}

			table.pool[i].draw(window);
			table.pool[i].move(dt, table.Nmove);
		}

		window.display();
		if (table.Nmove == 0) return 0;
		else cout << table.Nmove << std::endl;
	}

	return 1;
}

int main()
{
	//creating fullscreen window
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	int width = mode.width;
	int height = mode.height;
	sf::RenderWindow window(mode, "My window", sf::Style::Fullscreen);
	bool fullscreen = true;

	//string name = "BilliardBalls1.png";

	Table table("Table.png", mode, "CyrilicOld.ttf");
	//setting parameters of the table to this window and mode
	table.SetParameters();
	//radius of pool ball for this table
	//float R = 68 * table.getSize().y / 1775;

	//preparing to work with time
	sf::Clock clock;
	float prevtime = 0.0;		//time of previous frame
	float ball_time = 0.0;		//time when the last ball was created
	float time = 0.0;			//time of current frame
	
	sf::Event event;
	
	int r = raw(1, table, window, clock, event, mode, fullscreen);
	
	//std::vector < Ball > queue;

	//unsigned int Nmove = 0;
	
	/*while (window.isOpen())
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
		table.draw(window, mode);

		//creating new ball
		/*if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && ((ball_time - time) < -0.2))
		{
			//getting mouse coordinates
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
			
			//defining velocity as random
			int k = rand() % 100 + 100;
			int a = rand() % 360 + 1;
			sf::Vector2f v(k * cos(3.14159f * a / 180), k * sin(3.14159f * a / 180));
			//sf::Vector2f v(0, -200);
			sf::Vector2f pos(mouse_pos.x, mouse_pos.y);
			
			//defining random skin
			unsigned int st = rand() % 16 + 1;
			//unsigned int st = 9;
			
			//creating new ball and add it to those on the table
			Ball newp(pos, name, R, st, v);
			queue.push_back(newp);
			Nmove++;

			//remembering ball creature time
			ball_time = clock.getElapsedTime().asSeconds();
		}

		//accounting for interactions
		for (unsigned int i = 0; i < table.pool.size(); i++)
		{
			//collision to borders
			table.pool[i].collisionToBorder(table.pool[i].ifCloseToBorder(table), table);

			//hitting in pocket
			if (table.pool[i].ifCloseToPocket(table))
			{
				int Pnum = 0;
				if (table.pool[i].getStyle() < 8) Pnum = 0;
				else if (table.pool[i].getStyle() > 8 && table.pool[i].getStyle() < 16) Pnum = 1;
				table.countAdd(Pnum);
				table.pool.erase(table.pool.begin() + i);
				table.Nmove--;
				//Player[Pnum]++;
				//Pnum = 1 - Pnum;
			}

			table.pool[i].draw(window);
			table.pool[i].move(dt, table.Nmove);
		}
		
		window.display();
		
	}*/

	cout << r << std::endl;

	return 0;
}