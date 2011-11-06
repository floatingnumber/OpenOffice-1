/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef _BGFX_TOOLS_RECTCLIPTOOLS_HXX
#define _BGFX_TOOLS_RECTCLIPTOOLS_HXX

#include <sal/types.h>

//////////////////////////////////////////////////////////////////////////////

namespace basegfx
{
	namespace tools
	{
        namespace RectClipFlags 
        {
            static const sal_uInt32 LEFT   = (sal_Int32)0x01;
            static const sal_uInt32 RIGHT  = (sal_Int32)0x02;
            static const sal_uInt32 TOP    = (sal_Int32)0x04;
            static const sal_uInt32 BOTTOM = (sal_Int32)0x08;
        }

        /** Calc clip mask for Cohen-Sutherland rectangle clip

            This function returns a clip mask used for the
            Cohen-Sutherland rectangle clip method, where one or more
            of the lower four bits are set, if the given point is
            outside one or more of the four half planes defining the
            rectangle (see RectClipFlags for possible values)
         */
		template< class Point, class Rect > inline 
           sal_uInt32 getCohenSutherlandClipFlags( const Point& rP,
                                                   const Rect&  rR ) 
		{
			// maxY | minY | maxX | minX
			sal_uInt32 clip  = (rP.getX() < rR.getMinX()) << 0;
                       clip |= (rP.getX() > rR.getMaxX()) << 1;
                       clip |= (rP.getY() < rR.getMinY()) << 2;
                       clip |= (rP.getY() > rR.getMaxY()) << 3;
			return clip;
		}

        /** Determine number of clip planes hit by given clip mask

            This method returns the number of one bits in the four
            least significant bits of the argument, which amounts to
            the number of clip planes hit within the
            getCohenSutherlandClipFlags() method.
         */
        inline sal_uInt32 getNumberOfClipPlanes( sal_uInt32 nFlags )
        {
            // classic bit count algo, see e.g. Reingold, Nievergelt,
            // Deo: Combinatorial Algorithms, Theory and Practice,
            // Prentice-Hall 1977
            nFlags = (nFlags & 0x05) + ((nFlags >> 1) & 0x05);
            nFlags = (nFlags & 0x03) + (nFlags >> 2); // no need for &
                                                      // 0x03, can't
                                                      // overflow
            return nFlags;
		}
	}
}

#endif // _BGFX_TOOLS_RECTCLIPTOOLS_HXX
