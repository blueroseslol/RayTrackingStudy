#pragma once
#include "material.h"
vec3 reflect(const vec3& v, const vec3& n){
	return v - 2 * dot(v, n)*n;
}

class metal :public material
{
public:
	metal(const vec3& a,double f) : albedo(a) {
		if (f < 1)
			fuzz = f;
		else
			fuzz = 1;
	}
	//对于光滑金属，射线并不会发生随机的散射现象，所以不使用随机向量处理
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}
	vec3 albedo;
	float fuzz;
};

