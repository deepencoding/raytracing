#pragma once

#include "ray.h"
#include "hittable.h"
#include "utility.h"
#include <memory>

class Sphere: public Hittable {
public:
	point3 m_Center;
	double m_Radius;
	std::shared_ptr<Material> m_pMat;

	Sphere(const point3& center, double radius, shared_ptr<Material> p_mat)
		: m_Center(center), m_Radius(std::fmax(0,radius)), m_pMat(p_mat) {}

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

		rec.intersected_at = root;
		rec.poi = r.at(rec.intersected_at);
		vec3 outward_normal = (rec.poi - m_Center) / m_Radius;
		rec.set_face_normal(r, outward_normal);
		rec.p_mat = m_pMat;

		return true;
	}
};
