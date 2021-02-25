#include "Counter.h"
#include <iostream>

using std::cout;
using std::endl;

Counter::Counter(uint32_t startValue) : m_counter(startValue) {
}

void Counter::decrease() {
	m_counter--;
}

void Counter::increase() {
	m_counter++;
}

void Counter::printState() {
	cout << "Counter address: " << this << ", Counter value: " << m_counter << endl;
}

uint32_t Counter::getCounter() const {
	return m_counter;
}
