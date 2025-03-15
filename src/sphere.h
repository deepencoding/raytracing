#pragma once

#include "ray.h"
#include "hittable.h"

class Sphere: public Hittable {
public:
	point3 m_Center;
	double m_Radius;

	Sphere(const point3& center, double radius): m_Center(center), m_Radius(std::fmax(0,radius)) {}

	bool hit(const Ray& r, Interval ray_t, hit_record& rec) const override {
		vec3 oc  = m_Center - r.origin();
		double a = r.direction().length_squared();
		double h = dot(oc, r.direction());
		double c = oc.length_squared() - m_Radius*m_Radius;

		double discriminant = h*h - a*c;
		if (discriminant < 0)
			return false;

		double sqrt_d = std::sqrt(discriminant);

		// Nearest root that lies in acceptable range
		double root = (h - sqrt_d) / a;
		if (root <= ray_t.Min || root >= ray_t.Max) {
			root = (h + sqrt_d) / a;
			if (root <= ray_t.Min || root >= ray_t.Max)
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		vec3 outward_normal = (rec.p - m_Center) / m_Radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	}
};
