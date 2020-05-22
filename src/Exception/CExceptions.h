#include <exception>
#include <cfloat>
#include <cmath>

namespace err
{
    class math : public std::exception { };

    class input_stream : public std::exception { };

    class invalid_dimensions : public std::exception { };
}

namespace my
{
    inline double DoubleEpsilon ( double lhs , double rhs , int constant = 1e4 )
    {
        return ( std::abs ( lhs - rhs ) <= constant * DBL_EPSILON ) ? 0 : ( lhs - rhs );
    }
}
