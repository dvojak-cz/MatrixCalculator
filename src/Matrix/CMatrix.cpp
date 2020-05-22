#include "CMatrix.h"
#include <istream>
#include <iomanip>
#include <climits>
#include "../Exception/CExceptions.h"
#include "CSparseMatrix.h"
#include "CDenseMatrix.h"

class CDenseMatrix;

class CSparseMatrix;

typedef double T;

CMatrix::CMatrix ( unsigned rows , unsigned columns )
        : m_Rows ( rows ) , m_Columns ( columns )
{
    if ( rows == 0 || columns == 0 )
        throw err::invalid_dimensions ( );

    m_Rows = rows;
    m_Columns = columns;
}
T CMatrix::operator () ( unsigned int row , unsigned int col ) const
{
    if ( row >= m_Rows || col >= m_Columns )
        throw err::invalid_dimensions ( );

    return T ( );
}

std::shared_ptr < CMatrix > CMatrix::Cut ( unsigned row0 , unsigned coll0 , unsigned row1 , unsigned coll1 ) const
{
    if ( row1 > CMatrix::m_Rows || coll1 > CMatrix::m_Columns || row1 <= row0 || coll1 <= coll0 )
        throw err::invalid_dimensions ( );

    unsigned nulCounter = 0;
    std::deque < T > deque;
    for ( unsigned i = row0 ; i < row1 ; ++i )
        for ( unsigned j = coll0 ; j < coll1 ; ++j )
        {
            if ( !my::DoubleEpsilon ( ( * this ) ( i , j ) , 0 ) )
                ++nulCounter;
            deque.push_back ( ( * this ) ( i , j ) );
        }

    return CMatrix::generateNew ( deque , nulCounter , row1 - row0 , coll1 - coll0 );
}
std::shared_ptr < CMatrix > CMatrix::mergeHorizontally ( const CMatrix & rhs , bool ) const
{
    if ( m_Rows != rhs.m_Rows )
        throw err::invalid_dimensions ( );

    return nullptr;
}
std::shared_ptr < CMatrix > CMatrix::mergeVertically ( const CMatrix & rhs , bool ) const
{
    if ( m_Columns != rhs.m_Columns )
        throw err::invalid_dimensions ( );

    return nullptr;
}

std::shared_ptr < CMatrix > CMatrix::operator + ( const CMatrix & rhs ) const
{
    if ( std::tie ( m_Rows , m_Columns ) != std::tie ( rhs.m_Rows , rhs.m_Columns ) )
        throw err::invalid_dimensions ( );

    std::deque < T > deque;
    unsigned nulCounter = 0;

    for ( unsigned i = 0 ; i < m_Rows ; ++i )
        for ( unsigned j = 0 ; j < m_Columns ; ++j )
        {
            T value = ( * this ) ( i , j ) + rhs ( i , j );
            deque.push_back ( value );
            if ( !my::DoubleEpsilon ( value , 0 ) )
                ++nulCounter;
        }

    return generateNew ( deque , nulCounter , m_Rows , m_Columns );
}
std::shared_ptr < CMatrix > CMatrix::operator - ( const CMatrix & rhs ) const
{
    if ( std::tie ( m_Rows , m_Columns ) != std::tie ( rhs.m_Rows , rhs.m_Columns ) )
        throw err::invalid_dimensions ( );

    std::deque < T > deque;
    unsigned nulCounter = 0;

    for ( unsigned i = 0 ; i < m_Rows ; ++i )
        for ( unsigned j = 0 ; j < m_Columns ; ++j )
        {
            T value = ( * this ) ( i , j ) - rhs ( i , j );
            deque.push_back ( value );
            if ( !my::DoubleEpsilon ( value , 0 ) )
                ++nulCounter;
        }

    return generateNew ( deque , nulCounter , m_Rows , m_Columns );
}
std::shared_ptr < CMatrix > CMatrix::operator * ( const CMatrix & rhs ) const
{
    if ( m_Columns != rhs.m_Rows )
        throw err::invalid_dimensions ( );

    std::deque < T > deque;
    unsigned nulCounter = 0;

    for ( unsigned i = 0 ; i < m_Rows ; ++i )
        for ( unsigned j = 0 ; j < rhs.m_Columns ; ++j )
        {
            T value = 0;
            for ( unsigned k = 0 ; k < m_Columns ; ++k )
                value += ( * this ) ( i , k ) * rhs ( k , j );
            deque.push_back ( value );
            if ( !my::DoubleEpsilon ( value , 0 ) )
                ++nulCounter;
        }

    return generateNew ( deque , nulCounter , m_Rows , rhs.m_Columns );
}

std::ostream & operator << ( std::ostream & os , const CMatrix & matrix )
{
    return matrix.Print ( os , false );
}
std::ostream & CMatrix::Print ( std::ostream & os , bool toFile ) const
{
    if ( toFile )
    {
        os << CMatrix::m_Rows << 'x' << CMatrix::m_Columns << "\n";
        for ( unsigned i = 0 ; i < CMatrix::m_Rows ; ++i )
        {
            for ( unsigned j = 0 ; j < CMatrix::m_Columns ; ++j )
                os << ( * this ) ( i , j ) << ' ';
            os << '\n';
            if ( !os.good ( ) )
                throw err::input_stream ( );
        }
    }
    else
    {
        for ( unsigned i = 0 ; i < CMatrix::m_Rows ; ++i )
        {
            os << std::fixed << std::setprecision ( sc_NumberOfDecimalPlaces );
            os << "(";
            for ( unsigned j = 0 ; j < CMatrix::m_Columns ; ++j )
                os << std::setprecision ( sc_NumberOfDecimalPlaces ) << std::setw ( this->m_spaceNeededToPrintMaxVal + sc_NumberOfDecimalPlaces + 2 )
                   << ( * this ) ( i , j ) << ' ';
            os << ")\n";
        }
    }
    return os;
}

std::shared_ptr < CMatrix > CMatrix::Scan ( std::istream & is , unsigned row , unsigned coll )
{
    T value = 0;
    unsigned nulCounter = 0;
    std::deque < T > deque;
    for ( unsigned i = 0 ; i < row ; ++i )
        for ( unsigned j = 0 ; j < coll ; ++j )
        {
            if ( !( is >> value ) )
            {
                is.setstate ( std::ios::failbit );
                throw err::input_stream ( );
            }
            if ( !my::DoubleEpsilon ( value , 0 ) )
                ++nulCounter;
            deque.push_back ( value );
        }
    is.ignore ( INT_MAX , '\n' );

    return generateNew ( deque , nulCounter , row , coll );
}
std::shared_ptr < CMatrix > CMatrix::generateNew ( std::deque < T > & deque , unsigned nulCounter , unsigned row , unsigned coll )
{
    if ( nulCounter > row * coll * CMatrix::sc_SparseNullStatic )
    {
        CSparseMatrix res ( row , coll );
        res.m_NumberOfNulls = nulCounter;
        return res.CreateNew ( deque );
    }
    CDenseMatrix res ( row , coll );
    res.m_NumberOfNulls = nulCounter;
    return res.CreateNew ( deque );
}
