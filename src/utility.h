#pragma once

#include <iostream>
#include <memory>
#include <cmath>
#include <limits>

// Using C++ STL
using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions
inline double deg_to_rad(double deg) {
	return deg * pi / 180.0;
}

inline double rad_to_deg(double rad) {
	return rad * 180.0 / pi;
}

// Common Headers
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "interval.h"
