#pragma once
#include <exception>
#include <string>

class WrongInitializingArray : public std::exception
{
public:
	WrongInitializingArray() {
	}
	const char* what() const noexcept;
};

