
#ifndef PARSER_H_
#define PARSER_H_

#include "serdes.h"
#include <tuple>
#include <map>

namespace Parser_detail {

template< typename... TypesT >
std::tuple< std::vector<TypesT>... >
return_tuple_of_vectors( feature_types_t<TypesT...> ); // no implementation needed

}

template< typename FeatureTypesT >
using tuple_of_vectors_t = decltype( Parser_detail::return_tuple_of_vectors( FeatureTypesT() ) );

using FeatureVectors = tuple_of_vectors_t<Features>;



template< typename FeatureTypesT >
class Parser
{
protected:
    using this_t = Parser<FeatureTypesT>;

    using DeserializeAndPushFunc =  void (this_t::*)( std::istream& is, FeatureVectors& fv) const;

    using DeserializeAndPushFuncMap = std::map< std::string, DeserializeAndPushFunc >;

    DeserializeAndPushFuncMap _deserialize_and_push_funcs;

public:
    Parser();

    FeatureVectors
    parse( std::istream& is ) const;

    void
    parse( std::istream& is, FeatureVectors& ) const;

private:
    template< typename FeatureT  >
    void DeseriazlieAndPush( std::istream& is, FeatureVectors& fv ) const
    {
        auto feature = serdes::deserialize<FeatureT>( is );
        if( not is.fail() ) {
            std::get< std::vector<FeatureT> >( fv ).push_back( feature );
        }
    }

    template<typename T1 >
    static DeserializeAndPushFuncMap
    ConstructDeserializeAndPushFuncs()
    {
        DeserializeAndPushFuncMap funcs;
        funcs[ serdes::name<T1>() ] = &this_t::DeseriazlieAndPush<T1>;
        return funcs;
    }

    template<typename T1, typename T2, typename... Ts>
    static DeserializeAndPushFuncMap
    ConstructDeserializeAndPushFuncs()
    {
        auto funcs = ConstructDeserializeAndPushFuncs<T2, Ts...>();
        funcs[ serdes::name<T1>() ] = &this_t::DeseriazlieAndPush<T1>;
        return funcs;
    }

    template< typename... FeaturesT >
    static DeserializeAndPushFuncMap
    ConstructDeserializeAndPushFuncMap( feature_types_t< FeaturesT...> )
    {
        return ConstructDeserializeAndPushFuncs<FeaturesT...>();
    }
};



template< typename FeatureTypesT >
Parser<FeatureTypesT>::Parser()
: _deserialize_and_push_funcs( ConstructDeserializeAndPushFuncMap( FeatureTypesT() ) )
{}



template< typename FeatureTypesT >
FeatureVectors
Parser<FeatureTypesT>::parse( std::istream& is ) const
{
    FeatureVectors fv;
    parse( is, fv );
    return fv;
}



template< typename FeatureTypesT >
void
Parser<FeatureTypesT>::parse( std::istream& is, FeatureVectors& fv ) const
{
    while( is.good() ) {
        std::string feature_name;
        is >> feature_name;
        if( _deserialize_and_push_funcs.count( feature_name ) ) {
            const auto deserialize_and_push_func = _deserialize_and_push_funcs.at( feature_name );
            (this->*deserialize_and_push_func)( is, fv );
        }
        else {
            is.setstate( std::ios::failbit );
        }
    }
}



template<typename FeatureTypesT = Features >
Parser<FeatureTypesT>
make_parser()
{ return Parser<FeatureTypesT>(); }



#endif /* PARSER_H_ */
