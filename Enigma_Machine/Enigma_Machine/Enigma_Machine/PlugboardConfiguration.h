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


	
	float InitializeCircles(std::vector<sf::CircleShape>& vector, sf::Vector2f startPosition)
	{

		for (int i = 0; i <= 25; i++)
		{
			vector.push_back(sf::CircleShape());
		}

		for (int i = 0; i <= 25; i++)
		{
			vector[i].setRadius(27.f);
			vector[i].setPosition(startPosition);
			vector[i].setFillColor(sf::Color(40, 40, 40));
			vector[i].setOutlineThickness(2.f);
			vector[i].setOutlineColor(sf::Color(180, 180, 180));
			startPosition.x = startPosition.x + vector[i].getRadius() * 3;

			if (i == 8)
			{

				startPosition = { (vector[i].getRadius() * 2) + 28.f, startPosition.y + vector[i].getRadius() * 3 };


			}
			else if (i == 16)
			{
				startPosition = { 40.f, startPosition.y + vector[i].getRadius() * 3 };
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

			text[i].setFillColor(sf::Color{ 230,255,215 });
			//casting to float 
			text[i].setPosition(startPosition);
			startPosition.x = startPosition.x + circleRadius * 3.f;


			if (i == 8)
			{

				startPosition = { (circleRadius * 2.95f) + 20.f, startPosition.y + circleRadius * 3 };


			}
			else if (i == 16)
			{
				startPosition = { (circleRadius + 35.f), startPosition.y + circleRadius * 3 };
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
	void RenderValues(sf::RenderWindow& window, sf::Text& textDisplayTitle, sf::Sprite& background,std::vector<sf::CircleShape>& vector, std::vector<sf::Text>& textDisplay)
	{
		window.draw(background);
		window.draw(textDisplayTitle);
		for (int i = 0; i < 26; i++)
		{
			window.draw(vector[i]);
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
		sf::RenderWindow window;
		window.create(sf::VideoMode({ 800, 600 }), "Plugboard Configuration");
		sf::Font font;
		font.openFromFile("Movistar Text Regular.ttf");

		sf::Texture backgroundTexture("Wood.jpeg");
		sf::Sprite background(backgroundTexture);
		background.setScale({ 800.f / backgroundTexture.getSize().x , 1000.f / backgroundTexture.getSize().y });

		sf::Text textDisplayTitle(font);
		textDisplayTitle.setString("Plugboard");

		textDisplayTitle.setFont(font);
		textDisplayTitle.setPosition({ 350.f,0 });
		textDisplayTitle.setCharacterSize(24);

		InitializeText(textDisplay, { 65.f,static_cast<float>(window.getSize().y) / 3.3f }, font, InitializeCircles(vector, { 50.f,static_cast<float>(window.getSize().y) / 2.7f }));
		while (window.isOpen())
		{
			RenderValues(window, textDisplayTitle, background, vector,textDisplay);
		}
	}


	//rendering the plugboard circles to the screen





};

