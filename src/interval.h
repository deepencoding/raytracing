#pragma once

#include "utility.h"

class Interval {
public:
	double Min, Max;

	Interval(): Min(+infinity), Max(-infinity) {}
	Interval(double m, double M): Min(m), Max(M) {}

	double Size() const {
		return Max - Min;
	}

	bool Contains(double x) const {
		return x >= Min && x <= Max;
	}

	bool Surrounds(double x) const {
		return x > Min && x < Max;
	}

	static const Interval empty, universe;
};

const Interval Interval::empty(+infinity, -infinity);
const Interval Interval::universe(-infinity, +infinity);
