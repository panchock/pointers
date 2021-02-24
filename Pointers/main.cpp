#include "Rectangle.h"
#include "UniquePtr.h"
#include <iostream>

using std::cout;
using std::endl;

UniquePtr<Rectangle> createRectangle() {
	return new Rectangle(3, 8);
}

void stepTwo() {
	UniquePtr<Rectangle> ptr = new Rectangle(2, 4);
	ptr = createRectangle();
	ptr = std::move(ptr);
	UniquePtr<Rectangle> ptr2 = std::move(ptr);
	cout << ptr2->getWidth() << ", " << ptr2->getHeight() << endl;
}

void stepOne() {
	UniquePtr<int> ptr1 = new int(5);
	UniquePtr<Rectangle> ptr2 = new Rectangle(4, 5);
	cout << *ptr1 << endl;
	*ptr1 = 3;
	cout << *ptr1 << endl;
	cout << ptr2->getArea() << endl;
}

int wmain() {
	// stepOne();
	stepTwo();
	return 0;
}