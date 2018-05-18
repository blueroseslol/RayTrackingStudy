#pragma once
#include "ray.h"
inline double ffmin(double a, double b) { return a < b ? a : b; }
inline double ffmax(double a, double b) { return a > b ? a : b; }
class aabb
{
public:
	aabb(){}
	//��Χ�п���ͨ����С�������㹹��
	aabb(const vec3 &a, const vec3 &b) { _min = a; _max = b; }

	vec3 min() const { return _min; }
	vec3 max() const { return _max; }
	bool hit(const ray& r, double tmin, double tmax) const {
		//ѭ��x��y��z��3������
		for (int a = 0; a < 3; a++) {

			//t0~t1���Կ������������ϵ�һ�����䣨Ҳ�����߶Σ���֮���Կ��Խ�x��y��z����ά�ȴ���������tֵ���бȽ�Ҳ���������
			//���x��y��z������������й�ͬ���غϲ����������Ϊ���������ߴ����˰�Χ��

			//����С���������xyz�ֱ���������У����������һά��tֵ��
			//double t0 = ffmin((_min[a] - r.origin()[a] / r.direction()[a]), (_max[a] - r.origin()[a] )/ r.direction()[a]);
			//double t1 = ffmax((_min[a] - r.origin()[a] / r.direction()[a]), (_max[a] - r.origin()[a]) / r.direction()[a]);
			//tmin = ffmax(t0, tmin);
			//tmax = ffmin(t1, tmax);

			double invD = 1.0 / r.direction()[a];
			double t0 = (min()[a] - r.origin()[a])*invD;
			double t1 = (max()[a] - r.origin()[a])*invD;
			//����������е���
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

