#pragma once
#include <iostream>;
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
//configuraiton of the plugboard
class PlugboardConfiguration
{

private:

	//plugboard settings and user input vairables
	char letter1 = ' ';
	char letter2 = ' ';
	char quit = ' ';

	char plugboardSettings[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char plugboardSettingsOrigonal[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };


	
	float InitializeCircles(std::vector<sf::CircleShape>& vector, std::vector<sf::CircleShape>& innercircle, sf::Vector2f startPosition)
	{
		sf::Vector2f innerCircleStartPos = startPosition;
		for (int i = 0; i <= 25; i++)
		{
			vector.push_back(sf::CircleShape());
		}

		for (int i = 0; i <= 25; i++)
		{
			vector[i].setRadius(24.f);
			vector[i].setPosition(startPosition);
			vector[i].setFillColor(sf::Color{ 255, 247, 228 });
			//vector[i].setOutlineThickness(5.f);
			//vector[i].setOutlineColor(sf::Color{ 189, 178, 161 });
			startPosition.x = startPosition.x + vector[i].getRadius() * 3;

			if (i == 8)
			{

				startPosition = { (vector[i].getRadius() * 2) + 65.f, startPosition.y + vector[i].getRadius() * 4 };


			}
			else if (i == 16)
			{
				startPosition = { 80.f, startPosition.y + vector[i].getRadius() * 4 };
			}
		}

		startPosition = innerCircleStartPos;
		startPosition.y = startPosition.y + 12.f;
		startPosition.x = 92.f;
		for (int i = 0; i <= 25; i++)
		{
			innercircle.push_back(sf::CircleShape());
		}

		for (int i = 0; i <= 25; i++)
		{
			innercircle[i].setRadius(12.f);
			innercircle[i].setPosition(startPosition);
			innercircle[i].setFillColor(sf::Color::Black);
			//innercircle[i].setOutlineThickness(5.f);
			//innercircle[i].setOutlineColor(sf::Color{ 189, 178, 161 });
			startPosition.x = startPosition.x + vector[i].getRadius() * 3;

			if (i == 8)
			{

				startPosition = { 125.f, startPosition.y + vector[i].getRadius() * 4 };


			}
			else if (i == 16)
			{
				startPosition = { 92.f, startPosition.y + vector[i].getRadius() * 4 };
			}
		}


		return vector[0].getRadius();

	}

	void InitializeText(std::vector<sf::Text>& text, sf::Vector2f startPosition, sf::Font& font, float circleRadius)
	{
		for (int i = 0; i <= 25; i++)
		{

			text.push_back(sf::Text(font));
		}
		for (int i = 0; i <= 25; i++)
		{

			text[i].setFillColor(sf::Color::White);
			//casting to float 
			text[i].setPosition(startPosition);
			startPosition.x = startPosition.x + circleRadius * 3.f;


			if (i == 8)
			{
				startPosition = { (circleRadius * 2.95f) + 60.f, startPosition.y + circleRadius * 4 };
			}
			else if (i == 16)
			{
				startPosition = { (circleRadius + 70.f), startPosition.y + circleRadius * 4 };
			}

			text[i].setString(char(i + 65));


		}
	}



public:

	int PlugboardSettings()
	{
		char* plugboardsettingstemp = plugboardSettings;

		int size = sizeof(plugboardSettings) / sizeof(plugboardSettings[0]);


		while (true)
		{
			
			//reseting to the start of the array
			*plugboardSettings = *plugboardsettingstemp;
			std::cout << "Please enter your plugboard settings" << std::endl;



			std::cout << "First letter" << std::endl;
			std::cin >> letter1;
			std::cout << "Second Letter" << std::endl;
			std::cin >> letter2;

			//making the connection between letters
			LettersSwap(letter1, letter2, plugboardSettings, size);

			std::cout << "Quit? -> Y/N" << std::endl;
			std::cin >> quit;
			if (quit == 'Y' || quit == 'y')
			{
				PlugboardConfigurationsPrint(plugboardSettings);
				break;
			}
		}
		return 0;
	}
	// swapping mechanism
	void LettersSwap(char letter1, char letter2, char* plugboardSettings, int arraySize)
	{

		for (char* i = plugboardSettings; i < (plugboardSettings + arraySize); i++)
		{
			if (*i == letter1)
			{
				*i = letter2;
			}
			else if (*i == letter2)
			{
				*i = letter1;
			}
		}
	}

	//works, find a way to do this with pointers?
	void PlugboardConfigurationsPrint(char* plugboardSettings)
	{
		//showing the plugboard configurations
		for (int i = 0; i < 26; i++)
		{
			std::cout << plugboardSettings[i] << " ";
		}
		std::cout << "\n";

	}

	//Gets the value which corresponds to the users input
	int GetPlugboardConfigurationsVals(int value, bool val1)
	{
		
		for (int i = 0; i < 26; i++)
		{
			

			if ((char)(value + 97) == plugboardSettingsOrigonal[i] && val1 == true)
			{

				return (int)plugboardSettings[i];
			}

			
			else if ((char)(value + 97) == plugboardSettings[i] && val1 == false)
			{
				return (int)plugboardSettingsOrigonal[i];
			}
		}

	}
	void RenderValues(sf::RenderWindow& window, sf::Text& textDisplayTitle, sf::Sprite& background,std::vector<sf::CircleShape>& vector, std::vector<sf::Text>& textDisplay, sf::RectangleShape& rect, std::vector<sf::CircleShape>& innerCircle, sf::RectangleShape& plugboardCreatePairRect, sf::Text& plugboardCreatePair, sf::RectangleShape& plugboardDeletePairRect, sf::Text& plugboardDeletePair)
	{
		window.draw(background);
		window.draw(rect);
		window.draw(textDisplayTitle);
		window.draw(plugboardCreatePairRect);
		window.draw(plugboardCreatePair);
		window.draw(plugboardDeletePairRect);
		window.draw(plugboardDeletePair);
		for (int i = 0; i < 26; i++)
		{
			window.draw(vector[i]);
		}
		for (int i = 0; i < 26; i++)
		{
			window.draw(innerCircle[i]);
		}
		for (int i = 0; i < 26; i++)
		{
			window.draw(textDisplay[i]);
		}
		window.display();
	}
	// we need to go over the plugboard settings and potentially change structure of program to make sure that the correct values are being sent to the engima machine code
	void SetupPlugboard()
	{
		std::vector<sf::CircleShape> vector;
		std::vector<sf::Text> textDisplay;
		std::vector<sf::CircleShape> innercircle;
		sf::RenderWindow window;
		window.create(sf::VideoMode({ 800, 600 }), "Plugboard Configuration");
		sf::Font font;
		font.openFromFile("Movistar Text Regular.ttf");

		sf::Texture backgroundTexture("Wood.jpeg");
		sf::Sprite background(backgroundTexture);
		background.setScale({ 800.f / backgroundTexture.getSize().x , 1000.f / backgroundTexture.getSize().y });


		sf::RectangleShape rect(sf::Vector2f(700.f, 360.f));
		rect.setPosition(sf::Vector2f(45.f, 150.f));
		rect.setFillColor(sf::Color{50, 49, 45});
		//rect.setOutlineThickness(3.f);
		//rect.setOutlineColor(sf::Color(160, 130, 80));

		sf::Text textDisplayTitle(font);
		textDisplayTitle.setString("Plugboard");

		textDisplayTitle.setFont(font);
		textDisplayTitle.setPosition({ 350.f,0 });
		textDisplayTitle.setCharacterSize(24);


		sf::Text plugboardCreatePair(font);
		sf::RectangleShape plugboardCreatePairRect(sf::Vector2(90.f, 40.f));
		plugboardCreatePairRect.setPosition(sf::Vector2f(600.f, 550.f));
		plugboardCreatePairRect.setFillColor(sf::Color{ 43,40,38 });
		plugboardCreatePair.setOutlineColor(sf::Color{ 212,175,55 });
		plugboardCreatePair.setString("Create Pair");
		plugboardCreatePair.setPosition(sf::Vector2(605.0f, 560.0f));
		plugboardCreatePair.setFillColor(sf::Color::White);
		plugboardCreatePair.setCharacterSize(15);

		sf::Text plugboardDeletePair(font);
		sf::RectangleShape plugboardDeletePairRect(sf::Vector2(90.f, 40.f));
		plugboardDeletePairRect.setPosition(sf::Vector2f(100.f, 550.f));
		plugboardDeletePairRect.setFillColor(sf::Color{ 43,40,38 });
		plugboardDeletePair.setOutlineColor(sf::Color{ 212,175,55 });
		plugboardDeletePair.setString("Delete Pair");
		plugboardDeletePair.setPosition(sf::Vector2(105.0f, 560.0f));
		plugboardDeletePair.setFillColor(sf::Color::White);
		plugboardDeletePair.setCharacterSize(15);



		InitializeText(textDisplay, { 95.f,static_cast<float>(window.getSize().y) / 3.3f }, font, InitializeCircles(vector, innercircle, { 80.f,static_cast<float>(window.getSize().y) / 2.7f }));
		
		int pos1Val = NULL;
		int pos2Val = NULL;

		bool pos1ValBool = false;
		bool pos2ValBool = false;


		//two buttons, pair and remove pair



		while (window.isOpen())
		{
			RenderValues(window, textDisplayTitle, background, vector,textDisplay,rect, innercircle, plugboardCreatePairRect, plugboardCreatePair, plugboardDeletePairRect, plugboardDeletePair);
			
			
			//detecting if the user has actually selected any of the plugboard values
			while (const std::optional event = window.pollEvent())
			{
				if (const auto* mousepress = event->getIf<sf::Event::MouseButtonPressed>())
				{
					for (int i = 0; i < vector.size(); i++)
					{
						if (mousepress->button == sf::Mouse::Button::Left && vector[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
						{
							//first value, then second value we need to set we then need to update the outer value
							vector[i].setOutlineThickness(3.f);
							
							if (pos1ValBool == true && pos2ValBool == true)
							{
								vector[pos1Val].setOutlineColor(sf::Color{ 255, 247, 228 });
								vector[pos2Val].setOutlineColor(sf::Color{ 255, 247, 228 });
								vector[pos1Val].setOutlineThickness(0.f);
								vector[pos2Val].setOutlineThickness(0.f);
								pos1ValBool = false;
								pos2ValBool = false;
							}
							else if (pos1ValBool == false)
							{
								pos1Val = i;
								vector[i].setOutlineColor(sf::Color::Red);
								pos1ValBool = true;
							}
							
							else if (pos1ValBool == true && pos1Val == i)
							{
								pos1Val = NULL;
								pos1ValBool = false;
								vector[i].setOutlineColor(sf::Color{ 255, 247, 228 });
							}
							else if (pos2ValBool == false && pos1ValBool == true)
							{
								pos2Val = i;
								vector[i].setOutlineColor(sf::Color::Red);
								pos2ValBool = true;
							}
							else if (pos2ValBool == true && pos2Val == i && pos1ValBool == true)
							{
								pos2Val = NULL;
								pos2ValBool = false;
								vector[i].setOutlineThickness(0.f);
								vector[i].setOutlineColor(sf::Color{ 255, 247, 228 });
							}
							
							
							std::cout << "Pos1Val: " << pos1Val << " Pos2Val: " << pos2Val << std::endl;



							// need a button that says pair, then takes these values and we create a line between each of the values
						}
					}
				}
			}
			


		}
	}


	//rendering the plugboard circles to the screen





};

