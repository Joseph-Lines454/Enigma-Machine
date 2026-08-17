#include <iostream>
#include <vector>


#pragma once
//Rotor object (Rotor 1,2,3)
class Rotor
{
private:
	std::vector<int> rotorOut;
	int revolutionPositon = 0;
	int rotorTitle = 0;

public:
	void SetRotorValues(std::vector<int>rotorout)
	{
		this->rotorOut = rotorout;
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