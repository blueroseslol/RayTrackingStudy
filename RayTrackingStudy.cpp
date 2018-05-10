// RayTrackingStudy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "hitable_list.h"
#include "float.h"
#include "sphere.h"
#include "camera.h"

#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

vec3 color(const ray& r,hitable *world,int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, DBL_MAX, rec)) {
		//散射出的光线
		ray scattered;
		//材质的衰减数值
		vec3 attenuation;
		//进行50次采样，直到能量衰减到0或是光线射到背景中
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return attenuation*color(scattered, world, depth + 1);
		}
		else{
			return vec3(0, 0, 0);
		}
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

	hitable *list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5,new lambertian(vec3(0.1,0.2,0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1.0, 0.0, -1.0), 0.5, new metal(vec3(0.8, 0.6, 0.2),0.3));
	list[3] = new sphere(vec3(-1, 0.0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0.0, -1), -0.45, new dielectric(1.5));
	hitable *world = new hitable_list(list, 5);
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
				col += color(r, world,0);
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

