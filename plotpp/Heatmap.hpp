#pragma once

#include <ostream>
#include <functional>
#include "plotpp/IPlot.hpp"

namespace plotpp{
	/*
		Heat Map for custom matrix like objects
	*/
	template<class T>
	class Heatmap : public IPlot{
		optional_ptr<T> _matrix;
		size_t _rows = 0;
		size_t _columns = 0;
		std::function<double(const T&, size_t/*row*/, size_t/*col*/)> _at;
		
	public:

		Heatmap(optional_ptr<T> matrix, size_t rows, size_t columns, std::function<double(const T&, size_t/*row*/, size_t/*col*/)> at, Text title="")
			: _matrix(std::move(matrix))
			, _rows(rows)
			, _columns(columns)
			, _at(std::move(at))
			{}
		
		virtual void printPlot(std::ostream& stream) const {
			stream << "matrix with image title '" << this->IPlot::label() << "'";
		}
		
		virtual void printData(std::ostream& stream) const {
			for(size_t row=0; row < this->_rows; ++row){
				for(size_t col=0; col < this->_columns; ++col){
					stream << this->_at(*(this->_matrix), row, col) << ' ';
				}
				stream << '\n';
			}
		}
		
	};
	
	// Construction Helper
	template<PtrOrMoved U1>
	auto heatmap(U1 matrix, size_t rows, size_t columns,
				 std::function<double(const remove_ptr_t<std::remove_reference_t<U1>>&, size_t, size_t)> at,
				 Text title = "") {
		using T = remove_ptr_t<std::remove_reference_t<U1>>;
		return Heatmap<T>(optional_ptr<T>(std::forward<U1>(matrix)), rows, columns, at, std::move(title));
	}
	
	template <typename T>
	concept MatrixLike = requires(T t, size_t i, size_t j) {
		{ t.rows() } -> std::convertible_to<int>;
		{ t.columns() } -> std::convertible_to<int>;
		{ t.at(i, j) };
	};
	
	// Construction Helper for common matrix objects with common interfaces
	template<MatrixLike U1>
	auto heatmap(U1&& matrix, Text title = "") 
	{
		using T = std::remove_reference_t<U1>;
		
		auto at = [](const T& matrix, size_t row, size_t col) -> double {
			return static_cast<double>(matrix.at(row, col));
		};
		
		return Heatmap<T>(optional_ptr<T>(std::move<U1>(matrix)), matrix.rows(), matrix.columns(), at, std::move(title));
	}
	
	// Construction Helper for common matrix pointers with common interfaces
	template<MatrixLike U1>
	auto heatmap(U1* matrix, Text title = "") 
	{
		using T = std::remove_reference_t<U1>;
		
		auto at = [](const T& matrix, size_t row, size_t col) -> double {
			return static_cast<double>(matrix.at(row, col));
		};
		
		return Heatmap<T>(optional_ptr<T>(matrix), matrix->rows(), matrix->columns(), at, std::move(title));
	}

	// Construction Helper
	template<class T, size_t ROWS, size_t COLS>
	auto heatmap(const T(*array)[ROWS][COLS], Text title = "") {
		// Custom Access Function
		auto at = [](const T (&matrix)[ROWS][COLS], size_t row, size_t col) -> double {
			return static_cast<double>(matrix[row][col]);
		};

		return heatmap(array, ROWS, COLS, at, std::move(title));
	}

}