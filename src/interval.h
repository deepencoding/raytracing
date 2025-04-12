#pragma once

#include "utility.h"

class Interval {
public:
	double Min, Max;

	Interval(): Min(+infinity), Max(-infinity) {}
	Interval(double m, double M): Min(m), Max(M) {}
	Interval(const Interval& a, const Interval& b): Min(std::min(a.Min, b.Min)), Max(std::max(a.Max, b.Max)) {}

	double Size() const {
		return Max - Min;
	}

	bool Contains(double x) const {
		return x >= Min && x <= Max;
	}

	bool Surrounds(double x) const {
		return x > Min && x < Max;
	}

	double Clamp(double x) const {
		if (x < Min) return Min;
		if (x > Max) return Max;
		return x;
	}

	Interval Expand(double delta) const {
		double padding = delta/2;
		return Interval(Min - padding, Max + padding);
	}

	static const Interval empty, universe;
};

const Interval Interval::empty(+infinity, -infinity);
const Interval Interval::universe(-infinity, +infinity);
