// exponent.h
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

#ifndef NOISE_MODULE_EXPONENT_H
#define NOISE_MODULE_EXPONENT_H

#include "modulebase.h"

namespace noise
{

  namespace module {

    /// @addtogroup libnoise
    /// @{

    /// @addtogroup modules
    /// @{

    /// @addtogroup modifiermodules
    /// @{

    /// Default exponent for the ModuleExponent module.
    const double DEFAULT_EXPONENT = 1.0;

    /// Noise module that maps the value from the source module onto an
    /// exponential curve.
    ///
    /// @image html moduleexponent.png
    ///
    /// Because most noise modules output a value within the @b -1.0 to @b +1.0
    /// range, this noise module first normalizes the value from the source
    /// module (the range becomes @b 0.0 to @b +1.0 ), maps that value onto an
    /// exponential curve, then rescales the value back to the original range.
    ///
    /// This noise module requires one source module.
    class Exponent: public Module
      {

      public:

	/// Constructor.
	///
	/// The default exponent is set to ::DEFAULT_EXPONENT.
	Exponent ();

	/// Returns the exponent value to apply to the value from the source
	/// module.
	///
	/// @returns The exponent value.
	///
	/// Because most noise modules output a value within the @b -1.0 to
	/// @b +1.0 range, this noise module first normalizes the value from the
	/// source module (the range becomes @b 0.0 to @b +1.0 ), maps that
	/// value onto an exponential curve, then rescales the value back to the
	/// original range.
	double GetExponent () const
	  {
	    return m_exponent;
	  }

	virtual int GetSourceModuleCount () const
	  {
	    return 1;
	  }

	virtual double GetValue (double x, double y, double z) const;

	/// Sets the exponent value to apply to the value from the source module.
	///
	/// @param exponent The exponent value.
	///
	/// Because most noise modules output a value within the @b -1.0 to
	/// @b +1.0 range, this noise module first normalizes the value from
	/// the source module (the range becomes @b 0.0 to @b +1.0 ), maps that
	/// value onto an exponential curve, then rescales the value back to the
	/// original range.
	void SetExponent (double exponent)
	  {
	    m_exponent = exponent;
	  }

      protected:

	/// Exponent to apply to the value from the source module.
	double m_exponent;

      };

    /// @}

    /// @}

    /// @}

  }

}

#endif
