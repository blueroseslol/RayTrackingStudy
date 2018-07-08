#pragma once
#include "hitable.h"
#include "pdf.h"
//#include <ctime>
//#include <random>

//std::default_random_engine reng(time(nullptr));
//std::uniform_real_distribution<double> uni_dist(0.0f, 1.0f);

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n)*n;
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		//生成随机数vec3后，将坐标从（0,1）=>（-1，1）,也就是在一个（-1，1）的立方体区域中生成随机点
		//之后判断，是使用在球内的点，x^2+y^2+z^2=1，
		p = 2.0*vec3(uni_dist(reng), uni_dist(reng), uni_dist(reng)) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);
	return p;
}

inline vec3 random_cosine_direction() {
	double r1 = uni_dist(reng);
	double r2 = uni_dist(reng);
	double z = sqrt(1 - r2);
	double phi = 2 * M_PI*r1;
	double x = cos(phi) * 2 * sqrt(r2);
	double y = sin(phi) * 2 * sqrt(r2);
	return vec3(x, y, z);
}

struct scatter_record
{
	ray specular_ray;
	bool is_specular;
	vec3 attenuation;
	pdf *pdf_ptr;
};

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec,scatter_record& srec) const { return false; }

	virtual double scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const {return false;}

	virtual vec3 emitted(const ray& r_in,const hit_record& rec,double u, double v, const vec3& p) const {
		return vec3(0, 0, 0);
	}
};

