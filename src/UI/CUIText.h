#pragma once

#include <string>
#include <map>

class CUIText
{
public:
    CUIText ( ) = delete;
    CUIText ( const CUIText & ) = delete;
    CUIText ( const CUIText && ) = delete;
    CUIText & operator = ( const CUIText & ) = delete;
    CUIText & operator = ( const CUIText && ) = delete;

    enum class EKey
    {
        HELP , SCAN , LOAD , SAVE , PRINT , CALCULATE , DELETE ,
        DELETE_ALL , EXIT , HORIZONTAL_MERGE , VERTICAL_MERGE , TRANSPOSE , INVERSE ,
        GEM , GEM_INFO , CUT , DETERMINANT , RANGE , APP , UNKNOWN_COMMAND , INVALID_SYNTAX ,
        NO_VAR , INVALID_INPUT , DIMENSION , MATH , STH_ELSE
    };
private:
    typedef std::map < EKey , std::string > MyMap;
public:
    static std::string Intro;
    static std::string Outro;
    static std::string Prefix;
    static MyMap error;
    static MyMap mainCommands;
    static MyMap calculateCommands;
    static MyMap helpText;
    static MyMap messages;
};
