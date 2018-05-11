#pragma once
#define _USE_MATH_DEFINES
#include "ray.h"
#include <math.h>
#include <ctime>
#include <random>

std::default_random_engine reng(time(nullptr));
std::uniform_real_distribution<double> uni_dist(0.0f, 1.0f);
vec3 random_in_unit_disk() {
	vec3 p;
	do {
		p = 2.0*vec3(uni_dist(reng), uni_dist(reng), 0) - vec3(1, 1, 0);
	} while (dot(p,p)>=1.0);
	return p;
}

class camera
{
public:
	camera(vec3 lookfrom,vec3 lookat,vec3 vup,double vfor,double aspect,double aperture,double focus_dist)
	{
		lens_radius = aperture / 2;
		double theta = vfor*M_PI / 180;
		double half_height = tan(theta / 2);
		double half_width = aspect*half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = origin - half_width*u*focus_dist - half_height*v*focus_dist - focus_dist*w;
		horizontal = 2 * half_width*u*focus_dist;
		vertical = 2*half_height*v*focus_dist;
	}
	ray get_ray(double s, double t) {
		vec3 rd = lens_radius*random_in_unit_disk();
		vec3 offset = u*rd.x(); +v*rd.y();
		return ray(origin+offset, lower_left_corner + s*horizontal + t*vertical - origin-offset); 
	}
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
};

