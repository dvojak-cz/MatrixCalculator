#include "CSparseMatrix.h"
#include <algorithm>
#include "../Exception/CExceptions.h"

typedef double T;

CSparseMatrix::CSparseMatrix ( unsigned int rows , unsigned int columns )
        : CMatrix ( rows , columns ) { }
std::shared_ptr < CMatrix > CSparseMatrix::Clone ( ) const
{
    return std::make_shared < CSparseMatrix > ( * this );
}
T CSparseMatrix::operator () ( unsigned int row , unsigned int col ) const
{
    CMatrix::operator () ( row , col );

    auto it = m_Map.find ( std::make_pair ( row , col ) );
    if ( it == m_Map.end ( ) )
        return 0;
    return it->second;
}
std::shared_ptr < CMatrix > CSparseMatrix::Transpose ( ) const
{
    CSparseMatrix res ( m_Columns , m_Rows );

    for ( const auto &[key , val]: m_Map )
        res.m_Map.insert ( std::make_pair ( std::make_pair ( key.second , key.first ) , val ) );

    res.CountNumberOfNulls ( );
    return res.Clone ( );
}

std::shared_ptr < CMatrix > CSparseMatrix::CreateNew ( std::deque < T > & deque )
{
    T maxAbsVal = 0;
    for ( unsigned i = 0 ; i < CMatrix::m_Rows * CMatrix::m_Columns ; ++i )
    {
        T value;
        value = deque.front ( );
        deque.pop_front ( );

        if ( !my::DoubleEpsilon ( value , 0 ) )
            continue;

        maxAbsVal = std::max ( maxAbsVal , std::abs ( value ) );

        unsigned first = i / CMatrix::m_Columns;
        unsigned second = i - ( i / CMatrix::m_Columns * CMatrix::m_Columns );

        m_Map.insert ( std::make_pair ( std::make_pair ( first , second ) , value ) );
    }
    m_spaceNeededToPrintMaxVal = std::to_string ( ( int ) maxAbsVal ).length ( );
    return this->Clone ( );
}
std::shared_ptr < CMatrix > CSparseMatrix::mergeHorizontally ( const CMatrix & rhs , bool rightOrder ) const
{
    CMatrix::mergeHorizontally ( rhs );
    if ( rhs.m_NumberOfNulls + this->m_NumberOfNulls <= rhs.m_Rows * ( rhs.m_Columns + this->m_Columns ) * CMatrix::sc_SparseNullStatic )
        return rhs.mergeHorizontally ( * this , false );

    CSparseMatrix res ( m_Rows , m_Columns + rhs.m_Columns );

    if ( rightOrder )
        res.m_Map = m_Map;
    else
        for ( auto &[key , val] : m_Map )
            res.m_Map.insert ( std::make_pair ( std::make_pair ( key.first , key.second + rhs.m_Columns ) , val ) );

    for ( unsigned i = 0 ; i < rhs.m_Rows ; ++i )
        for ( unsigned j = 0 ; j < rhs.m_Columns ; ++j )
            if ( my::DoubleEpsilon ( rhs ( i , j ) , 0 ) )
            {
                if ( rightOrder )
                    res.m_Map.insert ( std::make_pair ( std::make_pair ( i , j + m_Columns ) , rhs ( i , j ) ) );
                else
                    res.m_Map.insert ( std::make_pair ( std::make_pair ( i , j ) , rhs ( i , j ) ) );

            }


    res.m_NumberOfNulls = rhs.m_NumberOfNulls + this->m_NumberOfNulls;
    res.m_spaceNeededToPrintMaxVal = std::max ( res.m_spaceNeededToPrintMaxVal , res.m_spaceNeededToPrintMaxVal );
    return res.Clone ( );
}
std::shared_ptr < CMatrix > CSparseMatrix::mergeVertically ( const CMatrix & rhs , bool rightOrder ) const
{
    CMatrix::mergeVertically ( rhs );

    if ( rhs.m_NumberOfNulls + this->m_NumberOfNulls <= rhs.m_Columns * ( rhs.m_Rows + this->m_Rows ) * CMatrix::sc_SparseNullStatic )
        return rhs.mergeVertically ( * this , false );

    CSparseMatrix res ( m_Rows + rhs.m_Rows , m_Columns );

    if ( rightOrder )
        res.m_Map = m_Map;
    else
        for ( auto &[key , val] : m_Map )
            res.m_Map.insert ( std::make_pair ( std::make_pair ( key.first + rhs.m_Rows , key.second ) , val ) );

    for ( unsigned i = 0 ; i < rhs.m_Rows ; ++i )
        for ( unsigned j = 0 ; j < rhs.m_Columns ; ++j )
            if ( my::DoubleEpsilon ( rhs ( i , j ) , 0 ) )
            {
                if ( rightOrder )
                    res.m_Map.insert ( std::make_pair ( std::make_pair ( i + m_Rows , j ) , rhs ( i , j ) ) );
                else
                    res.m_Map.insert ( std::make_pair ( std::make_pair ( i , j ) , rhs ( i , j ) ) );
            }

    res.m_NumberOfNulls = rhs.m_NumberOfNulls + this->m_NumberOfNulls;
    res.m_spaceNeededToPrintMaxVal = std::max ( res.m_spaceNeededToPrintMaxVal , res.m_spaceNeededToPrintMaxVal );
    return res.Clone ( );
}
void CSparseMatrix::CountNumberOfNulls ( )
{
    CMatrix::m_NumberOfNulls = m_Rows * m_Columns - m_Map.size ( );
}
