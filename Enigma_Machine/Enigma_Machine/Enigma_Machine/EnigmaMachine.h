#pragma once
#include "Rotor.h"
#include "PlugboardConfiguration.h"
#include "RotorSetup.h"
class EnigmaMachine
{
private:

	// checks the values of the rotorm going from rotor 1 to 3
	void NewrotorAss(int letterNum, Rotor* currentrotor, Rotor* lastrotor, int* number)
	{
		
		int newPositon = ((letterNum + (*currentrotor).GetRotorRevolutionPositon())) % 26;
		newPositon = (*currentrotor).GetRotorOutValues()[newPositon];
		*number = newPositon;
		if (currentrotor != lastrotor)
		{
			currentrotor++;
			NewrotorAss(newPositon, currentrotor, lastrotor, number);
		}

	}
	//checks the values of the rotor going from 3 - 1
	void NewrotorDes(int letterNum, Rotor* currentrotor, Rotor* lastrotor, int* number)
	{
		int newPositon = ((letterNum + (*currentrotor).GetRotorRevolutionPositon())) % 26;

		newPositon = (*currentrotor).GetRotorOutValues()[newPositon];
		*number = newPositon;
		if (currentrotor != lastrotor)
		{
			currentrotor--;
			NewrotorDes(newPositon, currentrotor, lastrotor, number);
		}
		
	}

	void DecryptProccess(int letterNum, Rotor* currentrotor, Rotor* lastrotor, int* number, bool assed)
	{



		for (int i = 0; i < (*currentrotor).GetRotorOutValues().size(); i++)
		{

			if ((*currentrotor).GetRotorOutValues()[i] == letterNum)
			{

				letterNum = i;
				letterNum = ((letterNum - (*currentrotor).GetRotorRevolutionPositon()) + 26) % 26;
				*number = letterNum;
				break;
			}
		}
		//checks weather to assend or deccend through the rotors (right to left)
		if (currentrotor != lastrotor && assed == false)
		{
			currentrotor--;
			DecryptProccess(letterNum, currentrotor, lastrotor, number, false);
		}
		else if (currentrotor != lastrotor && assed == true)
		{
			currentrotor++;
			DecryptProccess(letterNum, currentrotor, lastrotor, number, true);
		}
	}


	void RevolutionCheck(Rotor* rotor, int size)
	{
		// Automatically set the rotor position
		
		rotor->SetRotorPositon(rotor->GetRotorRevolutionPositon() + 1);
		Rotor* Rotorsize = rotor + size;
		// loop through the rotors, if they have made a full turn, the rotors will change their positon
		for (rotor; rotor <= Rotorsize; rotor++)
		{


			// sets the current rotors position back to zero then increased the next rotors position
			if (rotor->GetRotorRevolutionPositon() == 26 && rotor != Rotorsize)
			{
				rotor->SetRotorPositon(0);
				rotor++;
				rotor->SetRotorPositon(rotor->GetRotorRevolutionPositon() + 1);
				rotor--;
			}
			// last rotor just gets set back to zero
			else if (rotor->GetRotorRevolutionPositon() == 26 && rotor == Rotorsize)
			{
				rotor->SetRotorPositon(0);
			}



		}
	}



public:
	
	char EncryptMenu(Rotor* rotors, PlugboardConfiguration& plugboard, char letter)
	{
		
		Rotor* lastval = rotors;
		lastval = lastval + 2;


		RevolutionCheck(rotors, 2);

		// letter being converted from ascii to a number
		int numberresult = letter - 97;

		numberresult = plugboard.GetPlugboardConfigurationsVals(numberresult, true);

		numberresult = numberresult - 97;

		int* number = &numberresult;
		NewrotorAss(*number, rotors, lastval, number);
		NewrotorDes(*number, lastval, rotors, number);
	

		//plugboard code
		numberresult = plugboard.GetPlugboardConfigurationsVals(numberresult, false);
		numberresult = numberresult - 97;
		
		return char(numberresult + 97);

	}
	char DecryptMenu(Rotor* rotors, PlugboardConfiguration& plugboard, char letter)
	{
		
		Rotor* lastval = rotors;
		lastval = lastval + 2;
		RevolutionCheck(rotors, 2);


		int numberresult = letter - 97;

		numberresult = plugboard.GetPlugboardConfigurationsVals(numberresult, false);
		numberresult = numberresult - 97;

		int* number = &numberresult;
		DecryptProccess(*number, rotors, lastval, number, true);
		DecryptProccess(*number, lastval, rotors, number, false);

		numberresult = plugboard.GetPlugboardConfigurationsVals(numberresult, true);

		numberresult = numberresult - 97;


		
		return char(numberresult + 97);
	}


	void Instructions()
	{
		std::cout << "The current program is the enigma machine. \n The interface has different buttons. Select encrypt and to decrypt for the encrpytion/decryption of text." << std::endl;
		std::cout << "When you type, one of the letters will light up with the output." << std::endl;
		std::cout << "You need to click on the setup button for the machine to work correctly, you will need to define rotor positions, ect" << std::endl;
	}

};
