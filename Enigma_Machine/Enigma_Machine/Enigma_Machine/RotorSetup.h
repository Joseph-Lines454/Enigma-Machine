#pragma once
#include <iostream>
#include <cstring>
#include <vector>

#include "rotor.h"

//make this the base class.
class RotorSetup
{


private:

	//rotor values
	std::vector<int> RotorOneOutput = { 19,15,5,7,23,16,2,1,14,22,8,20,21,6,24,11,25,4,0,12,13,18,9,10,3,17 };
	std::vector<int> RotorTwoOutput = { 8,9,14,20,7,3,21,2,17,19,24,18,0,11,22,25,12,4,16,6,1,5,23,10,13,15 };
	std::vector<int> RotorThreeOutput = { 7,3,11,8,12,2,20,21,25,10,4,19,5,17,18,15,16,9,22,1,24,23,0,6,13,14 };

	// Pointing to the other vector values
	std::vector<std::vector<int>*> VectorPointer = { &RotorOneOutput,&RotorTwoOutput,&RotorThreeOutput };


	
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
	//compile time polymorphism (method overloading)
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

