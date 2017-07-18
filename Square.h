
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

    static std::string
    name()
    { return "Square"; }

    friend std::istream&
    operator>>( std::istream& is, Square& v);

    std::ostream&
    print( std::ostream& os ) {
        os << name();
        for( size_t iVtx = 0; iVtx < n_vertices(); ++iVtx ) {
            os << " " << vertex(iVtx);
        }
        return os;
    }

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



inline std::ostream&
operator<<( std::ostream& os, const Square& square )
{
    return os << square.name() << " "
            << square.vertex(0) << " "
            << square.vertex(1);
}



inline  std::istream&
operator>>( std::istream& is, Square& square)
{
    std::string read_name;
    is >> read_name
        >> square._v0
        >> square._v1;
    if( read_name != Square::name() ) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

#endif /* SQUARE_H_ */
