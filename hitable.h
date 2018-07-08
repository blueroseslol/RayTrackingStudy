#pragma once
#include "ray.h"
#include "aabb.h"
//记录ray的各种参数的结构体
class material;

void get_sphere_uv(const vec3& p, double& u, double &v) {
	double phi = atan2(p.z(), p.x());
	double theta = asin(p.y());
	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
}

struct hit_record
{
	//ray中的参数t
	double t;
	//入射点位置
	vec3 p;
	//入射点法向量
	vec3 normal;
	material *mat_ptr;
	double u;
	double v;
};

class hitable
{
public:
	virtual bool hit(const ray& r,double t_min,double t_max,hit_record& rec) const=0;
	//构建包围盒
	virtual bool bounding_box(double t0, double t1, aabb& box) const = 0;
	virtual double pdf_value(const vec3& o, const vec3& v) const { return 0.0; }
	virtual vec3 random(const vec3& o) const { return vec3(1.0, 0, 0); }
};

