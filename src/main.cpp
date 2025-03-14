#include <iostream>

#include "vec3.h"
#include "color.h"
#include "ray.h"

double hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 camera_to_sphere = center - r.origin();

	// double a = dot(r.direction(), r.direction());
	double a = r.direction().length_squared();

	// double b = -2.0 * dot(r.direction(), origin_to_center);
	double h = dot(r.direction(), camera_to_sphere);

	// double c = dot(origin_to_center, origin_to_center) - radius*radius;
	double c = camera_to_sphere.length_squared() - radius*radius;

	double discriminant = h*h - a*c;

	if (discriminant < 0) {
		return -1.0;
	} else {
		// return (-b - std::sqrt(discriminant)) / (2.0*a);
		return (h - std::sqrt(discriminant)) / a;
	}
}

color ray_color(const ray& r) {
	// Sphere Intersection
	double t = hit_sphere(point3(0,0,-1), 0.5, r);
	if (t > 0.0) {
		vec3 N = unit_vector(r.at(t) - point3(0,0,-1)); // Components range from [-1, 1]
		return 0.5*color(N.x()+1, N.y()+1, N.z()+1); // Components range from [0, 1]
	}

	// Lerp from White to Blue
	vec3 unit_dir = unit_vector(r.direction());
	double a = 0.5 * (unit_dir.y() + 1.0);
	return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
	// Image
	double aspect_ratio = 16.0 / 9.0;
	int img_width = 400;
	int img_height = std::max(1, int(img_width / aspect_ratio));

	// Camera
	double focal_len = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * (double(img_width) / img_height);
	point3 camera_center = point3();

	// Viewport Vectors
	vec3 viewport_x = vec3(viewport_width, 0, 0);
	vec3 viewport_y = vec3(0, -viewport_height, 0);

	vec3 pixel_delta_x = viewport_x / img_width;
	vec3 pixel_delta_y = viewport_y / img_height;

	point3 vp_upper_left = camera_center - vec3(0, 0, focal_len) - viewport_x/2 - viewport_y/2;
	point3 pixel_upper_left = vp_upper_left + 0.5 * (pixel_delta_x + pixel_delta_y);

	// Render
	std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

	for (int row = 0; row < img_height; ++row) {
		std::clog << "\rScanlines remaining: " << (img_height - row) << ' ' << std::flush;
		for (int col = 0; col < img_width; ++col) {
			color pixel_center = pixel_upper_left + col * pixel_delta_x + row * pixel_delta_y;
			vec3 ray_dir = pixel_center - camera_center;
			ray r(camera_center, ray_dir);

			color pixel = ray_color(r);
			write_color(std::cout, pixel);
		}
	}
	std::clog << "\rDone.                 \n";
	return 0;
}
