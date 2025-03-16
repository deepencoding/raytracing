#pragma once

#include "hittable.h"

class Camera {
public:
	double m_AspectRatio     = 1.0;  // Ratio of image width over height
	int    m_ImageWidth      = 100;  // Rendered image width in pixel count
	int		 m_SamplesPerPixel = 10;   // Number of random ray samples per pixel

	void Render(const Hittable& world) {
		Initialize();
		std::cout << "P3\n" << m_ImageWidth << ' ' << m_ImageHeight << "\n255\n";

		for (int row = 0; row < m_ImageHeight; row++) {
			std::clog << "\rProgress: ";
			int i = 0;
			for (; i < (50 * row / m_ImageHeight); ++i) std::clog << '#';
			for (; i < 50; ++i) std::clog << '.' << std::flush;
			for (int col = 0; col < m_ImageWidth; col++) {
				color pixel_color(0,0,0);
				for (int sample = 0; sample < m_SamplesPerPixel; sample++) {
					Ray r = get_ray(col, row);
					pixel_color += RayColor(r, world);
				}

				write_color(std::cout, m_PixelSamplesScale * pixel_color);
			}
		}
		std::clog << "\rDone.                                                                \n";
	}

private:
	int    m_ImageHeight;   // Rendered image height
	double m_PixelSamplesScale; // Color scale factor for a sum of pixel samples
	point3 m_Center;         // Camera center
	point3 m_Pixel00Loc;    // Location of pixel 0, 0
	vec3   m_PixelDeltaU;  // Offset to pixel to the right
	vec3   m_PixelDeltaV;  // Offset to pixel below

	void Initialize() {
		m_ImageHeight = std::max(1, int(m_ImageWidth / m_AspectRatio));

		m_PixelSamplesScale = 1.0 / m_SamplesPerPixel;

		m_Center = point3(0, 0, 0);

		// Determine viewport dimensions.
		double focal_len = 1.0;
		double viewport_height = 2.0;
		double viewport_width = viewport_height * (double(m_ImageWidth) / m_ImageHeight);
	
		// Viewport Vectors
		vec3 viewport_x = vec3(viewport_width, 0, 0);
		vec3 viewport_y = vec3(0, -viewport_height, 0);

		m_PixelDeltaU = viewport_x / m_ImageWidth;
		m_PixelDeltaV = viewport_y / m_ImageHeight;

		// Calculate the location of the upper left pixel.
		auto viewport_upper_left =
		    m_Center - vec3(0, 0, focal_len) - viewport_x/2 - viewport_y/2;
		m_Pixel00Loc = viewport_upper_left + 0.5 * (m_PixelDeltaU + m_PixelDeltaV);
	}

	Ray get_ray(int col, int row) const {
		vec3 offset = sample_square();
		point3 sample_pixel = m_Pixel00Loc + (col+offset.x()) * m_PixelDeltaU + (row+offset.y()) * m_PixelDeltaV;
		point3 ray_origin = m_Center;
		vec3 ray_dir = sample_pixel - ray_origin;
		return Ray(ray_origin, ray_dir);
	}

	vec3 sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
		return vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}

	color RayColor(const Ray& r, const Hittable& world) {
		hit_record rec;
		if (world.hit(r, Interval(0.0, infinity), rec)) {
			return 0.5 * color(rec.normal + color(1, 1, 1));
		}
		/*
		// Sphere Intersection
		double t = hit_sphere(point3(0,0,-1), 0.5, r);
		if (t > 0.0) {
			vec3 N = unit_vector(r.at(t) - point3(0,0,-1)); // Components range from [-1, 1]
			return 0.5*color(N.x()+1, N.y()+1, N.z()+1); // Components range from [0, 1]
		}
		*/
		// Lerp from White to Blue
		vec3 unit_dir = unit_vector(r.direction());
		double a = 0.5 * (unit_dir.y() + 1.0);
		return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
	}

};
