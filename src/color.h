#pragma once

#include "interval.h"
#include "utility.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel) {
	double R = pixel.x();
	double G = pixel.y();
	double B = pixel.z();

	// Convert normalized values to [0, 255]
	static const Interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.Clamp(R));
	int gbyte = int(256 * intensity.Clamp(G));
	int bbyte = int(256 * intensity.Clamp(B));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

// Book Implementation
/*
#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
*/
