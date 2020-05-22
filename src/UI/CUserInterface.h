#pragma once

#include <string>
#include <vector>
#include "../Calculator/CCalculator.h"

/**
 * UI of the application.
 * This class provides user interface for the application.
 */
class CUserInterface
{
private:
    /// holds calculator
    CCalculator cal;

    /**
     * Process main command.
     * Converts command into vector of words.
     *
     * In of case command is unknown prints out error message
     *
     * @param command Command from user.
     */
    void ProcessCommand ( const std::string & command );
    /**
     * Prints HELP or HELP for command.
     *
     * In case of command is unknown prints out error message.
     * In case of invalid syntax prints out error message.
     *
     * @param words Vector of words from command.
     */
    void PrintHelp ( const std::vector < std::string > & words ) const;
    /**
     * Calculate with the matrices.
     * This function provides this operations with matrices:
     *  - algebraic operations (+,-,*)
     *  - merge two matrices
     *  - CUT out part of the matrix
     *  - TRANSPOSE the matrix
     *  - convert the matrix into REF(row echelon form) using GEM
     *  - count DETERMINANT of the matrix
     *  - count RANGE of the matrix
     *  - generate INVERSE matrix
     *
     * In case of invalid syntax prints out error message.
     * In case of problem with calculating (unknown variable...) prints out error message.
     *
     * @param words Vector of words from command.
     */
    void Calculate ( const std::vector < std::string > & words );
    /**
     * Prints a matrix out to the stream.
     *
     * In case of invalid syntax prints out error message.
     * In case of problem with printing (unknown variable...) prints out error message.
     *
     * @param words Vector of words from command.
     */
    void Print ( const std::vector < std::string > & words ) const;
    /**
     * Scan or overwrite a new matrix.
     *
     * In case of invalid syntax prints out error message.
     * In case of problem with saning (invalid input...) prints out error message.
     *
     * @param words Vector of words from command.
     */
    void Scan ( const std::vector < std::string > & words );
    /**
     * Delete a matrix.
     *
     * In case of invalid syntax prints out error message.
     * In case of problem with deleting (unknown variable...) prints out error message.
     *
     * @param words Vector of words from command.
     */
    void Delete ( const std::vector < std::string > & words );
    /**
     * Deletes all matrices.
     *
     * @param words of words from command.
     */
    void DeleteAll ( const std::vector < std::string > & words );
    /**
     * Load matrices from file.
     *
     * @param words of words from command.
     */
    void Load ( const std::vector < std::string > & words );
    /**
     * Save matrices to file.
     *
     * @param words of words from command.
     */
    void Save ( const std::vector < std::string > & words );
public:
    CUserInterface ( const CUserInterface & ) = delete;
    CUserInterface ( const CUserInterface && ) = delete;
    CUserInterface operator = ( const CUserInterface & ) = delete;
    CUserInterface operator = ( const CUserInterface && ) = delete;

    /**
     * Prints out greeting message, when application starts.
     */
    CUserInterface ( );
    /**
     * Print out leaving message, when application ends.
     */
    virtual ~CUserInterface ( );
    /**
     * Run whole UI.
     * This function is reads commands from stream.
     * In case of command *sc_TextCommandExit* EXIT application.
     */
    void Run ( );
};
