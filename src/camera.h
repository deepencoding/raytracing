#pragma once

#include "hittable.h"

class Camera {
public:
	void Render(const Hittable& world) {
		initialize();
	}

private:
	void initialize() {
		
	}

	color ray_color(const Ray& r, const Hittable& world) {

	}

};
