#pragma once
#include "material.h"
#include "texture.h"
class diffuse_light : public material
{
public:
	diffuse_light(texture *a) :emit(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const { return false; }
	virtual vec3 emitted(const ray& r_in, const hit_record& rec, double u, double v, const vec3& p) const {
		if (dot(rec.normal, r_in.direction()) < 0.0)
			return vec3(0, 0, 0);
		else
			return emit->value(u, v, p);
	}

	texture *emit;
};