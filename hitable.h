#pragma once
#include "ray.h"
#include "aabb.h"
//记录ray的各种参数的结构体
class material;
struct hit_record
{
	//ray中的参数t
	double t;
	//入射点位置
	vec3 p;
	//入射点法向量
	vec3 normal;
	material *mat_ptr;
};

class hitable
{
public:
	virtual bool hit(const ray& r,double t_min,double t_max,hit_record& rec) const=0;
	virtual bool bounding_box(double t0, double t1, aabb& box) const = 0;
};

