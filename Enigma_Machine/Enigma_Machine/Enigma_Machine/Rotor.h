#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

#pragma once
class Rotor
{
private:
	std::vector<int> rotorOut;
	int revolutionPositon = 0;
	int rotorTitle = 0;
	std::vector<sf::Text> textUpdate;
	std::vector<sf::RectangleShape> backgroundUpdate;

public:
	void SetRotorValues(std::vector<int>rotorout)
	{
		this->rotorOut = rotorout;
	}

	void SetPositions(sf::Vector2f startingPos, sf::Font& font)
	{

		// 3 new text objects
		// 3 new background objects
		//Each needs to be incremented downwards
		
		for (int i = 0; i < 3; i++)
		{
			textUpdate.push_back(sf::Text(font));
			backgroundUpdate.push_back(sf::RectangleShape(sf::Vector2(45.0f, 40.0f)));
		}


		sf::Vector2 tempPositionText = startingPos;
		sf::Vector2 tempPositionBackground = startingPos;

		for (int i = 0; i < 3; i++)
		{
			textUpdate[i].setOutlineColor(sf::Color{ 212,175,55 });
			// we want to display the intial values for each of the text letters - because we want to simulate a rotor, so we are starting with 1 and zero
			textUpdate[i].setString(std::to_string(i + 1));
			textUpdate[i].setPosition({ tempPositionText.x + 20.0f,tempPositionText.y + 10.0f});
			textUpdate[i].setCharacterSize(12);
			tempPositionText.y += 50.0f;
		}


		//Setting the background up for each of the text elements
		for (int i = 0; i < 3; i++)
		{
			//backgroundUpdate[i] = sf::RectangleShape(sf::Vector2(90.0f, 40.0f));
			backgroundUpdate[i].setPosition(tempPositionBackground);
			backgroundUpdate[i].setFillColor(sf::Color(40, 40, 40));
			backgroundUpdate[i].setOutlineColor(sf::Color::Red);
			tempPositionBackground.y += 50.0f;
		}



	}
	


	std::vector<sf::Text> GetTextUpdate()
	{
		return textUpdate;
	}
	std::vector<sf::RectangleShape> GetBackgroundUpdate()
	{
		return backgroundUpdate;
	}

	void SetRotorTitle(int setValue)
	{
		rotorTitle = setValue;
	}

	int GetRotorTitle()
	{
		return rotorTitle;
	}
	std::vector<int> GetRotorOutValues()
	{
		return rotorOut;
	}
	bool SetRotorPositon(int turnposInput)
	{
		if (turnposInput > 26)
		{
			std::cout << "This value is to large, please input a new value";
		}
		else if (turnposInput < 0)
		{
			std::cout << "This position is to small, please enter a new value" << std::endl;
		}
		else
		{
			//std::cout << revolutionPositon << std::endl;
			this->revolutionPositon = turnposInput;
			//std::cout << revolutionPositon << std::endl;
			return true;
		}
		return false;

	}
	int GetRotorRevolutionPositon()
	{
		return revolutionPositon;
	}




};