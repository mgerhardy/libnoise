// select.h
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

#ifndef NOISE_MODULE_SELECT_H
#define NOISE_MODULE_SELECT_H

#include "modulebase.h"

namespace noise
{

  namespace module
    {

      /// @addtogroup libnoise
      /// @{

      /// @addtogroup modules
      /// @{

      /// @addtogroup selectormodules
      /// @{

      /// Default falloff value for the Select noise module.
      const double DEFAULT_SELECT_EDGE_FALLOFF = 0.0;

      /// Default lower bound of the selection range for the Select noise
      /// module.
      const double DEFAULT_SELECT_LOWER_BOUND = -1.0;

      /// Default upper bound of the selection range for the Select noise
      /// module.
      const double DEFAULT_SELECT_UPPER_BOUND = 1.0;

      /// Noise module that outputs one of the values from two source modules
      /// depending on the value from another source module.
      ///
      /// @image html moduleselect.png
      ///
      /// Unlike most other noise modules, the index value assigned to a source
      /// module determines its role in the selection operation:
      /// - Source module @b 0 (upper left in the diagram) outputs a value.
      /// - Source module @b 1 (lower left in the diagram) outputs a value.
      /// - Source module @b 2 (bottom of the diagram) is known as the <i>selector
      ///   module</i>.  This module determines the value to select.  If the value
      ///   from the selector module is within a range of values known as the
      ///   <i>selection range</i>, this noise module outputs the value from the
      ///   source module with an index value of @b 1.  Otherwise, this noise
      ///   module outputs the value from the source module with an index value of
      ///   @b 0.
      ///
      /// To specify the bounds of the selection range, call the SetBounds()
      /// method.
      ///
      /// An application can pass the selector module to the SetSelectorModule()
      /// method instead of the SetSourceModule() method.  This may make the
      /// application code easier to read.
      ///
      /// By default, there is an abrupt transition between the values from the
      /// two source modules at the boundaries of the selection range.  To smooth
      /// the transition, pass a non-zero value to the SetEdgeFalloff() method.
      /// Higher values result in a smoother transition.
      ///
      /// This noise module requires three source modules.
      class Select: public Module
	{

	public:

	  /// Constructor.
	  ///
	  /// The default falloff value for the the edge transition is set to
	  /// ::DEFAULT_SELECT_EDGE_FALLOFF.
	  ///
	  /// The default lower bound of the selection range is set to
	  /// ::DEFAULT_SELECT_LOWER_BOUND.
	  ///
	  /// The default upper bound of the selection range is set to
	  /// ::DEFAULT_SELECT_UPPER_BOUND.
	  Select ();

	  /// Returns the falloff value for the edge transition.
	  ///
	  /// @returns The falloff value for the edge transition.
	  ///
	  /// The falloff value is the width of the edge transition at either
	  /// edge of the selection range.
	  ///
	  /// By default, there is an abrupt transition between the values from
	  /// the two source modules at the boundaries of the selection range.
	  double GetEdgeFalloff () const
	    {
	      return m_edgeFalloff;
	    }

	  /// Returns the lower bound of the selection range.
	  ///
	  /// @returns The lower bound of the selection range.
	  ///
	  /// If the value from the selector module is within the
	  /// bounds of the selection range, this noise module outputs
	  /// the value from the source module with an index value of
	  /// @b 1.  Otherwise, this noise module outputs the value
	  /// from the source module with an index value of @b 0.
	  double GetLowerBound () const
	    {
	      return m_lowerBound;
	    }

	  /// Returns the selector module.
	  ///
	  /// @returns A reference to the selector module.
	  ///
	  /// @pre A selector module has been added to this module via
	  /// a call to SetSourceModule() or SetSelectorModule().
	  ///
	  /// @throw NoiseEx
	  /// - @a EX_NO_MODULE: See the preconditions for more information.
	  ///
	  /// The selector module determines the value to select.  If
	  /// the value from the selector module is within a range of
	  /// values known as the <i>selection range</i>, this noise
	  /// module outputs the value from the source module with an
	  /// index value of @b 1.  Otherwise, this noise module
	  /// outputs the value from the source module with an index
	  /// value of @b 0.
	  const Module& GetSelectorModule () const
	    {
	      if (m_pSourceModule == NULL || m_pSourceModule[2] == NULL) {
		throw EX_NO_MODULE;
	      }
	      return *(m_pSourceModule[2]);
	    }

	  virtual int GetSourceModuleCount () const
	    {
	      return 3;
	    }

	  /// Returns the upper bound of the selection range.
	  ///
	  /// @returns The upper bound.
	  ///
	  /// If the value from the selector module is within the
	  /// bounds of the selection range, this noise module outputs
	  /// the value from the source module with an index value of
	  /// @b 1.  Otherwise, this noise module outputs the value
	  /// from the source module with an index value of @b 0.
	  double GetUpperBound () const
	    {
	      return m_upperBound;
	    }

	  virtual double GetValue (double x, double y, double z) const;

	  /// Sets the lower and upper bounds of the selection range.
	  ///
	  /// @param lowerBound The lower bound.
	  /// @param upperBound The upper bound.
	  ///
	  /// @pre The lower bound must be less than or equal to the
	  /// upper bound.
	  ///
	  /// @throw NoiseEx
	  /// - @a EX_INVALID_PARAM: An invalid parameter was specified; see the
	  ///   preconditions for more information.
	  ///
	  /// If the value from the selector module is within the
	  /// bounds of the selection range, this noise module outputs
	  /// the value from the source module with an index value of
	  /// @b 1.  Otherwise, this noise module outputs the value
	  /// from the source module with an index value of @b 0.
	  void SetBounds (double lowerBound, double upperBound);

	  /// Sets the falloff value for the edge transition.
	  ///
	  /// @param edgeFalloff The falloff value.
	  ///
	  /// The falloff value is the width of the edge transition at either
	  /// edge of the selection range.
	  ///
	  /// By default, there is an abrupt transition between the values from
	  /// the two source modules at the boundaries of the selection range.
	  ///
	  /// For example, if the selection range is @b 0.5 to @b 0.8
	  /// and the edge falloff value is @b 0.1, then this module
	  /// outputs:
	  /// - the value from the source module with an index value
	  ///   of @b 0 if the value from the selector module is less
	  ///   than @b 0.4 ( @b 0.5 - @b 0.1 ).
	  /// - a linear blend between the values from the two source modules if
	  ///   the value from the selector module is between @b 0.4 ( @b 0.5 -
	  ///   @b 0.1 ) and @b 0.6 ( @b 0.5 + @b 0.1 ).
	  /// - the value from the source module with an index value of @b 1 if
	  ///   the value from the selector module is between @b 0.6 ( @b 0.5 +
	  ///   @b 0.1 ) and @b 0.7 ( @b 0.8 - @b 0.1 ).
	  /// - a linear blend between the values from the two source modules if
	  ///   the value from the selector module is between @b 0.7 ( @b 0.8 -
	  ///   @b 0.1 ) and @b 0.9 ( @b 0.8 + @b 0.1 ).
	  /// - the value from the source module with an index value of @b 0 if
	  ///   the value from the selector module is greater than @b 0.9
	  ///   ( @b 0.8 + @b 0.1 ).
	  void SetEdgeFalloff (double edgeFalloff);

	  /// Sets the selector module.
	  ///
	  /// @param selectorModule The selector module.
	  ///
	  /// @pre A selector module has been added to this module via a call to
	  /// SetSourceModule() or SetSelectorModule().
	  ///
	  /// @throw NoiseEx
	  /// - @a EX_NO_MODULE: See the preconditions for more information.
	  ///
	  /// The selector module determines the value to select.  If
	  /// the value from the selector module is within a range of
	  /// values known as the <i>selection range</i>, this noise
	  /// module outputs the value from the source module with an
	  /// index value of @b 1.  Otherwise, this noise module
	  /// outputs the value from the source module with an index
	  /// value of @b 0.
	  ///
	  /// This method assigns an index value of @b 2 to the
	  /// selector module.  Passing the selector module to this
	  /// method produces the same results as passing the selector
	  /// module to the SetSourceModule() method while assigning
	  /// that module an index value of @b 2.
	  ///
	  /// The selector module must exist throughout the lifetime
	  /// of this noise module unless another selector module
	  /// replaces that selector module.
	  void SetSelectorModule (const Module& selectorModule)
	    {
	      assert (m_pSourceModule != NULL);
	      m_pSourceModule[2] = &selectorModule;
	    }

	protected:

	  /// Edge falloff value.
	  double m_edgeFalloff;

	  /// Lower bound of the selection range.
	  double m_lowerBound;

	  /// Upper bound of the selection range.
	  double m_upperBound;

	};

      /// @}

      /// @}

      /// @}

    }

}

#endif
