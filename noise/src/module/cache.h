// cache.h
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

#ifndef NOISE_MODULE_CACHE_H
#define NOISE_MODULE_CACHE_H

#include "modulebase.h"

namespace noise
{

  namespace module
  {

    /// @addtogroup libnoise
    /// @{

    /// @addtogroup modules
    /// @{

    /// @defgroup miscmodules Miscellaneous Modules
    /// @addtogroup miscmodules
    /// @{

    /// Noise module that caches the last value generated from the source
    /// module.
    ///
    /// If an application passes an input point to the GetValue() method that
    /// differs from the previously passed input point, this module instructs
    /// the source module to calculate the value.  This value, as well as the
    /// ( @a x, @a y, @a z ) coordinates of the input point, are stored
    /// (cached) in this noise module.
    ///
    /// If the application passes an input point to the GetValue() method
    /// that is equal to the previously passed input point, this module
    /// returns the cached value without having the source module recalculate
    /// the output value.
    ///
    /// If an application passes a new source module to the SetSourceModule()
    /// method, the cache is invalidated.
    ///
    /// Caching a noise module is useful when a module is used as an source
    /// module for multiple noise modules.  If a source module is not cached,
    /// the source module will redundantly calculate the same output value
    /// once for each module in which it is included.
    ///
    /// This noise module requires one source module.
    class Cache: public Module
    {

      public:

        /// Constructor.
        Cache ();

        virtual int GetSourceModuleCount () const
        {
          return 1;
        }

        virtual double GetValue (double x, double y, double z) const;

        virtual void SetSourceModule (int index, const Module& sourceModule)
        {
          Module::SetSourceModule (index, sourceModule);
          m_isCached = false;
        }

      protected:

        /// The cached value at the cached coordinates.
        mutable double m_cachedValue;

        /// Determines if a cached value is stored in this noise module.
        mutable double m_isCached;

        /// @a x coordinate of the cached value.
        mutable double m_xCache;

        /// @a y coordinate of the cached value.
        mutable double m_yCache;

        /// @a z coordinate of the cached value.
        mutable double m_zCache;

    };

    /// @}

    /// @}

    /// @}

  }

}

#endif
