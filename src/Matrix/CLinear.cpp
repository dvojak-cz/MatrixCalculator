#include <algorithm>
#include <iomanip>
#include "CLinear.h"

CLinear::CLinear ( const CMatrix & matrix ) : m_Rows ( matrix.m_Rows ) , m_Columns ( matrix.m_Columns )
{
    for ( unsigned i = 0 ; i < m_Rows ; ++i )
    {
        m_matrix.push_back ( std::make_unique < std::vector < T > > ( ) );
        for ( unsigned j = 0 ; j < m_Columns ; ++j )
            ( * m_matrix[ i ] ).push_back ( matrix ( i , j ) );
    }
    if ( m_Rows == m_Columns )
        for ( unsigned i = 0 ; i < m_Rows ; ++i )
        {
            ( * m_matrix[ i ] ).resize ( m_Rows * 2 , 0 );
            ( * m_matrix[ i ] )[ m_Rows + i ] = 1;
        }
    gem ( );
}
void CLinear::g1 ( unsigned int rowIndex0 , unsigned int rowIndex1 , bool log )
{
    if ( rowIndex0 >= m_Rows || rowIndex1 >= m_Rows )
        throw std::out_of_range ( "G1 invalid index" );
    if ( rowIndex1 == rowIndex0 )
        return;
    std::swap ( m_matrix[ rowIndex0 ] , m_matrix[ rowIndex1 ] );

    if ( log )
        m_deque.push_back ( "G1: r" + std::to_string ( rowIndex0 ) + " <-> r" + std::to_string ( rowIndex1 ) );
}
void CLinear::g2 ( unsigned int rowIndex , double num , bool log )
{
    if ( rowIndex >= m_Rows )
        throw std::out_of_range ( "G1 invalid index" );
    if ( num == 0 )
        throw err::math ( );
    if ( num == 1 )
        return;
    for ( auto & it : * m_matrix[ rowIndex ] )
        it *= num;

    if ( log )
    {
        std::ostringstream out;
        out.precision ( CMatrix::sc_NumberOfDecimalPlaces );
        out << "G2: r" << std::to_string ( rowIndex ) << " * " << num;
        m_deque.push_back ( out.str ( ) );
    }
}
void CLinear::g3 ( unsigned rowIndex0 , unsigned rowIndex1 , T num0 , T num1 , bool log )
{
    if ( rowIndex0 >= m_Rows || rowIndex1 >= m_Rows )
        throw std::out_of_range ( "G1 invalid index" );
    g2 ( rowIndex0 , num0 , false );
    g2 ( rowIndex1 , num1 , false );

    for ( unsigned i = 0 ; i < ( * m_matrix[ 0 ] ).size ( ) ; ++i )
        ( * m_matrix[ rowIndex1 ] )[ i ] = ( * m_matrix[ rowIndex0 ] )[ i ] + ( * m_matrix[ rowIndex1 ] )[ i ];
    g2 ( rowIndex0 , std::pow ( num0 , -1 ) , false );

    if ( log )
    {
        std::ostringstream out;
        out.precision ( CMatrix::sc_NumberOfDecimalPlaces );
        out << "G3: r" << std::to_string ( rowIndex1 ) << " = r" << std::to_string ( rowIndex0 ) << " * " << num0 <<
            " + r" << std::to_string ( rowIndex1 ) << " * " << num1;
        m_deque.push_back ( out.str ( ) );
    }

}
void CLinear::gem ( )
{
    std::pair < unsigned , T > maxElementIn;
    unsigned col = 0;
    unsigned row = 0;
    for ( ; row < m_Rows && col < m_Columns ; ++row , ++col )
    {
        maxElementIn = std::make_pair < unsigned , T > ( 0 , 0. );
        //find max value in col, move it to the top
        for ( unsigned i = row ; i < m_Rows ; ++i )
            if ( maxElementIn.second <= std::abs ( ( * m_matrix[ i ] )[ col ] ) )
                maxElementIn = std::make_pair ( i , std::abs ( ( * m_matrix[ i ] )[ col ] ) );
        if ( maxElementIn.first != row )
            signOfDeterminant *= -1;
        g1 ( maxElementIn.first , row );
        //check if coll is main
        if ( my::DoubleEpsilon ( maxElementIn.second , 0 ) == 0 )
        {
            --row;
            continue;
        }
        // make all rows below 0
        for ( unsigned i = row + 1 ; i < m_Rows ; ++i )
        {
            double mutipicativeCon = -( * m_matrix[ i ] )[ col ] / ( * m_matrix[ row ] )[ col ];
            if ( !mutipicativeCon ) continue;
            g3 ( row , i , mutipicativeCon );
            ( * m_matrix[ i ] )[ col ] = 0;
        }
    }
    if ( row < m_Rows && m_Rows == m_Columns )
        for ( unsigned i = 0 ; i < m_Rows ; ++i )
            ( * m_matrix[ i ] ).resize ( m_Columns );
    m_range = row;
}
void CLinear::inverse ( )
{
    m_inverse = std::make_optional ( std::vector < std::vector < T > > ( ) );
    // copy
    for ( unsigned i = 0 ; i < m_Rows ; ++i )
    {
        m_inverse->push_back ( std::vector < T > ( ) );
        for ( unsigned j = 0 ; j < m_Rows * 2 ; ++j )
            ( * m_inverse )[ i ].push_back ( ( * m_matrix[ i ] )[ j ] );
    }
    // make diag = 1 (A[i][i] = 0)
    for ( unsigned i = 0 ; i < m_Rows ; ++i )
        for ( unsigned j = 0 ; j < m_Rows * 2 ; ++j )
            ( * m_inverse )[ i ][ j ] /= ( * m_matrix[ i ] )[ i ];

    // count inverse
    for ( long int rowIAdd = m_Rows - 1 ; rowIAdd >= 0 ; --rowIAdd )
        for ( unsigned rowIChange = 0 ; rowIChange < rowIAdd ; ++rowIChange )
        {
            double mutipicativeCon = -( ( * m_inverse )[ rowIChange ][ rowIAdd ] );
            for ( unsigned col = 0 ; col < m_Rows * 2 ; ++col )
                ( * m_inverse )[ rowIChange ][ col ] += ( * m_inverse )[ rowIAdd ][ col ] * mutipicativeCon;

        }

    for ( unsigned i = 0 ; i < m_Rows ; ++i )
    {
        ( * m_inverse )[ i ].erase ( ( * m_inverse )[ i ].begin ( ) , ( * m_inverse )[ i ].begin ( ) + m_Rows );
        ( * m_matrix[ i ] ).resize ( m_Columns );
    }
}

unsigned int CLinear::GetRange ( ) const { return m_range; }
T CLinear::GetDeterminant ( ) const
{
    T res = signOfDeterminant;
    if ( m_Rows == m_Columns )
        for ( unsigned i = 0 ; i < m_Rows ; ++i )
            res *= ( * m_matrix[ i ] )[ i ];
    else throw err::math ( );
    return res;
}
std::shared_ptr < CMatrix > CLinear::gemGem ( ) const
{
    std::deque < T > deque;
    unsigned nulCounter = 0;

    for ( unsigned i = 0 ; i < m_Rows ; ++i )
        for ( unsigned j = 0 ; j < m_Columns ; ++j )
        {
            if ( ( * m_matrix[ i ] )[ j ] == 0 )
                ++nulCounter;
            deque.push_back ( ( * m_matrix[ i ] )[ j ] );
        }

    return CMatrix::generateNew ( deque , nulCounter , m_Rows , m_Columns );
}
std::shared_ptr < CMatrix > CLinear::GetInverse ( )
{
    if ( m_Rows != m_Columns || m_Rows != m_range )
        throw err::math ( );
    if ( !m_inverse->empty ( ) )
    {
        std::deque < T > deque;
        unsigned nulCounter = 0;

        for ( unsigned i = 0 ; i < m_Rows ; ++i )
            for ( unsigned j = 0 ; j < m_Columns ; ++j )
            {
                if ( ( * m_inverse )[ i ][ j ] == 0 )
                    ++nulCounter;
                deque.push_back ( ( * m_inverse )[ i ][ j ] );
            }

        return CMatrix::generateNew ( deque , nulCounter , m_Rows , m_Columns );
    }
    inverse ( );
    return this->GetInverse ( );
}
const std::deque < std::string > & CLinear::GetGemInfo ( ) const
{
    return m_deque;
}
