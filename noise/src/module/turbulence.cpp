// turbulence.cpp
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

#include "turbulence.h"

using namespace noise::module;

Turbulence::Turbulence ():
  Module (GetSourceModuleCount ()),
  m_power (DEFAULT_TURBULENCE_POWER)
{
  SetSeed (DEFAULT_TURBULENCE_SEED);
  SetFrequency (DEFAULT_TURBULENCE_FREQUENCY);
}

double Turbulence::GetFrequency () const
{
  // Since each ModulePerlin noise module has the same frequency, it does not
  // matter which module we use to retrieve the frequency.
  return m_xDistortModule.GetFrequency ();
}

int Turbulence::GetSeed () const
{
  return m_xDistortModule.GetSeed ();
}

double Turbulence::GetValue (double x, double y, double z) const
{
  assert (m_pSourceModule[0] != NULL);

  // Get the values from the three ModulePerlin noise modules and add each
  // value to each coordinate of the input point.
  double xDistort = x + (m_xDistortModule.GetValue (x, y, z) * m_power);
  double yDistort = y + (m_yDistortModule.GetValue (x, y, z) * m_power);
  double zDistort = z + (m_zDistortModule.GetValue (x, y, z) * m_power);

  // Retrieve the value at the offsetted input coordinates instead of the
  // original input coordinates
  return m_pSourceModule[0]->GetValue (xDistort, yDistort, zDistort);
}

void Turbulence::SetFrequency (double frequency)
{
  // Set the frequency of each ModulePerlin noise modules.
  m_xDistortModule.SetFrequency (frequency);
  m_yDistortModule.SetFrequency (frequency);
  m_zDistortModule.SetFrequency (frequency);
}

void Turbulence::SetSeed (int seed)
{
  // Set the seed of each ModulePerlin noise modules.  To prevent any sort of
  // weird artifacting, use a slightly different seed for each noise module.
  m_xDistortModule.SetSeed (seed    );
  m_yDistortModule.SetSeed (seed + 1);
  m_zDistortModule.SetSeed (seed + 2);
}
