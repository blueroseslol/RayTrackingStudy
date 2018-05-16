#pragma once
#include "ray.h"
#include "aabb.h"
//��¼ray�ĸ��ֲ����Ľṹ��
class material;
struct hit_record
{
	//ray�еĲ���t
	double t;
	//�����λ��
	vec3 p;
	//����㷨����
	vec3 normal;
	material *mat_ptr;
};

class hitable
{
public:
	virtual bool hit(const ray& r,double t_min,double t_max,hit_record& rec) const=0;
	virtual bool bounding_box(double t0, double t1, aabb& box) const = 0;
};

