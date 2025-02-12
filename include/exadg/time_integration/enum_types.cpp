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

// deal.II
#include <deal.II/base/exceptions.h>

// ExaDG
#include <exadg/time_integration/enum_types.h>

namespace ExaDG
{
std::string
enum_to_string(CFLConditionType const enum_type)
{
  std::string string_type;

  switch(enum_type)
  {
    case CFLConditionType::VelocityNorm:
      string_type = "VelocityNorm";
      break;
    case CFLConditionType::VelocityComponents:
      string_type = "VelocityComponents";
      break;
    default:
      AssertThrow(false, dealii::ExcMessage("Not implemented."));
      break;
  }

  return string_type;
}

std::string
enum_to_string(GenAlphaType const enum_type)
{
  std::string string_type;

  switch(enum_type)
  {
    case GenAlphaType::Newmark:
      string_type = "Newmark";
      break;
    case GenAlphaType::GenAlpha:
      string_type = "GenAlpha";
      break;
    case GenAlphaType::HHTAlpha:
      string_type = "HHTAlpha";
      break;
    case GenAlphaType::BossakAlpha:
      string_type = "BossakAlpha";
      break;
    default:
      AssertThrow(false, dealii::ExcMessage("Not implemented."));
      break;
  }

  return string_type;
}

} // namespace ExaDG
