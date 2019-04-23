/**
 * Implementation of bull-pgia game
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */

#include "play.hpp"
#include "calculate.hpp"
#include <string>
using std::string;

namespace bullpgia {
	uint play(Chooser& chooser, Guesser& guesser, uint length, uint maxTurns) {
		const uint TECHNICAL_VICTORY_TO_GUESSER = 0;
		const uint TECHNICAL_VICTORY_TO_CHOOSER = maxTurns+1;

		string choice = chooser.choose(length);

		printf("choose - %s\n", choice.c_str());

		if (choice.length()!=length)       // Illegal choice
			return TECHNICAL_VICTORY_TO_GUESSER;
		guesser.startNewGame(length);  // tell the guesser that a new game starts now
		uint indexOfTurn;
		for (indexOfTurn=0; indexOfTurn<maxTurns; ++indexOfTurn) {
			string guess = guesser.guess();
			printf("try_%d: guess - %s choice %s \n", indexOfTurn, guess.c_str(), choice.c_str());
			if (guess.length()!=length)  // Illegal guess
				return TECHNICAL_VICTORY_TO_CHOOSER;
			if (guess==choice) {
				printf("success guess - %s choice %s \n", guess.c_str(), choice.c_str());
				return indexOfTurn + 1; 
			} else {
				auto reply = calculateBullAndPgia(choice, guess);
				guesser.learn(reply); // tell the guesser how many bull and pgia were in its latest guess
			}
		}
		return TECHNICAL_VICTORY_TO_CHOOSER;  // Guesser could not guess in time
	}
}
