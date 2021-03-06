// #define BOOST_TEST_MODULE IOFactoryTest

// #include <boost/test/unit_test.hpp>

#include "data/io_factory.hpp"
#include "util/generic_plugin_loader.hpp"
#include "util/widget_base.hpp"

extern "C" {
#include <liboil/liboil.h>
}

int main( int /*argc*/, char **argv )
{
	//  ENABLE_LOG( isis::glance::data::Debug, isis::util::DefaultMsgPrint, isis::verbose_info );
	//  ENABLE_LOG( isis::glance::util::Debug, isis::util::DefaultMsgPrint, isis::verbose_info );
	ENABLE_LOG( isis::glance::data::Runtime, isis::util::DefaultMsgPrint, isis::verbose_info );
	//  const int dstr = atoi(argv[1]);
	//  const int sstr1 = atoi(argv[2]);
	//  const int sstr2 = atoi(argv[3]);
	//  oil_init();
	//  size_t length = 10;
	//  const int32_t perm[] = { 0,2,4,6,8,1,3,5,7,9 };
	//  const uint16_t src[] = { 10,11,12,13,14,15,16,17,18,19 };
	//  uint16_t dest[10];
	//  oil_permute_u16( dest, dstr, src, sstr1, perm, sstr2, length );
	//
	//  for( size_t i = 0; i < length; i++ ) {
	//      std::cout << (float)dest[i] << " ";
	//  }
	//  std::cout << std::endl;


	isis::util::slist paths;
	paths.push_back( argv[1] );

	boost::timer timer;

	isis::glance::data::IOFactory::setUseProposedDataType( true );
	isis::glance::data::IOFactory::setProposedDataType( isis::glance::data::ImageDataProperties::SCALAR, isis::glance::data::types::UINT16_T );

	isis::glance::data::Image::SharedPointer image = isis::glance::data::IOFactory::load( paths ).front();

	const isis::glance::data::Volume &vol = image->operator[]( 0 );

	isis::glance::data::Volume::fvec perp;
	perp[0] = 1;
	perp[1] = 0;
	perp[2] = 0;
	isis::glance::data::Volume::ivec coords;
	coords[0] = image->image_size[0] / 2;
	coords[1] = image->image_size[1] / 2;
	coords[2] = image->image_size[2] / 2;

	const size_t iterations = 5000;
	const bool aligned = true;

	isis::glance::data::Slice sliceSagittal = vol.extractSlice( perp, coords, aligned );
	isis::data::Chunk chunkSag( sliceSagittal,  sliceSagittal.getSizeAsVector()[0], sliceSagittal.getSizeAsVector()[1], 1, 1, true );
	isis::data::Image imageOutSag( chunkSag );
	isis::data::IOFactory::write( imageOutSag, "/tmp/sagittal.nii" );

	perp[0] = 0;
	perp[1] = 1;
	perp[2] = 0;

	isis::glance::data::Slice sliceCoronal = vol.extractSlice( perp, coords, aligned );
	isis::data::Chunk chunkCoronal( sliceCoronal,  sliceCoronal.getSizeAsVector()[0], sliceCoronal.getSizeAsVector()[1], 1, 1, true );
	isis::data::Image imageOutCoronal( chunkCoronal );
	isis::data::IOFactory::write( imageOutCoronal, "/tmp/coronal.nii" );


	perp[0] = 0;
	perp[1] = 0;
	perp[2] = 1;
	isis::glance::data::Slice slice = vol.extractSlice( perp, coords, aligned );

	isis::data::Chunk chunk( slice,  slice.getSizeAsVector()[0], slice.getSizeAsVector()[1], 1, 1, true );
	isis::data::Image imageOut( chunk );

	isis::data::IOFactory::write( imageOut, "/tmp/axial.nii" );

	std::vector<isis::glance::data::Slice> slices = vol.extractAllSlices( perp );

	for ( size_t i = 0; i < slices.size(); i++ ) {
		isis::data::Chunk chunk( slices[i],  slices[i].getSizeAsVector()[0], slices[i].getSizeAsVector()[1], 1, 1, true );
		isis::data::Image imageOut( chunk );
		std::stringstream name;
		name << "/tmp/series" << i << ".nii";
		isis::data::IOFactory::write( imageOut, name.str() );
	}




	return 0;
}
// }
// }
// }
