// blend.h
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

#ifndef NOISE_MODULE_BLEND_H
#define NOISE_MODULE_BLEND_H

#include "modulebase.h"

namespace noise
{

  namespace module
  {

    /// @addtogroup libnoise
    /// @{
    
    /// @addtogroup modules
    /// @{
    
    /// @defgroup selectormodules Selector Modules
    /// @addtogroup selectormodules
    /// @{
    
    /// Noise module that outputs a value blended between two source modules
    /// given a weight supplied by another source module.
    ///
    /// @image html moduleblend.png
    ///
    /// Unlike most other noise modules, the index value assigned to a source
    /// module determines its role in the blending operation:
    /// - Source module @b 0 (upper left in the diagram) outputs one of the
    ///   values to blend.
    /// - Source module @b 1 (lower left in the diagram) outputs one of the
    ///   values to blend.
    /// - Source module @b 2 (bottom of the diagram) is known as the <i>blender
    ///   module</i>.  This module determines the weight of the blending
    ///   operation.  Negative values weigh the blend towards the value from
    ///   the source module with an index value of @b 0.  Positive values weigh
    ///   the blend towards the value from the source module with an index value
    ///   of @b 1.
    ///
    /// An application can pass the blender module to the SetBlenderModule()
    /// method instead of the SetSourceModule() method.  This may make the
    /// application code easier to read.
    ///
    /// This noise module uses linear interpolation to perform the blending
    /// operation.
    ///
    /// This noise module requires three source modules.
    class Blend: public Module
      {
	
      public:
	
	/// Constructor.
	Blend ();
	
	/// Returns the blender module.
	///
	/// @returns A reference to the blender module.
	///
	/// @pre A blender module has been added to this module via a call to
	/// SetSourceModule() or SetBlenderModule().
	///
	/// @throw NoiseEx
	/// - @a EX_NO_MODULE: See the preconditions for more information.
	///
	/// The blender module determines the weight of the blending operation.
	/// Negative values weigh the blend towards the value from the source
	/// module with an index value of @b 0.  Positive values weigh the blend
	/// towards the value from the source module with an index value of
	/// @b 1.
	const Module& GetBlenderModule () const
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
	
	virtual double GetValue (double x, double y, double z) const;
	
	/// Sets the blender module.
	///
	/// @param blenderModule The blender module.
	///
	/// The blender module determines the weight of the blending operation.
	/// Negative values weigh the blend towards the value from the source
	/// module with an index value of @b 0.  Positive values weigh the blend
	/// towards the value from the source module with an index value of
	/// @b 1.
	///
	/// This method assigns an index value of @b 2 to the blender module.
	/// Passing the blender module to this method produces the same results
	/// as passing the blender module to the SetSourceModule() method while
	/// assigning that module an index value of @b 2.
	///
	/// The blender module must exist throughout the lifetime of this noise
	/// module unless another blender module replaces that blender module.
	void SetBlenderModule (const Module& blenderModule)
	  {
	    assert (m_pSourceModule != NULL);
	    m_pSourceModule[2] = &blenderModule;
	  }
	
      };
    
    /// @}
    
    /// @}
    
    /// @}
    
  }

}

#endif
