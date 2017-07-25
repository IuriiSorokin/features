
#define BOOST_TEST_MODULE is_has_vertices test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Features.h"

BOOST_AUTO_TEST_CASE(test_is_has_vertices)
{
    BOOST_CHECK_EQUAL( (bool)is_has_vertices<int>::value,       false );
    BOOST_CHECK_EQUAL( (bool)is_has_vertices<Circle>::value,    false );

    BOOST_CHECK_EQUAL( (bool)is_has_vertices<Square>::value,    true  );
    BOOST_CHECK_EQUAL( (bool)is_has_vertices<Polygon>::value,   true  );
    BOOST_CHECK_EQUAL( (bool)is_has_vertices<Triangle>::value,  true  );
}
