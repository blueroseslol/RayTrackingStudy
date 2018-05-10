#pragma once
#define _USE_MATH_DEFINES
#include "ray.h"
#include <math.h>
//#define M_PI       3.14159265358979323846   // pi
class camera
{
public:
	camera(double vfor,double aspect):origin(vec3(0.0,0.0,0.0))
	{
		double theta = vfor*M_PI / 180;
		double half_height = tan(theta / 2);
		double half_width = aspect*half_height;
		lower_left_corner=vec3(-half_width,-half_height, -1.0);
		horizontal = vec3(2*half_height, 0.0, 0.0); 
		vertical = vec3(0.0, 2*half_height, 0.0);
	}
	ray get_ray(double u, double v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin); }
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

};

