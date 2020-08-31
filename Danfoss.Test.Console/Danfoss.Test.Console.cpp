// Danfoss.Test.Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct letterType
{
    char letter;
    int letterCount;
};

void initLetterList(letterType letterList[])
{
	for (int index = 0; index < 26; index++)
	{
		//This segment sets the uppercase letters
		letterList[index].letter = static_cast<char>(65 + index);
		letterList[index].letterCount = 0;

		//This segment sets the lowercase letters
		letterList[index + 26].letter = static_cast<char>(97 + index);
		letterList[index + 26].letterCount = 0;

	}
}

void getAllLettersCount(std::string& path, letterType letterList[])
{
	initLetterList(letterList);
	std::fstream stream(path, std::fstream::in);

	if (!stream.is_open())
	{
		std::cout << "Cannot read the text file to count number of the letters in the text!" << std::endl;
		return;
	}

	char ch;

	while (stream >> std::noskipws >> ch)
	{

		if ('A' <= ch && ch <= 'Z')
		{
			letterList[static_cast<int>(ch) - 65].letterCount++;
		}
		else if ('a' <= ch && ch <= 'z')
		{
			letterList[static_cast<int>(ch) - 71].letterCount++;
		}

	}

	stream.close();
}

void getStartingLetterCount(std::string& path, letterType letterList[])
{
		
	initLetterList(letterList);
	std::fstream stream(path, std::fstream::in);

	if (!stream.is_open())
	{
		std::cout << "Cannot read the text file to count number of words starting with specific letter!" << std::endl;
		return;
	}

	std::string input;
	std::vector<char> text;

	while (stream >> input)
	{
		text.push_back(input.at(0));
	}

	for (size_t i = 0; i < text.size(); i++)
	{
		char ch = text[i];
		if ('A' <= ch && ch <= 'Z')
		{
			letterList[static_cast<int>(ch) - 65].letterCount++;
		}
		else if ('a' <= ch && ch <= 'z')
		{
			letterList[static_cast<int>(ch) - 71].letterCount++;
		}
	}

	stream.close();
}

bool sorter(letterType const letterOne, letterType const letterTwo) {
		
	return letterOne.letterCount > letterTwo.letterCount;
}

int main()
{
    std::string path;

    std::cout << "Please enter path for the testfile location:\n";

    std::cin >> path;
	
	letterType allLetterList[52];
	letterType startingLetterList[52];

	getAllLettersCount(path, allLetterList);

	std::sort(std::begin(allLetterList), std::end(allLetterList), sorter);

	std::cout << "The number of the letters in the text:" << std::endl;

	for (letterType word : allLetterList)
	{
		if (word.letterCount > 0)
		{
			std::cout << word.letter << word.letterCount << std::endl;
		}
	}

	getStartingLetterCount(path, startingLetterList);

	std::sort(std::begin(startingLetterList), std::end(startingLetterList), sorter);

	std::cout << "The number of words starting with this letter:" << std::endl;

	for (letterType word : startingLetterList)
	{
		if (word.letterCount > 0)
		{
			std::cout << word.letter << word.letterCount << std::endl;
		}
		
	}

}

