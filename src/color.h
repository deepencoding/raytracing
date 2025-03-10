#pragma once

#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel) {
	const double& R = pixel.x();
	const double& G = pixel.y();
	const double& B = pixel.z();

	// Convert normalized values to [1, 255]
	int rbyte = int(255.999 * R);
	int gbyte = int(255.999 * G);
	int bbyte = int(255.999 * B);

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
