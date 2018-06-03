#pragma once
#include "material.h"
#include "texture.h"
class isotropic : public material
{
public:
	isotropic(texture *a) : albedo(a){}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		//光线色散方向球形随机
		scattered = ray(rec.p, random_in_unit_sphere());
		//理论上这种材质是会吸收光能的，但是这里并没有吸收光能
		attenuation = albedo->value(rec.u, rec.v, rec.p);
		return true;
	}

	texture *albedo;
};