#pragma once
#include "hitable.h"
#include <ctime>
#include <random>

std::default_random_engine reng(time(nullptr));
std::uniform_real_distribution<double> uni_dist(0.0f, 1.0f);

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		//生成随机数vec3后，将坐标从（0,1）=>（-1，1）,也就是在一个（-1，1）的立方体区域中生成随机点
		//之后判断，是使用在球内的点，x^2+y^2+z^2=1，
		p = 2.0*vec3(uni_dist(reng), uni_dist(reng), uni_dist(reng)) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);
	return p;
}

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

