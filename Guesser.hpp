/*
 * Guesser.hpp
 *
 *  Created on: Apr 14, 2019
 *      Author: elazar
 */

#ifndef GUESSER_HPP_
#define GUESSER_HPP_
#include <string>
#include <vector>
#include "typedefs.h"

using namespace std;

namespace bullpgia {

class Guesser {

protected:

	static const char MAP[];

	struct guessCache
	{
		guessCache(string g, int b, int p)
		{
			guess = g;
			bull = b;
			pgia = p;
		}
		int bull, pgia;
		string guess;
	};

	vector<guessCache> m_cache;

public:
	uint length;

	Guesser(){length = 0;}
	virtual ~Guesser(){}

	virtual string guess()
	{
		string ret = string("1234");

		m_cache.push_back(guessCache(ret, 0, 0));

		return ret;
	}

	void startNewGame(uint l)
	{
		length = l;
		m_cache.clear();
	}

	void learn(string replay)
	{
		int bull, pgia;
		sscanf(replay.c_str(), BULL_PGIA_FORMAT, &bull, &pgia);

		if(m_cache.size() > 0)
		{
			m_cache.back().bull = bull;
			m_cache.back().pgia = pgia;
		}
	}
};

} //namespace bullpgia

#endif /* GUESSER_HPP_ */
