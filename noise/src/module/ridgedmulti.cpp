// ridgedmulti.cpp
//
// Version 0.1.1 - 2004-03-04
// - Changed GetNumSourceModules() to GetSourceModuleCount() for consistency.
// - Changed m_numOctaves to m_octaveCount for consistency.
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

#include "../noisegen.h"
#include "ridgedmulti.h"

using namespace noise::module;

RidgedMulti::RidgedMulti ():
  Module (GetSourceModuleCount ()),
  m_octaveCount (DEFAULT_RIDGED_OCTAVE_COUNT),
  m_frequency   (DEFAULT_RIDGED_FREQUENCY   ),
  m_lacunarity  (DEFAULT_RIDGED_LACUNARITY  ),
  m_seed        (DEFAULT_RIDGED_SEED)
{
}

double RidgedMulti::GetValue (double x, double y, double z) const
{
  // Multifractal code originally written by F. Kenton "Doc Mojo" Musgrave,
  // 1998.  Modified by jas for use with libnoise.

  const double offset = 0.8; // Seems to produce the best results.
  double value = 0.0;
  double signal = 0.0;
  double weight = 1.0;
  int seed;

  x *= m_frequency;
  y *= m_frequency;
  z *= m_frequency;

  for (int curOctave = 1; curOctave < m_octaveCount; curOctave++) {

    // Make sure that these floating-point values have the same range as a 32-
    // bit integer so that we can pass them to the noise functions.
    double nx, ny, nz;
    nx = MakeInt32Range (x);
    ny = MakeInt32Range (y);
    nz = MakeInt32Range (z);

    // Get the noise value from the (x, y, z) position and add it to the final
    // result.
    seed = (m_seed + curOctave) & 0x7fffffff;
    signal = SmoothGradientNoise3D (nx, ny, nz, seed);
    signal = fabs (signal);
    signal = offset - signal;
    signal *= weight;
    value += signal;

    // Prepare the next octave.
    x *= m_lacunarity;
    y *= m_lacunarity;
    z *= m_lacunarity;
    weight = signal;
    if (weight > 1.0) {
      weight = 1.0;
    }
    if (weight < 0.0) {
      weight = 0.0;
    }
  }

  // A value is usually in the 0.0 to 2.0 range.  Apply a bias to get the
  // value to the -1.0 to +1.0 range like standard Perlin noise.
  value -= 1.0;

  return value;
}
