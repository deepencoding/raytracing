#pragma once

#include "aabb.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include <cstddef>
#include <memory>
#include <vector>
#include <algorithm>

using std::shared_ptr;
using std::vector;

class BVHNode : public Hittable {
public:
	BVHNode(Hittable_list list) : BVHNode(list.m_Objects, 0, list.m_Objects.size()) {}
	BVHNode(vector<shared_ptr<Hittable>>& objects, size_t start, size_t end) {
		int axis = random_int(0,2);

		auto comparator = 
			(axis == 0) ? box_x_compare
		: (axis == 1) ? box_y_compare
									:	box_z_compare;

		std::size_t obj_span = end - start;

		if (obj_span == 1) {
			m_Left = m_Right = objects[start];
		} else if (obj_span == 2) {
			m_Left = objects[start];
			m_Right = objects[start+1];
		} else {
			std::sort(objects.begin() + start, objects.begin() + end, comparator);

			auto mid = start + obj_span/2;
			m_Left = make_shared<BVHNode>(objects, start, mid);
			m_Right = make_shared<BVHNode>(objects, mid, end);
		}

		m_BoundingBox = AABB(m_Left->bounding_box(), m_Right->bounding_box());
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

	static bool box_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b, int axis) {
		Interval a_axis_interval = a->bounding_box().axis_interval(axis);
		Interval b_axis_interval = b->bounding_box().axis_interval(axis);
		return a_axis_interval.Min < b_axis_interval.Min;
	}

	static bool box_x_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
		return box_compare(a, b, 0);
	}
	static bool box_y_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
		return box_compare(a, b, 1);
	}
	static bool box_z_compare(const shared_ptr<Hittable> a, const shared_ptr<Hittable> b) {
		return box_compare(a, b, 2);
	}
};
