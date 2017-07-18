
#ifndef SQUARE_H_
#define SQUARE_H_

#include "Vector2.h"

class Square
{
public:
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




    std::ostream&
    serialize( std::ostream& os ) const
    {
        os << name() << " ";
        _v0.serialize(os);
        os << " ";
        _v1.serialize(os);
        os << "\n";
        return os;
    }

    static boost::optional<Square>
    deserialize( std::istream& is )
    {
        std::string read_name;
        is >> read_name;
        if( read_name != name() ) {
            return {};
        }

        const auto v0 = Vector2::deserialize( is );
        const auto v1 = Vector2::deserialize( is );

        if( not v0.is_initialized() or not v1.is_initialized() ) {
            return {};
        }

        return Square(v0.get(), v1.get());
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



#endif /* SQUARE_H_ */
