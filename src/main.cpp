#include "utility.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main() {
	// World
	Hittable_list world;

    auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Metal>(color(0.8, 0.8, 0.8));
    auto material_right  = make_shared<Metal>(color(0.8, 0.6, 0.2));

    world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

	Camera cam;
	cam.m_AspectRatio = 16.0 / 9.0;
	cam.m_ImageWidth = 400;
	cam.m_SamplesPerPixel = 100;
	cam.m_MaxDepth = 50;
	cam.Render(world);
	return 0;
}
