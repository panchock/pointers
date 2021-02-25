#include "Rectangle.h"
#include "UniquePtr.h"
#include "SharedPtr.h"
#include "Utils.h"
#include <iostream>

using std::cout;
using std::endl;

void foo(SharedPtr<int> ptr) {
	cout << *ptr << endl;
}

void stepThree() {
	SharedPtr<int> ptr = make_shared<int>(4);
	SharedPtr<int> ptr2 = ptr;

	foo(ptr);
	foo(ptr2);

	{
		SharedPtr<int> ptr3 = ptr;
		SharedPtr<int> ptr4 = make_shared<int>(3);
		ptr2 = ptr4;
	}

	cout << *ptr << ", " << *ptr2 << endl;
}

UniquePtr<Rectangle> createRectangle() {
	return make_unique<Rectangle>(3, 8);
}

void stepTwo() {
	UniquePtr<Rectangle> ptr = make_unique<Rectangle>(2, 4);
	ptr = createRectangle();
	ptr = std::move(ptr);
	UniquePtr<Rectangle> ptr2 = std::move(ptr);
	cout << ptr2->getWidth() << ", " << ptr2->getHeight() << endl;
}

void stepOne() {
	UniquePtr<int> ptr1 = make_unique<int>(5);
	UniquePtr<Rectangle> ptr2 = make_unique<Rectangle>(4, 5);
	cout << *ptr1 << endl;
	*ptr1 = 3;
	cout << *ptr1 << endl;
	cout << ptr2->getArea() << endl;
}

int wmain() {
	// stepOne();
	// stepTwo();
	stepThree();
	return 0;
}