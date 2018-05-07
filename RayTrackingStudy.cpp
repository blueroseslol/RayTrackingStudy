// RayTrackingStudy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "hitable_list.h"
#include "float.h"
#include "sphere.h"
#include "camera.h"
#include <random>

vec3 color(const ray& r,hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.0, DBL_MAX, rec)) {
		return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		double t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	std::ofstream out;
	out.open("result.ppm");

	int nx = 200;
	int ny = 100;
	int ns = 100;
	out << "P3\n" << nx << " " << ny << "\n255\n";

	//vec3 lower_left_corner(-2.0, -1.0, -1.0);
	//vec3 horizontal(4.0, 0.0, 0.0);
	//vec3 vertical(0.0, 2.0, 0.0);
	//vec3 origin(0.0, 0.0, 0.0);

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;
	//随机数引擎
	//default_random_engine reng(time(nullptr));
	//uniform_real_distribution<float> uni_dist(0.0f, 1.0f);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i=0;i<nx;i++)
		{
			vec3 col(0.0, 0.0, 0.0);
			for (int s = 0; s < ns; s++)
			{
				double u = double(i) / double(nx);
				double v = double(j) / double(ny);
				ray r = cam.get_ray(u, v);
				//vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}
			col /= double(ns);

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

