/*
 * streamers.h
 *
 *  Created on: 24 Jul 2017
 *      Author: sorokin
 */

#ifndef STREAMERS_H_
#define STREAMERS_H_

#include "Features.h"
#include "serdes.h"

inline std::ostream&
operator<<( std::ostream& os, const Vector2& v )
{
    serdes::serialize( v, os );
    return os;
}



template<typename FeatureT,
         std::enable_if_t< is_feature<FeatureT>::value, bool> = true >
inline std::ostream&
operator<<( std::ostream& os, const FeatureT& feature )
{
    serdes::serialize_with_name( feature, os );
    return os;
}


#endif /* STREAMERS_H_ */
