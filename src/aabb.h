#pragma once

#include "interval.h"
class AABB {
public:
	Interval x, y, z;

	AABB() {}
	AABB(const Interval& _x, const Interval& _y, const Interval& _z) : x(_x), y(_y), z(_z) {}
	AABB(const point3& p1, const point3& p2) {
		x = (p1.x() < p2.x()) ? Interval(p1.x(), p2.x()) : Interval(p2.x(), p1.x());
		y = (p1.y() < p2.y()) ? Interval(p1.y(), p2.y()) : Interval(p2.y(), p1.y());
		z = (p1.z() < p2.z()) ? Interval(p1.z(), p2.z()) : Interval(p2.z(), p1.z());
	}
	AABB(const AABB& b1, const AABB& b2) {
		x = Interval(b1.x, b2.x);
		y = Interval(b1.y, b2.y);
		z = Interval(b1.z, b2.z);
	}

	const Interval& axis_interval(int n) const {
		if (n == 1) return y;
		if (n == 2) return z;
		return x;
	}

	bool hit(const Ray& r, Interval ray_t) const {
		const point3& ray_origin = r.origin();
		const vec3& ray_dir = r.direction();

		for (int axis = 0; axis < 3; axis++) {
			const Interval& ax_t = axis_interval(axis);
			const double inv_d = 1.0 / ray_dir[axis];

			double t0 = (ax_t.Min - ray_origin[axis]) * inv_d;
			double t1 = (ax_t.Max - ray_origin[axis]) * inv_d;
			
			if (t0 < t1) {
				if (t0 > ray_t.Min) ray_t.Min = t0;
				if (t1 < ray_t.Max) ray_t.Max = t1;
			} else {
				if (t1 > ray_t.Min) ray_t.Min = t1;
				if (t0 < ray_t.Max) ray_t.Max = t0;
			}

			if (ray_t.Min >= ray_t.Max) return false;
		}

		return true;
	}

};
