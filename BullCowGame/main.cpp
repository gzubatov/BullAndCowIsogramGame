// Udemy Unreal Engine Course Practice
// will use Unreal best practice naming conventions

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal Engine friendly
using FString = std::string;
using int32 = int;

// function prototypes outside of a class
void PrintIntro();
void PlayGame();
FString GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

int main() 
{
	do {
		PrintIntro();
		PlayGame();
	} while(AskToPlayAgain());
	system("pause");
	return 0;
}

void PrintIntro() 
{
	BCGame.Reset();
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "\nAn 'isogram' is a word without any repeating letters,"
		<< "\nfor example 'hair' is an isogram while 'mono' is not\nbecause "
		<< "it uses the letter 'o' twice." << std::endl;
	std::cout << "BULL = correct letter in the correct spot\n"
		<< "COW = correct letter in the incorrect spot\n" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl << std::endl;
}


void PlayGame() 
{
	//BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FString Guess = GetValidGuess(); 

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess); // check if guess is valid

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FString GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::INVALID_STATUS;	
	FString Guess = "";
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess); // check if guess is valid
		switch (Status) {
			case EGuessStatus::WRONG_LENGTH:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;
			case EGuessStatus::NOT_ISOGRAM:
				std::cout << "Please enter a word without repeating letters.\n\n";
				break;
			case EGuessStatus::NOT_LOWERCASE:
				std::cout << "Please enter all lower case letters.\n\n";
				break;
			default:
				// asume the guess is valid
				break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors

	return Guess;
}


bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FString Response{ "" };
	getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) {
		std::cout << "Congrats! You've won the game!\n" << std::endl;
	}
	else {
		std::cout << "Sorry :(\nYou've lost the game. Better luck next time." << std::endl;
		std::cout << "The word was: " << BCGame.GetHiddenWord() << "\n" << std::endl;
	}
}
