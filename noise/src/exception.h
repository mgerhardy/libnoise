// exception.h
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

#ifndef NOISE_EXCEPTION_H
#define NOISE_EXCEPTION_H

namespace noise
{

  /// @addtogroup libnoise
  /// @{

  /// Defines the exceptions raised by libnoise.
  enum NoiseEx
  {

    /// Unknown exception
    EX_UNKNOWN = 0,

    /// An invalid parameter was specified.
    EX_INVALID_PARAM = 1,

    /// No noise module was specified.
    EX_NO_MODULE = 2,

    /// Out of memory.
    EX_OUT_OF_MEMORY = 3

  };

  /// @}

}

#endif
