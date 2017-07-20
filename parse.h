
#ifndef PARSE_H_
#define PARSE_H_

#include <iostream>
#include <tuple>
#include <utility>
#include <exception>
#include "dbg.h"


class parsing_failure : public std::ios::failure
{
private:
    std::string _line;
public:
    parsing_failure( std::string line )
    : std::ios_base::failure( std::string("Failed parsing line \"")  + line + "\"." )
    , _line( line )
    {}

    std::string
    line() const
    { return _line; }
};



namespace parse_detail {

template< typename... Types >
std::tuple< std::vector<Types>... >
return_tuple_of_vectors( std::tuple<Types...> ); // no implementation needed

} /* namespace deserialize_detail */



/**
 *  Make type
 *      std::tuple< std::vector<TypeA>,
 *                  std::vector<TypeB>,
 *                  std::vector<TypeC>,
 *                  ...                    >
 *  from type
 *      std::tuple< TypeA,
 *                  TypeB,
 *                  TypeC,
 *                  ....      >
 *
 *  TypeA, TypeB, TypeC,... must be default-constructible.
 */
template< typename Tuple >
using tuple_of_vectors_t = decltype( parse_detail::return_tuple_of_vectors( Tuple() ) );



namespace parse_detail {

template<typename FeatureTypes,
         size_t Index,
         std::enable_if_t< (Index == std::tuple_size<FeatureTypes>::value), bool > = true >
void
parse_line( std::string line, tuple_of_vectors_t<FeatureTypes>& feature_vectors )
{
    throw parsing_failure(line);
}

template<typename FeatureTypes,
         size_t Index = 0,
         std::enable_if_t< (Index < std::tuple_size<FeatureTypes>::value), bool > = true >
void
parse_line( std::string line, tuple_of_vectors_t<FeatureTypes>& feature_vectors )
{
    using Feature = typename std::tuple_element<Index, FeatureTypes>::type;
    Feature feature;
    std::istringstream is( line );
    is >> feature;
    if( not is.fail() ) {
        std::get< std::vector<Feature> >( feature_vectors ).push_back( feature );
        return;
    }
    parse_line<FeatureTypes, Index + 1>( line, feature_vectors );
}

bool
is_empty( std::string s ) {
    for( auto c : s ) {
        if( not std::isspace(c) ) {
            return false;
        }
    }
    return true;
}

} /* namespace deserialize_detail */



template< typename FeatureTypes >
void
parse( std::istream& is, tuple_of_vectors_t<FeatureTypes>& feature_vectors )
{
    while( not is.eof() ) {
        std::string line;
        std::getline( is, line );
        if( is.fail() ) {
            // if exceptions in "is" enabled, "is" shall throw
            // otherwise, the error is signalized by the fail flag
            break;
        }

        if( parse_detail::is_empty( line ) ) {
            continue;
        }

        try {
            parse_detail::parse_line<FeatureTypes>( line, feature_vectors );
        } catch ( parsing_failure& pf ) {
            if ( is.exceptions() & std::ios::failbit ) {
                throw;
            }
            is.setstate( std::ios::failbit );
            break;
        }
    }
}



template< typename FeatureTypes >
tuple_of_vectors_t<FeatureTypes >
parse( std::istream& is ) {
    tuple_of_vectors_t<FeatureTypes> feature_vectors;
    parse<FeatureTypes>( is, feature_vectors );
    return feature_vectors;
}



#endif /* PARSE_H_ */
