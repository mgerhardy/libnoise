// spheres.h
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

#ifndef NOISE_MODULE_SPHERES_H
#define NOISE_MODULE_SPHERES_H

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

    /// Default frequency value for the Spheres noise module.
    const double DEFAULT_SPHERES_FREQUENCY = 1.0;

    /// Noise module that outputs concentric spheres.
    ///
    /// @image html modulespheres.png
    ///
    /// This module outputs concentric spheres centered on ( @b 0.0, @b 0.0,
    /// @b 0.0 ), similar to the concentric rings of an onion.
    ///
    /// The first sphere has a radius of @b 1.0.  Each subsequent sphere has a
    /// radius that is @b 1.0 unit larger than the previous sphere.
    ///
    /// The output value from this noise module is determined by the distance
    /// from the the nearest sphere surface.  Input points on the sphere
    /// surface are given the value @b +1.0 and the input points equidistant
    /// from two sphere surfaces are given the value @b -1.0.
    ///
    /// An application can change the <i>frequency</i> of this noise module,
    /// changing the density of the concentric spheres.  Increasing the
    /// frequency increases the density of concentric spheres, reducing the
    /// distances between spheres.  To specify the frequency, call the
    /// SetFrequency() method.
    ///
    /// This noise module, modified with some low-frequency, low-power
    /// turbulence, is useful for generating agate-like textures.
    ///
    /// This noise module does not require any source modules.
    class Spheres: public Module
    {

      public:

        /// Constructor.
        ///
        /// The default frequency is set to ::DEFAULT_SPHERES_FREQUENCY.
        Spheres ();

        /// Returns the frequency of the concentric spheres.
        ///
        /// @returns The frequency of the concentric spheres.
        ///
        /// Increasing the frequency increases the density of concentric
        /// spheres, reducing the distances between spheres.
        double GetFrequency () const
        {
          return m_frequency;
        }

        virtual int GetSourceModuleCount () const
        {
          return 0;
        }

        virtual double GetValue (double x, double y, double z) const;

        /// Sets the frequenct of the concentric spheres.
        ///
        /// @param frequency The frequency of the concentric spheres.
        ///
        /// Increasing the frequency increases the density of concentric
        /// spheres, reducing the distances between spheres.
        void SetFrequency (double frequency)
        {
          m_frequency = frequency;
        }

      protected:

        /// Frequency of the concentric spheres.
        double m_frequency;

    };

    /// @}

    /// @}

    /// @}

  }

}

#endif
