#pragma once

#include <cmath>
#include <iostream>

// Utility Function Prototypes
double random_double();
double random_double(double min, double max);

class vec3 {
public:
	double e[3];

	vec3(): e{0, 0, 0} {}
	vec3(double e1, double e2, double e3): e{e1, e2, e3} {}

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](unsigned int i) const { return e[i]; }
	double& operator[](unsigned int i) { return e[i]; }

	vec3& operator+=(const vec3& other) {
		this->e[0] += other.x();
		this->e[1] += other.y();
		this->e[2] += other.z();
		return *this;
	}

	vec3& operator*=(double val) {
		this->e[0] *= val;
		this->e[1] *= val;
		this->e[2] *= val;
		return *this;
	}

	vec3& operator/=(double val) {
		return *this *= (1/val);
	}

	double length() const {
		return std::sqrt(length_squared());
	}

	double length_squared() const {
		return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
	}

	bool near_zero() const {
		// Return true if the vector is close to zero in all dimensions.
		const double s = 1e-8;
		return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
	}
	
	static vec3 random() {
		return vec3(random_double(), random_double(), random_double());
  }

  static vec3 random(double min, double max) {
    return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
  }
};

using point3 = vec3;

// Utility functions

inline std::ostream& operator<<(std::ostream& out, const vec3& vec) {
	return out << vec.e[0] << ' ' << vec.e[1] << ' ' << vec.e[2];
}

inline vec3 operator+(const vec3& v, const vec3& u) {
	return vec3(v.e[0] + u.e[0], v.e[1] + u.e[1], v.e[2] + u.e[2]);
}

inline vec3 operator-(const vec3& v, const vec3& u) {
	return vec3(v.e[0] - u.e[0], v.e[1] - u.e[1], v.e[2] - u.e[2]);
}

inline vec3 operator*(const vec3& v, const vec3& u) {
	return vec3(v.e[0] * u.e[0], v.e[1] * u.e[1], v.e[2] * u.e[2]);
}

inline vec3 operator*(const vec3& v, double val) {
	return vec3(v.e[0]*val, v.e[1]*val, v.e[2]*val);
}

inline vec3 operator*(double val, const vec3& v) {
	return v * val;
}

inline vec3 operator/(const vec3& v, double val) {
	return v * (1/val);
}

inline double dot(const vec3& u, const vec3& v) {
	return u.e[0]*v.e[0] +u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
	     	    u.e[2] * v.e[0] - u.e[0] * v.e[2], 
	     	    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
	return v / v.length();
}

inline vec3 random_unit_vector() {
	while (true) {
		vec3 rand_vec = vec3::random(-1, 1);
		double lens_rv = rand_vec.length_squared();
		if (lens_rv > 1e-160 && lens_rv <= 1) return rand_vec / std::sqrt(lens_rv);
	}
}

inline vec3 random_on_hemisphere(const vec3& normal) {
	vec3 in_unit_sphere = random_unit_vector();
	if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return in_unit_sphere;

	return -in_unit_sphere;
}

inline vec3 random_in_unit_disk() {
	while (true) {
		auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() < 1)
			return p;
	}
}

inline vec3 reflect(const vec3& vec, const vec3& normal) {
	return vec - 2 * dot(vec, normal) * normal;
}

inline vec3 refract(const vec3& incident, const vec3& normal, double relative_refraction_idx) {
	double cos_theta = std::fmin(dot(-incident, normal), 1.0);
	vec3 r_out_perp = relative_refraction_idx * (incident + cos_theta * normal);
	vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * normal;
	return r_out_perp + r_out_parallel;
}
