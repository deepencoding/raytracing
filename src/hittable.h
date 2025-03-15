#pragma once

#include "interval.h"
#include "utility.h"

struct hit_record {
	point3 p;
	vec3   normal;
	double t;
	bool front_face;

	void set_face_normal(const ray& r, const vec3& outward_normal) {
		// Note: outward_normal is assumed to be normalized.

		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable {
public:
	virtual ~Hittable()  = default;
	virtual bool hit(const ray& r, Interval ray_interval, hit_record& rec) const = 0;
};
