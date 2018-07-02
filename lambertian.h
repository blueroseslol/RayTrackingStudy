#pragma once
#include "material.h"
#include "texture.h"
#include "onb.h"
class lambertian :public material
{
public:
	//lambertian(const vec3& a):albedo(a)	{}
	lambertian(texture *a): albedo(a){}
	double scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const {
		double cosine = dot(rec.normal, unit_vector(scattered.direction()));
		if (cosine < 0)cosine = 0;
		return cosine / M_PI;
	}

	bool scatter(const ray& r_in, const hit_record& rec, vec3& alb, ray& scattered,double& pdf) const{
		//vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		onb uvw;
		uvw.build_from_w(rec.normal);
		vec3 direction = uvw.local(random_cosine_direction());
		scattered = ray(rec.p, unit_vector(direction),r_in.time());
		alb = albedo->value(rec.u, rec.v, rec.p);
		pdf = dot(uvw.w(), scattered.direction()) / M_PI;
		return true;
	}
	texture *albedo;
};

