// rotatepoint.h
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

#ifndef NOISE_MODULE_ROTATEPOINT_H
#define NOISE_MODULE_ROTATEPOINT_H

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

    /// Default @a x rotation angle for the RotatePoint noise module.
    const double DEFAULT_ROTATE_X = 0.0;

    /// Default @a y rotation angle for the RotatePoint noise module.
    const double DEFAULT_ROTATE_Y = 0.0;

    /// Default @a z rotation angle for the RotatePoint noise module.
    const double DEFAULT_ROTATE_Z = 0.0;

    /// Noise module that rotates the input point around the origin and
    /// returns the value from the source module at that point.
    ///
    /// @image html modulerotatepoint.png
    ///
    /// This module's GetValue() method rotates the coordinates of the
    /// input point around the origin before returning the value from the
    /// source module at that point.  To set the rotation angles, call the
    /// SetAngles() method.  To set the rotation angle around the individual
    /// @a x, @a y, or @a z axes, call the SetXAngle(), SetYAngle() or
    /// SetZAngle() methods, respectively.
    ///
    /// The input point is assumed to be in the left-handed coordinate
    /// system (@a x increases to the right, @a y increases upward, and @a z
    /// increases inward.)
    ///
    /// This noise module requires one source module.
    class RotatePoint: public Module
    {

      public:

        /// Constructor.
        ///
        /// The default rotation angle around the @a x axis, in degrees, is
        /// set to ::DEFAULT_ROTATE_X.
        ///
        /// The default rotation angle around the @a y axis, in degrees, is
        /// set to ::DEFAULT_ROTATE_Y.
        ///
        /// The default rotation angle around the @a z axis, in degrees, is
        /// set to ::DEFAULT_ROTATE_Z.
        RotatePoint ();

        virtual int GetSourceModuleCount () const
        {
          return 1;
        }

        virtual double GetValue (double x, double y, double z) const;

        /// Returns the rotation angle around the @a x axis to apply to the
        /// input point.
        ///
        /// @returns The rotation angle around the @a x axis, in degrees.
        double GetXAngle () const
        {
          return m_xAngle;
        }

        /// Returns the rotation angle around the @a y axis to apply to the
        /// input point.
        ///
        /// @returns The rotation angle around the @a y axis, in degrees.
        double GetYAngle () const
        {
          return m_yAngle;
        }

        /// Returns the rotation angle around the @a z axis to apply to the
        /// input point.
        ///
        /// @returns The rotation angle around the @a z axis, in degrees.
        double GetZAngle () const
        {
          return m_zAngle;
        }

        /// Sets the rotation angles around all three axes to apply to the
        /// input point.
        ///
        /// @param xAngle The rotation angle around the @a x axis, in degrees.
        /// @param yAngle The rotation angle around the @a y axis, in degrees.
        /// @param zAngle The rotation angle around the @a z axis, in degrees.
        ///
        /// This module's GetValue() method rotates the coordinates
        /// of the input point around the origin before returning
        /// the value from the source module at that point.
        void SetAngles (double xAngle, double yAngle, double zAngle);

        /// Sets the rotation angle around the @a x axis to apply to the input
        /// point.
        ///
        /// @param xAngle The rotation angle around the @a x axis, in degrees.
        ///
        /// This module's GetValue() method rotates the coordinates of the
        /// input point around the origin before returning the value from the
        /// source module at that point.
        void SetXAngle (double xAngle)
        {
          SetAngles (xAngle, m_yAngle, m_zAngle);
        }

        /// Sets the rotation angle around the @a y axis to apply to the input
        /// point.
        ///
        /// @param yAngle The rotation angle around the @a y axis, in degrees.
        ///
        /// This module's GetValue() method rotates the coordinates of the
        /// input point around the origin before returning the value from the
        /// source module at that point.
        void SetYAngle (double yAngle)
        {
          SetAngles (m_xAngle, yAngle, m_zAngle);
        }

        /// Sets the rotation angle around the @a z axis to apply to the input
        /// point.
        ///
        /// @param zAngle The rotation angle around the @a z axis, in degrees.
        ///
        /// This module's GetValue() method rotates the coordinates of the
        /// input point around the origin before returning the value from the
        /// source module at that point.
        void SetZAngle (double zAngle)
        {
          SetAngles (m_xAngle, m_yAngle, zAngle);
        }

      protected:

        /// An entry within the 3x3 rotation matrix used for rotating the
        /// input point.
        double m_x1Matrix;

        /// An entry within the 3x3 rotation matrix used for rotating the
        /// input point.
        double m_x2Matrix;

        /// An entry within the 3x3 rotation matrix used for rotating the
        /// input point.
        double m_x3Matrix;

        /// @a x rotation angle applied to the input point, in degrees.
        double m_xAngle;

        /// An entry within the 3x3 rotation matrix used for rotating the
        /// input point.
        double m_y1Matrix;

        /// An entry within the 3x3 rotation matrix used for rotating the
        /// input point.
        double m_y2Matrix;

        /// An entry within the 3x3 rotation matrix used for rotating the
        /// input point.
        double m_y3Matrix;

        /// @a y rotation angle applied to the input point, in degrees.
        double m_yAngle;

        /// An entry within the 3x3 rotation matrix used for rotating the
        /// input point.
        double m_z1Matrix;

        /// An entry within the 3x3 rotation matrix used for rotating the
        /// input point.
        double m_z2Matrix;

        /// An entry within the 3x3 rotation matrix used for rotating the
        /// input point.
        double m_z3Matrix;

        /// @a z rotation angle applied to the input point, in degrees.
        double m_zAngle;

    };

    /// @}

    /// @}

    /// @}

  }

}

#endif
