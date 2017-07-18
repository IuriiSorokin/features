
#ifndef TRIANGLE_H_
#define TRIANGLE_H_

class Triangle
{
public:
    Triangle( Vector2 v0, Vector2 v1, Vector2 v2 )
    : _vertices( { v0, v1, v2 } )
    {}

    Vector2
    vertex( size_t i ) const
    { return _vertices.at(i); } // array::at() check that i <= 3. Don't perform additional check.

    static constexpr size_t
    n_vertices()
    { return _n_vertices; }

    static std::string
    name()
    { return "Triangle"; }

    std::ostream&
    serialize( std::ostream& os ) const
    {
        os << name();
        for( const auto& v : _vertices ) {
            os << " ";
            v.serialize( os );
        }
        os << "\n";
        return os;
    }

    static boost::optional<Triangle>
    deserialize( std::istream& is )
    {
        std::array<Vector2, _n_vertices> vertices;

        std::string read_name;
        is >> read_name;

        if( read_name != name() ) {
            return {};
        }

        for( size_t i_vtx = 0; i_vtx < _n_vertices; ++i_vtx ) {
            auto vertex = Vector2::deserialize( is );
            if( not vertex.is_initialized() or is.bad() or is.fail() )  {
                return {};
            }
            vertices.at(i_vtx) = vertex.get();
        }

        return boost::optional<Triangle>( Triangle( vertices.at(0), vertices.at(1), vertices.at(2) ) ) ;
    }

private:
    static constexpr size_t _n_vertices = 3;
    std::array< Vector2, _n_vertices> _vertices; // One may consider changing to std::vector to make the _vertices movable
                                                 // at the cost of dynamic memory allocation during construction
};

#endif /* TRIANGLE_H_ */
