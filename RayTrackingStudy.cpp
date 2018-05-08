// RayTrackingStudy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "hitable_list.h"
#include "float.h"
#include "sphere.h"
#include "camera.h"
#include <ctime>
#include <random>

std::default_random_engine reng(time(nullptr));
std::uniform_real_distribution<double> uni_dist(0.0f, 1.0f);

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		//生成随机数vec3后，将坐标从（0,1）=>（-1，1）,也就是在一个（-1，1）的立方体区域中生成随机点
		//之后判断，是使用在球内的点，x^2+y^2+z^2=1，
		p = 2.0*vec3(uni_dist(reng), uni_dist(reng), uni_dist(reng)) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);
	return p;
}

vec3 color(const ray& r,hitable *world) {
	hit_record rec;
	if (world->hit(r, 0.001, DBL_MAX, rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color(ray(rec.p, target - rec.p), world);
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

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i=0;i<nx;i++)
		{
			vec3 col(0.0, 0.0, 0.0);
			//使用了SSAA
			for (int s = 0; s < ns; s++)
			{
				double u = double(i+ uni_dist(reng)) / double(nx);
				double v = double(j+ uni_dist(reng)) / double(ny);
				ray r = cam.get_ray(u, v);
				//vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}
			col /= double(ns);
			//伽马矫正是较为复杂的曲线，这里使用比较接近的平方根进行计算
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			out << ir << " " << ig << " " << ib << "\n";
		}
	}
	out.close();
	//system("pause");
    return 0;
}

