// noisegen.cpp
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

#include "noisegen.h"
#include "interp.h"
#include "vectortable.h"

using namespace noise;

// jas20041019 added
// Specifies the noise generator algorithm.
// - Set to 2 to use the current algorithm.
// - Set to 1 to use the flawed algorithm from the original version of
//   libnoise.
// Change this constant to the appropriate value if your application requires
// noise values that were generated from an earlier version of libnoise.
#define NOISE_VERSION 2

// jas20041019 added
// These constants control the noise generating algorithm.
#if (NOISE_VERSION == 1)
// Constants for the old version of the noise generator.  Because X_NOISE_GEN
// is not relatively prime to the other values, and Z_NOISE_GEN is close to
// 256 (the number of random gradient vectors), patterns show up in high-
// frequency noise.
const int X_NOISE_GEN = 1;
const int Y_NOISE_GEN = 31337;
const int Z_NOISE_GEN = 263;
const int SEED_NOISE_GEN = 1013;
const int SHIFT_NOISE_GEN = 13;
#else
// Constants for the current version of the noise generator.
const int X_NOISE_GEN = 1619;
const int Y_NOISE_GEN = 31337;
const int Z_NOISE_GEN = 6971;
const int SEED_NOISE_GEN = 1013;
const int SHIFT_NOISE_GEN = 8;
#endif

double noise::GradientNoise3D (double x, double y, double z, int ix, int iy,
  int iz, int seed)
{
  // Randomly generate a gradient vector given the input (x, y, z)
  // coordinates.  This implementation generates a random number and
  // uses it as an index into a normalized vector lookup table.
  // jas20040713 modified
  // Gradient noise generation is much quicker now.  We don't call
  // IntValueNoise3D() anymore because it turns out that the vectors
  // themselves are fairly random.
  // jas20041010 modified
  // The multipliers are now constants.
  int vectorIndex = (
      X_NOISE_GEN    * ix
    + Y_NOISE_GEN    * iy
    + Z_NOISE_GEN    * iz
    + SEED_NOISE_GEN * seed)
    & 0xffffffff;
  vectorIndex ^= (vectorIndex >> SHIFT_NOISE_GEN);
  vectorIndex &= 0xff;

  double xvGradient = g_randomVectors[(vectorIndex << 2)    ];
  double yvGradient = g_randomVectors[(vectorIndex << 2) + 1];
  double zvGradient = g_randomVectors[(vectorIndex << 2) + 2];

  // Set up us another vector equal to the distance between the two vectors
  // passed to this function.
  double xvPoint = (x - (double)ix);
  double yvPoint = (y - (double)iy);
  double zvPoint = (z - (double)iz);

  // Now compute the dot product of the gradient vector with the distance
  // vector.  That's our noise value.  Apply a scaling value so that the
  // noise value is within the -1.0 to 1.0 range.
  return ((xvGradient * xvPoint)
    + (yvGradient * yvPoint)
    + (zvGradient * zvPoint)) * 2.12;
}

int noise::IntValueNoise3D (int x, int y, int z, int seed)
{
  // All integer numbers you see (except the bit flags) are primes and must
  // remain prime in order for this noise function to work correctly.
  // jas20041010 modified
  // The prime multipliers are now constants.
  int n = (
      X_NOISE_GEN    * x
    + Y_NOISE_GEN    * y
    + Z_NOISE_GEN    * z
    + SEED_NOISE_GEN * seed)
    & 0x7fffffff;
  n = (n << 13) ^ n;
  return (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
}

double noise::SmoothGradientNoise3D (double x, double y, double z, int seed,
  NoiseQuality noiseQuality)
{
  // Determine the integer coordinates of the eight points surrounding the
  // (x, y, z) point.
  int x0 = (int)(floor (x));
  int x1 = x0 + 1;
  int y0 = (int)(floor (y));
  int y1 = y0 + 1;
  int z0 = (int)(floor (z));
  int z1 = z0 + 1;

  // Map the difference between the integer and floating-point coordinates
  // to an S-curve to produce a smoother noise value.
  // jas20040710 modified
  // Now selectes between different noise qualities.
  double xs, ys, zs;
  switch (noiseQuality) {
    case QUALITY_FAST:
      xs = (x - (double)x0);
      ys = (y - (double)y0);
      zs = (z - (double)z0);
      break;
    case QUALITY_STD:
      xs = SCurve3 (x - (double)x0);
      ys = SCurve3 (y - (double)y0);
      zs = SCurve3 (z - (double)z0);
      break;
    case QUALITY_BEST:
      xs = SCurve5 (x - (double)x0);
      ys = SCurve5 (y - (double)y0);
      zs = SCurve5 (z - (double)z0);
      break;
  }

  // Now calculate the gradient noise values at these eight points and perform
  // trilinear interpolation.
  double n0, n1, ix0, ix1, iy0, iy1;
  n0   = GradientNoise3D (x, y, z, x0, y0, z0, seed);
  n1   = GradientNoise3D (x, y, z, x1, y0, z0, seed);
  ix0  = LinearInterp (n0, n1, xs);
  n0   = GradientNoise3D (x, y, z, x0, y1, z0, seed);
  n1   = GradientNoise3D (x, y, z, x1, y1, z0, seed);
  ix1  = LinearInterp (n0, n1, xs);
  iy0  = LinearInterp (ix0, ix1, ys);
  n0   = GradientNoise3D (x, y, z, x0, y0, z1, seed);
  n1   = GradientNoise3D (x, y, z, x1, y0, z1, seed);
  ix0  = LinearInterp (n0, n1, xs);
  n0   = GradientNoise3D (x, y, z, x0, y1, z1, seed);
  n1   = GradientNoise3D (x, y, z, x1, y1, z1, seed);
  ix1  = LinearInterp (n0, n1, xs);
  iy1  = LinearInterp (ix0, ix1, ys);

  return LinearInterp (iy0, iy1, zs);
}

double noise::SmoothValueNoise3D (double x, double y, double z, int seed,
  NoiseQuality noiseQuality)
{
  // Determine the integer coordinates of the eight points surrounding the
  // (x, y, z) point.
  int x0 = (int)(floor (x));
  int x1 = x0 + 1;
  int y0 = (int)(floor (y));
  int y1 = y0 + 1;
  int z0 = (int)(floor (z));
  int z1 = z0 + 1;

  // Map the difference between the integer and floating-point coordinates
  // to an S-curve to produce a smoother noise value.
  // jas20040710 modified
  // Now selectes between different noise qualities.
  double xs, ys, zs;
  switch (noiseQuality) {
    case QUALITY_FAST:
      xs = (x - (double)x0);
      ys = (y - (double)y0);
      zs = (z - (double)z0);
      break;
    case QUALITY_STD:
      xs = SCurve3 (x - (double)x0);
      ys = SCurve3 (y - (double)y0);
      zs = SCurve3 (z - (double)z0);
      break;
    case QUALITY_BEST:
      xs = SCurve5 (x - (double)x0);
      ys = SCurve5 (y - (double)y0);
      zs = SCurve5 (z - (double)z0);
      break;
  }

  // Now calculate the noise values at these eight points and perform
  // trilinear interpolation.
  double n0, n1, ix0, ix1, iy0, iy1;
  n0   = ValueNoise3D (x0, y0, z0, seed);
  n1   = ValueNoise3D (x1, y0, z0, seed);
  ix0  = LinearInterp (n0, n1, xs);
  n0   = ValueNoise3D (x0, y1, z0, seed);
  n1   = ValueNoise3D (x1, y1, z0, seed);
  ix1  = LinearInterp (n0, n1, xs);
  iy0  = LinearInterp (ix0, ix1, ys);
  n0   = ValueNoise3D (x0, y0, z1, seed);
  n1   = ValueNoise3D (x1, y0, z1, seed);
  ix0  = LinearInterp (n0, n1, xs);
  n0   = ValueNoise3D (x0, y1, z1, seed);
  n1   = ValueNoise3D (x1, y1, z1, seed);
  ix1  = LinearInterp (n0, n1, xs);
  iy1  = LinearInterp (ix0, ix1, ys);
  return LinearInterp (iy0, iy1, zs);
}

double noise::ValueNoise3D (int x, int y, int z, int seed)
{
  return 1.0 - ((double)IntValueNoise3D (x, y, z, seed) / 1073741824.0);
}

