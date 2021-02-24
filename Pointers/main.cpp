#include "Rectangle.h"
#include "SharedPtr.h"
#include <iostream>

using std::cout;
using std::endl;

template<typename T, class... Args>
SharedPtr<T> make_shared(Args&&... args) {
	return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

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

int wmain() {
	stepThree();
	return 0;
}