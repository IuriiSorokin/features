
#ifndef SQUARE_H_
#define SQUARE_H_

#include "Vector2.h"
#include <iostream>

class Square
{
public:
    Square() = default;

    Square( Vector2 v0, Vector2 v1  )
    : _v0( v0 ), _v1( v1 )
    {}

    static constexpr size_t
    n_vertices()
    { return 4; }

    Vector2
    vertex( size_t i ) const;

private:
    Vector2 _v0;
    Vector2 _v1;
};



inline Vector2
Square::vertex( size_t i ) const
{
    auto rotate_plus_90_deg = [](Vector2 v){ return Vector2(  -v.y(), v.x() ); };

    switch( i ) {
        case 0: {
            return _v0;
        }
        case 1: {
            return _v1;
        }
        case 2: {
            return _v1 + rotate_plus_90_deg( _v1 - _v0 );
        }
        case 3: {
            return _v0 + rotate_plus_90_deg( _v1 - _v0 );
        }
    }

    throw std::out_of_range( std::string("Invalid vertex id ") + std::to_string(i) );
}



inline bool
operator==( const Square& lhs, const Square& rhs )
{
    return lhs.vertex(0) == rhs.vertex( 0 )
            and lhs.vertex( 1 ) == rhs.vertex( 1 );
}



inline bool
operator!=( const Square& lhs, const Square& rhs )
{
    return not (lhs == rhs);
}


#endif /* SQUARE_H_ */
