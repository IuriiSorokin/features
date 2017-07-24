#define BOOST_TEST_MODULE features test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Features.h"
#include "streamers.h"


BOOST_AUTO_TEST_CASE(Vector2_operators)
{
    Vector2 v1( -2,  5   );
    Vector2 v2(  7, -6.5 );
    BOOST_CHECK_NE( v1, v2 );
    BOOST_CHECK_EQUAL( v1,  Vector2( -2,  5 ) );
    BOOST_CHECK_EQUAL( v1 + v2, Vector2(5, -1.5 ) );
    BOOST_CHECK_EQUAL( v1 - v2, Vector2(-9, 11.5 ) );
}



BOOST_AUTO_TEST_CASE(Square_vertices)
{
    Square square( {3.,3.}, {4., 5.} );

    BOOST_CHECK_EQUAL( square.n_vertices(), 4 );

    BOOST_CHECK_EQUAL( square.vertex(0), Vector2(3,3) );
    BOOST_CHECK_EQUAL( square.vertex(1), Vector2(4,5) );
    BOOST_CHECK_EQUAL( square.vertex(2), Vector2(2,6) );
    BOOST_CHECK_EQUAL( square.vertex(3), Vector2(1,4) );

    try {
        square.vertex(4);
        BOOST_FAIL("Must have thrown std::out_of_range");
    } catch( std::out_of_range& e ) {}
}



BOOST_AUTO_TEST_CASE(Triangle_vertices)
{
    Triangle triangle( {11., 12.}, {13., 14.}, {15.,16.} );

    BOOST_CHECK_EQUAL( triangle.n_vertices(), 3 );

    BOOST_CHECK_EQUAL( triangle.vertex(0), Vector2(11,12) );
    BOOST_CHECK_EQUAL( triangle.vertex(1), Vector2(13,14) );
    BOOST_CHECK_EQUAL( triangle.vertex(2), Vector2(15,16) );

    try {
        triangle.vertex(3);
        BOOST_FAIL("Must have thrown std::out_of_range");
    } catch( std::out_of_range& e ) {}
}



BOOST_AUTO_TEST_CASE(Polygon_vertices)
{
    Polygon polygon( { {10., 11.},
                       {20., 21.},
                       {30., 31.},
                       {40., 41.},
                       {50., 51.}  } );

    BOOST_CHECK_EQUAL( polygon.n_vertices(), 5 );

    BOOST_CHECK_EQUAL( polygon.vertex(0), Vector2(10,11) );
    BOOST_CHECK_EQUAL( polygon.vertex(1), Vector2(20,21) );
    BOOST_CHECK_EQUAL( polygon.vertex(2), Vector2(30,31) );
    BOOST_CHECK_EQUAL( polygon.vertex(3), Vector2(40,41) );
    BOOST_CHECK_EQUAL( polygon.vertex(4), Vector2(50,51) );

    try {
        polygon.vertex(5);
        BOOST_FAIL("Must have thrown std::out_of_range");
    } catch( std::out_of_range& e ) {}
}



BOOST_AUTO_TEST_CASE(Polygon_0_vertices)
{
    Polygon polygon( {} );
    BOOST_CHECK_EQUAL( polygon.n_vertices(), 0 );
}



BOOST_AUTO_TEST_CASE(Circle_negative_radius)
{
    try {
        Circle( {1., 2.}, -4.2 );
        BOOST_FAIL("Must have thrown std::out_of_range");
    } catch( std::invalid_argument& e ) {}
}


