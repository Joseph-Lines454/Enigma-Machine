#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include "rotor.h"

//make this the base class.
class RotorSetup
{


private:

	struct Slots {
		int index;
		//we need to set positions as well allowing for slots to be added to the program.
		sf::Texture texture;
		sf::Sprite sprite;
		Rotor* rotorAssigned;
		Slots(int index) : index(index), texture("white.jpg"),sprite(texture)
		{
			this->index = index;
		}
		void UpdateRotor(Rotor* rotorVal)
		{

			this->rotorAssigned = rotorVal;
		}
	};

	void RotorSetPositions(Rotor* rotorValues, sf::Font& font)
	{

		Rotor* size = rotorValues + 2;
		Rotor* loopThrough = rotorValues + 2;
		Rotor* startPos = rotorValues;
		int input = 0;
		int counter = 0;

		//starting positions
		sf::Vector2f startingPositions = { 100.0f,20.0f };


		//loop through the different rotors
		for (Rotor* i = rotorValues; i <= size; i++)
		{
			i->SetPositions(startingPositions, font);
			startingPositions.x += 120.f;
		}

		

		//Each rotor is going to have 3 letters and one gray bar.
		//We need to render all 3 of these rotors in an efficent way




	}

	


	//rotor values
	std::vector<int> RotorOneOutput = { 19,15,5,7,23,16,2,1,14,22,8,20,21,6,24,11,25,4,0,12,13,18,9,10,3,17 };
	std::vector<int> RotorTwoOutput = { 8,9,14,20,7,3,21,2,17,19,24,18,0,11,22,25,12,4,16,6,1,5,23,10,13,15 };
	std::vector<int> RotorThreeOutput = { 7,3,11,8,12,2,20,21,25,10,4,19,5,17,18,15,16,9,22,1,24,23,0,6,13,14 };

	// Pointing to the other vector values
	std::vector<std::vector<int>*> VectorPointer = { &RotorOneOutput,&RotorTwoOutput,&RotorThreeOutput };

	std::vector<std::unique_ptr<Slots>> slots;

public:

	// Setting rotor Values
	void RotorSet(Rotor* rotorValues)
	{

		std::cout << "This is the menu where you set your rotors" << std::endl;
		std::cout << "Each rotor input a value between 0 and 26" << std::endl;

		Rotor* size = rotorValues + 2;
		int input = 0;
		int counter = 0;
		//loop through the different rotors
		for (Rotor* i = rotorValues; i <= size; i++)
		{
			std::cout << "What is the starting position for Rotor Number " << ++counter << "?" << std::endl;
			std::cin >> input;

			if (i->SetRotorPositon(input) != true)
				i--, counter--;
			std::cout << "Rotor has been set to position " << i->GetRotorRevolutionPositon() << std::endl;

		}


	}

	// it makes sensse to put the rotor code in here so the slots which result in the rotor being dragged.
	// we can remove the function above becuase we would be setting the starting positions for each rotor.
	//bottom function can be changed to ensure that the value has been added.

	const std::vector<std::unique_ptr<Slots>>& GetSlots() const
	{
		return slots;
	}

	//This will show the position to the users on the actual Enigma Machine


	//This will show the current letters when not on the current screen
	void FrontEndSetup()
	{
		//we need to draw each slot and assign a numerical value to each



		slots.push_back(std::make_unique<Slots>(1));
		slots.push_back(std::make_unique<Slots>(2));
		slots.push_back(std::make_unique<Slots>(3));

		//slots.push_back(Slots(2));
		//slots.push_back(Slots(3));


		slots[0]->sprite.setPosition({ 240.f,270.f });
		slots[1]->sprite.setPosition({ 340.f,270.f });
		slots[2]->sprite.setPosition({ 440.f,270.f });
		slots[0]->sprite.setScale({ 80.0f / slots[0]->texture.getSize().x,130.0f / slots[0]->texture.getSize().y});
		slots[1]->sprite.setScale({ 80.0f / slots[1]->texture.getSize().x,130.0f / slots[1]->texture.getSize().y });
		slots[2]->sprite.setScale({ 80.0f / slots[2]->texture.getSize().x,130.0f / slots[2]->texture.getSize().y });
	}

	//We make it so that the user can assign each rotor to a slot, we can cut out this old Command Line code!




	



	void SetupRotors(Rotor* values)
	{
		sf::RenderWindow window;
		window.create(sf::VideoMode({ 800, 600 }), "Setup Slots");
		sf::Font font;
		font.openFromFile("Movistar Text Regular.ttf");

		sf::Texture backgroundTexture("Wood.jpeg");
		sf::Sprite background(backgroundTexture);
		background.setScale({ 800.f / backgroundTexture.getSize().x , 1000.f / backgroundTexture.getSize().y });

		sf::Text textDisplayTitle(font);
		textDisplayTitle.setString("Setup Slots");

		textDisplayTitle.setFont(font);
		textDisplayTitle.setPosition({ 350.f,0 });
		textDisplayTitle.setCharacterSize(24);

		
		// call function to setup the arry of values here use a for loop

		Rotor* setupValsRotors = values;

		RotorSetPositions(setupValsRotors, font);

		//Idea for showing rotor to user, get an image of a cog, show three numbers in vertical order to show that each rotor is different
		
		

		// run the program as long as the window is open
		while (window.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			while (const std::optional event = window.pollEvent())
			{
				
				RenderAllValues(window,background,textDisplayTitle,values);

				
				//we can also do some code here for checking if any of the values are pressed

				// "close requested" event: we close the window
				if (event->is<sf::Event::Closed>())
					window.close();
			}
		}
	}

	void RenderAllValues(sf::RenderWindow& renderWindow, sf::Sprite& background, sf::Text& textDisplayTitle,Rotor* values)
	{
		renderWindow.draw(background);
		renderWindow.draw(textDisplayTitle);

		Rotor* size = values + 2;

		for (Rotor* i = values; i <= size; i++)
		{
			
			for (int j = 0; j < i->GetBackgroundUpdate().size(); j++)
			{
				// draw the background values
				renderWindow.draw(i->GetBackgroundUpdate()[j]);
			}

			for (int j = 0; j < i->GetTextUpdate().size(); j++)
			{
				// draw the text values
				renderWindow.draw(i->GetTextUpdate()[j]);
			}
		}

		renderWindow.display();
		// we got get a memory error here because of the values point not being reset but we will see i guess lol
	}











	//compile time polymorphism (method overloading)ss
	void RotorSet(Rotor* rotor, int size)
	{
		// set the rotors with their respective values
		Rotor* firstval = rotor;
		std::vector<int> rotorNames;
		Rotor* valAssign = rotor;


		rotorNames.push_back(1);
		rotor++;

		rotorNames.push_back(2);
		rotor++;
		rotorNames.push_back(3);
		rotor = firstval;



		std::cout << "Select which rotors you want in each slot From right to left" << std::endl;

		int counter = 0;


		//user set their rotor order
		for (rotor; rotor <= (firstval + size - 1); rotor++)
		{
			std::cout << "List of the rotors" << std::endl;

			for (int i = 0; i < rotorNames.size(); i++)
			{
				std::cout << rotorNames[i] << std::endl;
			}


			int rotorInput = 0;


			//user selects the order of the rotors
			std::cout << "What rotor would you like in the " << ++counter << " slot?" << std::endl;
			try
			{

				std::cin >> rotorInput;
				bool found = false;
				for (int i = 0; i < rotorNames.size(); i++)
				{
					if (rotorInput == rotorNames[i])
					{
						found = true;
						remove(rotorNames.begin(), rotorNames.end(), rotorInput);
						rotorNames.pop_back();
						valAssign->SetRotorTitle(rotorInput);
						valAssign->SetRotorValues(*VectorPointer[rotorInput - 1]);
						valAssign++;


					}
				}
				if (found == false)
				{
					std::cout << "Please input on of the remaining rotors" << std::endl;
					rotor--;
					counter--;
				}
			}
			catch (...)
			{


				std::cout << "You need to input a number between 1 and 3" << std::endl;
				rotor--;
				counter--;
				rotorInput = 0;
				break;
			}
		}

	}
};

