#pragma once
#include <string>
#include <exception>

class IndexOutOfRange: public std::exception {
	std::string s;
public:
	IndexOutOfRange(size_t i, size_t j);
	const char* what() const noexcept;
};
