#pragma once

#include "aabb.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

class BVHNode : public Hittable {
public:
	BVHNode(Hittable_list list) : BVHNode(list.m_Objects, 0, list.m_Objects.size()) {}
	BVHNode(vector<shared_ptr<Hittable>>& objects, size_t start, size_t end) {
	}

	bool hit(const Ray& r, Interval ray_t, hit_record& rec) const override {
		if (!m_BoundingBox.hit(r, ray_t))
			return false;

		bool hit_left = m_Left->hit(r, ray_t, rec);
		bool hit_right = m_Right->hit(r, Interval(ray_t.Min, hit_left ? rec.intersected_at : ray_t.Max), rec);

		return hit_left || hit_right;
	}

private:
	shared_ptr<Hittable> m_Left;
	shared_ptr<Hittable> m_Right;
	AABB m_BoundingBox;
};
