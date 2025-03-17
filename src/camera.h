#pragma once

#include "hittable.h"
#include "vec3.h"
#include "material.h"

class Camera {
public:
	double m_AspectRatio     = 1.0; // Ratio of image width over height
	int    m_ImageWidth      = 100; // Rendered image width in pixel count
	int    m_SamplesPerPixel = 10;  // Number of random ray samples per pixel
	int    m_MaxDepth	 = 10;  // Max num of ray bounces
	
	double m_vFov     = 90;
	point3 m_LookFrom = point3(0,0,0);   // Point camera is looking from
	point3 m_LookAt   = point3(0,0,-1);  // Point camera is looking at
	vec3   m_ViewUp   = vec3(0,1,0);

	double m_DefocusAngle = 0;
	double m_FocusDist    = 10;

	void Render(const Hittable& world) {
		Initialize();
		std::cout << "P3\n" << m_ImageWidth << ' ' << m_ImageHeight << "\n255\n";

		for (int row = 0; row < m_ImageHeight; row++) {
			std::clog << "\rProgress: ";
			int i = 0;
			for (; i < (50 * row / m_ImageHeight); ++i) std::clog << '#';
			for (; i < 50; ++i) std::clog << '.' << std::flush;
			for (int col = 0; col < m_ImageWidth; col++) {
				color pixel_color = color(0,0,0);
				for (int sample = 0; sample < m_SamplesPerPixel; sample++) {
					Ray r = get_ray(col, row);
					pixel_color += RayColor(r, m_MaxDepth, world);
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
	vec3   u, v, w;
	vec3   m_DefocusDiskX, m_DefocusDiskY;

	void Initialize() {
		m_ImageHeight = std::max(1, int(m_ImageWidth / m_AspectRatio));

		m_PixelSamplesScale = 1.0 / m_SamplesPerPixel;

		m_Center = m_LookFrom;

		// Determine viewport dimensions.
		// double focal_len = (m_LookFrom - m_LookAt).length();
		auto theta = deg_to_rad(m_vFov);
		auto h = std::tan(theta/2);
		auto viewport_height = 2 * h * m_FocusDist;
		double viewport_width = viewport_height * (double(m_ImageWidth) / m_ImageHeight);

		// Calc Basis vectors
		w = unit_vector(m_LookFrom - m_LookAt);
		u = unit_vector(cross(m_ViewUp, w));
		v = cross(w, u);
	
		// Viewport Vectors
		vec3 viewport_x = viewport_width * u;
		vec3 viewport_y = viewport_height * -v;

		m_PixelDeltaU = viewport_x / m_ImageWidth;
		m_PixelDeltaV = viewport_y / m_ImageHeight;

		// Calculate the location of the upper left pixel.
		auto viewport_upper_left = m_Center - (m_FocusDist * w) - viewport_x/2 - viewport_y/2;
		m_Pixel00Loc = viewport_upper_left + 0.5 * (m_PixelDeltaU + m_PixelDeltaV);

		double defocus_radius = m_FocusDist * std::tan(deg_to_rad(m_DefocusAngle / 2));
		m_DefocusDiskX = u * defocus_radius;
		m_DefocusDiskY = v * defocus_radius;
	}

	Ray get_ray(int col, int row) const {
		vec3 offset = sample_square();
		point3 sample_pixel = m_Pixel00Loc + (col+offset.x()) * m_PixelDeltaU + (row+offset.y()) * m_PixelDeltaV;
		point3 ray_origin = (m_DefocusAngle <= 0) ? m_Center : defocus_disk_sample();;
		vec3 ray_dir = sample_pixel - ray_origin;
		return Ray(ray_origin, ray_dir);
	}

	vec3 sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
		return vec3(random_double() - 0.5, random_double() - 0.5, 0);
	}

	point3 defocus_disk_sample() const {
		auto p = random_in_unit_disk();
		return m_Center + (p[0] * m_DefocusDiskX) + (p[1] * m_DefocusDiskY);
	}

	color RayColor(const Ray& r, int Depth, const Hittable& world) {
		if (Depth <= 0) 
			return color(0, 0, 0);

		hit_record rec;

		if (world.hit(r, Interval(0.001, infinity), rec)) {
			Ray scattered;
			color attenuation;
			if (rec.p_mat->scatter(r, rec, attenuation, scattered))
				return attenuation * RayColor(scattered, Depth-1, world);
			return color(0,0,0);
		}

		vec3 unit_dir = unit_vector(r.direction());
		double a = 0.5 * (unit_dir.y() + 1.0);
		return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
	}

};
