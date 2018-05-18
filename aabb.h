#pragma once
#include "ray.h"
inline double ffmin(double a, double b) { return a < b ? a : b; }
inline double ffmax(double a, double b) { return a > b ? a : b; }
class aabb
{
public:
	aabb(){}
	//包围盒可以通过最小点与最大点构成
	aabb(const vec3 &a, const vec3 &b) { _min = a; _max = b; }

	vec3 min() const { return _min; }
	vec3 max() const { return _max; }
	bool hit(const ray& r, double tmin, double tmax) const {
		//循环x、y、z，3个方向
		for (int a = 0; a < 3; a++) {

			//t0~t1可以看成是在射线上的一段区间（也就是线段），之所以可以将x、y、z三个维度代入计算出的t值进行比较也是这个道理
			//如果x、y、z计算出的区间有共同的重合部分则可以认为，这条射线穿过了包围盒

			//将最小点与最大点的xyz分别带入射线中，计算出各自一维的t值，
			//double t0 = ffmin((_min[a] - r.origin()[a] / r.direction()[a]), (_max[a] - r.origin()[a] )/ r.direction()[a]);
			//double t1 = ffmax((_min[a] - r.origin()[a] / r.direction()[a]), (_max[a] - r.origin()[a]) / r.direction()[a]);
			//tmin = ffmax(t0, tmin);
			//tmax = ffmin(t1, tmax);

			double invD = 1.0 / r.direction()[a];
			double t0 = (min()[a] - r.origin()[a])*invD;
			double t1 = (max()[a] - r.origin()[a])*invD;
			//反方向则进行调换
			if (invD<0.0)
			{
				std::swap(t0, t1);
			}
			tmin = t0 > tmin ? t0 : tmin;
			tmax = t1 < tmax ? t1 : tmax;

			if (tmax <= tmin)
				return false;
		}
		return true;
	}

	vec3 _min;
	vec3 _max;
};

