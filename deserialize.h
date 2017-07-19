/*
 * deserialize.h
 *
 *  Created on: 18 Jul 2017
 *      Author: sorokin
 */

#ifndef DESERIALIZE_H_
#define DESERIALIZE_H_

#include <iostream>
#include <tuple>
#include <utility>
#include "dbg.h"


namespace deserialize_detail
{

template< typename First, typename... Other >
std::tuple<Other...>
without_first_element_impl( std::tuple<First, Other...> );
// no implementation needed

}



template< typename Tuple>
struct without_first_element {
    using type = decltype(deserialize_detail::without_first_element_impl(Tuple()));
};



template< typename Tuple >
using without_first_element_t = typename without_first_element<Tuple>::type;



template< typename Tuple,
          template<typename> class Func,
          std::enable_if_t< std::tuple_size<Tuple>::value == 0, bool > = true >
void
for_each_tuple_type_impl()
{}



template< typename Tuple,
          template<typename> class Func,
          typename First = typename std::tuple_element<0,Tuple>::type,
          typename Other = without_first_element_t<Tuple> >
void
for_each_tuple_type_impl()
{
    Func<First>()();
    for_each_tuple_type_impl<Other, Func>();
}



template< typename Tuple, template<typename> class Func >
void
for_each_tuple_type()
{
    for_each_tuple_type_impl<Tuple,Func>();
}



template< typename... Features >
std::tuple< std::vector<Features>... >
tuple_of_vectors_impl( std::tuple<Features...> );
// no implementation needed

template< typename FeaturesTuple >
using tuple_of_vectors_t = decltype(tuple_of_vectors_impl(FeaturesTuple()));



template<typename FeaturesTuple,
         size_t Index = 0,
         std::enable_if_t< (Index < std::tuple_size<FeaturesTuple>::value), bool > = true >
bool
try_deserialize( std::string line, tuple_of_vectors_t<FeaturesTuple>& features )
{
    using Feature = typename std::tuple_element<Index, FeaturesTuple>::type;
    Feature feature;
    if( not (std::istringstream(line) >> feature).fail() ) {
        std::get< std::vector<Feature> >( features ).push_back( feature );
        return true;
    }
    return try_deserialize<FeaturesTuple, Index + 1>( line, features );
}



template<typename FeaturesTuple,
         size_t Index,
         std::enable_if_t< (Index == std::tuple_size<FeaturesTuple>::value), bool > = true >
bool
try_deserialize( std::string line, tuple_of_vectors_t<FeaturesTuple>& features )
{
    return false;
}



template< typename FeaturesTuple >
tuple_of_vectors_t<FeaturesTuple >
deserialize( std::istream& is ) {

    tuple_of_vectors_t<FeaturesTuple> features;

    while( not is.eof() ) {
        std::string line;
        std::getline( is, line );

        if( false == try_deserialize<FeaturesTuple>( line, features ) ) {
            std::cout << "Error parsing line [" << line << "]" << std::endl;
        }
    }

    return features;
}




/////////////////

//
//
//template< typename Tuple,
//          template<typename> class Func,
//          std::enable_if_t< std::tuple_size<Tuple>::value == 0, bool > = true >
//void
//for_each_tuple_type_impl2(Func func)
//{}
//
//
//
//template< typename Tuple,
//          typename Func,
//          typename First = typename std::tuple_element<0,Tuple>::type,
//          typename Other = without_first_element_t<Tuple> >
//void
//for_each_tuple_type_impl2( Func func )
//{
//    func.operator()<First>();
//    for_each_tuple_type_impl2<Other, Func>( func );
//}
//
//
//
//template< typename Tuple, typename Functor,  >
//void
//for_each_tuple_type2( Func func )
//{
//    for_each_tuple_type_impl2<Tuple,Func>( func );
//}



//template< typename First>
//void
//print_type()
//{
//    std::cout << typeid(First).name() << std::endl;
//}
//
//
//
//template< typename Tuple,
//          typename std::enable_if< std::tuple_size<Tuple>::value == 0, bool >::type = true >
//void
//print_types()
//{
//    TRACE;
//}
//
//
//
//template< typename Tuple,
//          typename First = typename std::tuple_element<0,Tuple>::type,
//          typename Other = without_first_element_t<Tuple> >
//void
//print_types()
//{
//    TRACE;
//    print_type<First>();
//    print_types<Other>();
//}






#endif /* DESERIALIZE_H_ */
