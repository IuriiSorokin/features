
#define BOOST_TEST_MODULE is_feature test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Features.h"

BOOST_AUTO_TEST_CASE(test_is_feature)
{
    BOOST_CHECK_EQUAL( (bool)is_feature<Circle>::value,   true );
    BOOST_CHECK_EQUAL( (bool)is_feature<Square>::value,   true );
    BOOST_CHECK_EQUAL( (bool)is_feature<Triangle>::value, true );
    BOOST_CHECK_EQUAL( (bool)is_feature<Polygon>::value,  true );

    BOOST_CHECK_EQUAL( (bool)is_feature<int>::value,          false );
    BOOST_CHECK_EQUAL( (bool)is_feature<Vector2>::value,      false );
    BOOST_CHECK_EQUAL( (bool)is_feature<Square&>::value,      false );
    BOOST_CHECK_EQUAL( (bool)is_feature<Square*>::value,      false );
    BOOST_CHECK_EQUAL( (bool)is_feature<const Square>::value, false );
}
