/*
 * Chooser.hpp
 *
 *  Created on: Apr 14, 2019
 *      Author: elazar
 */

#ifndef CHOOSER_HPP_
#define CHOOSER_HPP_

#include "typedefs.h"
#include <string>

using namespace std;

namespace bullpgia
{

class Chooser {
public:
	Chooser(){}
	virtual ~Chooser(){}

	virtual string choose(uint length){return string("1234");}

};

}  // namespace bulpgia

#endif /* CHOOSER_HPP_ */
