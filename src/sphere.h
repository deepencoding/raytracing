#pragma once

#include "ray.h"
#include "hittable.h"
#include "utility.h"
#include <memory>

class Sphere: public Hittable {
public:
	Ray m_Center;
	double m_Radius;
	std::shared_ptr<Material> m_pMat;
	AABB m_BoundingBox;

	Sphere(const point3& static_center, double radius, shared_ptr<Material> p_mat)
		: m_Center(static_center, vec3(0,0,0)), m_Radius(std::fmax(0,radius)), m_pMat(p_mat) 
	{
		vec3 radius_vec(m_Radius, m_Radius, m_Radius);
		m_BoundingBox = AABB(static_center - radius_vec, static_center + radius_vec);
	}

	Sphere(const point3& start_center, const point3& end_center, double radius, shared_ptr<Material> p_mat)
		: m_Center(start_center, end_center - start_center), m_Radius(std::fmax(0,radius)), m_pMat(p_mat) 
	{
		vec3 radius_vec(m_Radius, m_Radius, m_Radius);
		AABB bbox1(m_Center.at(0) - radius_vec, m_Center.at(0) + radius_vec);
		AABB bbox2(m_Center.at(1) - radius_vec, m_Center.at(1) + radius_vec);
		m_BoundingBox = AABB(bbox1, bbox2);
	}

	bool hit(const Ray& r, Interval ray_t, hit_record& rec) const override {
		point3 cur_center = m_Center.at(r.time());
		vec3 oc  = cur_center - r.origin();
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
		vec3 outward_normal = (rec.poi - cur_center) / m_Radius;
		rec.set_face_normal(r, outward_normal);
		rec.p_mat = m_pMat;

		return true;
	}

	AABB bounding_box() const override { return m_BoundingBox; }
};
