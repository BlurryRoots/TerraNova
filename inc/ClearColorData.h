#ifndef ClearColorData_h
#define ClearColorData_h

#include <yanecos/Data.h>

class ClearColorData
: public Yanecos::Data<ClearColorData> {

public:
	ClearColorData (float r, float g, float b, float a)
	: r(r)
	, g(g)
	, b(b)
	, a(a) {
		//
	}

	float r;
	float g;
	float b;
	float a;

};

#endif
