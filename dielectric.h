#pragma once
#include "material.h"
bool refract(const vec3& v, const vec3& n, double ni_over_nt, vec3& refracted) {
	//ni_over_nt是折射率的倒数，也就是pdf中的，sin（theta'）/sin(theta)
	vec3 uv = unit_vector(v);
	double dt = dot(uv, n);
	//discriminant貌似为出射光线的sin值
	double discriminant = 1.0 - ni_over_nt*ni_over_nt*(1 - dt*dt);
	if (discriminant > 0) {
		refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
		return true;
	}
	else
		return false;
}

class dielectric :	public material
{
public:
	dielectric(double ri):ref_idx(ri)	{}
	
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		double ni_over_nt;
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;
		//double reflect_prob;
		//double cosine;
		if (dot(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
	/*		cosine = ref_idx*dot(r_in.direction(), rec.normal) / r_in.direction().length();*/
		}else{
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			//cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		//if (refract(r_in.direction(),outward_normal,ni_over_nt,refracted)){
		//	reflect_prob = schlick(cosine, ref_idx);
		//}
		//else {
		//	scattered = ray(rec.p, refracted);
		//	reflect_prob = 1.0;
		//}
		//if (uni_dist(reng) < reflect_prob) {
		//	scattered = ray(rec.p, reflected);
		//}
		//else {
		//	scattered = ray(rec.p, refracted);
		//}
		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
			scattered = ray(rec.p, refracted);
		}
		else {
			scattered = ray(rec.p, reflected);
			return false;
		}
		return true;
	}
	double ref_idx;
};

