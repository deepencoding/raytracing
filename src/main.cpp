#include <iostream>

int main() {
	// Image
	int img_width = 256, img_height = 256;

	// Render
	std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";
	
	for (int row = 0; row < img_height; ++row) {
		for (int col = 0; col < img_width; ++col) {
			double R = double(col) / (img_width -1);
			double G = double(row) / (img_height-1);
			double B = 0.0;

			int ir = int(255.999 * R);
			int ig = int(255.999 * G);
			int ib = int(255.999 * B);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	return 0;
}
