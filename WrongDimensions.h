#pragma once
#include <exception>
#include <string>

class WrongDimensions : public std::exception
{
	std::string s;
public:
	WrongDimensions(size_t m1i, size_t m1j, size_t m2i, size_t m2j);
	const char * what() const noexcept;
};

