#pragma once
#include "material.h"
#include "texture.h"
class lambertian :public material
{
public:
	//lambertian(const vec3& a):albedo(a)	{}
	lambertian(texture *a): albedo(a){}
	bool scatter(const ray& r_in, const hit_record& rec, vec3& alb, ray& scattered,double& pdf) const{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, unit_vector(target-rec.p),r_in.time());
		alb = albedo->value(rec.u, rec.v, rec.p);
		pdf = dot(rec.normal, scattered.direction()) / M_PI;
		return true;
	}

	double scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const {
		double cosine = dot(rec.normal, unit_vector(scattered.direction()));
		if (cosine < 0)cosine = 0;
		return cosine / M_PI;
	}
	
	texture *albedo;
};

