#define BOOST_TEST_MODULE features test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "Square.h"
#include "Triangle.h"
#include "Polygon.h"
#include "Canvas.h"

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
    Polygon polygon;
    BOOST_CHECK_EQUAL( polygon.n_vertices(), 0 );
}



BOOST_AUTO_TEST_CASE(Vector2_serialize)
{
    Vector2 v(-11.77, 6.33);
    std::ostringstream s;
    s << v;
    BOOST_CHECK_EQUAL( s.str(),  "-11.77 6.33" );
}



BOOST_AUTO_TEST_CASE(Vector2_deserialize)
{
    {
        std::istringstream is( "16.5 -11.2" );
        Vector2 v;
        is >> v;
        BOOST_CHECK( not is.fail() );
        BOOST_CHECK( not is.bad() );
        BOOST_CHECK_EQUAL( v,  Vector2( 16.5, -11.2 ) );
    }
}



BOOST_AUTO_TEST_CASE(Vector2_deserialize_fail)
{
    {
        std::istringstream is( "" );
        Vector2 v;
        is >> v;
        BOOST_CHECK( is.fail() );
    }

    {
        std::istringstream is( "16.5" );
        Vector2 v;
        is >> v;
        BOOST_CHECK( is.fail() );
    }

    {
        std::istringstream is( "abc 12.6 11.3" );
        Vector2 v;
        is >> v;
        BOOST_CHECK( is.fail() );
    }

    {
        std::istringstream is( "15.3 abc -7.2" );
        Vector2 v;
        is >> v;
        BOOST_CHECK( is.fail() );
    }
}



BOOST_AUTO_TEST_CASE(Square_serialize)
{
    Square square( {-11.77, 6.33}, {22.6, -3.9} );
    std::ostringstream os;
    os << square;
    BOOST_CHECK_EQUAL( os.str(),  "Square -11.77 6.33 22.6 -3.9" );
}



BOOST_AUTO_TEST_CASE(Square_deserialize)
{
    std::istringstream is( "Square 0 1 2 3");
    Square square;
    is >> square;
    BOOST_CHECK( not is.fail() );
    BOOST_CHECK( not is.bad() );
    BOOST_CHECK_EQUAL( square.vertex(0), Vector2(0,1) );
    BOOST_CHECK_EQUAL( square.vertex(1), Vector2(2,3) );
}



BOOST_AUTO_TEST_CASE(Triangle_serialize)
{
    Triangle triangle( {-11.77, 6.33}, {22.6, -3.9}, {66.22, 8. } );
    std::ostringstream os;
    os << triangle;
    BOOST_CHECK_EQUAL( os.str(),  "Triangle -11.77 6.33 22.6 -3.9 66.22 8" );
}



BOOST_AUTO_TEST_CASE(Triangle_deserialize)
{
    {
        std::istringstream is( "Triangle 0 1 2 3 -4 -5") ;
        Triangle triangle;
        is >> triangle;
        BOOST_CHECK( not is.fail() );
        BOOST_CHECK( not is.bad() );
        BOOST_CHECK_EQUAL( triangle.vertex(0), Vector2( 0, 1) );
        BOOST_CHECK_EQUAL( triangle.vertex(1), Vector2( 2, 3) );
        BOOST_CHECK_EQUAL( triangle.vertex(2), Vector2(-4,-5) );
    }

    {
        std::istringstream is( "Triangle 0 1 2 3") ;
        Triangle triangle;
        is >> triangle;
        BOOST_CHECK( is.fail() );
    }

    {
        std::istringstream is( "Triangle 0 1 2 3 5") ;
        Triangle triangle;
        is >> triangle;
        BOOST_CHECK( is.fail() );
    }
}



BOOST_AUTO_TEST_CASE(Polygon_serialize)
{
    Polygon polygon( { {-11.77, 6.33}, {22.6, -3.9}, {66.22, 8. } } );
    std::ostringstream os;
    os << polygon;
    BOOST_CHECK_EQUAL( os.str(),  "Polygon -11.77 6.33 22.6 -3.9 66.22 8" );
}



BOOST_AUTO_TEST_CASE(Polygon_serialize_empty)
{
        Polygon polygon;
        std::ostringstream os;
        os << polygon;
        BOOST_CHECK_EQUAL( os.str(),  "Polygon" );
}



BOOST_AUTO_TEST_CASE(Polygon_deserialize)
{
    std::istringstream is( "Polygon 10 20 30 40 50 60 -77 33");
    Polygon polygon;
    is >> polygon;
    BOOST_CHECK( not is.fail() );
    BOOST_CHECK( not is.bad() );
    BOOST_CHECK_EQUAL( polygon.n_vertices(), 4 );
    BOOST_CHECK_EQUAL( polygon.vertex(0), Vector2( 10, 20) );
    BOOST_CHECK_EQUAL( polygon.vertex(1), Vector2( 30, 40) );
    BOOST_CHECK_EQUAL( polygon.vertex(2), Vector2( 50, 60) );
    BOOST_CHECK_EQUAL( polygon.vertex(3), Vector2(-77, 33) );
}



BOOST_AUTO_TEST_CASE(Polygon_deserialize_with_trailing_spaces)
{
    std::istringstream is( "Polygon 10 20 30 40 50 60 -77 33   ");
    Polygon polygon;
    is >> polygon;
    BOOST_CHECK( not is.fail() );
    BOOST_CHECK( not is.bad() );
    BOOST_CHECK_EQUAL( polygon.n_vertices(), 4 );
    BOOST_CHECK_EQUAL( polygon.vertex(0), Vector2( 10, 20) );
    BOOST_CHECK_EQUAL( polygon.vertex(1), Vector2( 30, 40) );
    BOOST_CHECK_EQUAL( polygon.vertex(2), Vector2( 50, 60) );
    BOOST_CHECK_EQUAL( polygon.vertex(3), Vector2(-77, 33) );
}



BOOST_AUTO_TEST_CASE(Polygon_deserialize_empty)
{
    std::istringstream is("Polygon");
    Polygon polygon( { {2,3}, {-4, -5} } );
    is >> polygon;
    BOOST_CHECK( not is.fail() );
    BOOST_CHECK( not is.bad() );
    BOOST_CHECK_EQUAL( polygon.n_vertices(), 0 );
}


//BOOST_AUTO_TEST_CASE(Canvas_draw_overload_resolution)
//{
//    Canvas c;
//    c.draw( Polygon({}) );
//    c.draw( Circle( {0.,0.}, 1 ) );
//}


