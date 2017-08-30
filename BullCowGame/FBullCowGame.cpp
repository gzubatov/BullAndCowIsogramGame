#pragma once
#include "FBullCowGame.h"
#include <map>
#include <vector>
#include <ctime>
#include <random>
#define TMap std::map

using FString = std::string;
using int32 = int;

// Random words you can play with
std::vector<FString> WordBank{ "planet", "cat", "bat", "course", "horse", "planes","isogram",
	"amigos", "ageism", "image", "mirage", "gizmos", "cargo", "cigar", "corgi", "cram", "macro", "micro"
	"farms", "farm", "game", "gamer", "games","dorm", "dorms", "omega", "fair", "fairs", "fire", "tire", 
	"rage", "gear", "gears", "germ", "germs", "raise", "rise", "hair", "hairs", "age", "grows", "grow",
	"visor", "air", "bear", "bare", "oar", "soar", "raid", "road", "soda", "acid", "orange", "blue", "red",
	"arm", "army", "ear", "swam", "swim", "warm", "wig", "wigs", "worm", "grow", "gasp", "grasp"};



FBullCowGame::FBullCowGame() 
{
	Reset();
}

void FBullCowGame::Reset()
{
	std::default_random_engine engine(static_cast<unsigned int>(time(0)));
	std::uniform_int_distribution<unsigned int> randomInt{ 0, WordBank.vector::size() - 1 };
	const FString HIDDEN_WORD = WordBank[randomInt(engine)];
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) { // if the guess isn't an isogram 
		return EGuessStatus::NOT_ISOGRAM; 
	}
	else if (!IsLowercase(Guess)) {// if the guess isn't all lower case 
		return EGuessStatus::NOT_LOWERCASE; // TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength()) {// if the guess length is wrong
		return EGuessStatus::WRONG_LENGTH;
	}
	else {
		return EGuessStatus::OK;
	}
}


// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // increment bulls
				}
				else {
					BullCowCount.Cows++; // increment cows
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

FString FBullCowGame::GetHiddenWord() const
{
	return MyHiddenWord;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() < 2) { return true; }

	TMap<char, bool> LetterSeen; // setup our map

	for (auto Letter : Word) {	
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {// if the letter is in the map
			return false; // we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if(!islower(Letter))// if not a lower case letter
			return false;
	}
	return true;
}

