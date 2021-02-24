#include "Rectangle.h"
#include "SharedPtr.h"
#include <iostream>

using std::cout;
using std::endl;

void foo(SharedPtr<int> ptr) {
	cout << *ptr << endl;
}

void stepThree() {
	SharedPtr<int> ptr = new int(4);
	SharedPtr<int> ptr2 = ptr;

	foo(ptr);
	foo(ptr2);

	{
		SharedPtr<int> ptr3 = ptr;
		SharedPtr<int> ptr4 = new int(3);
		ptr2 = ptr4;
	}

	cout << *ptr << ", " << *ptr2 << endl;
}

int wmain() {
	stepThree();
	return 0;
}