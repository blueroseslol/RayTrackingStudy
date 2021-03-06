#pragma once
#include "pdf.h"
class mixture_pdf :	public pdf
{
public:
	mixture_pdf(pdf *p0, pdf *p1) { p[0] = p0; p[1] = p1; }
	virtual double value(const vec3& direction) const {
		return 0.5*p[0]->value(direction) + 0.5*p[1]->value(direction);
	}
	virtual vec3 generate() const {
		if (uni_dist(reng)<0.5) {
			return p[0]->generate();
		}
		else {
			return p[1]->generate();
		}
	}

	pdf *p[2];
};

