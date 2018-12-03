#include "MatrixData.h"
#include "WrongInitializingArray.h"
#include "WrongDimensions.h"
#include "IndexOutOfRange.h"
#include <iostream>

MatrixData::MatrixData(size_t rows, size_t columns)
{
	references = 1;
	this->columns = columns;
	this->rows = rows;

	m = new double*[rows];

	size_t i;
	try {

		for (i = 0; i < rows; i++) {
			m[i] = new double[columns];
			for (size_t j = 0; j < columns; j++) {
				m[i][j] = 0;
			}
		}
	}
	catch (...) {
		for (i = 0; i < rows; i++) {
			delete [] m[i];
		}
		delete [] m;
		throw;
	}
}

MatrixData::MatrixData(size_t rows, size_t columns, double ** a) {
	if (a == nullptr) {
		throw WrongInitializingArray();
	}
	references = 1;
	this->columns = columns;
	this->rows = rows;
	m = new double*[rows];
	size_t i;
	try {

		for (i = 0; i < rows; i++) {
			m[i] = new double[columns];
			for (size_t j = 0; j < columns; j++) {
				m[i][j] = a[i][j];
			}
		}
	}
	catch (...) {
		for (i = 0; i < rows; i++) {
			delete[] m[i];
		}
		delete[] m;
		abort();
	}
}

MatrixData::~MatrixData()
{
	for (size_t i = 0; i < rows; i++) {
		delete[] m[i];
	}
	delete[] m;
}

MatrixData* MatrixData::detach() {
	if (references == 1) return this;
	references--;
	return new MatrixData(rows, columns, m);
}
