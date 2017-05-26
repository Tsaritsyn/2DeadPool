#include <SFML\Graphics.hpp>
#include <table.hpp>
#include <ball.hpp>
#include <string>
#include <iostream>
#include <Count.h>
#include <billiard.hpp>

bool fullscreen;
bool start_step;
sf::Font font;
int hit = -1;

int step(int Pnum, Table& table, sf::RenderWindow& window, sf::Clock& clock, sf::Event& event, sf::VideoMode& mode, Count& count, Billiard& billiard)
{
	hit = -1;

	float prevtime = 0.0;		//time of previous frame
	float time = 0.0;

	//creating step sign
	std::string s = count.getName(Pnum) + " step!\n";
	sf::Text step_warning(s, font, 100);
	sf::FloatRect rect = step_warning.getLocalBounds();
	sf::Vector2f textOrigin = sf::Vector2f(rect.width / 2, rect.height / 2);
	step_warning.setOrigin(textOrigin);
	step_warning.setColor(sf::Color::Red);
	step_warning.setPosition(sf::Vector2f(mode.width / 2, mode.height / 2));
	float text_time = clock.getElapsedTime().asSeconds();

	bool change_step = false;
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
		table.draw(window);
		
		//displaying step sign
		if (time - text_time < 2)
		{
			window.draw(step_warning);
		}

		// hit setup
		sf::Vector2f hit_velocity(0.0f, 0.0f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (table.balls_stopped() == 1))
		{
			billiard.setPosition(table.getBalls()[table.getBalls().size() - 1].getPosition());
			hit_velocity = billiard.setHit(window, table);
			table.getBalls()[table.getBalls().size() - 1].setVelocity(hit_velocity);
			start_step = false;
		}

		count.draw(window);

		int style = table.update(dt);

		if (!start_step)
		{
			if (style >= 0 && style <= 6)
			{
				hit = 0;
				if (Pnum == 1) change_step = true;
				count.update(hit);
			}
			else if (style >= 8 && style <= 14)
			{
				hit = 1;
				if (Pnum == 0) change_step = true;
				count.update(hit);
			}
			else if (style == 7)
			{
				if (count.getScore(Pnum) == 7) count.update(Pnum, Pnum);
				else count.update(Pnum, 1 - Pnum);
				return 0;
			}

			if (table.balls_stopped())
			{
				if (change_step || hit == -1) return 1;
				else
				{
					text_time = clock.getElapsedTime().asSeconds();
					hit = -1;
					start_step = true;
				}
			}
		}
		
		window.display();

	}

	return -1;
}

int main()
{
	std::string name;
	std::cout << "Player 1, please, enter your name\n";
	std::cin >> name;
	std::string name1;
	std::cout << "Player 2, please, enter your name\n";
	std::cin >> name1;

	//creating fullscreen window
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	float width = mode.width;
	float height = mode.height;
	sf::RenderWindow window(mode, "My window", sf::Style::Fullscreen);
	fullscreen = true;
	
	//creating score
	std::string font_name = "CyrilicOld.TTF";
	font.loadFromFile(font_name);
	Count count(sf::Vector2f(width / 2, height * 0.075), font_name);
	count.setName(0, name);
	count.setName(1, name1);

	//creating table with set of balls
	Table table(sf::Vector2f(width / 2, height * 0.55), mode, "Table.png", "BilliardBalls1.png");

	//preparing to work with time
	sf::Clock clock;
	float prevtime = 0.0;		//time of previous frame
	float ball_time = 0.0;		//time when the last ball was created
	float time = 0.0;			//time of current frame

	sf::Event event;

	//creating billiard
	sf::Vector2f billiard_direction(1, 0);
	const std::string billiard_file = "../bin/Billiard1.png";
	Billiard billiard(table.getBalls()[table.getBalls().size() - 1].getPosition(), billiard_direction, billiard_file);

	table.update(1.0f);

	int Pnum = 0;
	bool end_game = false;

	//describing the game itself
	while (!end_game)
	{
		start_step = true;
		//making a step
		int r = step(Pnum, table, window, clock, event, mode, count, billiard);
		//deciding whether to transfer a move or announce the winner
		if (r == 1 && !start_step)
		{
			Pnum = 1 - Pnum;
			
		}
		else if (r == 0)
		{
			end_game = true;
		}
	}
	
	//creating winner sign
	std::string s = count.getName(count.getWinner()) +  " Win!\n";
	sf::Text win_warning(s, font, 100);
	sf::FloatRect rect = win_warning.getLocalBounds();
	sf::Vector2f textOrigin = sf::Vector2f(rect.width / 2, rect.height / 2);
	win_warning.setOrigin(textOrigin);
	win_warning.setColor(sf::Color::Red);
	win_warning.setPosition(sf::Vector2f(width / 2, height / 2));

	count.setPosition(sf::Vector2f(width / 2, height / 2 + rect.height));

	//displaying the winner and the final score
	while (window.isOpen())
	{
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
		window.draw(win_warning);
		count.draw(window);

		window.display();

	}

	return 0;
}