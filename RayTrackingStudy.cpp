// RayTrackingStudy.cpp : 定义控制台应用程序的入口点。
//
//#define _USE_MATH_DEFINES
#include "stdafx.h"
#include "camera.h"
#include <iostream>
#include <fstream>
#include "float.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "hitable_list.h"

#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "constant_texture.h"
#include "checker_texture.h"
#include "noise_texture.h"
#include "image_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "diffuse_light.h"
#include "rect.h"
#include "flip_normals.h"
#include "box.h"
#include "translate.h"
#include "rotate_y.h"

hitable *cornell_box() {
	hitable **list = new hitable*[6];
	int i = 0;
	material *red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
	material *white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
	material *green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
	material *light = new diffuse_light(new constant_texture(vec3(16, 16, 16)));

	list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
	list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
	list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
	list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));
	list[i++] = new translate(new rotate_y(new box(vec3(130, 0, 65), vec3(295, 165, 230), white),-18),vec3(130,0,65));
	list[i++] = new translate(new rotate_y(new box(vec3(265, 0, 295), vec3(430, 330, 460), white),15),vec3(265,0,295));
	return new hitable_list(list, i);
}

hitable *simple_light() {
	hitable **list = new hitable *[4];
	texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3, 0.1)), new constant_texture(vec3(0.9, 0.9, 0.9)));
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(checker));
	list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(checker));
	list[2] = new sphere(vec3(0, 7, 0), 2 ,new diffuse_light(new constant_texture(vec3(4, 4, 4))));
	list[3] = new xy_rect(3, 5, 1, 3, -2, new diffuse_light(new constant_texture(vec3(4, 4, 4))));
	return new hitable_list(list, 4);
}

hitable *earth() {
	int nx, ny, nn;
	//unsigned char *tex_data = stbi_load("tiled.jpg", &nx, &ny, &nn, 0);
	unsigned char *tex_data = stbi_load("earth.jpg", &nx, &ny, &nn, 0);
	material *mat = new lambertian(new image_texture(tex_data, nx, ny));
	return new sphere(vec3(0, 0, 0), 2, mat);
}

hitable *two_perlin_spheres() {
	texture *pertext = new noise_texture();
	hitable **list = new hitable *[2];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
	list[1] = new sphere(vec3(0, 2, 0),2, new lambertian(pertext));
	return new hitable_list(list, 2);
}

vec3 color(const ray& r,hitable *world,int depth) {
	hit_record rec;
	if (world->hit(r, 0.001, DBL_MAX, rec)) {
		//散射出的光线
		ray scattered;
		//材质的衰减数值
		vec3 attenuation;
		vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
		//进行50次采样，直到能量衰减到0或是光线射到背景中
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
			return emitted+attenuation*color(scattered, world, depth + 1);
		}
		else{
			return emitted;
		}
	}
	else {
		return vec3(0, 0, 0);
	}
}

hitable *random_scene() {
	int n = 500;
	hitable **list = new hitable*[n + 1];
	texture *checker = new checker_texture(new constant_texture(vec3(0.2, 0.3, 0.1)), new constant_texture(vec3(0.9, 0.9, 0.9)));
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(checker));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b= - 11; b < 11; b++) {
			double choose_mat = uni_dist(reng);
			vec3 center(a+0.9*uni_dist(reng),0.2,b+0.9*uni_dist(reng));
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {
					list[i++] = new moving_sphere(center,center+vec3(0,0.5*uni_dist(reng),0),0.0,1.0,0.2,new lambertian(new constant_texture(vec3(uni_dist(reng)*uni_dist(reng), uni_dist(reng)*uni_dist(reng), uni_dist(reng)*uni_dist(reng)))));
				}else if (choose_mat<0.95) {
					list[i++]= new sphere(center, 0.2, new metal(vec3(0.5*(1+ uni_dist(reng)), 0.5*(1 + uni_dist(reng)), 0.5*(1 + uni_dist(reng))), uni_dist(reng)*0.5));
				}
				else {
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4,1,0), 1.0, new lambertian(new constant_texture(vec3(0.4,0.2,0.1))));
	list[i++] = new sphere(vec3(4,1,0), 1.0, new metal(vec3(0.7,0.6,0.5),0.0));

	return new hitable_list(list, i);
}

int main()
{
	std::ofstream out;
	out.open("result.ppm");
	int nx = 1000;
	int ny = 1000;
	int ns = 100;
	out << "P3\n" << nx << " " << ny << "\n255\n";
	double R = cos(M_PI / 4);
	//hitable *list[4];
	//list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	//list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	//list[2] = new sphere(vec3(1.0, 0.0, -1.0), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
	//list[3] = new sphere(vec3(-1, 0.0, -1), 0.5, new dielectric(1.5));
	//list[4] = new sphere(vec3(-1, 0.0, -1), -0.45, new dielectric(1.5));
	//hitable *world = random_scene();
	hitable *world = cornell_box();
	vec3 lookfrom(278, 278, -800);
	vec3 lookat(278, 278, 0);
	double dist_to_focus = 10;
	double aperture = 0.0;
	camera cam(lookfrom , lookat, vec3(0, 1, 0), 40, nx / ny,aperture,dist_to_focus,0.0,1.0);
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
		std::cout << j<<"\n";
	}
	out.close();
	//system("pause");
    return 0;
}

