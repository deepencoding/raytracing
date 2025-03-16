#include "utility.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main() {
	// World
	Hittable_list world;
	world.add(make_shared<Sphere>(point3(0,0,-1), 0.5));
	world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));

	Camera cam;
	cam.m_AspectRatio = 16.0 / 9.0;
	cam.m_ImageWidth = 400;
	cam.m_SamplesPerPixel = 100;
	cam.Render(world);
	return 0;
}
