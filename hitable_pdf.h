#pragma once
#include "pdf.h"
#include "hitable.h"
class hitable_pdf : public pdf
{
public:
	hitable_pdf(hitable *p,const vec3& origin):ptr(p),o(origin)
	{
	}
	virtual double value(const vec3& direction) const {
		return ptr->pdf_value(o, direction);
	}
	virtual vec3 generate() const {
		return ptr->random(o);
	}
	vec3 o;
	hitable *ptr;
};

