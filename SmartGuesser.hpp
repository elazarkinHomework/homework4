/*
 * SmartGuesser.hpp
 *
 *  Created on: Apr 14, 2019
 *      Author: elazar
 */

#ifndef SMARTGUESSER_HPP_
#define SMARTGUESSER_HPP_

#include "Guesser.hpp"

namespace bullpgia {

class SmartGuesser:public Guesser
{
private:

	typedef struct
	{
		int w, h;
		float *chanceMap;
	}GuessMap;

	GuessMap m__guessMap;

	int m_digitsAmount[10];

public:
	SmartGuesser();
	virtual ~SmartGuesser();

	string guess();

private:
	void prepareBeforeNewGame();

	string guessNext();

	void nextUnknowNumbersGuess(vector<guessCache> &cache, char *ret, int length);

	void updateDigits(vector<guessCache> &cache, int *m_digitsAmount, int length);

	void createGoodGuessByCacheHistory(vector<guessCache> &cache, char *in_out, int length);
};

}// namespace bullpgia

#endif /* SMARTGUESSER_HPP_ */
