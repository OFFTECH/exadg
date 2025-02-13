/*  ______________________________________________________________________
 *
 *  ExaDG - High-Order Discontinuous Galerkin for the Exa-Scale
 *
 *  Copyright (C) 2021 by the ExaDG authors
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *  ______________________________________________________________________
 */
#ifndef INCLUDE_EXADG_OPERATORS_VARIABLE_COEFFICIENTS_H_
#define INCLUDE_EXADG_OPERATORS_VARIABLE_COEFFICIENTS_H_

namespace ExaDG
{
template<int dim, typename Number>
class VariableCoefficientsCells
{
private:
  typedef dealii::VectorizedArray<Number> scalar;

public:
  void
  initialize(dealii::MatrixFree<dim, Number> const & matrix_free,
             unsigned int const                      degree,
             Number const &                          constant_coefficient)
  {
    unsigned int const points_per_cell = dealii::Utilities::pow(degree + 1, dim);

    coefficients_cell.reinit(matrix_free.n_cell_batches(), points_per_cell);
    coefficients_cell.fill(dealii::make_vectorized_array<Number>(constant_coefficient));
  }

  scalar
  get_coefficient(unsigned int const cell, unsigned int const q) const
  {
    return coefficients_cell[cell][q];
  }

  void
  set_coefficient(unsigned int const cell, unsigned int const q, scalar const & value)
  {
    coefficients_cell[cell][q] = value;
  }

private:
  // variable coefficients
  dealii::Table<2, scalar> coefficients_cell;
};

template<int dim, typename Number>
class VariableCoefficients
{
private:
  typedef dealii::VectorizedArray<Number> scalar;

public:
  void
  initialize(dealii::MatrixFree<dim, Number> const & matrix_free,
             unsigned int const                      degree,
             Number const &                          constant_coefficient)
  {
    unsigned int const points_per_cell = dealii::Utilities::pow(degree + 1, dim);
    unsigned int const points_per_face = dealii::Utilities::pow(degree + 1, dim - 1);

    // cells
    coefficients_cell.reinit(matrix_free.n_cell_batches(), points_per_cell);

    coefficients_cell.fill(dealii::make_vectorized_array<Number>(constant_coefficient));

    // face-based loops
    coefficients_face.reinit(matrix_free.n_inner_face_batches() +
                               matrix_free.n_boundary_face_batches(),
                             points_per_face);

    coefficients_face.fill(dealii::make_vectorized_array<Number>(constant_coefficient));

    coefficients_face_neighbor.reinit(matrix_free.n_inner_face_batches(), points_per_face);

    coefficients_face_neighbor.fill(dealii::make_vectorized_array<Number>(constant_coefficient));

    // TODO cell-based face loops
    //    coefficients_face_cell_based.reinit(matrix_free.n_cell_batches()*2*dim,
    //        points_per_face);
    //
    //    coefficients_face_cell_based.fill(dealii::make_vectorized_array<Number>(constant_coefficient));
  }

  scalar
  get_coefficient_cell(unsigned int const cell, unsigned int const q) const
  {
    return coefficients_cell[cell][q];
  }

  void
  set_coefficient_cell(unsigned int const cell, unsigned int const q, scalar const & value)
  {
    coefficients_cell[cell][q] = value;
  }

  scalar
  get_coefficient_face(unsigned int const face, unsigned int const q) const
  {
    return coefficients_face[face][q];
  }

  void
  set_coefficient_face(unsigned int const face, unsigned int const q, scalar const & value)
  {
    coefficients_face[face][q] = value;
  }

  scalar
  get_coefficient_face_neighbor(unsigned int const face, unsigned int const q) const
  {
    return coefficients_face_neighbor[face][q];
  }

  void
  set_coefficient_face_neighbor(unsigned int const face, unsigned int const q, scalar const & value)
  {
    coefficients_face_neighbor[face][q] = value;
  }

  // TODO
  //  scalar
  //  get_coefficient_cell_based(unsigned int const face,
  //                             unsigned int const q) const
  //  {
  //    return coefficients_face_cell_based[face][q];
  //  }
  //
  //  void
  //  set_coefficient_cell_based(unsigned int const face,
  //                             unsigned int const q,
  //                             scalar const &     value)
  //  {
  //    coefficients_face_cell_based[face][q] = value;
  //  }

private:
  // variable coefficients

  // cell
  dealii::Table<2, scalar> coefficients_cell;

  // face-based loops
  dealii::Table<2, scalar> coefficients_face;
  dealii::Table<2, scalar> coefficients_face_neighbor;

  // TODO
  //  // cell-based face loops
  //  dealii::Table<2, scalar> coefficients_face_cell_based;
};

} // namespace ExaDG

#endif /* INCLUDE_EXADG_OPERATORS_VARIABLE_COEFFICIENTS_H_ */
