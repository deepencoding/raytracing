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
	Metal(const color& a, double fuzz): m_Albedo(a), m_Fuzz(fuzz < 1 ? fuzz : 1) {}

	bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override {
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		reflected = unit_vector(reflected) + (m_Fuzz * random_unit_vector());
		scattered = Ray(rec.poi, reflected);
		attenuation = m_Albedo;
		return dot(scattered.direction(), rec.normal) > 0;
	}

private:
	color m_Albedo;
	double m_Fuzz;
};

class Dielectric : public Material {
public:
	Dielectric(double refraction_idx) : m_RefractionIdx(refraction_idx) {}

	bool scatter(const Ray& r_in, const hit_record& rec, color& attenuation, Ray& scattered) const override {
		attenuation = color(1.0, 1.0, 1.0);
		double refraction_ratio = rec.front_face ? (1.0 / m_RefractionIdx) : m_RefractionIdx;

		vec3 unit_direction = unit_vector(r_in.direction());
		
		double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0 || reflectance(cos_theta, refraction_ratio) > random_double();
		vec3 direction;
		if (cannot_refract) {
			direction = reflect(r_in.direction(), rec.normal);
		} else {
			direction = refract(unit_direction, rec.normal, refraction_ratio);
		}
		
		scattered = Ray(rec.poi, direction);
		return true;
	}

private:
	double m_RefractionIdx;

	static double reflectance(double cosine, double refraction_idx) {
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - refraction_idx) / (1 + refraction_idx);
		r0 *= r0;
		return r0 + (1 - r0) * std::pow((1 - cosine), 5);
	}
};
