// turbulence.h
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

#ifndef NOISE_MODULE_TURBULENCE_H
#define NOISE_MODULE_TURBULENCE_H

#include "perlin.h"

namespace noise
{

  namespace module 
  {

    /// @addtogroup libnoise
    /// @{

    /// @addtogroup modules
    /// @{

    /// @addtogroup transformermodules
    /// @{

    /// Default frequency for the Turbulence noise module.
    const double DEFAULT_TURBULENCE_FREQUENCY = DEFAULT_PERLIN_FREQUENCY;

    /// Default power for the Turbulence noise module.
    const double DEFAULT_TURBULENCE_POWER = 1.0;

    /// Default noise seed for the Turbulence noise module.
    const int DEFAULT_TURBULENCE_SEED = DEFAULT_PERLIN_SEED;

    /// Noise module that randomly displaces the input point and returns the
    /// value from the source module at that point.
    ///
    /// @image html moduleturbulence.png
    ///
    /// <i>Turbulence</i> is the pseudo-random displacement of the input
    /// point.  This noise module's GetValue() method randomly displaces the
    /// ( @a x, @a y, @a z ) coordinates of the input point before retrieving
    /// the value from the source module at that point.  To control the
    /// turbulence, an application can modify its <i>frequency</i> and its
    /// <i>power</i>.
    ///
    /// The <i>frequency</i> determines how rapidly the coordinates of the
    /// input point changes by displacement.  To specify the frequency, call
    /// the SetFrequency() method.
    ///
    /// The <i>power</i> determines the scale of the displacement of the input
    /// point.  The power is a scaling value applied to each of the @a x,
    /// @a y, and @a z coordinates of the input point.  To specify the power,
    /// call the SetPower() method.
    ///
    /// Use of this noise module may require some trial and error.  Assuming
    /// you are using a Perlin or Voronoi noise module as the source module,
    /// you should first:
    /// - Set the frequency to the same frequency as the source module.
    /// - Set the power to the reciprocal of the frequency.
    ///
    /// From these initial frequency and power values, modify these values
    /// until this noise module produce the desired changes in your terrain or
    /// texture.  For example:
    /// - Low frequency (1/8 initial frequency) and low power (1/8 initial
    ///   power) produces very minor, almost unnoticeable changes.
    /// - Low frequency (1/8 initial frequency) and high power (8 times
    ///   initial power) produces "ropey" lava-like terrain or marble-like
    ///   textures.
    /// - High frequency (8 times initial frequency) and low power (1/8
    ///   initial power) produces a noisy version of the initial terrain or
    ///   texture.
    /// - High frequency (8 times initial frequency) and high power (8 times
    ///   initial power) produces nearly pure noise, which isn't entirely
    ///   useful.
    ///
    /// Displacing the points results in more realistic terrain and textures.
    /// If you are generating elevations for terrain heightmaps, you can use
    /// this module to produce more realistic mountain ranges or terrain
    /// features that look like flowing lava rock.  If you are generating
    /// values for textures, you can use this module to produce realistic
    /// marble-like or "oily" textures.
    ///
    /// Internally, this module uses three Perlin noise modules: one
    /// module displaces the @a x coordinate, one displaces the @a y
    /// coordinate, and one displaces the @a z coordinate.
    ///
    /// This noise module requires one source module.
    class Turbulence: public Module
    {

      public:

        /// Constructor.
        ///
        /// The default frequency is set to ::DEFAULT_TURBULENCE_FREQUENCY.
        ///    
        /// The default power is set to ::DEFAULT_TURBULENCE_POWER.
        ///
        /// The default seed value is set to ::DEFAULT_TURBULENCE_SEED.
        Turbulence ();

        /// Returns the frequency of the turbulence.
        ///
        /// @returns The frequency of the turbulence.
        ///
        /// The frequency determines how rapidly the coordinates of the input
        /// point changes by displacement.
        double GetFrequency () const;

        /// Returns the power of the turbulence.
        ///
        /// @returns The power of the turbulence.
        ///
        /// The power determines the scale of the displacement of the input
        /// point.
        double GetPower () const
        {
          return m_power;
        }

        /// Returns the seed value of the internal noise modules used to
        /// displace the input points.
        ///
        /// @returns The seed.
        int GetSeed () const;

        virtual int GetSourceModuleCount () const
        {
          return 1;
        }

        virtual double GetValue (double x, double y, double z) const;

        /// Sets the frequency of the turbulence.
        ///
        /// @param frequency The frequency of the turbulence.
        ///
        /// The frequency determines how rapidly the coordinates of the input
        /// point changes by displacement.
        void SetFrequency (double frequency);

        /// Sets the power of the turbulence.
        ///
        /// @param power The power of the turbulence.
        ///
        /// The power determines the scale of the displacement of the input
        /// point.
        void SetPower (double power)
        {
          m_power = power;
        }

        /// Sets the seed value of the internal noise modules used to displace
        /// the input points.
        ///
        /// @param seed The seed.
        ///
        /// Internally, there are three Perlin modules that displace the input
        /// point; one for the @a x, one for the @a y, and one for the @a z
        /// coordinate.  This noise module assigns the following seeds to the
        /// Perlin module:
        /// - The module assigns the seed value to the @a x module.
        /// - The module assigns the seed value plus one to the @a y module.
        /// - The module assigns the seed value plus two to the @a z module.
        void SetSeed (int seed);

      protected:

        /// The power (scale) of the displacement.
        double m_power;

        /// Noise module that displaces the @a x coordinate.
        Perlin m_xDistortModule;

        /// Noise module that displaces the @a y coordinate.
        Perlin m_yDistortModule;

        /// Noise module that displaces the @a z coordinate.
        Perlin m_zDistortModule;

    };

    /// @}

    /// @}

    /// @}

  }

}

#endif
