#pragma once
#include "hitable.h"
class flip_normals : public hitable {
public:
	flip_normals(hitable *p):ptr(p){}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
		if (ptr->hit(r, t_min, t_max, rec)) {
			rec.normal = -rec.normal;
			return true;
		}
		else
			return false;
	}
	virtual bool bounding_box(double t0, double t1, aabb& box) const {
		return ptr->bounding_box(t0, t1, box);
	}
	hitable *ptr;
};
