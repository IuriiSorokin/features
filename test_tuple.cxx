#define BOOST_TEST_MODULE deser test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "deserialize.h"

#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Polygon.h"


template<typename T>
struct F
{
    void
    operator()() {
        std::cout << typeid(T).name() << std::endl;
    }
};



struct G
{
    template<typename T>
    void
    process(){
        std::cout << typeid(T).name() << std::endl;
    }
};




BOOST_AUTO_TEST_CASE(deser_tuple)
{
    using Features = std::tuple<
            Circle,
            Square,
            Triangle,
            Polygon>;

    std::istringstream is(
            "Square 1 1 2 2\n"
            "Square 2 2 4 4\n"
            "Triangle -3 -3 -2 -2 1 1\n"
            "Circle -3 -3 5" );

    auto features = deserialize<Features>( is );

    std::cout << "\n\n*** Squares: ***" << std::endl;
    for( auto sq : std::get< std::vector<Square> >( features ) ) {
        std::cout << sq << std::endl;
    }

    std::cout << "\n\n*** Triangles: ***" << std::endl;
    for( auto triangle : std::get< std::vector<Triangle> >( features )) {
        std::cout << triangle << std::endl;
    }
}
