#pragma once

#include <iostream>
#include <memory>
#include <cmath>
#include <limits>
#include <random>

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

// Random Number Generation
static std::random_device rd;
static std::mt19937 rng(rd());
static std::uniform_real_distribution<double> dist(0.0, std::nextafter(1.0, 0.0));

inline double random_double() {
    // Returns a random real in [0, 1).
	return dist(rng);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

// Common Headers
#include "ray.h"
#include "vec3.h"
#include "color.h"
#include "interval.h"
