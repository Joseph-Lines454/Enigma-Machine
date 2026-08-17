#pragma once
#include <iostream>;
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



};

