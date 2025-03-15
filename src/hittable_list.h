#pragma once

#include "utility.h"
#include "hittable.h"

#include <vector>

class Hittable_list : public Hittable {
public:
	std::vector<shared_ptr<Hittable>> m_Objects;

	Hittable_list() {}
	Hittable_list(shared_ptr<Hittable> object) { add(object); }

	void clear() { m_Objects.clear(); }
	void add(shared_ptr<Hittable> object) { m_Objects.push_back(object); }

	bool hit(const ray& r, Interval ray_t, hit_record& rec) const override {
		hit_record temp_rec;
		bool hit_anything = false;
		double closest_so_far = ray_t.Max;
		for (const auto& object : m_Objects) {
			if (object->hit(r, Interval(ray_t.Min, closest_so_far), temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
};
