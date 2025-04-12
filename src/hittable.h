#pragma once

#include "interval.h"
#include "utility.h"
#include "aabb.h"

class Material;

struct hit_record {
  point3 poi;
  vec3 normal;
  double intersected_at;
  bool front_face;
  std::shared_ptr<Material> p_mat;

  void set_face_normal(const Ray& r, const vec3 &outward_normal) {
    // Note: outward_normal is assumed to be normalized.

    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  virtual ~Hittable() = default;
  virtual bool hit(const Ray &r, Interval ray_interval, hit_record &rec) const = 0;
  virtual AABB bounding_box() const = 0;
};
