/*
 * Canvas.h
 *
 *  Created on: 17 Jul 2017
 *      Author: sorokin
 */

#ifndef CANVAS_H_
#define CANVAS_H_

#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Polygon.h"
#include <type_traits>
#include <cmath>

// A class that can draw various features
class Canvas
{
public:
    virtual
    ~Canvas() = default;

    template< typename FeatureT,
        typename std::enable_if<
        std::is_same< decltype( ((FeatureT*)nullptr)->FeatureT::vertex(0)    ), Vector2 >::value and
        std::is_same< decltype( ((FeatureT*)nullptr)->FeatureT::n_vertices() ), size_t >::value, bool>::type _enable = true >
    void
    draw( FeatureT feature ) {
        for( size_t iVtx = 0; iVtx < feature.n_vertices(); ++iVtx ) {
            // const auto iNextVtx = (iVtx + 1) % feature.n_vertices();
            // const auto v1 = feature.vertex(iVtx);
            // const auto v2 = feature.vertex(iNextVtx);
        }
    }

    void
    draw( Circle circle ) {
    }

};

#endif /* CANVAS_H_ */
