#include <SFML\Graphics.hpp>
#include <Table.h>
#include <Ball.h>
#include <string>
#include <iostream>
#include <sstream>

int main()
{
	//creatin fullscreen window
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	int width = mode.width;
	int height = mode.height;
	sf::RenderWindow window(mode, "My window", sf::Style::Fullscreen);
	bool fullscreen = true;

	string name = "BilliardBalls.png";

	Table table;
	//setting parameters of the table to this window and mode
	table.Set("Table.png", mode);
	//radius of pool ball for this table
	float R = 68 * table.getSize().y / 1775;

	//preparing to work with time
	sf::Clock clock;
	float prevtime = 0.0;		//time of previous frame
	float ball_time = 0.0;		//time when the last ball was created
	float time = 0.0;			//time of current frame
	
	sf::Event event;
	
	std::vector < Ball > queue;

	//initializing scores of players
	int Player[2] = { 0, 0 };
	int Pnum = 0;

	//initializing text
	sf::Font font;
	font.loadFromFile("CyrilicOld.ttf");
	sf::Text text("", font, 40);
	text.setColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	std::ostringstream PlayerScore;
	PlayerScore << "Player1 - 0 : 0 - Player2\n";
	text.setString(PlayerScore.str());
	sf::FloatRect rect = text.getLocalBounds();
	text.setOrigin(sf::Vector2f(rect.width / 2, rect.height / 2));
	sf::Vector2f text_pos(width / 2, height / 2);
	text.setPosition(text_pos);
	
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
			//getting mouse coordinates
			sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
			
			//defining velocity as random
			int k = rand() % 100 + 100;
			int a = rand() % 360 + 1;
			sf::Vector2f v(k * cos(3.14159f * a / 180), k * sin(3.14159f * a / 180));
			//sf::Vector2f v(0, -200);
			sf::Vector2f pos(mouse_pos.x, mouse_pos.y);
			
			//defining random skin
			unsigned int st = rand() % 8 + 1;
			
			//creating new ball and add it to those on the table
			Ball newp(pos, name, R, st, v);
			queue.push_back(newp);

			//remembering ball creature time
			ball_time = clock.getElapsedTime().asSeconds();
		}

		//accounting for interactions
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
			//collision to borders
			queue[i].collisionToBorder(queue[i].ifCloseToBorder(table), table);

			//hitting in pocket
			if (queue[i].ifCloseToPocket(table))
			{
				queue.erase(queue.begin() + i);
				Player[Pnum]++;
				//Pnum = 1 - Pnum;
			}

			//rendering and moving balls
			queue[i].draw(window);
			queue[i].move(dt);
		}

		std::ostringstream PlayerScore;
		PlayerScore << "Player1 - " << Player[0] << " : " << Player[1] << " - Player2\n";
		text.setString(PlayerScore.str());
		sf::FloatRect rect = text.getLocalBounds();
		text.setOrigin(sf::Vector2f(rect.width / 2, rect.height / 2));
		window.draw(text);

		window.display();
		
	}

	

	return 0;
}