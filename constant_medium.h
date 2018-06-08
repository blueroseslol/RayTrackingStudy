#pragma once
#include "hitable.h"
#include "texture.h"
#include "isotropic.h"

class constant_medium : public hitable
{
public:
	constant_medium(hitable *b,double d,texture *a):boundary(b),density(d){
		phase_function = new isotropic(a);
	}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;
	virtual bool bounding_box(double t0, double t1, aabb& box) const {
		return boundary->bounding_box(t0, t1, box);
	}

	hitable *boundary;
	double density;
	material *phase_function;

};

bool constant_medium::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	bool db = (uni_dist(reng) < 0.00001);
	db = false;
	hit_record rec1, rec2;
	//使用两个hit_record来计算采样位置到边界的距离，rec1入射点，rec2为出射点
	if (boundary->hit(r, -DBL_MIN, DBL_MAX, rec1)) {
		if (boundary->hit(r,rec1.t+0.0001, DBL_MAX,rec2))
		{
			if (db)
				std::cerr << "\n0 t1 " << rec1.t << " " << rec2.t << "\n";
			if (rec1.t < t_min)
				rec1.t = t_min;
			if (rec2.t > t_max)
				rec2.t = t_max;
			//如果物体不在视角正方向则忽略
			if (rec1.t >= rec2.t)
				return false;
			//如果在物体内部，就把摄像机平面当作入射面
			if (rec1.t < 0)
				rec1.t = 0;
			//boundingBox撞击点的距离
			double distance_inside_boundary = (rec2.t - rec1.t)*r.direction().length();
			//雾计算公式，t为距离
			//Transmittance = e ^ (-t * d).
			double hit_distance = -(1 / density)*log(uni_dist(reng));
			if (hit_distance==0)
			{
				std::cout << "error!";
			}
			if (hit_distance < distance_inside_boundary) {
				if(db)std::cerr << "hit_distance = " << hit_distance << "\n";
				//加上散射光线的t值
				rec.t = rec1.t + hit_distance / r.direction().length();
				if ((hit_distance / r.direction().length())== 0)
				{
					std::cout << "error!";
				}

				if(db)std::cerr << "rec.t = " << rec.t << "\n";
				//更新位置为下一次光追做准备
				rec.p = r.point_at_parameter(rec.t);
				if(db)std::cerr << "rec.p = " << rec.p << "\n";
				rec.normal = vec3(1, 0, 0);//arbitrary
				rec.mat_ptr = phase_function;
				return true;
			}
		}
	}
	return false;
}