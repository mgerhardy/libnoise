// noisegen.h
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

#ifndef NOISE_NOISEGEN_H
#define NOISE_NOISEGEN_H

#include <math.h>
#include "basictypes.h"

namespace noise
{

  /// @addtogroup libnoise
  /// @{

  /// Returns a floating-point gradient noise value.
  ///
  /// @param x The floating-point @a x coordinate of the 3D point.
  /// @param y The floating-point @a y coordinate of the 3D point.
  /// @param z The floating-point @a z coordinate of the 3D point.
  /// @param ix The integer @a x coordinate of a nearby 3D point.
  /// @param iy The integer @a y coordinate of a nearby 3D point.
  /// @param iz The integer @a z coordinate of a nearby 3D point.
  /// @param seed The random number seed.
  ///
  /// @returns The noise value.
  ///
  /// @pre The distance from the integer coordinates of the point ( @a ix,
  /// @a iy, @a iz ) to the corresponding floating-point coordinates of the
  /// point ( @a x, @a y, @a z ) must be less than or equal to one.
  ///
  /// <i>Gradient</i> noise produces more variation in the noise than the
  /// <i>value</i> noise functions.  Most noise modules use gradient noise for
  /// this reason, although gradient noise takes much longer to calculate than
  /// value noise.
  ///
  /// The returned noise value ranges from @b -1.0 to @b +1.0.
  ///
  /// This function calculates a gradient noise value by performing the
  /// following three steps:
  /// - This function calculates a random normalized vector based on the
  ///   integer point passed to this function.
  /// - This function applies this vector to the integer point passed to this
  ///   function.
  /// - The function calculates the dot product of the offset point and the
  ///   floating-point point.
  ///
  /// A noise function differs from a random-number generator in that the same
  /// value is returned if you pass in the same values.
  double GradientNoise3D (double x, double y, double z, int ix, int iy,
    int iz, int seed = 0);

  /// Returns an integer noise value.
  ///
  /// @param x The integer @a x coordinate of the 3D point.
  /// @param y The integer @a y coordinate of the 3D point.
  /// @param z The integer @a z coordinate of the 3D point.
  /// @param seed A random number seed.
  ///
  /// @returns The noise value.
  ///
  /// The noise value ranges from @b 0 to @b 2147483647.
  ///
  /// A noise function differs from a random-number generator in that the same
  /// value is returned if you pass in the same values.
  int IntValueNoise3D (int x, int y, int z, int seed = 0);

  /// Modifies a floating-point value such that the resulting value can be
  /// stored in an ::int32 variable.
  ///
  /// @param n A floating-point number.
  ///
  /// @returns The modified floating-point number.
  ///
  /// In libnoise, the noise algorithms are all integer-based using ::int32
  /// variables.  Before calling a noise function, pass the @a x, @a y, and
  /// @a z coordinates to this function to ensure that these coordinates can
  /// be cast to an ::int32 value.
  ///
  /// Although you could do a straight cast from double to ::int32, the
  /// resulting value may differ between platforms.  By using this function,
  /// you ensure that the resulting value is identical between platforms.
  inline double MakeInt32Range (double n)
  {
    if (n >= 1073741824.0) {
      return (2.0 * fmod (n, 1073741824.0)) - 1073741824.0;
    } else if (n <= -1073741824.0) {
      return (2.0 * fmod (n, 1073741824.0)) + 1073741824.0;
    } else {
      return n;
    }
  }

  /// Returns a smoothly-interpolated gradient noise value.
  ///
  /// @param x The @a x coordinate of the 3D point.
  /// @param y The @a y coordinate of the 3D point.
  /// @param z The @a z coordinate of the 3D point.
  /// @param seed The random number seed.
  ///
  /// @returns The random value.
  ///
  /// For an explanation of the difference between gradient noise and value
  /// noise, see the comments for the GradientNoise3D() function.
  double SmoothGradientNoise3D (double x, double y, double z, int seed = 0);

  /// Returns a smoothly-interpolated noise value.
  ///
  /// @param x The @a x coordinate of the 3D point.
  /// @param y The @a y coordinate of the 3D point.
  /// @param z The @a z coordinate of the 3D point.
  /// @param seed The random number seed.
  ///
  /// @returns The random value.
  ///
  /// For an explanation of the difference between gradient noise and value
  /// noise, see the comments for the GradientNoise3D() function.
  double SmoothValueNoise3D (double x, double y, double z, int seed = 0);

  /// Returns a floating-point noise value.
  ///
  /// @param x The integer @a x coordinate of the 3D point.
  /// @param y The integer @a y coordinate of the 3D point.
  /// @param z The integer @a z coordinate of the 3D point.
  /// @param seed A random number seed.
  ///
  /// @returns The noise value.
  ///
  /// The returned noise value ranges from @b -1.0 to @b +1.0.
  ///
  /// A noise function differs from a random-number generator in that the same
  /// value is returned if you pass in the same values.
  double ValueNoise3D (int x, int y, int z, int seed = 0);

  /// @}

}

#endif
