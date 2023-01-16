#include <iostream>
#include <cmath>
#include <string>

struct Dimensions {
	double width = 0;
	double height = 0;

};

class Shape {
public:
	Shape() = default;
	~Shape() = default;
	virtual double square() = 0;

	virtual Dimensions dimensions() = 0;

	virtual std::string type() = 0;

	void printParams(Shape* shape) {
		std::cout << "Type: " << shape->type() << std::endl;
		std::cout << "Square: " << this->square() << std::endl;
		std::cout << "Bounding Box Dimensions: " << std::endl;
		std::cout << "\t\t\tWidth: " << this->dimensions().width << std::endl;
		std::cout << "\t\t\tHeight: " << this->dimensions().height << std::endl;
	}
};

class Circle : virtual public Shape {
private:
	double radius = 0;
public:
	explicit Circle(double in_radius) {
		if (in_radius >= 0)
			this->radius = in_radius;
		else
			std::cout << "Radius can't be less zero!" << std::endl;
	}

	double square() override {
		return 3.14 * radius * radius;
	}

	Dimensions dimensions() override {
		Dimensions boundingBoxDimensions;
		boundingBoxDimensions.width = radius * 2;
		boundingBoxDimensions.height = radius * 2;
		return boundingBoxDimensions;
	}

	std::string type() override {
		return "Circle";
	}
};

class Rectangle : virtual public Shape {
private:
	double width = 0;
	double height = 0;
public:
	Rectangle(double in_width, double in_height) {
		if (in_width >= 0 || in_height >= 0) {
			this->width = in_width;
			this->height = in_height;
		}
		else
			std::cout << "Sides can't be less zero!" << std::endl;
	}

	double square() override {
		return this->width * this->height;
	}

	Dimensions dimensions() override {
		Dimensions boundingBoxDimensions;
		double hypothesis = std::sqrt((this->width * this->width) + (this->height * this->height));
		boundingBoxDimensions.width = hypothesis;
		boundingBoxDimensions.height = hypothesis;
		return boundingBoxDimensions;
	}

	std::string type() override {
		return "Rectangle";
	}
};

class Triangle : virtual public Shape {
private:
	double side_A = 0;
	double side_B = 0;
	double side_C = 0;
public:
	Triangle(double in_side_A, double in_side_B, double in_side_C) {
		if (in_side_A >= 0 || in_side_B >= 0 || in_side_C >= 0) {
			this->side_A = in_side_A;
			this->side_B = in_side_B;
			this->side_C = in_side_C;
		}
		else
			std::cout << "Sides can't be less zero!" << std::endl;
	}

	double square() override {
		double p = (this->side_A + this->side_B + this->side_C) / 2;
		return std::sqrt(p * (p - side_A) * (p - side_B) * (p - side_C));
	}

	Dimensions dimensions() override {
		Dimensions boundingBoxDimensions;
		boundingBoxDimensions.width = this->side_A * this->side_B * this->side_C / (4 * this->square()) * 2;
		boundingBoxDimensions.height = this->side_A * this->side_B * this->side_C / (4 * this->square()) * 2;
		return boundingBoxDimensions;
	}

	std::string type() override {
		return "Triangle";
	}
};

int main() {
	Shape* shapes[3];
	shapes[0] = new Circle(10);
	shapes[1] = new Rectangle(11, 12);
	shapes[2] = new Triangle(5, 7, 6);

	for (int i = 0; i < 3; ++i) {
		shapes[i]->printParams(shapes[i]);
	}

	for (int i = 0; i < 3; ++i)
		delete shapes[i];

	return 0;
}
