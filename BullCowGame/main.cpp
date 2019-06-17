/* This is the console executable , that makes use of the BullCow class.
This acts as the view in an MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game

//Entry point for the application
int main()
{
	bool bPlayAgain{ false };
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0; //Exit the application
}


//Introduce the game
void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls & Cows, a fun word game!\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram word I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// Plays the Game
void PlayGame()
{
	
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();
	std::cout << "You have " << MaxTries << " tries." << std::endl;

	//loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// Submit valid Guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();

	return;
}


// loop continually until user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		//Get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// Check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram word (an isogram is a word without repeating letters).\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		return true;
	}
	else if (Response[0] == 'n' || Response[0] == 'N')
	{
		return false;
	}
	else 
	{
		return false;
	}
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\nCongratulations! You won the game!";
	}
	else
	{
		std::cout << "\nToo bad, the Game is Over!";
	}
	std::cout << std::endl;
	return;
}
