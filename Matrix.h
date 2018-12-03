#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "MatrixData.h"


class Matrix
{
public:
	class Cref;
	MatrixData* data;

	Matrix(size_t rows, size_t columns, double ** a);
	Matrix(size_t rows, size_t columns);
	Matrix(const Matrix & matrix);
	Matrix(std::string fileName);
	~Matrix();

	Matrix& operator=(const Matrix & m1);
	double operator()(size_t i, size_t j) const;
	Matrix::Cref operator()(size_t i, size_t j);

	Matrix operator+(const Matrix & m1) const;
	Matrix operator-(const Matrix & m1) const;
	Matrix operator* (const Matrix & m1) const;
	Matrix operator*(double factor) const;

	Matrix & operator+=(const Matrix & m2);
	Matrix & operator-=(const Matrix & m2);
	Matrix & operator*= (const Matrix & m1);

	friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);
	friend std::istream& operator>>(std::istream& in, const Matrix& matrix);

	bool operator==(const Matrix & m1) const;
	bool operator!=(const Matrix & m1) const;
private:
	void wrongFile() const;
	double read(size_t i, size_t j) const;
	void write(size_t i, size_t j, double set);
	void checkDimesions(size_t i, size_t j) const;
};

class Matrix::Cref {
private:
	friend class Matrix;
	Matrix& matrix;
	int i, j;
public:
	Cref(Matrix & matrixx, size_t ii, size_t jj) : matrix(matrixx), i(ii), j(jj) {};

	operator double() const;
	Matrix::Cref& operator = (double set);
};
