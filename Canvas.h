/*
 * Canvas.h
 *
 *  Created on: 17 Jul 2017
 *      Author: sorokin
 */

#ifndef CANVAS_H_
#define CANVAS_H_

#include "Features.h"
#include <type_traits>
#include "streamers.h"

// A class that can draw various features
class Canvas
{
public:
    virtual
    ~Canvas() = default;

    template< typename FeatureT,
              enable_if_has_vertices_t<FeatureT, bool> = true >  // "Has vertices" does not necessarily mean "Consist only of vertices", but here assumed so.
    void
    draw( FeatureT feature ) {
        for( size_t iVtx = 0; iVtx < feature.n_vertices(); ++iVtx ) {
             const auto iNextVtx = (iVtx + 1) % feature.n_vertices();
             const auto v0 = feature.vertex(iVtx);
             const auto v1 = feature.vertex(iNextVtx);
             drawLine( v0, v1 );
        }
    }

    void
    draw( Circle circle ) {
        drawCircle( circle.center(), circle.radius() );
    }

protected:
    virtual void
    drawLine( Vector2 v0, Vector2 v1 )
    {}

    virtual void
    drawCircle( Vector2 center, double radius )
    {}
};

#endif /* CANVAS_H_ */
