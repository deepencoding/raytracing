#pragma once

#include "vec3.h"

class Ray {
public:
	Ray() {}
	Ray(const point3& _origin, const vec3& _dir, double _time): m_Origin(_origin), m_Direction(_dir), m_Time(_time) {}
	Ray(const point3& _origin, const vec3& _dir): m_Origin(_origin), m_Direction(_dir), m_Time(0) {}

	const point3& origin() const { return m_Origin; }
	const vec3& direction() const { return m_Direction; }

	double time() const { return m_Time; }

	point3 at(double t) const {
		return m_Origin + t * m_Direction;
	}

private:
	point3 m_Origin;
	vec3 m_Direction;
	double m_Time;
};
