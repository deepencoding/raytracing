#pragma once

#include "hittable.h"

class Material {
public:
	virtual ~Material() = default;
	virtual bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const {
		return false;
	}
};

class Lambertian : public Material {
public:
	Lambertian(const color& a) : m_Albedo(a) {}

	bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override {
		vec3 scattered_dir = rec.normal + random_unit_vector();

		if (scattered_dir.near_zero())
			scattered_dir = rec.normal;

		scattered = Ray(rec.poi, scattered_dir);
		attenuation = m_Albedo;
		return true;
	}

private:
	color m_Albedo;
};

class Metal : public Material {
public:
	Metal(const color& a): m_Albedo(a) {}

	bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override {
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		scattered = Ray(rec.poi, reflected);
		attenuation = m_Albedo;
		return true;
	}

private:
	color m_Albedo;
};
