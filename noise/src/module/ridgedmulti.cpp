// ridgedmulti.cpp
//
// Version 0.1.4 - 2004-07-10
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

#include "ridgedmulti.h"

using namespace noise::module;

RidgedMulti::RidgedMulti ():
  Module (GetSourceModuleCount ()),
  m_octaveCount  (DEFAULT_RIDGED_OCTAVE_COUNT),
  m_frequency    (DEFAULT_RIDGED_FREQUENCY   ),
  m_lacunarity   (DEFAULT_RIDGED_LACUNARITY  ),
  m_noiseQuality (DEFAULT_RIDGED_QUALITY     ),
  m_seed         (DEFAULT_RIDGED_SEED)
{
}

// Multifractal code originally written by F. Kenton "Doc Mojo" Musgrave,
// 1998.  Modified by jas for use with libnoise.
double RidgedMulti::GetValue (double x, double y, double z) const
{
  x *= m_frequency;
  y *= m_frequency;
  z *= m_frequency;
  double value = 0.0;
  double weight = 1.0;
  const double offset = 0.75; // Seems to produce the best results.

  // jas20040710 modified
  // This function was erroneously generating one less octave.
  for (int curOctave = 0; curOctave < m_octaveCount; curOctave++) {
    
    // Make sure that these floating-point values have the same range as a 32-
    // bit integer so that we can pass them to the noise functions.
    double nx, ny, nz;
    nx = MakeInt32Range (x);
    ny = MakeInt32Range (y);
    nz = MakeInt32Range (z);

    // Get the noise value from the (x, y, z) position and add it to the final
    // result.
    // jas20040710 modified
    // Added noise quality.
    int seed = (m_seed + curOctave) & 0x7fffffff;
    double signal = SmoothGradientNoise3D (nx, ny, nz, seed, m_noiseQuality);
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
