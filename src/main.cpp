#include "utility.h"
#include "bvh.h"
#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;

int main() {
    // World
    Hittable_list world;

    auto ground_material = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    world.add(make_shared<Sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; ++a) {
	for (int b = -11; b < 11; ++b) {
	    auto choose_mat = random_double();
	    point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

	    if ((center - point3(4, 0.2, 0)).length() > 0.9) {
		shared_ptr<Material> sphere_material;

		if (choose_mat < 0.8) {
		    // diffuse
		    auto albedo = color::random() * color::random();
		    sphere_material = make_shared<Lambertian>(albedo);
		    point3 end_center = center + vec3(0, random_double(0,0.5), 0);
		    world.add(make_shared<Sphere>(center, end_center, 0.2, sphere_material));
		}
		else if (choose_mat < 0.95) {
		    // metal
		    auto albedo = color::random(0.5, 1);
		    auto fuzz = random_double(0, 0.5);
		    sphere_material = make_shared<Metal>(albedo, fuzz);
		    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
		}
		else {
		    // glass
		    sphere_material = make_shared<Dielectric>(1.5);
		    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
		}
	    }
	}
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(point3(0,1,0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    world = Hittable_list(make_shared<BVHNode>(world));

    Camera cam;
    cam.m_AspectRatio = 16.0 / 9.0;
    cam.m_ImageWidth = 400;
    cam.m_SamplesPerPixel = 100;
    cam.m_MaxDepth = 50;

    cam.m_vFov     = 20;
    cam.m_LookFrom = point3(13,2,3);
    cam.m_LookAt   = point3(0,0,0);
    cam.m_ViewUp   = vec3(0,1,0);

    cam.m_DefocusAngle = 0.6;
    cam.m_FocusDist    = 10.0;

    cam.Render(world);
    return 0;
}


/*
    auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.50);
    auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
    auto material_right  = make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    auto R = std::cos(pi/4);

    auto material_left  = make_shared<Lambertian>(color(0,0,1));
    auto material_right = make_shared<Lambertian>(color(1,0,0));

    world.add(make_shared<Sphere>(point3(-R, 0, -1), R, material_left));
    world.add(make_shared<Sphere>(point3( R, 0, -1), R, material_right));
*/
