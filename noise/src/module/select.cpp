// select.cpp
//
// Version 0.1.1 - 2004-03-04
// - Changed GetNumSourceModules() to GetSourceModuleCount() for consistency.
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

#include "../interp.h"
#include "select.h"

using namespace noise::module;

Select::Select ():
  Module (GetSourceModuleCount ()),
  m_lowerBound (DEFAULT_SELECT_LOWER_BOUND),
  m_upperBound (DEFAULT_SELECT_UPPER_BOUND),
  m_edgeFalloff (DEFAULT_SELECT_EDGE_FALLOFF)
{
}

double Select::GetValue (double x, double y, double z) const
{
  assert (m_pSourceModule[0] != NULL);
  assert (m_pSourceModule[1] != NULL);
  assert (m_pSourceModule[2] != NULL);

  double selectorValue = m_pSourceModule[2]->GetValue (x, y, z);
  double alpha;
  if (m_edgeFalloff > 0.0) {
    if (selectorValue < (m_lowerBound - m_edgeFalloff)) {
      // Selector is below the selector threshold; return the first input
      // module's value.
      return m_pSourceModule[0]->GetValue (x, y, z);

    } else if (selectorValue < (m_lowerBound + m_edgeFalloff)) {
      // Selector is near the lower end of the selector, within the smooth
      // curve. Interpolate between the first input module's value and the
      // second input module's value.
      double lowerCurve = (m_lowerBound - m_edgeFalloff);
      double upperCurve = (m_lowerBound + m_edgeFalloff);
      alpha = SCurve (
        (selectorValue - lowerCurve) / (upperCurve - lowerCurve));
      return LinearInterp (m_pSourceModule[0]->GetValue (x, y, z),
        m_pSourceModule[1]->GetValue (x, y, z),
        alpha);

    } else if (selectorValue < (m_upperBound - m_edgeFalloff)) {
      /// Selector is within the selector threshold; return the second input
      /// module's value.
      return m_pSourceModule[1]->GetValue (x, y, z);

    } else if (selectorValue < (m_upperBound + m_edgeFalloff)) {
      // Selector is near the upper end of the selector, within the smooth
      // curve. Interpolate between the first input module's value and the
      // second input module's value.
      double lowerCurve = (m_upperBound - m_edgeFalloff);
      double upperCurve = (m_upperBound + m_edgeFalloff);
      alpha = SCurve (
        (selectorValue - lowerCurve) / (upperCurve - lowerCurve));
      return LinearInterp (m_pSourceModule[1]->GetValue (x, y, z),
        m_pSourceModule[0]->GetValue (x, y, z),
        alpha);

    } else {
      // Selector is after the selector threshold; return the first input
      // module's value.
      return m_pSourceModule[0]->GetValue (x, y, z);
    }
  } else {
    if (selectorValue < m_lowerBound || selectorValue > m_upperBound) {
      return m_pSourceModule[0]->GetValue (x, y, z);
    } else {
      return m_pSourceModule[1]->GetValue (x, y, z);
    }
  }
}

void Select::SetBounds (double lowerBound, double upperBound)
{
  assert (lowerBound < upperBound);

  m_lowerBound = lowerBound;
  m_upperBound = upperBound;

  // Make sure that the edge falloff curves do not overlap.
  SetEdgeFalloff (m_edgeFalloff);
}

void Select::SetEdgeFalloff (double edgeFalloff)
{
  // Make sure that the edge falloff curves do not overlap.
  double boundSize = m_upperBound - m_lowerBound;
  m_edgeFalloff = (edgeFalloff > boundSize / 2)? boundSize / 2: edgeFalloff;
}
