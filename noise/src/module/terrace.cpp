// terrace.cpp
//
// Version 0.1.3 - 2004-06-03
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
#include "../misc.h"
#include "terrace.h"

using namespace noise::module;

using namespace noise;

Terrace::Terrace ():
  Module (GetSourceModuleCount ()),
  m_pTerracePoints (NULL),
  m_terracePointCount (0),
  m_invertTerraces (false)
{
}

Terrace::~Terrace ()
{
  delete[] m_pTerracePoints;
}

void Terrace::AddTerracePoint (double value)
{
  // Find the insertion point for the new terracing point and insert the new
  // point at that position.  The terracing point array will remain sorted by
  // value.
  int insertionPos = FindInsertionPos (value);
  InsertAtPos (insertionPos, value);
}

void Terrace::ClearAllTerracePoints ()
{
  delete[] m_pTerracePoints;
  m_pTerracePoints = NULL;
  m_terracePointCount = 0;
}

int Terrace::FindInsertionPos (double value)
{
  int insertionPos;
  for (insertionPos = 0; insertionPos < m_terracePointCount; insertionPos++) {
    if (value < m_pTerracePoints[insertionPos]) {
      // We found the array index in which to insert the new terracing point.
      // Exit now.
      break;
    } else if (value == m_pTerracePoints[insertionPos]) {
      // Each terracing point is required to contain a unique value, so throw
      // an exception.
      throw EX_INVALID_PARAM;
    }
  }
  return insertionPos;
}

double Terrace::GetValue (double x, double y, double z) const
{
  assert (m_pSourceModule[0] != NULL);
  assert (m_terracePointCount >= 2);

  // Get the value from the source module.
  double sourceModuleValue = m_pSourceModule[0]->GetValue (x, y, z);

  // Find the first element in the terracing point array that has a value
  // larger than the value from the source module.
  int indexPos;
  for (indexPos = 0; indexPos < m_terracePointCount; indexPos++) {
    if (sourceModuleValue < m_pTerracePoints[indexPos]) {
      break;
    }
  }

  // Find the two nearest terracing points so that we can map their values
  // onto a quadratic curve.
  int index0 = ClampValue (indexPos - 1, 0, m_terracePointCount - 1);
  int index1 = ClampValue (indexPos    , 0, m_terracePointCount - 1);

  // If some terracing points are missing (which occurs if the value from the
  // source module is greater than the largest value or less than the smallest
  // value of the terracing point array), get the value of the nearest
  // terracing point and exit now.
  if (index0 == index1) {
    return m_pTerracePoints[index1];
  }
  
  // Compute the alpha value used for linear interpolation.
  double value0 = m_pTerracePoints[index0];
  double value1 = m_pTerracePoints[index1];
  double alpha = (sourceModuleValue - value0) / (value1 - value0);
  if (m_invertTerraces) {
    alpha = 1.0 - alpha;
    SwapValues (value0, value1);
  }

  // Squaring the alpha produces the terracing effect.
  alpha *= alpha;

  // Now perform the linear interpolation given the alpha value.
  return LinearInterp (value0, value1, alpha);
}

void Terrace::InsertAtPos (int insertionPos, double value)
{
  // Make room for the new terracing point at the specified position within
  // the terracing point array.  The position is determined by the value of
  // the terracing point; the terracing points must be sorted by value within
  // that array.
  double* newTerracePoints = new double[m_terracePointCount + 1];
  for (int i = 0; i < m_terracePointCount; i++) {
    if (i < insertionPos) {
      newTerracePoints[i] = m_pTerracePoints[i];
    } else {
      newTerracePoints[i + 1] = m_pTerracePoints[i];
    }
  }
  delete[] m_pTerracePoints;
  m_pTerracePoints = newTerracePoints;
  ++m_terracePointCount;

  // Now that we've made room for the new terracing point within the array,
  // add the new terracing point.
  m_pTerracePoints[insertionPos] = value;
}

void Terrace::MakeTerracePoints (noise::int8 terracePointCount)
{
  if (terracePointCount < 2) {
    throw EX_INVALID_PARAM;
  }

  ClearAllTerracePoints ();

  double terraceStep = 2.0 / ((double)terracePointCount - 1.0);
  double curValue = -1.0;
  for (int i = 0; i < (int)terracePointCount; i++) {
    AddTerracePoint (curValue);
    curValue += terraceStep;
  }
}
