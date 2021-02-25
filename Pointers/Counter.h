#pragma once
#include <cstdint>

class Counter {
public:
	Counter(uint32_t startValue = 1);
	void operator--();
	void operator++();
	void printState();
	uint32_t getCounter() const;
private:
	uint32_t m_counter;
};