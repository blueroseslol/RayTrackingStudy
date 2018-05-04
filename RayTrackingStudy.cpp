﻿// RayTrackingStudy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "ray.h"

bool hit_sphere(const vec3& center,float radius,const ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0*dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	//t*t*dot(B​,B​) + 2*t*dot(B,A​-C​) + dot(A-C,A​-C​) - R*R = 0
	//t可以看作为x，也就是ax^2+bx+c=0，一个二次函数，所以为了判断光线是否与球相交只需要判断b^2-4ac是否大于0即可
	float discriminant = b*b - 4 * a*c;
	return (discriminant > 0);
}

vec3 color(const ray& r) {
	if (hit_sphere(vec3(0, 0, -1), 0.5, r))
		return vec3(1, 0, 0);
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
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
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin,lower_left_corner+u*horizontal+v*vertical);
			vec3 col = color(r);
			//vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);

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

