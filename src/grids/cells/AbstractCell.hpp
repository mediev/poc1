#ifndef ABSTRACTCELL_HPP_
#define ABSTRACTCELL_HPP_

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include "src/grids/variables/Variables.hpp"
#include "src/models/ReservoirProperties.hpp"

namespace units {
	using data::uint;
	using data::Scalar;
/**
 Basic type of cell as an element of any hand-made grid

 @tparam Variable Type of container that has vector of variables
 @tparam DependentVariable Type of container that has all dependent variables which need to be stored
 */
	template<template<typename> typename PointType,
	typename TVariable, typename TDependentVariable = data::EmptyContainer>
	class AbstractCell
	{
	public:
		typedef PointType<Scalar> Point;
		template<typename DataType> using TPoint = PointType<DataType>;
		typedef typename Point::Base::IndexesType Indexes;
		typedef TVariable Variable;
		typedef TDependentVariable DependentVariable;
	public:
		// Geometry dimension of cell
		static const uint dim;
		// Center of cell
		Point coords;
		// Cell sizes;
		Point sizes;

		// Number of cell in grid
		int num;

		// Volume of cell
		Scalar V;

		// Pointer to formation properties
		models::properties::FormationProperties* prop_ptr;

		// Vectors of variables for temporary discretization
		TVariable u_next, u_iter, u_prev;
		// Vectors of dependent variables for temporary discretization
		TDependentVariable d_next, d_iter, d_prev;

		AbstractCell() : num(-1), V(0.0) {};
		AbstractCell(int _num) : num(_num) {};
		AbstractCell(const AbstractCell& cell) = default;
		~AbstractCell() {};

		AbstractCell& operator=(const AbstractCell& cell) = default;
	};

	template<template<typename> typename PointType,
	typename TVariable, typename TDependentVariable>
	const uint AbstractCell<PointType, TVariable, TDependentVariable>::dim = PointType<Scalar>::size;
};

namespace std
{
	template<template<typename> typename PointType,
	typename TVariable, typename TDependentVariable = data::EmptyContainer>
	inline std::ostream& operator<<(std::ostream& os, const units::AbstractCell<PointType, TVariable, TDependentVariable>& cell)
	{
		os << "#" << cell.num << std::endl;
		os << "Coords:\t" << cell.coords;
		os << "Sizes:\t" << cell.sizes;
		return os;
	};
};


#endif /* ABSTRACTCELL_HPP_ */
