#pragma once
#include "material.h"
#include "texture.h"
#include "onb.h"
#include "cosine_pdf.h"
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

	bool scatter(const ray& r_in, const hit_record& hrec, scatter_record& srec) const{
		srec.is_specular = false;
		srec.attenuation= albedo->value(hrec.u, hrec.v, hrec.p);
		srec.pdf_ptr = new cosine_pdf(hrec.normal);
		return true;
	}
	texture *albedo;
};

