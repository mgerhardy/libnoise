// terrace.h
//
// Version 0.1.1 - 2004-03-04
// - Changed GetNumSourceModules() to GetSourceModuleCount() for consistency.
// - Changed GetNumTerracePoints() to GetTerracePointCount() for consistency.
// - Changed m_numTerracePoints to m_terracePointCount for consistency.
// - Changed numTerracePoints to terracePointCount for consistency.
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

      /// Noise module that maps the value from the source module onto a terracing
      /// curve.
      ///
      /// @image html moduleterrace.png
      ///
      /// @attention This module's documentation needs a *lot* of work.
      ///
      /// A terracing curve is defined by two or more <i>terracing
      /// points</i>.  The slope of the terracing curve is zero to the
      /// immediate right of a terracing point; the slope smoothly
      /// increases towards the right until the next terracing point
      /// is reached.  To add a terracing point to this noise module,
      /// call the AddTerracePoint() method.
      ///
      /// This noise module clamps the value from the source module if
      /// that value is less than the value of the lowest terracing
      /// point or greater than the value of the highest terracing
      /// point.
      ///
      /// There is no limit to the number of terracing points that can
      /// be added to the curve.  There must be a minimum of two
      /// terracing points on the curve before an application can call
      /// the GetValue() method. The terracing points can have any
      /// value, although no two terracing points can have the same
      /// value.
      ///
      /// This noise module is often used to generate terrain features
      /// such as your stereotypical desert canyon.
      ///
      /// This noise module requires one source module.
      class Terrace: public Module
	{

	public:

	  /// Constructor.
	  Terrace ();

	  /// Destructor.
	  ~Terrace ();

	  /// Adds a terracing point to this noise module.
	  ///
	  /// @param value The value of the terracing point to add.
	  ///
	  /// @pre No two terracing points have the same value.
	  ///
	  /// @throw NoiseEx
	  /// - @a EX_INVALID_PARAM: An invalid parameter was specified; see the
	  ///   preconditions for more information.
	  ///
	  /// Two or more terracing points define a terracing curve.
	  /// The slope of the terracing curve is zero to the
	  /// immediate right of a terracing point; the slope smoothly
	  /// increases towards the right until the next terracing
	  /// point is reached.
	  ///
	  /// It does not matter which order these points are added.
	  void AddTerracePoint (double value);

	  /// Deletes all the terracing points from this noise module.
	  ///
	  /// @post All points from this noise module are deleted.
	  void ClearAllTerracePoints ();

	  virtual int GetSourceModuleCount () const
	    {
	      return 1;
	    }

	  /// Returns a pointer to the array of terracing points in this noise
	  /// module.
	  ///
	  /// @returns A pointer to the array of terracing points in this noise
	  /// module.
	  ///
	  /// Two or more terracing points define a terracing curve.
	  /// The slope of the terracing curve is zero to the
	  /// immediate right of a terracing point; the slope smoothly
	  /// increases towards the right until the next terracing
	  /// point is reached.
	  ///
	  /// Before calling this method, call GetTerracePointCount()
	  /// to determine the number of terracing points in this
	  /// array.
	  ///
	  /// It is recommended that an application does not store
	  /// this pointer for later use since the pointer to the
	  /// array may change if the application calls another method
	  /// of this object.
	  const double* GetTerracePointArray () const
	    {
	      return m_pTerracePoints;
	    }

	  /// Returns the number of terracing points stored in this
	  /// noise module.
	  ///
	  /// @returns The number of terracing points stored in this noise module.
	  int GetTerracePointCount () const
	    {
	      return m_terracePointCount;
	    }

	  /// Enables or disables the inversion of the individual
	  /// curves used to produce the terracing curve.
	  ///
	  /// @param invert Specifies whether to invert the individual curves.
	  ///
	  /// If the individual curves are not inverted, the slope of
	  /// the terracing curve is zero to the immediate right of a
	  /// terracing point; the slope smoothly increases towards
	  /// the right until the next terracing point is reached.
	  ///
	  /// If the individual curves are inverted, the slope of the
	  /// terracing curve is zero to the immediate left of a
	  /// terracing point; the slope smoothly decreases towards
	  /// the left until the previous terracing point is reached.
	  void InvertTerraces (bool invert = true)
	    {
	      m_invertTerraces = invert;
	    }

	  /// Determines if the individual curves used to produce the terracing
	  /// curve are inverted.
	  ///
	  /// @returns
	  /// - @b true if the individual curves are inverted.
	  /// - @b false if the individual curves are not inverted.
	  ///
	  /// If the individual curves are not inverted, the slope of
	  /// the terracing curve is zero to the immediate right of a
	  /// terracing point; the slope smoothly increases towards
	  /// the right until the next terracing point is reached.
	  ///
	  /// If the individual curves are inverted, the slope of the
	  /// terracing curve is zero to the immediate left of a
	  /// terracing point; the slope smoothly decreases towards
	  /// the left until the previous terracing point is reached.
	  bool IsTerracesInverted () const
	    {
	      return m_invertTerraces;
	    }

	  virtual double GetValue (double x, double y, double z) const;

	  /// Creates a number of equally-spaced terracing points.
	  ///
	  /// @param terracePointCount The number of terracing points to generate.
	  ///
	  /// @pre The number of terrace points must be greater than or equal to
	  /// @b 2.
	  ///
	  /// @post The previous terracing points stored in this noise module are
	  /// deleted.
	  ///
	  /// @throw NoiseEx
	  /// - @a EX_INVALID_PARAM: An invalid parameter was specified; see the
	  ///   preconditions for more information.
	  ///
	  /// Two or more terracing points define a terracing curve.
	  /// The slope of the terracing curve is zero to the
	  /// immediate right of a terracing point; the slope smoothly
	  /// increases towards the right until the next terracing
	  /// point is reached.
	  void MakeTerracePoints (int8 terracePointCount);

	protected:

	  /// Determines the array index in which to insert the terracing point
	  /// into the internal terracing point array.
	  ///
	  /// @param value The value of the terracing point.
	  ///
	  /// @returns The array index in which to insert the terracing point.
	  ///
	  /// @pre No two terracing points have the same value.
	  ///
	  /// @throw NoiseEx
	  /// - @a EX_INVALID_PARAM: An invalid parameter was specified; see the
	  ///   preconditions for more information.
	  ///
	  /// By inserting the terracing point at the returned array
	  /// index, this class ensures that the terracing point array
	  /// is sorted by value.  The code that maps a value onto the
	  /// curve requires a sorted terracing point array.
	  int FindInsertionPos (double value);

	  /// Inserts the terracing point at the specified position in the
	  /// internal terracing point array.
	  ///
	  /// @param insertionPos The zero-based array position in which to insert
	  /// the terracing point.
	  /// @param value The value of the terracing point.
	  ///
	  /// To make room for this new terracing point, this method
	  /// reallocates the terracing point array and shifts all
	  /// terracing points occurring after the insertion position
	  /// up by one.
	  ///
	  /// Because the curve mapping algorithm in this module
	  /// requires that all terracing points in the array be
	  /// sorted by value, the new terracing point should be
	  /// inserted at the position in which the order is still
	  /// preserved.
	  void InsertAtPos (int insertionPos, double value);

	  /// Determines if the individual curves used to produce the terracing
	  /// curve are inverted.
	  bool m_invertTerraces;

	  /// Array that stores the terracing points.
	  double* m_pTerracePoints;

	  /// Number of terracing points stored in this noise module.
	  int m_terracePointCount;

	};

      /// @}

      /// @}

      /// @}

    }

}

#endif
