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
 * container.hpp
 *
 * Description:
 *
 *  Created on: Jun 25, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_DATA_CONTAINER_HPP
#define _ISIS_GLANCE_DATA_CONTAINER_HPP

#include <DataStorage/ndimensional.hpp>
#include <DataStorage/valuearray.hpp>

namespace isis
{
namespace glance
{
namespace data
{

template<unsigned short DIMS>
class DataContainer
	: public isis::data::_internal::NDimensional<DIMS>,
  protected isis::data::ValueArrayReference
{
public:
	inline DataContainer( const isis::data::ValueArrayReference &src, const size_t dims[DIMS] )
		: isis::data::ValueArrayReference( src ) {
		isis::data::_internal::NDimensional<DIMS>::init( dims );
	}

	template<typename TYPE>
	inline TYPE &voxel( const size_t dims[DIMS] ) {
		assert( (*this)->getTypeID() == isis::data::ValueArray<TYPE>::staticID );
		//hopefully the user knows what he is doing in release build
		isis::data::ValueArray<TYPE> &ret = reinterpret_cast<isis::data::ValueArray<TYPE> & >(*this ); 
		return ret[isis::data::_internal::NDimensional<DIMS>::getLinearIndex(dims)];
	}

	template<typename TYPE>
	inline const TYPE &voxel( const size_t dims[DIMS] ) {
		assert( (*this)->getTypeID() == isis::data::ValueArray<TYPE>::staticID );
		//hopefully the user knows what he is doing in release build
		const isis::data::ValueArray<TYPE> &ret = reinterpret_cast<isis::data::ValueArray<TYPE> & >(*this );
		return ret[isis::data::_internal::NDimensional<DIMS>::getLinearIndex(dims)];
	}

	
};

} // end namespace data
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_DATA_CONTAINER_HPP