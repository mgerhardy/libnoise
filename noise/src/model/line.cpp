// line.cpp
//
// Copyright (C) 2003, 2004 by Jason Bevins    
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
// The developer's email is zigjas@greymartinzig.com (for great email, take
// off every 'zig'.)
//

#include "line.h"

using namespace noise::model;

Line::Line ()
  : m_pModule (NULL)
  , m_attenuate( true)
{
}

double Line::GetValue ( double p) const
{
  assert (m_pModule != NULL);

  double x = (m_x1 - m_x0) * p + m_x0;
  double y = (m_y1 - m_y0) * p + m_y0;
  double z = (m_z1 - m_z0) * p + m_z0;
  double value = m_pModule->GetValue (x, y, z);

  if (m_attenuate) {
    return p * (1.0 - p) * 4 * value;
  } else {
    return value;
  }
}
