#pragma once
#include "pdf.h"
#include "onb.h"
#include "material.h"
class cosine_pdf : public pdf
{
public:
	cosine_pdf( const vec3& w)
	{
		uvw.build_from_w(w);
	}

	virtual double value(const vec3& direction) const {
		double cosine = dot(unit_vector(direction), uvw.w());
		if (cosine > 0)
			return cosine / M_PI;
		else
			return 0;
	}

	virtual vec3 generate() const {
		return uvw.local(random_cosine_direction());
	}
	onb uvw;
};

