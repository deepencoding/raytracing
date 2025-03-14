#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public Hittable {
public:
	std::vector<shared_ptr<Hittable>> m_Objects;

	hittable_list() {}
	hittable_list(shared_ptr<Hittable> object) { add(object); }

	void clear() { m_Objects.clear(); }
	void add(shared_ptr<Hittable> object) { m_Objects.push_back(object); }

	bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
		hit_record temp_rec;
		bool hit_anything = false;
		double closest_so_far = t_max;
		for (const auto& object : m_Objects) {
			if (object->hit(r, t_min, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}
		return hit_anything;
	}
};
