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
 * data_handler.hpp
 *
 * Description:
 *
 *  Created on: Jul 12, 2012
 *      Author: tuerke
 ******************************************************************/
#ifndef _ISIS_GLANCE_DATA_HANDLER_HPP
#define _ISIS_GLANCE_DATA_HANDLER_HPP

#include <boost/shared_array.hpp>
#include <map>
#include <CoreUtils/vector.hpp>
#include <DataStorage/valuearray_base.hpp>
#include "common.hpp"

#ifdef ISIS_GLANCE_USE_LIBOIL
extern "C" {
#include <liboil/liboil.h>
}
#endif

namespace isis
{
namespace glance
{
namespace data
{

#ifdef ISIS_GLANCE_USE_LIBOIL
namespace _internal
{
struct OilInitializer {
	OilInitializer() {
		LOG( Runtime, info ) << "Initializing oil";
		oil_init();
	}
};

template<typename TYPE>
void oilExtractSagittal( TYPE *destPtr, const TYPE *srcPtr, const int32_t *permutation, const size_t &length )
{
	for ( size_t index = 0; index < length; index++ ) {
		destPtr[index] = srcPtr[permutation[index]];
	}
}

#define DECL_OIL_EXTRACT_SAG( TYPE ) template<> void oilExtractSagittal<TYPE>( TYPE *destPtr, const TYPE *srcPtr, const int32_t *permutation, const size_t &length )

DECL_OIL_EXTRACT_SAG( int8_t );
DECL_OIL_EXTRACT_SAG( uint8_t );
DECL_OIL_EXTRACT_SAG( int16_t );
DECL_OIL_EXTRACT_SAG( uint16_t );
DECL_OIL_EXTRACT_SAG( int32_t );
DECL_OIL_EXTRACT_SAG( uint32_t );
DECL_OIL_EXTRACT_SAG( float );
DECL_OIL_EXTRACT_SAG( double );

}
#endif

class Volume;
class DataHandler
{
public:
	typedef boost::shared_array<int32_t> permutation_type;

	static isis::data::ValueArrayReference extractSagittal( const Volume &vol, const int32_t &x, bool aligned32Bit );

	static permutation_type getPermutationSagittal( const isis::util::vector3<size_t> &size, bool aligned32Bit );
private:
	template<typename T>
	static isis::data::ValueArrayReference _extractSagittal( const isis::data::ValueArrayBase &src, const size_t &lengthAligned32Bit, const size_t &length, const size_t &offset, DataHandler::permutation_type permutation ) {
		const T *srcPtr = static_cast<const T *>( src.getRawAddress( offset * sizeof( T ) ).get() );
		const isis::data::ValueArrayReference dest = src.cloneToNew( lengthAligned32Bit );
		T *destPtr = static_cast<T *>( dest->getRawAddress().get() );
#ifdef ISIS_GLANCE_USE_LIBOIL
		_internal::oilExtractSagittal<T>( destPtr, srcPtr, permutation.get(), length );
#else

		for ( size_t index = 0; index < length; index++ ) {
			destPtr[index] = srcPtr[permutation[index]];
		}

#endif
		return dest;
	}
};




} // end namespace data
} // end namespace glance
} // end namespace isis

#endif // _ISIS_GLANCE_DATA_HANDLER_HPP