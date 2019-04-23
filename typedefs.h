/*
 * typedefs.h
 *
 *  Created on: Apr 14, 2019
 *      Author: elazar
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char BULL_PGIA_FORMAT[] = "%d,%d";

typedef uint32_t uint;
typedef unsigned char uchar;

class MallocGuard
{
private:
	char *m_ptr;
	uint m_len;
public:
	MallocGuard(uint size, char initValue=0)
	{
		m_len = size;
		m_ptr = (char *) malloc(m_len + 1);
		memset(m_ptr, initValue, m_len);
	}

	char *ptr(){return m_ptr;}

	uint len(){return m_len;}

	virtual ~MallocGuard()
	{
		free(m_ptr);
	}
};

#endif /* TYPEDEFS_H_ */
