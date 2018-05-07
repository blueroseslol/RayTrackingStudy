// RayTrackingStudy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "ray.h"

double hit_sphere(const vec3& center,double radius,const ray& r) {
	vec3 oc = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double b = 2.0*dot(oc, r.direction());
	double c = dot(oc, oc) - radius*radius;
	//t*t*dot(B​,B​) + 2*t*dot(B,A​-C​) + dot(A-C,A​-C​) - R*R = 0
	//t可以看作为x，也就是ax^2+bx+c=0，一个二次函数，所以为了判断光线是否与球相交只需要判断b^2-4ac是否大于0即可
	double discriminant = b*b - 4 * a*c;
	if (discriminant < 0){
		return -1.0;
	}else{
		return (-b - sqrt(discriminant)) / (2.0*a);
	}
}

vec3 color(const ray& r) {
	double t=hit_sphere(vec3(0,0,-1),0.5,r);
	if (t > 0.0) {
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
		//return vec3(1.0, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main()
{
	std::ofstream out;
	out.open("result.ppm");

	int nx = 200;
	int ny = 100;
	out << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i=0;i<nx;i++)
		{
			double u = double(i) / double(nx);
			double v = double(j) / double(ny);
			ray r(origin,lower_left_corner+u*horizontal+v*vertical);
			vec3 col = color(r);
			//vec3 col(double(i) / double(nx), double(j) / double(ny), 0.2);

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			out << ir << " " << ig << " " << ib << "\n";
		}
	}
	out.close();
	system("pause");
    return 0;
}

