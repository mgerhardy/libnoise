// interp.h
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

#ifndef NOISE_INTERP_H
#define NOISE_INTERP_H

namespace noise
{

  /// @addtogroup libnoise
  /// @{

  /// Performs cubic interpolation between two values.
  ///
  /// @param n0 The value before the first value.
  /// @param n1 The first value.
  /// @param n2 The second value.
  /// @param n3 The value after the second value.
  /// @param a The alpha value.
  ///
  /// @returns The interpolated value.
  ///
  /// The alpha value should lie between @b 0.0 and @b 1.0, inclusive.  If the
  /// alpha value is @b 0.0, this function returns @a n1.  If the alpha value
  /// is @b 1.0, this function returns @a n2.
  inline double CubicInterp (double n0, double n1, double n2, double n3,
    double a)
  {
	  double p = (n3 - n2) - (n0 - n1);
	  double q = (n0 - n1) - p;
	  double r = n2 - n0;
	  double s = n1;
	  return p * a * a * a + q * a * a + r * a + s;
  }

  /// Performs linear interpolation between two values.
  ///
  /// @param n0 The first value.
  /// @param n1 The second value.
  /// @param a The alpha value.
  ///
  /// @returns The interpolated value.
  ///
  /// The alpha value should lie between @b 0.0 and @b 1.0, inclusive.  If the
  /// alpha value is @b 0.0, this function returns @a n0.  If the alpha value
  /// is @b 1.0, this function returns @a n1.
  inline double LinearInterp (double n0, double n1, double a)
  {
    return ((1.0 - a) * n0) + (a * n1);
  }

  /// Maps a value onto an S-curve.
  ///
  /// @param a The value to map onto the S-curve.
  ///
  /// @returns The mapped value.
  ///
  /// The S-curve has the following formula:
  /// <i>a' = 3a<sup>2</sup> - 2a<sup>3</sup></i>
  ///
  /// @a a should lie between @b 0.0 to @b 1.0, inclusive.
  inline double SCurve (double a)
  {
    return (a * a * (3.0 - 2.0 * a));
  }

  // @}

}

#endif
