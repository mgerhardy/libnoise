// terrace.h
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

#ifndef NOISE_MODULE_TERRACE_H
#define NOISE_MODULE_TERRACE_H

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

    /// Noise module that maps the value from the source module onto a
    /// terrace-forming curve.
    ///
    /// @image html moduleterrace.png
    ///
    /// This module maps the value from the source module onto a
    /// terrace-forming curve.  The start of this curve has a slope of zero;
    /// its slope then smoothly increases.  This curve also contains
    /// discontinuities at certain application-defined points known as
    /// <i>terrace points</i>.  At a terrace point, the slope becomes zero
    /// again, producing a "terracing" effect.  Refer to the following
    /// illustration:
    ///
    /// @image html terrace.png
    ///
    /// To add a terrace point to this noise module, call the
    /// AddTerracePoint() method.
    ///
    /// An application must add a minimum of two terrace points onto the
    /// curve.  If this is not done, the GetValue() method fails.  The terrace
    /// points can have any value, although no two terrace points can have the
    /// same value.  There is no limit to the number of terrace points that
    /// can be added to the curve.
    ///
    /// This noise module clamps the value from the source module if that
    /// value is less than the value of the lowest terrace point or greater
    /// than the value of the highest terrace point.
    ///
    /// This noise module is often used to generate terrain features such as
    /// your stereotypical desert canyon.
    ///
    /// This noise module requires one source module.
    class Terrace: public Module
    {

	    public:

	      /// Constructor.
	      Terrace ();

	      /// Destructor.
	      ~Terrace ();

	      /// Adds a terrace point onto the terrace-forming curve.
	      ///
	      /// @param value The value of the terrace point to add.
	      ///
	      /// @pre No two terrace points have the same value.
	      ///
	      /// @throw NoiseEx
	      /// - @a EX_INVALID_PARAM: An invalid parameter was specified; see
        ///   the preconditions for more information.
	      ///
	      /// Two or more terrace points define the terrace-forming curve.  The
        /// start of this curve has a slope of zero; its slope then smoothly
        /// increases.  A <i>terrace point</i> is a discontinuity on the
        /// curve.  At a terrace point, the slope becomes zero gain.
	      ///
	      /// It does not matter which order these points are added.
	      void AddTerracePoint (double value);

	      /// Deletes all the terrace points on the terrace-forming curve.
	      ///
	      /// @post All terrace points on the terrace-forming curve are deleted.
	      void ClearAllTerracePoints ();

    	  virtual int GetSourceModuleCount () const
	      {
	        return 1;
	      }

	      /// Returns a pointer to the array of terrace points on the
	      /// terrace-forming curve.
	      ///
	      /// @returns A pointer to the array of terrace points in this noise
	      /// module.
	      ///
	      /// Two or more terrace points define the terrace-forming curve.  The
        /// start of this curve has a slope of zero; its slope then smoothly
        /// increases.  A <i>terrace point</i> is a discontinuity on the
        /// curve.  At a terrace point, the slope becomes zero again.
	      ///
        /// Before calling this method, call GetTerracePointCount() to
        /// determine the number of terrace points in this array.
	      ///
	      /// It is recommended that an application does not store this pointer
        /// for later use since the pointer to the array may change if the
        /// application calls another method of this object.
	      const double* GetTerracePointArray () const
	      {
	        return m_pTerracePoints;
	      }

	      /// Returns the number of terrace points on the terrace-forming curve.
	      ///
	      /// @returns The number of terrace points on the terrace-forming
        /// curve.
	      int GetTerracePointCount () const
	      {
	        return m_terracePointCount;
	      }

	      /// Enables or disables the inversion of the terrace-forming curve
        /// between all terrace points.
        ///
	      /// @param invert Specifies whether to invert the curve between all
        /// terrace points.
	      void InvertTerraces (bool invert = true)
	      {
	        m_invertTerraces = invert;
	      }

	      /// Determines if the terrace-forming curve between all terrace
        /// points is inverted.
        ///
        /// @returns
        /// - @b true if the curve between the terrace points is inverted.
        /// - @b false if the curve between the terrace points is not
        ///   inverted.
        bool IsTerracesInverted () const
        {
	        return m_invertTerraces;
        }

    	  virtual double GetValue (double x, double y, double z) const;

	      /// Creates a number of equally-spaced terrace points.
	      ///
	      /// @param terracePointCount The number of terrace points to generate.
	      ///
	      /// @pre The number of terrace points must be greater than or equal to
	      /// @b 2.
	      ///
	      /// @post The previous terrace points on the terrace-forming curve are
        /// deleted.
	      ///
	      /// @throw NoiseEx
	      /// - @a EX_INVALID_PARAM: An invalid parameter was specified; see the
	      ///   preconditions for more information.
	      ///
	      /// Two or more terrace points define the terrace-forming curve.  The
        /// start of this curve has a slope of zero; its slope then smoothly
        /// increases.  A <i>terrace point</i> is a discontinuity on the
        /// curve.  At a terrace point, the slope becomes zero again.
        void MakeTerracePoints (noise::int8 terracePointCount);

    	protected:

	      /// Determines the array index in which to insert the terrace point
	      /// into the internal terrace point array.
	      ///
	      /// @param value The value of the terrace point.
	      ///
	      /// @returns The array index in which to insert the terrace point.
	      ///
	      /// @pre No two terrace points have the same value.
	      ///
	      /// @throw NoiseEx
	      /// - @a EX_INVALID_PARAM: An invalid parameter was specified; see the
	      ///   preconditions for more information.
	      ///
	      /// By inserting the terrace point at the returned array index, this
        /// class ensures that the terrace point array is sorted by value.
        /// The code that maps a value onto the curve requires a sorted
        /// terrace point array.
	      int FindInsertionPos (double value);

	      /// Inserts the terrace point at the specified position in the
	      /// internal terrace point array.
	      ///
	      /// @param insertionPos The zero-based array position in which to
        /// insert the terrace point.
	      /// @param value The value of the terrace point.
	      ///
	      /// To make room for this new terrace point, this method reallocates
        /// the terrace point array and shifts all terrace points occurring
        /// after the insertion position up by one.
	      ///
	      /// Because the curve mapping algorithm in this module requires that
        /// all terrace points in the array be sorted by value, the new
        /// terrace point should be inserted at the position in which the
        /// order is still preserved.
	      void InsertAtPos (int insertionPos, double value);

	      /// Determines if the terrace-forming curve between all terrace points
        /// is inverted.
	      bool m_invertTerraces;

	      /// Array that stores the terrace points.
	      double* m_pTerracePoints;

	      /// Number of terrace points stored in this noise module.
	      int m_terracePointCount;

    };

    /// @}

    /// @}

    /// @}

  }

}

#endif
