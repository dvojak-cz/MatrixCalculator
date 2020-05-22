#include "CDenseMatrix.h"
#include "../Exception/CExceptions.h"

typedef double T;

CDenseMatrix::CDenseMatrix ( unsigned int rows , unsigned int columns )
        : CMatrix ( rows , columns )
{
    m_Matrix.resize ( CMatrix::m_Rows );
    for ( unsigned i = 0 ; i < CMatrix::m_Rows ; ++i )
        m_Matrix[ i ].resize ( CMatrix::m_Columns , CMatrix::c_InitValue );
}
T CDenseMatrix::operator () ( unsigned int row , unsigned int col ) const
{
    CMatrix::operator () ( row , col );
    return m_Matrix[ row ][ col ];
}
std::shared_ptr < CMatrix > CDenseMatrix::Transpose ( ) const
{
    CDenseMatrix res ( CMatrix::m_Columns , CMatrix::m_Rows );
    for ( unsigned i = 0 ; i < CMatrix::m_Columns ; ++i )
        for ( unsigned j = 0 ; j < CMatrix::m_Rows ; ++j )
            res.m_Matrix[ i ][ j ] = operator () ( j , i );

    return res.Clone ( );
}
std::shared_ptr < CMatrix > CDenseMatrix::mergeHorizontally ( const CMatrix & rhs , bool rightOrder ) const
{
    CMatrix::mergeHorizontally ( rhs );

    if ( rhs.m_NumberOfNulls + this->m_NumberOfNulls > rhs.m_Rows * ( rhs.m_Columns + this->m_Columns ) * CMatrix::sc_SparseNullStatic )
        return rhs.mergeHorizontally ( * this , false );


    CDenseMatrix res = * this;
    res.m_Columns += rhs.m_Columns;
    res.m_NumberOfNulls += rhs.m_NumberOfNulls;

    for ( unsigned i = 0 ; i < m_Rows ; ++i )
    {
        res.m_Matrix[ i ].reserve ( m_Rows + rhs.m_Rows );
        if ( rightOrder )
            for ( unsigned j = 0 ; j < rhs.m_Columns ; ++j )
                res.m_Matrix[ i ].push_back ( rhs ( i , j ) );
        else
            for ( unsigned j = 0 ; j < rhs.m_Columns ; ++j )
                res.m_Matrix[ i ].insert ( res.m_Matrix[ i ].begin ( ) + j , rhs ( i , j ) );
    }

    res.m_spaceNeededToPrintMaxVal = std::max ( res.m_spaceNeededToPrintMaxVal , rhs.m_spaceNeededToPrintMaxVal );
    res.m_NumberOfNulls = rhs.m_NumberOfNulls + this->m_NumberOfNulls;
    return res.Clone ( );
}
std::shared_ptr < CMatrix > CDenseMatrix::mergeVertically ( const CMatrix & rhs , bool rightOrder ) const
{
    CMatrix::mergeVertically ( rhs );

    if ( rhs.m_NumberOfNulls + this->m_NumberOfNulls > rhs.m_Columns * ( rhs.m_Rows + this->m_Rows ) * CMatrix::sc_SparseNullStatic )
        return rhs.mergeVertically ( * this , false );

    CDenseMatrix res = * this;
    res.m_Rows += rhs.m_Rows;
    res.m_NumberOfNulls += rhs.m_NumberOfNulls;

    res.m_Matrix.resize ( res.m_Rows );
    if ( rightOrder )
        for ( unsigned i = m_Rows ; i < res.m_Rows ; ++i )
        {
            res.m_Matrix[ i ].reserve ( res.m_Columns );
            for ( unsigned j = 0 ; j < rhs.m_Columns ; ++j )
                res.m_Matrix[ i ].push_back ( rhs ( i - m_Rows , j ) );
        }
    else
    {
        std::copy ( res.m_Matrix.begin ( ) , res.m_Matrix.begin ( ) + this->m_Rows , res.m_Matrix.begin ( ) + rhs.m_Rows );
        for ( unsigned i = 0 ; i < rhs.m_Rows ; ++i )
        {
            res.m_Matrix[ i ] = std::vector < T > ( );
            for ( unsigned j = 0 ; j < rhs.m_Columns ; ++j )
                res.m_Matrix[ i ].push_back ( rhs ( i , j ) );
        }

    }

    res.m_spaceNeededToPrintMaxVal = std::max ( res.m_spaceNeededToPrintMaxVal , rhs.m_spaceNeededToPrintMaxVal );
    res.m_NumberOfNulls = rhs.m_NumberOfNulls + this->m_NumberOfNulls;
    return res.Clone ( );
}
std::shared_ptr < CMatrix > CDenseMatrix::Clone ( ) const
{
    return std::make_shared < CDenseMatrix > ( * this );
}
void CDenseMatrix::CountNumberOfNulls ( )
{
    for ( unsigned i = 0 ; i < m_Rows ; ++i )
        for ( unsigned j = 0 ; j < m_Columns ; ++j )
            if ( !my::DoubleEpsilon ( ( * this ) ( i , j ) , 0 ) )
                ++CMatrix::m_NumberOfNulls;
}
std::shared_ptr < CMatrix > CDenseMatrix::CreateNew ( std::deque < T > & deque )
{
    T maxAbsVal = 0;
    for ( unsigned i = 0 ; i < CMatrix::m_Rows ; ++i )
        for ( unsigned j = 0 ; j < CMatrix::m_Columns ; ++j )
        {
            m_Matrix[ i ][ j ] = deque.front ( );
            maxAbsVal = std::max ( maxAbsVal , std::abs ( deque.front ( ) ) );
            deque.pop_front ( );
        }
    m_spaceNeededToPrintMaxVal = std::to_string ( ( int ) maxAbsVal ).length ( );
    return this->Clone ( );
}
