// cylinders.h
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

#ifndef NOISE_MODULE_CYLINDERS_H
#define NOISE_MODULE_CYLINDERS_H

#include "modulebase.h"

namespace noise
{

  namespace module {
    /// @addtogroup libnoise
    /// @{
    
    /// @addtogroup modules
    /// @{
    
    /// @addtogroup generatormodules
    /// @{
    
    /// Default frequency value for the ModuleCylinders noise module.
    const double DEFAULT_CYLINDERS_FREQUENCY = 1.0;
    
    /// Noise module that outputs concentric cylinders.
    ///
    /// @image html modulecylinders.png
    ///
    /// This module outputs concentric cylinders centered on ( @b 0.0, @b 0.0,
    /// @b 0.0 ).  The cylinders are oriented along the @a y axis similar to the
    /// concentric rings of a tree.  Each cylinder extends  infinitely along the
    /// @a y axis.
    ///
    /// The first cylinder has a radius of @b 1.0.  Each subsequent cylinder has
    /// a radius that is @b 1.0 unit larger than the previous cylinder.
    ///
    /// The output value from this noise module is determined by the distance
    /// from the the nearest cylinder surface.  Input points on the cylinder
    /// surface are given the value @b 1.0 and the input points equidistant from
    /// two cylinder surfaces are given the value @b -1.0.
    ///
    /// An application can change the frequency of this noise module, changing
    /// the density of the concentric cylinders.  Increasing the frequency
    /// increases the density of concentric cylinders, reducing the distances
    /// between cylinders.  To specify the frequency, call the SetFrequency()
    /// method.
    ///
    /// This noise module, modified with some low-frequency, low-power
    /// turbulence, is useful for generating wood-like textures.
    ///
    /// This noise module does not require any source modules.
    class Cylinders: public Module
      {
	
      public:
	
	/// Constructor.
	///
	/// The default frequency is set to ::DEFAULT_CYLINDERS_FREQUENCY.
	Cylinders ();

	/// Returns the frequency of the concentric cylinders.
	///
	/// @returns The frequency of the concentric cylinders.
	///
	/// Increasing the frequency increases the density of concentric
	/// cylinders, reducing the distances between cylinders.
	double GetFrequency () const
	  {
	    return m_frequency;
	  }
	
	virtual int GetSourceModuleCount () const
	  {
	    return 0;
	  }
	
	virtual double GetValue (double x, double y, double z) const;
	
	/// Sets the frequenct of the concentric cylinders.
	///
	/// @param frequency The frequency of the concentric cylinders.
	///
	/// Increasing the frequency increases the density of concentric
	/// cylinders, reducing the distances between cylinders.
	void SetFrequency (double frequency)
	  {
	    m_frequency = frequency;
	  }
	
      protected:
	
	/// Frequency of the concentric cylinders.
	double m_frequency;
	
      };
    
    /// @}
    
    /// @}
    
    /// @}
    
  }
}

#endif
