// perlin.cpp
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

#include "perlin.h"

using namespace noise::module;

Perlin::Perlin ():
  Module (GetSourceModuleCount ()),
  m_octaveCount  (DEFAULT_PERLIN_OCTAVE_COUNT),
  m_frequency    (DEFAULT_PERLIN_FREQUENCY   ),
  m_lacunarity   (DEFAULT_PERLIN_LACUNARITY  ),
  m_noiseQuality (DEFAULT_PERLIN_QUALITY     ),
  m_persistence  (DEFAULT_PERLIN_PERSISTENCE ),
  m_seed         (DEFAULT_PERLIN_SEED)
{
}

double Perlin::GetValue (double x, double y, double z) const
{
  double value = 0.0;
  double signal = 0.0;
  double curPersistence = 1.0;
  double nx, ny, nz;
  int seed;

  x *= m_frequency;
  y *= m_frequency;
  z *= m_frequency;

  for (int curOctave = 0; curOctave < m_octaveCount; curOctave++) {

    // Make sure that these floating-point values have the same range as a 32-
    // bit integer so that we can pass them to the noise functions.
    nx = MakeInt32Range (x);
    ny = MakeInt32Range (y);
    nz = MakeInt32Range (z);

    // Get the noise value from the (x, y, z) position and add it to the final
    // result.
    // jas20040710 modified
    // Added noise quality.
    seed = (m_seed + curOctave) & 0xffffffff;
    signal = SmoothGradientNoise3D (nx, ny, nz, seed, m_noiseQuality);
    value += signal * curPersistence;

    // Prepare the next octave.
    x *= m_lacunarity;
    y *= m_lacunarity;
    z *= m_lacunarity;
    curPersistence *= m_persistence;
  }

  return value;
}
