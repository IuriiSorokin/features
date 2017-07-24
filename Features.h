/*
 * Features.h
 *
 *  Created on: 24 Jul 2017
 *      Author: sorokin
 */

#ifndef FEATURES_H_
#define FEATURES_H_

#include "Circle.h"
#include "Polygon.h"
#include "Square.h"
#include "Triangle.h"
#include <type_traits>

template<typename... FeatureT>
struct feature_types_t
{};

using Features = feature_types_t<Circle, Polygon, Square, Triangle>;



namespace Features_detail {

template<typename TypeT, typename... FeaturesT >
struct is_feature_compare_recursively;



template<typename TypeT, typename FeatureT >
struct is_feature_compare_recursively<TypeT, FeatureT> {
    static constexpr bool value = std::is_same<TypeT, FeatureT>::value;
};



template<typename TypeT, typename Feature1T, typename Feature2T, typename... FeaturesT>
struct is_feature_compare_recursively<TypeT, Feature1T, Feature2T, FeaturesT... > {
    static constexpr bool value = std::is_same<TypeT, Feature1T>::value
                                    or is_feature_compare_recursively<TypeT, Feature2T, FeaturesT... >::value;
};



template<typename TypeT, typename... FeaturesT>
static constexpr bool
is_feature_unpack_feature_types( feature_types_t<FeaturesT...> )
{
    return is_feature_compare_recursively< TypeT, FeaturesT... >::value;
}

}



template<typename TypeT>
struct is_feature {
    static constexpr bool value = Features_detail::is_feature_unpack_feature_types<TypeT>( Features() );
};

#endif /* FEATURES_H_ */
