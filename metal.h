#pragma once
#include "material.h"
//vec3 reflect(const vec3& v, const vec3& n){
//	return v - 2 * dot(v, n)*n;
//}

class metal :public material
{
public:
	metal(const vec3& a,double f) : albedo(a) {
		if (f < 1)
			fuzz = f;
		else
			fuzz = 1;
	}
	//���ڹ⻬���������߲����ᷢ�������ɢ���������Բ�ʹ�������������
	virtual bool scatter(const ray& r_in, const hit_record& rec,scatter_record& srec) const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		srec.specular_ray = ray(rec.p, reflected+fuzz*random_in_unit_sphere());
		srec.attenuation = albedo;
		srec.is_specular = true;
		srec.pdf_ptr = 0;
		return true;
	}
	vec3 albedo;
	double fuzz;
};

