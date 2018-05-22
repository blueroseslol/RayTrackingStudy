#pragma once
#include "material.h"
#include "texture.h"
class lambertian :public material
{
public:
	//lambertian(const vec3& a):albedo(a)	{}
	lambertian(texture *a): albedo(a){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p,r_in.time());
		//attenuation = albedo->value(0, 0, rec.p);
		attenuation = albedo->value(rec.u, rec.v, rec.p);
		return true;
	}
	//vec3 albedo;
	texture *albedo;
};

