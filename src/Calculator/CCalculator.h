#pragma once

#include <string>
#include <memory>
#include <map>
#include <set>
#include "../Matrix/CMatrix.h"
#include "../Matrix/CLinear.h"

/**
 * This class mediator between UI and back-end part.
 * Class represents calculator, it holds variables and work with matrices.
 */
class CCalculator
{
    typedef double T;
private:
    /// Map of variables and matrices
    std::map < std::string , std::shared_ptr < CMatrix > > m_Matrices;
    ///Map of variables and liner class to matrices
    std::map < std::string , CLinear > m_Linear;
public:
    CCalculator ( ) = default;
    virtual ~CCalculator ( ) = default;

    /// Enum representing HORIZONTAL_MERGE or VERTICAL_MERGE marge
    enum class EMerge { HORIZONTAL_MERGE , VERTICAL_MERGE };

    /**
    * Add and SAVE or overwrite a matrix.
    *
    * @param key Variable of a matrix;
    * @param matrix Matrix its self.
    */
    void AddNew ( const std::string & key , std::shared_ptr < CMatrix > matrix );
    /**
     * Add two matrices.
     *
     * @param lhs EKey of first matrix.
     * @param rhs EKey of second matrix.
     * @param key EKey of the new (sum) matrix.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    void Add ( const std::string & lhs , const std::string & rhs , const std::string & key );
    /**
     * Subtract two matrices.
     *
     * @param lhs EKey of first matrix.
     * @param rhs EKey of second matrix.
     * @param key EKey of the new (difference) matrix.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    void Subtract ( const std::string & lhs , const std::string & rhs , const std::string & key );
    /**
     * Multiply two matrices.
     *
     * @param lhs EKey of first matrix.
     * @param rhs EKey of second matrix.
     * @param key EKey of the new (multiple) matrix.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    void Multiply ( const std::string & lhs , const std::string & rhs , const std::string & key );
    /**
     * Transpose matrix.
     *
     * @param old EKey of matrix to be transposed.
     * @param key EKey of the new (transposed) matrix.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    void Transpose ( const std::string & old , const std::string & key );
    /**
     * Count INVERSE matrix.
     *
     * @param old EKey of matrix to be INVERSE.
     * @param key EKey of the new (inverted) matrix.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    void Inverse ( const std::string & old , const std::string & key );
    /**
     * Convert matrix to REF(row echelon form).
     *
     * @param old EKey of matrix to be converted.
     * @param key EKey of the new (converted) matrix.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    void Gem ( const std::string & old , const std::string & key );
    /**
     * Convert matrix to REF(row echelon form).
     *
     * @param key EKey of the new (converted) matrix.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    [[nodiscard]] const std::deque < std::string > & GemInfo ( const std::string & key );
    /**
     * Cut part of the matrix out.
     *
     * @param old EKey of matrix to be CUT out.
     * @param key EKey of the new (CUT out) matrix.
     * @param row0 index of row from which to CUT (will be in result).
     * @param row1 index of row to which to CUT (will not be in result).
     * @param coll0 index of column from which to CUT (will be in result).
     * @param coll1 index of column to which to CUT (will not be in result).
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    void Cut ( const std::string & old , const std::string & key , unsigned row0 , unsigned coll0 , unsigned row1 , unsigned coll1 );
    /**
     * Merge two matrices together.
     *
     * @param lhs EKey of first matrix.
     * @param rhs EKey of second matrix.
     * @param key EKey of the new (merged) matrix.
     * @param typeOfMerge type of merge
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    void Merge ( const std::string & lhs , const std::string & rhs , const std::string & key , EMerge typeOfMerge );
    /**
     * Gets matrix.
     *
     * @param key EKey of the matrix to be printed.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     *
     * @return Matrix_orig.
     */
    [[nodiscard]] const CMatrix & Print ( const std::string & key ) const;
    /**
     * Delete specified matrix.
     *
     * @param key EKey of the matrix to be deleted.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     */
    void Delete ( const std::string & key );
    /**
     * Count RANGE of matrix.
     *
     * @param key EKey of the matrix for RANGE count.
     *
     * @throw std::out_of_range If there is no matrix with specified key.
     *
     * @return Range of matrix.
     */
    [[nodiscard]] unsigned Range ( const std::string & key );
    /**
    * Count DETERMINANT of matrix.
    *
    * @param key EKey of the matrix for DETERMINANT count.
    *
    * @throw std::out_of_range If there is no matrix with specified key.
    *
    * @return Determinant of matrix.
    */
    [[nodiscard]] T Determinant ( const std::string & key );
    /**
     * Delete all saved matrices.
     */
    void DeleteAll ( );
    /**
     * Saves saved matrices to the file.
     *
     * @param path Path to data file.
     */
    void LoadFromFile ( const std::string & path );
    /**
     * Load matrices to the file.
     *
     * @param path Path to data file.
     *
     * @throw throw err::input_stream ( )
     *
     */
    void SaveToFile ( const std::string & path );
    /**
     * List all used variables.
     *
     * @return set of all used variables.
     */
    [[nodiscard]] std::set < std::string > ListVariables ( ) const;
};
