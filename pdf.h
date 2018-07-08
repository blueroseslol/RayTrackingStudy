#pragma once
#include "vec3.h"
class pdf
{
public:
	virtual double value(const vec3& direction) const = 0;
	virtual vec3 generate() const = 0;

};

