/****************************************************************
 *
 * <Copyright information>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Author: Erik Tuerke, etuerke@googlemail.com
 *
 * common.hpp
 *
 * Description:
 *
 *  Created on: Jun 12, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_DATA_COMMON_HPP
#define _ISIS_GLANCE_DATA_COMMON_HPP

#include <DataStorage/common.hpp>
#include "Util/common.hpp"

namespace isis
{
namespace glance
{
namespace data
{
class Image;

typedef uint8_t ScalarRepn;
typedef util::color24 ColorRepn;
typedef util::fvector4 VectorRepn;
typedef std::complex< float > ComplexRepn;


typedef SharredPointer<Image> ImageSharedPointer;
typedef std::vector< ImageSharedPointer > ImageVector;

typedef SharredPointer<isis::data::Image> IsisImageSharredPointer;

} // end namespace data
} // end namespace glance
} // end namespace isis

#include "image.hpp"

#endif // _ISIS_GLANCE_COMMON_HPP