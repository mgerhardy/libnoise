// scalepoint.h
//
// Version 0.1.1 - 2004-03-04
// - Changed GetNumSourceModules() to GetSourceModuleCount() for consistency.
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

#ifndef NOISE_MODULE_SCALEPOINT_H
#define NOISE_MODULE_SCALEPOINT_H

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

      /// Default scaling value applied to the @a x coordinate for the
      /// ScalePoint noise module.
      const double DEFAULT_SCALE_POINT_X = 1.0;

      /// Default scaling value applied to the @a y coordinate for the
      /// ScalePoint noise module.
      const double DEFAULT_SCALE_POINT_Y = 1.0;

      /// Default scaling value applied to the @a z coordinate for the
      /// ScalePoint noise module.
      const double DEFAULT_SCALE_POINT_Z = 1.0;

      /// Noise module that scales the input point and returns the value from the
      /// source module at that point.
      ///
      /// @image html modulescalepoint.png
      ///
      /// This module's GetValue() method multiplies the ( @a x, @a y, @a z )
      /// coordinates of the input point with a scaling value before returning
      /// the value from the source module at that point.  To set the scaling
      /// value, call the SetScale() method.  To set the scaling value of the
      /// individual @a x, @a y, or @a z coordinate, call the SetXScale(),
      /// SetYScale() or SetZScale() methods, respectively.
      ///
      /// This noise module requires one source module.
      class ScalePoint: public Module
	{

	public:

	  /// Constructor.
	  ///
	  /// The default scaling value applied to the @a x coordinate is set
	  /// to ::DEFAULT_SCALE_POINT_X.
	  ///
	  /// The default scaling value applied to the @a y coordinate is set
	  /// to ::DEFAULT_SCALE_POINT_Y.
	  ///
	  /// The default scaling value applied to the @a z coordinate is set
	  /// to ::DEFAULT_SCALE_POINT_Z.
	  ScalePoint ();

	  virtual int GetSourceModuleCount () const
	    {
	      return 1;
	    }

	  virtual double GetValue (double x, double y, double z) const;

	  /// Returns the scaling value applied to the @a x coordinate of the
	  /// input point.
	  ///
	  /// @returns The scaling value applied to the @a x coordinate.
	  double GetXScale () const
	    {
	      return m_xScale;
	    }

	  /// Returns the scaling value applied to the @a y coordinate of the
	  /// input point.
	  ///
	  /// @returns The scaling value applied to the @a y coordinate.
	  double GetYScale () const
	    {
	      return m_yScale;
	    }

	  /// Returns the scaling value applied to the @a z coordinate of the
	  /// input point.
	  ///
	  /// @returns The scaling value applied to the @a z coordinate.
	  double GetZScale () const
	    {
	      return m_zScale;
	    }

	  /// Sets the scaling value to apply to the ( @a x, @a y, @a z )
	  /// coordinates of the input point.
	  ///
	  /// @param scale The scaling value to apply.
	  ///
	  /// This module's GetValue() method multiplies the ( @a x, @a y, @a z )
	  /// coordinates of the input point with a scaling value before returning
	  /// the value of the source module at that point.
	  void SetScale (double scale)
	    {
	      m_xScale = scale;
	      m_yScale = scale;
	      m_zScale = scale;
	    }

	  /// Sets the scaling value to apply to the ( @a x, @a y, @a z )
	  /// coordinates of the input point.
	  ///
	  /// @param xScale The scaling value to apply to the @a x coordinate.
	  /// @param yScale The scaling value to apply to the @a y coordinate.
	  /// @param zScale The scaling value to apply to the @a z coordinate.
	  ///
	  /// This module's GetValue() method multiplies the ( @a x, @a y, @a z )
	  /// coordinates of the input point with a scaling value before returning
	  /// the value of the source module at that point.
	  void SetScale (double xScale, double yScale, double zScale)
	    {
	      m_xScale = xScale;
	      m_yScale = yScale;
	      m_zScale = zScale;
	    }

	  /// Sets the scaling value to apply to the @a x coordinate of the input
	  /// point.
	  ///
	  /// @param xScale The scaling value to apply to the @a x coordinate.
	  ///
	  /// This module's GetValue() method multiplies the ( @a x, @a y, @a z )
	  /// coordinates of the input point with a scaling value before returning
	  /// the value of the source module at that point.
	  void SetXScale (double xScale)
	    {
	      m_xScale = xScale;
	    }

	  /// Sets the scaling value to apply to the @a y coordinate of the input
	  /// point.
	  ///
	  /// @param yScale The scaling value to apply to the @a y coordinate.
	  ///
	  /// This module's GetValue() method multiplies the ( @a x, @a y, @a z )
	  /// coordinates of the input point with a scaling value before returning
	  /// the value of the source module at that point.
	  void SetYScale (double yScale)
	    {
	      m_yScale = yScale;
	    }

	  /// Sets the scaling value to apply to the @a z coordinate of the input
	  /// point.
	  ///
	  /// @param zScale The scaling value to apply to the @a z coordinate.
	  ///
	  /// This module's GetValue() method multiplies the ( @a x, @a y, @a z )
	  /// coordinates of the input point with a scaling value before returning
	  /// the value of the source module at that point.
	  void SetZScale (double zScale)
	    {
	      m_zScale = zScale;
	    }

	protected:

	  /// Scaling value applied to the @a x coordinate of the input point.
	  double m_xScale;

	  /// Scaling value applied to the @a y coordinate of the input point.
	  double m_yScale;

	  /// Scaling value applied to the @a z coordinate of the input point.
	  double m_zScale;

	};

      /// @}

      /// @}

      /// @}

    }

}

#endif
