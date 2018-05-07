#pragma once
#include "hitable.h"
class sphere :	public hitable
{
public:
	sphere(){}
	sphere(vec3 cen, double r) :center(cen),radius(r){}
	virtual bool hit(const ray& r, double tmin, double tmax,hit_record& rec) const;
	vec3 center;
	double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double b = 2.0*dot(oc, r.direction());
	double c = dot(oc, oc) - radius*radius;
	//t*t*dot(B​,B​) + 2*t*dot(B,A​-C​) + dot(A-C,A​-C​) - R*R = 0
	//t可以看作为x，也就是ax^2+bx+c=0，一个二次函数，所以为了判断光线是否与球相交只需要判断b^2-4ac是否大于0即可
	double discriminant = b*b - 4 * a*c;
	if (discriminant > 0) {
		double temp = (-b - sqrt(b*b - a*c)) / a;
		if (temp<t_max && temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp= (-b + sqrt(b*b - a*c)) / a;
		if (temp<t_max && temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}