/*
 * SmartGuesser.cpp
 *
 *  Created on: Apr 14, 2019
 *      Author: elazar
 */

#include "SmartGuesser.hpp"
#include "calculate.hpp"

namespace bullpgia
{

const char Guesser::MAP[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

SmartGuesser::SmartGuesser()
{
	m__guessMap.chanceMap = NULL;
}

SmartGuesser::~SmartGuesser()
{
	if(m__guessMap.chanceMap != NULL)
	{
		free(m__guessMap.chanceMap);
		m__guessMap.chanceMap = NULL;
	}
}

string SmartGuesser::guess()
{
	string ret = guessNext();

	if(m_cache.size() <= 0 )// mean start new game
	{
		prepareBeforeNewGame();
	}

	m_cache.push_back(guessCache(ret, 0, 0));

	return ret;
}

void SmartGuesser::prepareBeforeNewGame()
{
	// m_cache already clean
	if(m__guessMap.chanceMap != NULL)
	{
		free(m__guessMap.chanceMap);
	}

	m__guessMap.w = length;

	m__guessMap.chanceMap = (float *) malloc(10*length*sizeof(float));// 10 digits*length of number

	for(int i = 0; i < length; i++)
	{
		m__guessMap.chanceMap[i] = 0.5f;
	}

	memset(m_digitsAmount, 0, sizeof(m_digitsAmount));
}

string SmartGuesser::guessNext()
{
	MallocGuard cret(length);
	char *ret = cret.ptr();

	if(m_cache.size() > 0 && m_cache.back().bull+m_cache.back().pgia >= length)
	{
//		printf("will copy %s we know all numbers\n", m_cache.back().guess.c_str());
		memcpy(ret, m_cache.back().guess.c_str(), length);
	}
	else
	{
		// should be in override function learn
		// but the problem is a object slicing in implementation of teacher
		// and we cant override it cause it not called!

		updateDigits(m_cache, m_digitsAmount, length);

		nextUnknowNumbersGuess(m_cache, ret, length);
	}

//	printf("try_%d: ", m_cache.size());
//	for(int i = 0; i < length; i++)
//	{
//		printf("%c", ret[i]);
//	}
//	printf("\n");

	// TODO add function createGoodGuessByCacheHistory

	createGoodGuessByCacheHistory(m_cache, ret, length);

	return string(ret);
}

void SmartGuesser::nextUnknowNumbersGuess(vector<guessCache> &cache, char *ret, int length)
{
	// More that 10 guest it cant go to here
	int counter = 0;

	for(int i = 0; i < cache.size(); i++)
	{
		for(int j = 0; j < m_digitsAmount[i]; j++)
		{
			ret[counter++] = MAP[i];
		}
	}

	for(;counter < length; counter++)
	{
		ret[counter] = MAP[cache.size()];
	}
}

void SmartGuesser::updateDigits(vector<guessCache> &cache, int *digitsAmount, int length)
{
	int alreadyCounted = 0;

	if(cache.size() <= 0)
	{
		return;
	}

	for(int i = 0; i < cache.size() - 1; i++)
	{
		alreadyCounted += digitsAmount[i];
	}

	digitsAmount[cache.size()-1] = cache.back().bull + cache.back().pgia - alreadyCounted;
}

void SmartGuesser::createGoodGuessByCacheHistory(vector<guessCache> &cache, char *ret, int len)
{
	int index;
	MallocGuard goffsets(len, 1);
	MallocGuard gtemp(len);
	MallocGuard gcounts((len+1)*sizeof(int));

	char *offsets = goffsets.ptr();
	char *temp = gtemp.ptr();
	int *counts = (int *)gcounts.ptr();

	while(!testCombinationByCache(cache, ret, len))
	{
		index = 1;
		counts[index]++;

		while(index < len && counts[index] > index)
		{
			counts[index] = 0;
			counts[++index]++;
		}

		if(counts[len] >= 1) break;

		memcpy(temp, ret, len);
		for(int i = 0; i <= index; i++)
		{
			temp[i] = ret[(i+offsets[index]+index+1)%(index+1)];
		}

		offsets[index] *= -1;

		memcpy(ret, temp, len);

//		for(int i = 0; i < len; i++)
//		{
//			printf("%c", ret[i]);
//		}
//
//		printf("\n");

	}
}

bool SmartGuesser::testCombinationByCache(vector<guessCache> &cache, const char *ret, int len)
{
	for(int i = 0; i < cache.size(); i++)
	{
		int bul, pgia;

		calculateBullAndPgia2(cache[i].guess, string(ret), bul, pgia);

		if(bul != cache[i].bull || pgia != cache[i].pgia) return false;
	}
	return true;
}

} //namespace bullpgia
