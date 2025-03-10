#pragma once

#include "vec3.h"

class ray {
public:
	ray() {}
	ray(const vec3& _origin, const point3& _dir): m_Origin(_origin), m_Direction(_dir) {}

	const point3& origin() const { return m_Origin; }
	const vec3& direction() const { return m_Direction; }

	point3 at(double t) const {
		return m_Origin + t * m_Direction;
	}

private:
	point3 m_Origin;
	vec3 m_Direction;
};
