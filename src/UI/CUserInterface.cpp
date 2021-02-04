#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <climits>
#include "CUserInterface.h"
#include "CUIText.h"

CUserInterface::CUserInterface ( ) : cal ( CCalculator ( ) )
{
    std::cout << CUIText::Intro << std::endl;
}

CUserInterface::~CUserInterface ( )
{
    std::cout << CUIText::Outro << std::endl;
}

void CUserInterface::Run ( )
{
    for ( std::string line ;
          std::cout << CUIText::Prefix &&
          std::getline ( std::cin >> std::ws , line ) && line != CUIText::mainCommands.at ( CUIText::EKey::EXIT ) ; )
        if ( !line.empty ( ) )
            ProcessCommand ( line );
}

void CUserInterface::ProcessCommand ( const std::string & command )
{
    // Converts command into vector of words(strings).
    std::vector < std::string > words;
    std::istringstream commandStream ( command );
    std::copy ( std::istream_iterator < std::string > ( commandStream ) , std::istream_iterator < std::string > ( ) , std::back_inserter ( words ) );

    //Process main command
    if ( words[ 0 ] == CUIText::mainCommands.at ( CUIText::EKey::HELP ) )
        PrintHelp ( words );
    else if ( words[ 0 ] == CUIText::mainCommands.at ( CUIText::EKey::SCAN ) )
        Scan ( words );
    else if ( words[ 0 ] == CUIText::mainCommands.at ( CUIText::EKey::LOAD ) )
        Load ( words );
    else if ( words[ 0 ] == CUIText::mainCommands.at ( CUIText::EKey::SAVE ) )
        Save ( words );
    else if ( words[ 0 ] == CUIText::mainCommands.at ( CUIText::EKey::PRINT ) )
        Print ( words );
    else if ( words[ 0 ] == CUIText::mainCommands.at ( CUIText::EKey::CALCULATE ) )
        Calculate ( words );
    else if ( words[ 0 ] == CUIText::mainCommands.at ( CUIText::EKey::DELETE ) )
        Delete ( words );
    else if ( words[ 0 ] == CUIText::mainCommands.at ( CUIText::EKey::DELETE_ALL ) )
        DeleteAll ( words );
    else
        std::cerr << CUIText::error.at ( CUIText::EKey::UNKNOWN_COMMAND ) << std::flush;
}

void CUserInterface::PrintHelp ( const std::vector < std::string > & words ) const
{
    if ( words.size ( ) == 1 )
        std::cout << CUIText::helpText.at ( CUIText::EKey::APP ) << std::endl;
    else if ( words.size ( ) == 2 )
    {
        if ( words[ 1 ] == CUIText::mainCommands.at ( CUIText::EKey::HELP ) )
            std::cout << CUIText::helpText.at ( CUIText::EKey::HELP ) << std::endl;
        else if ( words[ 1 ] == CUIText::mainCommands.at ( CUIText::EKey::SCAN ) )
            std::cout << CUIText::helpText.at ( CUIText::EKey::SCAN ) << std::endl;
        else if ( words[ 1 ] == CUIText::mainCommands.at ( CUIText::EKey::LOAD ) )
            std::cout << CUIText::helpText.at ( CUIText::EKey::LOAD ) << std::endl;
        else if ( words[ 1 ] == CUIText::mainCommands.at ( CUIText::EKey::SAVE ) )
            std::cout << CUIText::helpText.at ( CUIText::EKey::SAVE ) << std::endl;
        else if ( words[ 1 ] == CUIText::mainCommands.at ( CUIText::EKey::PRINT ) )
            std::cout << CUIText::helpText.at ( CUIText::EKey::PRINT ) << std::endl;
        else if ( words[ 1 ] == CUIText::mainCommands.at ( CUIText::EKey::CALCULATE ) )
            std::cout << CUIText::helpText.at ( CUIText::EKey::CALCULATE ) << std::endl;
        else if ( words[ 1 ] == CUIText::mainCommands.at ( CUIText::EKey::DELETE ) )
            std::cout << CUIText::helpText.at ( CUIText::EKey::DELETE ) << std::endl;
        else if ( words[ 1 ] == CUIText::mainCommands.at ( CUIText::EKey::DELETE_ALL ) )
            std::cout << CUIText::helpText.at ( CUIText::EKey::DELETE_ALL ) << std::endl;
        else if ( words[ 1 ] == CUIText::mainCommands.at ( CUIText::EKey::EXIT ) )
            std::cout << CUIText::helpText.at ( CUIText::EKey::EXIT ) << std::endl;
        else
            std::cerr << CUIText::error.at ( CUIText::EKey::UNKNOWN_COMMAND ) << std::flush;
    }
    else
        std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_SYNTAX ) << std::flush;
}

void CUserInterface::Calculate ( const std::vector < std::string > & words )
{
    try
    {
        // algebra operation
        if ( words.size ( ) == 6 && words[ 2 ] == "=" )
        {
            if ( words[ 4 ] == "+" )
            {
                cal.Add ( words[ 3 ] , words[ 5 ] , words[ 1 ] );
                std::cout << words[ 1 ] << ":\n";
                std::cout << cal.Print ( words[ 1 ] ) << std::endl;
                return;
            }
            if ( words[ 4 ] == "-" )
            {
                cal.Subtract ( words[ 3 ] , words[ 5 ] , words[ 1 ] );
                std::cout << words[ 1 ] << ":\n";
                std::cout << cal.Print ( words[ 1 ] ) << std::endl;
                return;
            }
            if ( words[ 4 ] == "*" )
            {
                cal.Multiply ( words[ 3 ] , words[ 5 ] , words[ 1 ] );
                std::cout << words[ 1 ] << ":\n";
                std::cout << cal.Print ( words[ 1 ] ) << std::endl;
                return;
            }
        }
        // merge
        if ( words.size ( ) == 6 && words[ 2 ] == "=" && words[ 4 ] == CUIText::calculateCommands.at ( CUIText::EKey::HORIZONTAL_MERGE ) )
        {
            cal.Merge ( words[ 3 ] , words[ 5 ] , words[ 1 ] , CCalculator::EMerge::HORIZONTAL_MERGE );
            std::cout << words[ 1 ] << ":\n";
            std::cout << cal.Print ( words[ 1 ] ) << std::endl;
            return;
        }
        if ( words.size ( ) == 6 && words[ 2 ] == "=" && words[ 4 ] == CUIText::calculateCommands.at ( CUIText::EKey::VERTICAL_MERGE ) )
        {
            cal.Merge ( words[ 3 ] , words[ 5 ] , words[ 1 ] , CCalculator::EMerge::VERTICAL_MERGE );
            std::cout << words[ 1 ] << ":\n";
            std::cout << cal.Print ( words[ 1 ] ) << std::endl;
            return;
        }
        // TRANSPOSE
        if ( words.size ( ) == 5 && words[ 2 ] == "=" && words[ 3 ] == CUIText::calculateCommands.at ( CUIText::EKey::TRANSPOSE ) )
        {
            cal.Transpose ( words[ 4 ] , words[ 1 ] );
            std::cout << words[ 1 ] << ":\n";
            std::cout << cal.Print ( words[ 1 ] ) << std::endl;
            return;
        }
        // INVERSE
        if ( words.size ( ) == 5 && words[ 2 ] == "=" && words[ 3 ] == CUIText::calculateCommands.at ( CUIText::EKey::INVERSE ) )
        {
            cal.Inverse ( words[ 4 ] , words[ 1 ] );
            std::cout << words[ 1 ] << ":\n";
            std::cout << cal.Print ( words[ 1 ] ) << std::endl;
            return;
        }
        // GEM
        if ( words.size ( ) == 5 && words[ 2 ] == "=" && words[ 3 ] == CUIText::calculateCommands.at ( CUIText::EKey::GEM ) )
        {
            cal.Gem ( words[ 4 ] , words[ 1 ] );
            std::cout << words[ 1 ] << ":\n";
            std::cout << cal.Print ( words[ 1 ] ) << std::endl;
            return;
        }
        // GEM info
        if ( words.size ( ) == 3 && words[ 1 ] == CUIText::calculateCommands.at ( CUIText::EKey::GEM_INFO ) )
        {
            for ( const auto & e : cal.GemInfo ( words[ 2 ] ) )
                std::cout << e << std::endl;
            std::cout << std::endl;
            return;
        }
        // CUT
        if ( words.size ( ) == 9 && words[ 2 ] == "=" && words[ 3 ] == CUIText::calculateCommands.at ( CUIText::EKey::CUT ) )
        {
            if ( !std::all_of ( words[ 5 ].begin ( ) , words[ 5 ].end ( ) , isdigit )
                 || !std::all_of ( words[ 6 ].begin ( ) , words[ 6 ].end ( ) , isdigit )
                 || !std::all_of ( words[ 7 ].begin ( ) , words[ 7 ].end ( ) , isdigit )
                 || !std::all_of ( words[ 8 ].begin ( ) , words[ 8 ].end ( ) , isdigit ) )
            {
                std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_SYNTAX ) << std::flush;
                return;
            }
            cal.Cut ( words[ 4 ] , words[ 1 ] ,
                      ( unsigned ) stoul ( words[ 5 ] , nullptr , 10 ) ,
                      ( unsigned ) stoul ( words[ 7 ] , nullptr , 10 ) ,
                      ( unsigned ) stoul ( words[ 6 ] , nullptr , 10 ) ,
                      ( unsigned ) stoul ( words[ 8 ] , nullptr , 10 ) );
            std::cout << words[ 1 ] << ":\n";
            std::cout << cal.Print ( words[ 1 ] ) << std::endl;
            return;
        }
        // DETERMINANT
        if ( words.size ( ) == 3 && words[ 1 ] == CUIText::calculateCommands.at ( CUIText::EKey::DETERMINANT ) )
        {
            std::cout << cal.Determinant ( words[ 2 ] ) << std::endl;
            return;
        }
        // rang
        if ( words.size ( ) == 3 && words[ 1 ] == CUIText::calculateCommands.at ( CUIText::EKey::RANGE ) )
        {
            std::cout << cal.Range ( words[ 2 ] ) << std::endl;
            return;
        }
        std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_SYNTAX ) << std::flush;
    }
    catch ( const std::out_of_range & )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::NO_VAR );
        std::cerr << std::flush;
    }
    catch ( const err::invalid_dimensions & )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::DIMENSION );
        std::cerr << std::flush;
    }
    catch ( const err::math & )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::MATH );
        std::cerr << std::flush;
    }
    catch ( ... )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::STH_ELSE );
        std::cerr << std::flush;
    }
}

void CUserInterface::Print ( const std::vector < std::string > & words ) const
{
    if ( words.size ( ) != 2 )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_SYNTAX ) << std::flush;
        return;
    }
    try
    {
        std::cout << cal.Print ( words[ 1 ] ) << std::endl;
    }
    catch ( const std::out_of_range & )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::NO_VAR );
        std::cerr << std::flush;
    }
}

void CUserInterface::Scan ( const std::vector < std::string > & words )
{
    unsigned row;
    unsigned coll;

    if ( words.size ( ) != 4
         || std::any_of ( words[ 1 ].begin ( ) , words[ 1 ].end ( ) , isupper )     // variable mus not contains uppercase
         || !std::all_of ( words[ 2 ].begin ( ) , words[ 2 ].end ( ) , isdigit )    // number of rows mus be digit
         || !std::all_of ( words[ 3 ].begin ( ) , words[ 3 ].end ( ) , isdigit )    // number of columns mus be digit
         || ( ( row = ( unsigned ) std::stoul ( words[ 2 ] ) ) < 1 ) || ( ( coll = ( unsigned ) std::stoul ( words[ 3 ] ) ) < 1 )
            )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_SYNTAX ) << std::flush;
        return;
    }

    try
    {
        cal.AddNew ( words[ 1 ] , CMatrix::Scan ( std::cin , row , coll ) );
        std::cout << CUIText::messages.at ( CUIText::EKey::SCAN );
    }
    catch ( const err::input_stream & )
    {
        std::cin.clear ( );
        std::cin.ignore ( INT_MAX , '\n' );
        std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_INPUT ) << std::flush;
    }
}

void CUserInterface::Delete ( const std::vector < std::string > & words )
{
    if ( words.size ( ) != 2 )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_SYNTAX ) << std::flush;
        return;
    }

    try
    {
        cal.Delete ( words[ 1 ] );
        std::cout << CUIText::messages.at ( CUIText::EKey::DELETE );
    }
    catch ( const std::out_of_range & )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::NO_VAR );
        std::cerr << std::flush;
    }
}

void CUserInterface::DeleteAll ( const std::vector < std::string > & words )
{
    if ( words.size ( ) != 1 )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_SYNTAX ) << std::flush;
        return;
    }
    cal.DeleteAll ( );

}

void CUserInterface::Save ( const std::vector < std::string > & words )
{
    if ( words.size ( ) != 2 )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_SYNTAX ) << std::flush;
        return;
    }
    try
    {
        cal.SaveToFile ( words[ 1 ] );
        std::cout << CUIText::messages.at ( CUIText::EKey::SAVE );
    }
    catch ( const err::input_stream & )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::SAVE );
        std::cerr << std::flush;
    }
}

void CUserInterface::Load ( const std::vector < std::string > & words )
{
    if ( words.size ( ) != 2 )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::INVALID_SYNTAX ) << std::flush;
        return;
    }
    try
    {
        cal.LoadFromFile ( words[ 1 ] );
        std::cout << CUIText::messages.at ( CUIText::EKey::LOAD );
    }
    catch ( const err::input_stream & )
    {
        std::cerr << CUIText::error.at ( CUIText::EKey::LOAD );
        std::cerr << std::flush;
    }
}
