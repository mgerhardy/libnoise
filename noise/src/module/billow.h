// billow.h
//
// Copyright (C) 2004 by Jason Bevins
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

#ifndef NOISE_MODULE_BILLOW_H
#define NOISE_MODULE_BILLOW_H

#include "modulebase.h"

namespace noise
{

  namespace module
  {

    /// @addtogroup libnoise
    /// @{

    /// @addtogroup modules
    /// @{

    /// @addtogroup generatormodules
    /// @{

    /// Default frequency for the Billow noise module.
    const double DEFAULT_BILLOW_FREQUENCY = 1.0;

    /// Default lacunarity for the Billow noise module.
    const double DEFAULT_BILLOW_LACUNARITY = 2.0;

    /// Default number of octaves for the Billow noise module.
    const int DEFAULT_BILLOW_OCTAVE_COUNT = 6;

    /// Default persistence for the Billow noise module.
    const double DEFAULT_BILLOW_PERSISTENCE = 0.5;

    /// Default noise quality for the Billow noise module.
    const noise::NoiseQuality DEFAULT_BILLOW_QUALITY = QUALITY_STD;

    /// Default noise seed for the Billow noise module.
    const int DEFAULT_BILLOW_SEED = 0;

    /// Maximum number of octaves for the Billow noise module.
    const int BILLOW_MAX_OCTAVE = 30;

    /// Noise module that outputs "billowy" noise.
    ///
    /// @image html modulebillow.png
    ///
    /// This module creates "billowy" noise suitable for clouds and rocks.
    ///
    /// This module is nearly identical to module::Perlin except this module
    /// modifies each octave with an absolute-value function.  See the
    /// documentation of module::Perlin for more information.
    class Billow: public Module
    {

      public:

        /// Constructor.
        ///
        /// The default frequency is set to ::DEFAULT_BILLOW_FREQUENCY.
        ///
        /// The default lacunarity is set to ::DEFAULT_BILLOW_LACUNARITY.
        ///
        /// The default number of octaves is set to
        /// ::DEFAULT_BILLOW_OCTAVE_COUNT.
        ///
        /// The default persistence is set to ::DEFAULT_BILLOW_PERSISTENCE.
        ///
        /// The default seed value is set to ::DEFAULT_BILLOW_SEED.
        Billow ();

        /// Returns the frequency of the first octave.
        ///
        /// @returns The frequency of the first octave.
        double GetFrequency () const
        {
          return m_frequency;
        }

        /// Returns the lacunarity of the billowy noise.
        ///
        /// @returns The lacunarity of the billowy noise.
        /// 
        /// The lacunarity is the frequency multiplier between successive
        /// octaves.
        double GetLacunarity () const
        {
          return m_lacunarity;
        }

        /// Returns the quality of the billowy noise.
        ///
        /// @returns The quality of the billowy noise.
        ///
        /// See noise::NoiseQuality for definitions of the various noise
        /// qualities.
        noise::NoiseQuality GetNoiseQuality () const
        {
          return m_noiseQuality;
        }

        /// Returns the number of octaves used to generate the billowy noise.
        ///
        /// @returns The number of octaves used to generate the billowy noise.
        ///
        /// The number of octaves controls the amount of detail in the billowy
        /// noise.
        int GetOctaveCount () const
        {
          return m_octaveCount;
        }

        /// Returns the persistence of the billowy noise.
        ///
        /// @returns The persistence of the billowy noise.
        ///
        /// The persistence controls the roughness of the billowy noise.
        double GetPersistence () const
        {
          return m_persistence;
        }

        /// Returns the seed value used by the smooth noise function.
        ///
        /// @returns The seed value.
        int GetSeed () const
        {
          return m_seed;
        }

        virtual int GetSourceModuleCount () const
        {
          return 0;
        }

        virtual double GetValue (double x, double y, double z) const;

        /// Sets the frequency of the first octave.
        ///
        /// @param frequency The frequency of the first octave.
        void SetFrequency (double frequency)
        {
          m_frequency = frequency;
        }

        /// Sets the lacunarity of the billowy noise.
        ///
        /// @param lacunarity The lacunarity of the billowy noise.
        /// 
        /// The lacunarity is the frequency multiplier between successive
        /// octaves.
        ///
        /// For best results, set the lacunarity to a number between @b 1.5
        /// and @b 3.5.
        void SetLacunarity (double lacunarity)
        {
          m_lacunarity = lacunarity;
        }

        /// Sets the quality of the billowy noise.
        ///
        /// @param noiseQuality The quality of the billowy noise.
        ///
        /// See noise::NoiseQuality for definitions of the various noise
        /// qualities.
        void SetNoiseQuality (noise::NoiseQuality noiseQuality)
        {
          m_noiseQuality = noiseQuality;
        }

        /// Sets the number of octaves used to generate the billowy noise.
        ///
        /// @param octaveCount The number of octaves used to generate the
        /// billowy noise.
        ///
        /// @pre The number of octaves is between 1 and ::BILLOW_MAX_OCTAVE,
        /// inclusive.
        ///
        /// @throw NoiseEx
        /// - @a EX_INVALID_PARAM: An invalid parameter was specified; see the
        ///   preconditions for more information.
        ///
        /// The number of octaves controls the amount of detail in the billowy
        /// noise.
        ///
        /// The larger the number of octaves, the more time required to
        /// calculate the billowy noise.
        void SetOctaveCount (int octaveCount)
        {
          if (octaveCount < 1 || octaveCount > BILLOW_MAX_OCTAVE) {
            throw EX_INVALID_PARAM;
          }
          m_octaveCount = octaveCount;
        }

        /// Sets the persistence of the billowy noise.
        ///
        /// @param persistence The persistence of the billowy noise.
        ///
        /// The persistence controls the roughness of the billowy noise.
        ///
        /// For best results, set the persistence to a number between @b 0.0
        /// and @b 1.0.
        void SetPersistence (double persistence)
        {
          m_persistence = persistence;
        }

        /// Sets the seed value used by the smooth noise function.
        ///
        /// @param seed The seed value.
        void SetSeed (int seed)
        {
          m_seed = seed;
        }

      protected:

        /// Frequency of the first octave.
        double m_frequency;

        /// Frequency multiplier between successive octaves.
        double m_lacunarity;

        /// Quality of the noise.
        noise::NoiseQuality m_noiseQuality;

        /// Total number of octaves that are used to generate the billowy
        /// noise.
        int m_octaveCount;

        /// Persistence of the billowy noise.
        double m_persistence;

        /// Seed value used by the smooth noise function.
        int m_seed;

    };

    /// @}

    /// @}

    /// @}

  }

}

#endif
