// power.cpp
//
// Version 0.1.2 - 2004-05-11
//
// Copyright (C) 2004 Owen Jacobson
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License (COPYING.txt) for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The developer's email is angstrom@lionsanctuary.net
//

#include <cmath>

#include "power.h"

using namespace noise::module;

Power::Power ():
  Module (GetSourceModuleCount ())
{
}

double Power::GetValue (double x, double y, double z) const
{
  assert (m_pSourceModule[0] != NULL);
  assert (m_pSourceModule[1] != NULL);

  return std::pow (m_pSourceModule[0]->GetValue (x, y, z),
		   m_pSourceModule[1]->GetValue (x, y, z));
}