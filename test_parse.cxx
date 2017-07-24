
#define BOOST_TEST_MODULE deser test
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <map>

#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Polygon.h"


template< typename... Types >
struct set_of_types_t
{};

template< typename... Types >
std::tuple< std::vector<Types>... >
return_tuple_of_vectors( set_of_types_t<Types...> ); // no implementation needed

template< typename Tuple >
using tuple_of_vectors_t = decltype( return_tuple_of_vectors( Tuple() ) );


// using Features = set_of_types_t<Square,Triangle,Circle,Polygon>;
using Features = set_of_types_t<Square,Circle>;

// using FeatureVectors = tuple_of_vectors_t<Features>;



template< typename... Types >
class Parser
{
    using SetOfFeatureTypes = set_of_types_t<Types...>;
    using FeatureVectors = tuple_of_vectors_t<SetOfFeatureTypes>;

protected:
    using this_t = Parser<Types...>;

    using DeserializeAndPushFunc =  void (this_t::*)( std::istream& is, FeatureVectors& fv);

    using DeserializeAndPushFuncs = std::map< std::string, DeserializeAndPushFunc >;

    DeserializeAndPushFuncs _deserialize_and_push_funcs;

    template< typename FeatureT  >
    void DeseriazlieAndPush( std::istream& is, FeatureVectors& fv )
    {
        auto feature = FeatureT::deserialize( is );
        std::get< std::vector<FeatureT> >( fv ).push_back( feature );
    }

    template<typename T1 >
    static DeserializeAndPushFuncs
    ConstructDeserializeAndPushFuncs()
    {
        DeserializeAndPushFuncs funcs;
        funcs[ T1::name() ] = &this_t::DeseriazlieAndPush<T1>;
        return funcs;
    }

    template<typename T1, typename T2, typename... Ts>
    static DeserializeAndPushFuncs
    ConstructDeserializeAndPushFuncs()
    {
        auto funcs = ConstructDeserializeAndPushFuncs<T2, Ts...>();
        funcs[ T1::name() ] = &this_t::DeseriazlieAndPush<T1>;
        return funcs;
    }


public:
    Parser() {
        _deserialize_and_push_funcs = ConstructDeserializeAndPushFuncs<Types...>();
    }

    FeatureVectors
    parse( std::istream& is )
    {
        FeatureVectors fv;

        while( not is.eof() ) {
            std::string n;
            is >> n;
            const auto& parse_func = _deserialize_and_push_funcs.at( n );
            (this->*parse_func)( is, fv );
        }

        return fv;
    }
};



template<typename... Types, typename... Args >
Parser<Types...>
make_parser( set_of_types_t<Types...> t, Args... args )
{
    return Parser<Types...>( std::forward(args)... );
}



BOOST_AUTO_TEST_CASE(aa)
{
    auto p = Parser<Circle,Square>();

    std::istringstream is( "Circle 5.2 6.3 1.7" );

    auto fv = p.parse( is );

    DBG( std::get< std::vector<Circle> >( fv ).at(0) );
}
