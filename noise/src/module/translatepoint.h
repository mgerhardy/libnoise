// translatepoint.h
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

#ifndef NOISE_MODULE_TRANSLATEPOINT_H
#define NOISE_MODULE_TRANSLATEPOINT_H

#include "modulebase.h"

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

    /// Default translation value to add to the @a x coordinate for the
    /// TranslatePoint noise module.
    const double DEFAULT_TRANSLATE_POINT_X = 0.0;

    /// Default translation value to add to the @a y coordinate for the
    /// TranslatePoint noise module.
    const double DEFAULT_TRANSLATE_POINT_Y = 0.0;

    /// Default translation value to add to the @a z coordinate for the
    /// TranslatePoint noise module.
    const double DEFAULT_TRANSLATE_POINT_Z = 0.0;

    /// Noise module that moves the input point and returns the value from
    /// the source module at that point.
    ///
    /// @image html moduletranslatepoint.png
    ///
    /// This module's GetValue() method moves the ( @a x, @a y, @a z )
    /// coordinates of the input point by a translation amount before
    /// returning the value from the source module at that point.  To set the
    /// translation values, call the SetTranslation() method.  To set the
    /// translation value of the individual @a x, @a y, or @a z coordinates,
    /// call the SetXTranslation(), SetYTranslation(), and SetZTranslation()
    /// methods, respectively.
    ///
    /// This noise module requires one source module.
    class TranslatePoint: public Module
    {

      public:

        /// Constructor.
        ///
        /// The default translation value to add to the @a x coordinate is set
        /// to ::DEFAULT_TRANSLATE_POINT_X.
        ///
        /// The default translation value to add to the @a y coordinate is set
        /// to ::DEFAULT_TRANSLATE_POINT_Y.
        ///
        /// The default translation value to add to the @a z coordinate is set
        /// to ::DEFAULT_TRANSLATE_POINT_Z.
        TranslatePoint ();

        virtual int GetSourceModuleCount () const
        {
          return 1;
        }

        virtual double GetValue (double x, double y, double z) const;

        /// Returns the translation value to add to the @a x coordinate of the
        /// input point.
        ///
        /// @returns The translation value to add to the @a x coordinate.
        double GetXTranslation () const
        {
          return m_xTranslation;
        }

        /// Returns the translation value to add to the @a y coordinate of the
        /// input point.
        ///
        /// @returns The translation value to add to the @a y coordinate.
        double GetYTranslation () const
        {
          return m_yTranslation;
        }

        /// Returns the translation value to add to the @a z coordinate of the
        /// input point.
        ///
        /// @returns The translation value to add to the @a z coordinate.
        double GetZTranslation () const
        {
          return m_zTranslation;
        }

        /// Sets the translation values to add to the ( @a x, @a y, @a z )
        /// coordinates of the input point.
        ///
        /// @param xTranslation The translation value to add to the @a x
        /// coordinate.
        /// @param yTranslation The translation value to add to the @a y
        /// coordinate.
        /// @param zTranslation The translation value to add to the @a z
        /// coordinate.
        ///
        /// This module's GetValue() method moves the ( @a x, @a y, @a z )
        /// coordinates of the input point by a translation amount before
        /// returning the value of the source module at that point.
        void SetTranslation (double xTranslation, double yTranslation,
          double zTranslation)
        {
          m_xTranslation = xTranslation;
          m_yTranslation = yTranslation;
          m_zTranslation = zTranslation;
        }

        /// Sets the translation values to add to the @a x coordinate of the
        /// input point.
        ///
        /// @param xTranslation The translation value to add to the @a x
        /// coordinate.
        ///
        /// This module's GetValue() method moves the ( @a x, @a y, @a z )
        /// coordinates of the input point by a translation amount before
        /// returning the value of the source module at that point.
        void SetXTranslation (double xTranslation)
        {
          m_xTranslation = xTranslation;
        }

        /// Sets the translation values to add to the @a y coordinate of the
        /// input point.
        ///
        /// @param yTranslation The translation value to add to the @a y
        /// coordinate.
        ///
        /// This module's GetValue() method moves the ( @a x, @a y, @a z )
        /// coordinates of the input point by a translation amount before
        /// returning the value of the source module at that point.
        void SetYTranslation (double yTranslation)
        {
          m_yTranslation = yTranslation;
        }

        /// Sets the translation values to add to the @a z coordinate of the
        /// input point.
        ///
        /// @param zTranslation The translation value to add to the @a x
        /// coordinate.
        ///
        /// This module's GetValue() method moves the ( @a x, @a y, @a z )
        /// coordinates of the input point by a translation amount before
        /// returning the value of the source module at that point.
        void SetZTranslation (double zTranslation)
        {
          m_zTranslation = zTranslation;
        }

      protected:

        /// Translation value added to the @a x coordinate of the input point.
        double m_xTranslation;

        /// Translation value added to the @a y coordinate of the input point.
        double m_yTranslation;

        /// Translation value added to the @a z coordinate of the input point.
        double m_zTranslation;

    };

    /// @}

    /// @}

    /// @}

  }

}

#endif
