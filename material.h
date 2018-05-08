#pragma once
#include "hitable.h"
#include <ctime>
#include <random>

std::default_random_engine reng(time(nullptr));
std::uniform_real_distribution<double> uni_dist(0.0f, 1.0f);

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		//���������vec3�󣬽�����ӣ�0,1��=>��-1��1��,Ҳ������һ����-1��1�������������������������
		//֮���жϣ���ʹ�������ڵĵ㣬x^2+y^2+z^2=1��
		p = 2.0*vec3(uni_dist(reng), uni_dist(reng), uni_dist(reng)) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);
	return p;
}

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

