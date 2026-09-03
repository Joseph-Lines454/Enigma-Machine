#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

#include "EnigmaMachine.h"




//button class
class Button
{
private:
	std::string name = " ";
	std::string text = "";

public:

	Button(std::string buttonName, sf::Vector2f buttonPosition, std::string text)
	{
		name = buttonName;
		this->buttonPosition = buttonPosition;
		this->text = text;
		
	}

	sf::Vector2f GetButtonPosition()
	{
		return buttonPosition;
	}
	std::string ReturnString()
	{
		return name;
	}
	

protected:
	sf::Vector2f buttonPosition = {15.f,30.f };
	
};
//inheritance implemented


class LampBoard
{
public:
	virtual float InitializeCircles(std::vector<sf::CircleShape>& vector, sf::Vector2f startPosition)
	{

		for (int i = 0; i <= 25; i++)
		{
			vector.push_back(sf::CircleShape());
		}

		for (int i = 0; i <= 25; i++)
		{
			vector[i].setRadius(27.f);
			vector[i].setPosition(startPosition);
			vector[i].setFillColor(sf::Color(18,16,12));
			vector[i].setOutlineThickness(3.f);
			vector[i].setOutlineColor(sf::Color(197, 160, 89));
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

	//positions for the text
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
};

class Keyboard : public LampBoard
{
public:
	float InitializeCircles(std::vector<sf::CircleShape>& vector, sf::Vector2f startPosition) override
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


};

class SFMLFrontEnd
{	
private:
	
	
	void InstructionsWindow()
	{
		sf::RenderWindow window;
		window.create(sf::VideoMode({ 800, 600 }), "Instructions");
		sf::Font font;
		font.openFromFile("Movistar Text Regular.ttf");

		sf::Texture backgroundTexture("Wood.jpeg");
		sf::Sprite background(backgroundTexture);
		background.setScale({ 800.f / backgroundTexture.getSize().x , 1000.f / backgroundTexture.getSize().y });

		sf::Text textDisplayTitle(font);
		textDisplayTitle.setString("Instructions");

		textDisplayTitle.setFont(font);
		textDisplayTitle.setPosition({ 350.f,0 });
		textDisplayTitle.setCharacterSize(24);

		sf::Text instructionsDisplay(font);
		instructionsDisplay.setString("This project has been designed to recreate an enigma machine. To start drag a rotor in each\n slot,then click on the rotor to set each individual rotors position. Configure the plugboard by\n swapping each letter in the desired letter. If your decrypting a message select, decrypt.\n Use your physical keyboard to type. Once you have typed a letter, note the letter which\n  flashes on the lampboard. You have now encrypted a letter.");
		instructionsDisplay.setPosition({ 5.f,200.f });
		instructionsDisplay.setCharacterSize(21);


		// run the program as long as the window is open
		while (window.isOpen())
		{
			// check all the window's events that were triggered since the last iteration of the loop
			while (const std::optional event = window.pollEvent())
			{
				window.draw(background);
				window.draw(textDisplayTitle);
				window.draw(instructionsDisplay);
				window.display();
				// "close requested" event: we close the window
				if (event->is<sf::Event::Closed>())
					window.close();
			}
		}
	}

	void UpdateWindow(sf::RenderWindow& window, sf::RectangleShape& Instructions, sf::Sprite& spriteSetup, sf::RectangleShape& encryptRec, sf::Text& textDisplayEnig, sf::Text& textDisplayIns, sf::Text& textDisplay3, sf::Text& textDisplay4, std::vector<sf::CircleShape>& vector, std::vector<sf::CircleShape>& vectorKeyBoard, std::vector<sf::Text>& textDisplay, std::vector<sf::Text>& textDisplayKeyBoard, sf::Sprite& background, sf::RectangleShape& rect, RotorSetup& setup)
	{
		window.draw(background);
		window.draw(rect);
		window.draw(Instructions);
		window.draw(spriteSetup);
		window.draw(textDisplayEnig);
		window.draw(textDisplay3);
		window.draw(encryptRec);
		window.draw(textDisplay4);
		window.draw(textDisplayIns);
		
		window.draw(textDisplayEnig);

		//display all of the circles and text
		for (int i = 0; i < 26; i++)
		{
			window.draw(vector[i]);
			window.draw(vectorKeyBoard[i]);
		}
		for (int i = 0; i < 26; i++)
		{
			window.draw(textDisplay[i]);
			window.draw(textDisplayKeyBoard[i]);

			
		}
		/*
		for (int i = 0; i < setup.GetSlots().size(); i++)
		{
			window.draw(setup.GetSlots()[i]->sprite);
		}*/
		for (size_t i = 0; i < setup.GetSlots().size(); ++i)
		{
			window.draw(setup.GetSlots()[i]->sprite);
		}
		window.display();
	}
public:

	

	void ProgramBegin()
	{

		// creating the window as well as setting the title (Enigma Machine)

		sf::RenderWindow window;
		window.create(sf::VideoMode({ 800, 1000 }), "Enigma Machine");
		//std::cout << "Window has been created: " << window.isOpen() << std::endl;
		sf::Font font;
		font.openFromFile("Movistar Text Regular.ttf");

		sf::Text textDisplayEnig(font);
		textDisplayEnig.setString("Enigma Machine");

		textDisplayEnig.setFont(font);
		textDisplayEnig.setPosition({ 10.f,0 });
		textDisplayEnig.setCharacterSize(24);

		// creating the circle and text elements.
		std::vector<sf::CircleShape> vector;
		std::vector<sf::Text> textDisplay;


		std::vector<sf::CircleShape> vectorKeyBoard;
		std::vector<sf::Text> textDisplayKeyBoard;
		

		sf::Texture backgroundTexture("Wood.jpeg");
		sf::Sprite background(backgroundTexture);

		sf::RectangleShape rect(sf::Vector2f(750.f,700.f));
		rect.setPosition(sf::Vector2f(25.f, 250.f));
		rect.setFillColor(sf::Color(45, 40, 35));
		rect.setOutlineThickness(3.f);
		rect.setOutlineColor(sf::Color(160, 130, 80));


		background.setScale({ 800.f / backgroundTexture.getSize().x , 1000.f / backgroundTexture.getSize().y });
		//initialization of the button values
		Button instructions("Instructions", { 300.f,10.f }, "Text");
		//sf::Texture textureInstructions("white.jpg", false, sf::IntRect({ 100,300 }, { 80,40 }));
		//sf::Sprite spriteInstructions(textureInstructions);
		sf::Text textDisplayIns(font);
		sf::RectangleShape instructionsRec(sf::Vector2(90.f,40.f));
		instructionsRec.setPosition(sf::Vector2f(300.f, 10.f));
		instructionsRec.setFillColor(sf::Color{ 43,40,38 });
		instructionsRec.setOutlineColor(sf::Color{ 212,175,55 });
		textDisplayIns.setString(instructions.ReturnString());
		//spriteInstructions.setPosition(instructions.GetButtonPosition());
		textDisplayIns.setPosition(sf::Vector2(305.0f,20.0f));
		textDisplayIns.setFillColor(sf::Color::White);
		
		textDisplayIns.setCharacterSize(15);

		





		Button setup("Setup", { 500.f,10.f }, "Text");
		sf::Texture textureSetup("white.jpg", false, sf::IntRect({ 100,300 }, { 80,40 }));
		sf::Sprite spriteSetup(textureSetup);
		sf::Text textDisplay3(font);
		textDisplay3.setString(setup.ReturnString());
		spriteSetup.setPosition(setup.GetButtonPosition());
		textDisplay3.setPosition(setup.GetButtonPosition());
		textDisplay3.setFillColor(sf::Color{ 51,255,51 });
		textDisplay3.setCharacterSize(15);

		/*
		Button encryptDec("Encrypt", { 600.f,10.f }, "Text");
		sf::Texture encryptDecrypt("white.jpg", false, sf::IntRect({ 100,300 }, { 80,40 }));
		sf::Sprite encryptDecS(encryptDecrypt);
		sf::Text textDisplay4(font);
		textDisplay4.setString(encryptDec.ReturnString());
		encryptDecS.setPosition(encryptDec.GetButtonPosition());
		textDisplay4.setPosition(encryptDec.GetButtonPosition());
		textDisplay4.setFillColor(sf::Color{ 51,255,51 });
		textDisplay4.setCharacterSize(15);
		*/
		Button encryptDec("Encrypt", { 600.f,10.f }, "Text");
		sf::Text textDisplay4(font);
		sf::RectangleShape encryptRec(sf::Vector2(90.f, 40.f));
		encryptRec.setPosition(sf::Vector2f(400.f, 10.f));
		encryptRec.setFillColor(sf::Color{ 43,40,38 });
		encryptRec.setOutlineColor(sf::Color{ 212,175,55 });
		textDisplay4.setString(encryptDec.ReturnString());
		//spriteInstructions.setPosition(instructions.GetButtonPosition());
		textDisplay4.setPosition(sf::Vector2(420.0f, 20.0f));
		textDisplay4.setFillColor(sf::Color::White);

		textDisplay4.setCharacterSize(15);



		//initalization of the enigam machine
		EnigmaMachine newEnigma;


		//plugboard configuration
		Rotor* rotorValues = new Rotor[3];
		Rotor* firstval = rotorValues;
		PlugboardConfiguration plugboard;
		RotorSetup Setup;
		LampBoard lampBoard;
		Keyboard keyBoard;
		bool encrypt = false;
		Setup.FrontEndSetup();
		try
		{
			lampBoard.InitializeText(textDisplay, { 65.f,static_cast<float>(window.getSize().y) / 2.7f }, font, lampBoard.InitializeCircles(vector, { 50.f,static_cast<float>(window.getSize().y) / 2.7f }));
			keyBoard.InitializeText(textDisplayKeyBoard, { 65.f,300.f + static_cast<float>(window.getSize().y) / 2.7f }, font, keyBoard.InitializeCircles(vectorKeyBoard, { 50.f,300.f + static_cast<float>(window.getSize().y) / 2.7f }));
			while (window.isOpen())
			{
				

				//event which is used to check for user input
				while (const std::optional event1 = window.pollEvent())
				{

					if (event1->is<sf::Event::Closed>())
						window.close();
					// if the user presses the mouse
					if (const auto* mousePress = event1->getIf<sf::Event::MouseButtonPressed>())
					{
						//show intructions on how to use the program
						if (mousePress->button == sf::Mouse::Button::Left && instructionsRec.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
						{
							//we want to create a new window here showing the user instructions
							InstructionsWindow();
							//newEnigma.Instructions();
						}
						//exit the program
						
						
						//Setup the enigma machine
						else if (mousePress->button == sf::Mouse::Button::Left && spriteSetup.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
						{
							std::cout << "Welcome to your engima machine" << std::endl;
							std::cout << "We need to set up your enviorement" << std::endl;
							//functions that are used to setup the enigma machine
							plugboard.PlugboardSettings();
							Setup.RotorSet(firstval, 3);
							Setup.RotorSet(firstval);

						}
						// switches to encrypt/decrypt
						else if (mousePress->button == sf::Mouse::Button::Left && encryptRec.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
						{
							encrypt = !encrypt;
						}
					}
					//checks for user input (when the user inputs values into the enigma machine)
					else if (const auto* keyPress = event1->getIf<sf::Event::KeyPressed>())
					{
						std::vector<sf::Keyboard::Scancode> keyboard = { sf::Keyboard::Scancode::A,sf::Keyboard::Scancode::B,sf::Keyboard::Scancode::C, sf::Keyboard::Scancode::D, sf::Keyboard::Scancode::E, sf::Keyboard::Scancode::F, sf::Keyboard::Scancode::G,sf::Keyboard::Scancode::H,
				   sf::Keyboard::Scancode::I, sf::Keyboard::Scancode::J, sf::Keyboard::Scancode::K, sf::Keyboard::Scancode::L, sf::Keyboard::Scancode::M, sf::Keyboard::Scancode::N,sf::Keyboard::Scancode::O,sf::Keyboard::Scancode::P,sf::Keyboard::Scancode::Q,sf::Keyboard::Scancode::R,sf::Keyboard::Scancode::S,
				   sf::Keyboard::Scancode::T,sf::Keyboard::Scancode::U,sf::Keyboard::Scancode::V,sf::Keyboard::Scancode::W,sf::Keyboard::Scancode::X,sf::Keyboard::Scancode::Y,sf::Keyboard::Scancode::Z };
						
						//need to create functionality for keyboard when user presses make the key a different colour

						for (int i = 0; i < 26; i++)
						{
							if (keyPress->scancode == keyboard[i])
							{
								
								//vectorKeyBoard[i].setFillColor(sf::Color(105, 105, 105));
								vectorKeyBoard[i].setRadius(25.f);
								window.clear();
								UpdateWindow(window, instructionsRec, spriteSetup, encryptRec, textDisplayEnig, textDisplayIns, textDisplay3, textDisplay4, vector, vectorKeyBoard, textDisplay, textDisplayKeyBoard,background,rect,Setup);
								
								Sleep(1400);
								//vectorKeyBoard[i].setFillColor(sf::Color::White);
								vectorKeyBoard[i].setRadius(27.f);
								window.clear();
								UpdateWindow(window, instructionsRec, spriteSetup, encryptRec, textDisplayEnig, textDisplayIns, textDisplay3, textDisplay4, vector, vectorKeyBoard, textDisplay, textDisplayKeyBoard,background,rect,Setup);
								
								//performs the encrypt proccess of the user input and lights up the bulb which corresponds to the enigma machines output
								if (encrypt == true)
								{
									int pos = newEnigma.EncryptMenu(rotorValues, plugboard, static_cast<char>(i + 97)) - 97;
									std::cout << char(pos + 97) << std::endl;

									vector[pos].setFillColor(sf::Color(226, 203, 40));
									window.draw(vector[pos]);
									window.display();

									Sleep(1000);
									vector[pos].setFillColor(sf::Color(40, 40, 40));
									window.draw(vector[pos]);
									window.display();
									
								}
								//performs the decrypt proccess of the user input and lights up the bulb which corresponds to the enigma machines output
								else if (encrypt == false)
								{

									int pos = newEnigma.DecryptMenu(rotorValues, plugboard, static_cast<char>(i + 97)) - 97;

									std::cout << char(pos + 97) << std::endl;

									vector[pos].setFillColor(sf::Color(226, 203, 40));
									window.draw(vector[pos]);
									window.clear();
									UpdateWindow(window, instructionsRec, spriteSetup, encryptRec, textDisplayEnig, textDisplayIns, textDisplay3, textDisplay4, vector, vectorKeyBoard, textDisplay, textDisplayKeyBoard,background,rect,Setup);

									Sleep(1000);
									vector[pos].setFillColor(sf::Color(18, 16, 12));
									window.draw(vector[pos]);
									window.clear();
									UpdateWindow(window, instructionsRec, spriteSetup, encryptRec, textDisplayEnig, textDisplayIns, textDisplay3, textDisplay4, vector, vectorKeyBoard, textDisplay, textDisplayKeyBoard,background,rect,Setup);
								}
								
								break;
							}
						}
					}

				}
				window.clear();
				UpdateWindow(window, instructionsRec,spriteSetup, encryptRec,textDisplayEnig,textDisplayIns,textDisplay3,textDisplay4,vector,vectorKeyBoard,textDisplay,textDisplayKeyBoard,background,rect,Setup);
				//draws all of the elements agian once the lightbulb needs to be turned off
				
			}
		}
		catch (...)
		{
			std::cout << "Invalid" << std::endl;
		}
	}
};



int main()
{
	SFMLFrontEnd SFML;
	SFML.ProgramBegin();
	return 0;
}


