#include "calculate.hpp"

bool calculateBullAndPgia2(string _input, string _expected, int &bul, int &pgia)
{
	char out[16];
	int l_input = strlen(_input.c_str());
	int l_expected = strlen(_input.c_str());

	bul = 0;
	pgia = 0;

	if(l_input != l_expected)
	{
		return false;
	}
	else
	{
		MallocGuard mg0(l_input), mg1(l_input);
		char *input = mg0.ptr(), *expected = mg1.ptr();
		static const char VOID_LOCATION = '*';

		memcpy(input, _input.c_str(), l_input);
		memcpy(expected, _expected.c_str(), l_input);

		for(int i = 0; i < l_input; i++)
		{
			if(input[i] == expected[i])
			{
				bul++;
				expected[i] = VOID_LOCATION;
				input[i] = VOID_LOCATION;
			}
		}

		for(int i = 0; i < l_input; i++)
		{
			for(int j = 0; j < l_input; j++)
			{
				if(i != j && input[i] != VOID_LOCATION && expected[j] != VOID_LOCATION && input[i] == expected[j])
				{
					expected[j] = VOID_LOCATION;
					input[i] = VOID_LOCATION;
					pgia++;
				}
			}
		}
	}

	return true;
}

string calculateBullAndPgia(string _input, string _expected)
{
	char out[16];
	int bul, pgia;

	if(calculateBullAndPgia2(_input, _expected, bul, pgia))
	{
		sprintf(out, BULL_PGIA_FORMAT, bul, pgia);
		return string(out);
	}

	return string("calculateBullAndPgia ERROR - diffrent lenghts of input vs expected");
}

