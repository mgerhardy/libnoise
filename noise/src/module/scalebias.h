// scalebias.h
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

#ifndef NOISE_MODULE_SCALEBIAS_H
#define NOISE_MODULE_SCALEBIAS_H

#include "modulebase.h"

namespace noise
{

  namespace module
  {

    /// @addtogroup libnoise
    /// @{

    /// @addtogroup modules
    /// @{

    /// @addtogroup modifiermodules
    /// @{

    /// Default bias for the ScaleBias noise module.
    const double DEFAULT_BIAS = 0.0;

    /// Default scale for the ScaleBias noise module.
    const double DEFAULT_SCALE = 1.0;

    /// Noise module that scales a value from the source module and applies a
    /// bias to the scaled value.
    ///
    /// @image html modulescalebias.png
    ///
    /// This noise module multiplies the value from the source module with the
    /// scaling value, adds the bias to the scaled value, and then outputs that
    /// value.
    ///
    /// This noise module requires one source module.
    class ScaleBias: public Module
    {

      public:

        /// Constructor.
        ///
        /// The default bias is set to ::DEFAULT_BIAS.
        ///
        /// The default scale is set to ::DEFAULT_SCALE.
        ScaleBias ();

        /// Returns the bias to apply to the scaled value from the source
        /// module.
        ///
        /// @returns The bias to apply.
        ///
        /// The bias is a constant value that is added to a scaled value from
        /// the source module.
        double GetBias () const
        {
          return m_bias;
        }

        /// Returns the scaling value to apply to the value from the source
        /// module.
        ///
        /// @returns The scaling value to apply.
        ///
        /// The scaling value is a constant value that is multiplied with the
        /// value from the source module.  This noise module applies the
        /// scaling value befor applying the bias.
        double GetScale () const
        {
          return m_scale;
        }

        virtual int GetSourceModuleCount () const
        {
          return 1;
        }

        virtual double GetValue (double x, double y, double z) const;

        /// Sets the bias to apply to the scaled value from the source module.
        ///
        /// @param bias The bias to apply.
        ///
        /// The bias is a constant value that is added to a scaled value from
        /// the source module.
        void SetBias (double bias)
        {
          m_bias = bias;
        }

        /// Sets the scaling value to apply to the value from the source
        /// module.
        ///
        /// @param scale The scaling value to apply.
        ///
        /// The scaling value is a constant value that is multiplied with a
        /// value from the source module.  This noise module applies the
        /// scaling value befor applying the bias.
        void SetScale (double scale)
        {
          m_scale = scale;
        }

      protected:

        /// Bias to apply to the scaled value from the source module.
        double m_bias;

        /// Scaling value to apply to the value from the source module.
        double m_scale;

    };

    /// @}

    /// @}

    /// @}

  }

}

#endif
