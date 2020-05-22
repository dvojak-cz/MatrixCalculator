#include <fstream>
#include "CCalculator.h"

typedef double T;

void CCalculator::AddNew ( const std::string & key , std::shared_ptr < CMatrix > matrix )
{
    m_Matrices[ key ] = move ( matrix );
    m_Linear.erase ( key );
}

void CCalculator::Add ( const std::string & lhs , const std::string & rhs , const std::string & key )
{
    auto lhsItem = m_Matrices.at ( lhs );
    auto rhsItem = m_Matrices.at ( rhs );

    AddNew ( key , * lhsItem + * rhsItem );
}

void CCalculator::Subtract ( const std::string & lhs , const std::string & rhs , const std::string & key )
{
    auto lhsItem = m_Matrices.at ( lhs );
    auto rhsItem = m_Matrices.at ( rhs );

    AddNew ( key , * lhsItem - * rhsItem );
}

void CCalculator::Multiply ( const std::string & lhs , const std::string & rhs , const std::string & key )
{
    auto lhsItem = m_Matrices.at ( lhs );
    auto rhsItem = m_Matrices.at ( rhs );

    AddNew ( key , * lhsItem * * rhsItem );
}

const CMatrix & CCalculator::Print ( const std::string & key ) const
{
    return * m_Matrices.at ( key );
}

void CCalculator::Delete ( const std::string & key )
{
    m_Matrices.at ( key );      // throws exception
    m_Matrices.erase ( key );
}

void CCalculator::DeleteAll ( )
{
    m_Matrices.clear ( );
}

void CCalculator::Transpose ( const std::string & old , const std::string & key )
{
    AddNew ( key , m_Matrices.at ( old )->Transpose ( ) );
}

void CCalculator::Cut ( const std::string & old , const std::string & key , unsigned row0 , unsigned coll0 , unsigned row1 , unsigned coll1 )
{
    AddNew ( key , m_Matrices.at ( old )->Cut ( row0 , coll0 , row1 , coll1 ) );
}

void CCalculator::Merge ( const std::string & lhs , const std::string & rhs , const std::string & key , EMerge typeOfMerge )
{
    switch ( typeOfMerge )
    {
        case EMerge::VERTICAL_MERGE:
            AddNew ( key , m_Matrices.at ( lhs )->mergeVertically ( * m_Matrices.at ( rhs ) ) );
            return;
        case EMerge::HORIZONTAL_MERGE:
            AddNew ( key , m_Matrices.at ( lhs )->mergeHorizontally ( * m_Matrices.at ( rhs ) ) );
            return;
    }
}

unsigned CCalculator::Range ( const std::string & key )
{
    auto it = m_Linear.find ( key );
    if ( it == m_Linear.end ( ) )
        m_Linear[ key ] = CLinear ( * m_Matrices.at ( key ) );
    return m_Linear[ key ].GetRange ( );
}

T CCalculator::Determinant ( const std::string & key )
{
    auto it = m_Linear.find ( key );
    if ( it == m_Linear.end ( ) )
        m_Linear[ key ] = CLinear ( * m_Matrices.at ( key ) );
    return m_Linear[ key ].GetDeterminant ( );
}

void CCalculator::Gem ( const std::string & old , const std::string & key )
{
    auto it = m_Linear.find ( old );
    if ( it == m_Linear.end ( ) )
        m_Linear[ old ] = CLinear ( * m_Matrices.at ( old ) );
    AddNew ( key , m_Linear[ old ].gemGem ( ) );
}

void CCalculator::LoadFromFile ( const std::string & path )
{
    std::ifstream ifs ( path );
    if ( !ifs.is_open ( ) || !ifs.good ( ) )
        throw err::input_stream ( );
    unsigned size , width , height;
    std::string name;
    char chunk;
    if ( !( ifs >> size ) )
        throw err::input_stream ( );
    for ( unsigned i = 0 ; i < size ; ++i )
    {
        if ( !( ifs >> name >> height >> chunk >> width ) || chunk != 'x' )
            throw err::input_stream ( );
        AddNew ( name , CMatrix::Scan ( ifs , height , width ) );
    }
    ifs.get ( chunk );
    if ( !ifs.eof ( ) )
        throw err::input_stream ( );
    ifs.close ( );
    if ( ifs.is_open ( ) )
        throw err::input_stream ( );
}

void CCalculator::SaveToFile ( const std::string & path )
{
    std::ofstream ofs ( path );
    if ( !ofs.is_open ( ) || !ofs.good ( ) )
        throw err::input_stream ( );
    ofs << m_Matrices.size ( ) << std::endl;
    if ( !ofs.good ( ) )
        throw err::input_stream ( );
    for ( const auto &[key , val]: m_Matrices )
    {
        ofs << key << "\n";
        val->Print ( ofs , true );
        ofs << std::flush;
        if ( !ofs.good ( ) )
            throw err::input_stream ( );
    }
    if ( !ofs.good ( ) )
        throw err::input_stream ( );
    ofs.close ( );
    if ( ofs.is_open ( ) )
        throw err::input_stream ( );
}

void CCalculator::Inverse ( const std::string & old , const std::string & key )
{
    auto it = m_Linear.find ( old );
    if ( it == m_Linear.end ( ) )
        m_Linear[ old ] = CLinear ( * m_Matrices.at ( old ) );
    AddNew ( key , m_Linear[ old ].GetInverse ( ) );
}
const std::deque < std::string > & CCalculator::GemInfo ( const std::string & key )
{
    auto it = m_Linear.find ( key );
    if ( it == m_Linear.end ( ) )
        m_Linear[ key ] = CLinear ( * m_Matrices.at ( key ) );
    return m_Linear[ key ].GetGemInfo ( );
}
