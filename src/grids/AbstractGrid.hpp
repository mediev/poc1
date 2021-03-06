#ifndef ABSTRACTGRID_HPP_
#define	ABSTRACTGRID_HPP_

#include <vector>
#include <algorithm>
#include <functional>

#include "src/grids/variables/Variables.hpp"

namespace grids
{
	using data::Scalar;
	using data::uint;

	template <class CellType>
	class AbstractGrid
	{
	public:
		typedef CellType Cell;
		typedef typename Cell::Point Point;
		template<typename DataType> using TPoint = typename Cell::template TPoint<DataType>;
		typedef typename Cell::Variable Variable;
		typedef typename Cell::DependentVariable DependentVariable;
		typedef typename Cell::Indexes Indexes;

		uint totalSize;
		Scalar Volume;

	// All cells
	protected:
		std::vector<Cell> cells;

	public:
		AbstractGrid() 
		{
			totalSize = 0;
			Volume = 0.0;
		};

		virtual ~AbstractGrid() {};

		void setInitialState(const Variable& vars, const DependentVariable& dep_vars)
		{
			std::for_each(cells.begin(), cells.end(), [&, this](Cell& cell)
			{
				cell.u_prev = cell.u_iter = cell.u_next = vars;
				cell.d_prev = cell.d_iter = cell.d_next = dep_vars;
			});
		};

		void setInitialState(std::function<const Cell&(const Point&)> getInitialVariables)
		{
			std::for_each(cells.begin(), cells.end(), [&, this](Cell& cell)
			{
				cell.u_prev = cell.u_iter = cell.u_next = getInitialVariables(cell.coords).u_next;
				cell.d_prev = cell.d_iter = cell.d_next = getInitialVariables(cell.coords).d_next;
			});
		};

		void copyIterLayer()
		{
			std::for_each(cells.begin(), cells.end(), [&, this](Cell& cell)
			{
				cell.u_iter = cell.u_next;
				cell.d_iter = cell.d_next;
			});
		};

		void copyTimeLayer()
		{
			std::for_each(cells.begin(), cells.end(), [&, this](Cell& cell)
			{
				cell.u_prev = cell.u_iter = cell.u_next;
				cell.d_prev = cell.d_iter = cell.d_next;
			});
		};

		Variable& getAverage() const
		{
			Variable var;
			std::for_each(cells.begin(), cells.end(), [&, this](Cell& cell)
			{
				var += cell.u_next * cell.V;
			});

			return var / Volume;
		};

		Variable convergance(/*std::vector<Cell>::iterator& maxIt, */)
		{
			Variable err, cur_err;
			/*std::vector<std::vector<Cell>::iterator> it (Variable::size, cells.begin());

			std::for_each(cells.begin(), cells.end(), [&, this](Cell& cell)
			{
				cur_err = data::abs(data::divide(cell.u_next - cell.u_iter, cell.u_next));
				//if(data::max(err, cur_err) == err)
			});*/

			return err;
		};
	};
};

#endif /* ABSTRACTGRID_HPP_ */
