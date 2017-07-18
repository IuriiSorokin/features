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

//
//
//BOOST_AUTO_TEST_CASE(Vector2_serialize)
//{
//    Vector2 v(-11.77, 6.33);
//    std::ostringstream s;
//    v.serialize( s );
//    BOOST_CHECK_EQUAL( s.str(),  "-11.77 6.33" );
//}
//
//
//
//BOOST_AUTO_TEST_CASE(Vector2_deserialize)
//{
//    {
//        std::istringstream is( "16.5 -11.2" );
//        const auto ov = Vector2::deserialize( is );
//        BOOST_CHECK( ov.is_initialized() );
//        if( ov.is_initialized() ) {
//            BOOST_CHECK_EQUAL( ov.get(),  Vector2( 16.5, -11.2 ) );
//        }
//    }
//
//    {
//        std::istringstream is( "77 .2222 trololo" );
//        const auto ov = Vector2::deserialize( is );
//        BOOST_CHECK( ov.is_initialized() );
//        if( ov.is_initialized() ) {
//            BOOST_CHECK_EQUAL( ov.get(),  Vector2( 77, .2222 ) );
//        }
//    }
//}
//
//
//
//BOOST_AUTO_TEST_CASE(Vector2_deserialize_fail)
//{
//    {
//        std::istringstream is( "" );
//        const auto ov = Vector2::deserialize( is );
//        BOOST_CHECK( not ov.is_initialized() );
//    }
//
//    {
//        std::istringstream is( "16.5" );
//        const auto ov = Vector2::deserialize( is );
//        BOOST_CHECK( not ov.is_initialized() );
//    }
//
//    {
//        std::istringstream is( "abc 12.6 11.3" );
//        const auto ov = Vector2::deserialize( is );
//        BOOST_CHECK( not ov.is_initialized() );
//    }
//
//    {
//        std::istringstream is( "15.3 abc -7.2" );
//        const auto ov = Vector2::deserialize( is );
//        BOOST_CHECK( not ov.is_initialized() );
//    }
//}
//
//BOOST_AUTO_TEST_CASE(Square_serialize)
//{
//    Square sq( {-11.77, 6.33}, {22.6, -3.9} );
//    std::ostringstream os;
//    sq.serialize( os );
//    BOOST_CHECK_EQUAL( os.str(),  "Square -11.77 6.33 22.6 -3.9\n" );
//}
//
//
//
//BOOST_AUTO_TEST_CASE(Square_deserialize)
//{
//    {
//        std::istringstream is( "Square 0 1 2 3") ;
//        const auto sq = Square::deserialize( is );
//        BOOST_CHECK( sq.is_initialized() );
//        if( sq.is_initialized() ) {
//            BOOST_CHECK_EQUAL( sq.get().vertex(0), Vector2(0,1) );
//            BOOST_CHECK_EQUAL( sq.get().vertex(1), Vector2(2,3) );
//        }
//    }
//
//    {
//        std::istringstream is( "Square 0 1 2 3 \n trololo") ;
//        const auto sq = Square::deserialize( is );
//        BOOST_CHECK( sq.is_initialized() );
//        if( sq.is_initialized() ) {
//            BOOST_CHECK_EQUAL( sq.get().vertex(0), Vector2(0,1) );
//            BOOST_CHECK_EQUAL( sq.get().vertex(1), Vector2(2,3) );
//        }
//    }
//
//    {
//        std::istringstream is( "Square 0 1 2 3 4") ;
//        const auto sq = Square::deserialize( is );
//        BOOST_CHECK( not sq.is_initialized() );
//    }
//}
//
//
//
//BOOST_AUTO_TEST_CASE(Triangle_serialize)
//{
//    Triangle triangle( {-11.77, 6.33}, {22.6, -3.9}, {66.22, 8. } );
//    std::ostringstream os;
//    triangle.serialize( os );
//    BOOST_CHECK_EQUAL( os.str(),  "Triangle -11.77 6.33 22.6 -3.9 66.22 8\n" );
//}
//
//
//
//BOOST_AUTO_TEST_CASE(Triangle_deserialize)
//{
//    std::istringstream is( "Triangle 0 1 2 3 -4 -5\n") ;
//    const auto triangle = Triangle::deserialize( is );
//    BOOST_CHECK( triangle.is_initialized() );
//    if( triangle.is_initialized() ) {
//        BOOST_CHECK_EQUAL( triangle.get().vertex(0), Vector2(0,1) );
//        BOOST_CHECK_EQUAL( triangle.get().vertex(1), Vector2(2,3) );
//        BOOST_CHECK_EQUAL( triangle.get().vertex(2), Vector2(-4,-5) );
//    }
//}
//
//
//BOOST_AUTO_TEST_CASE(Canvas_draw_overload_resolution)
//{
//    Canvas c;
//    c.draw( Polygon({}) );
//    c.draw( Circle( {0.,0.}, 1 ) );
//}


