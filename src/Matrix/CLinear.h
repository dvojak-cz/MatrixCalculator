#pragma once

#include <vector>
#include <memory>
#include <deque>
#include <optional>
#include "../Exception/CExceptions.h"
#include "CMatrix.h"
#include <iostream>

typedef double T;

class CLinear
{
private:
    /// GEM matrix
    std::vector < std::unique_ptr < std::vector < T > > > m_matrix;
    /// Inverse matrix
    std::optional < std::vector < std::vector < T > > > m_inverse;
    /// original number of rows
    unsigned m_Rows;
    /// original number of columns
    unsigned m_Columns;
    /// deque sores step-by-step gem
    std::deque < std::string > m_deque;
private:
    /// range of matrix
    size_t m_range = 0;
    /// signOfDeterminant after gem
    T signOfDeterminant = 1;
private:
    /**
     * Swaps two rows in matrix. (GEMo_1)
     *
     * @param rowIndex0 index of the first row
     * @param rowIndex1 index of the second row
     * @param log in case of true, operation will be saved to deque
     *
     * @throw std::out_of_range in case any of the indexes are greater or equal than number of rows.
     */
    void g1 ( unsigned rowIndex0 , unsigned rowIndex1 , bool log = true );
private:
    /**
     * Multiples row by value. (GEMo_2)
     *
     * @param rowIndex index of first row
     * @param num multiple of the rowIndex
     * @param log in case of true, operation will be saved to deque
     *
     * @throw std::out_of_range in case any of the indexes are greater or equal than number of rows.
     * @throw err::math in case value equals zero.
     */
    void g2 ( unsigned rowIndex , double num , bool log = true );
    /**
     * Add multiple of first row to multiple of second row. (GEMo_3,2)
     *
     * @param rowIndex0 index of the first row - will not be changed.
     * @param rowIndex1 index of the second row - will be changed
     * @param num0 multiple of the rowIndex0
     * @param num1 multiple of the rowIndex1
     * @param log in case of true, operation will be saved to deque
     *
     * @throw std::out_of_range in case invalid indexes
     *
     */
    void g3 ( unsigned rowIndex0 , unsigned rowIndex1 , T num0 = 1 , T num1 = 1 , bool log = true );
    /**
     * Convert matrix to HST
     *
     * Compute range of matrix
     */
    void gem ( );
    /**
     * Compute inverse matrix
     */
    void inverse ( );
public:

    CLinear ( ) = default;
    /**
     * Create instance of class
     *
     * @param matrix matrix
     */
    explicit CLinear ( const CMatrix & matrix );
    /**
     * Getter for range
     *
     * @return range
     */
    [[nodiscard]] unsigned int GetRange ( ) const;
    /**
     * Getter for inverse matrix
     *
     * @throw err::math in case matrix is not square
     *
     * @return inverse matrix
     */
    [[nodiscard]] std::shared_ptr < CMatrix > GetInverse ( );
    /**
     * Getter for determinant
     *
     * @throw err::math in case matrix is not square
     *
     * @return determinant
     */
    [[nodiscard]] T GetDeterminant ( ) const;
    /**
     * Getter for gem matrix
     *
     * @return gem matrix
     */
    [[nodiscard]] std::shared_ptr < CMatrix > gemGem ( ) const;
    /**
     * Getter for step-by-step gem info
     *
     * @return step-by-step gem info
     */
    [[nodiscard]] const std::deque < std::string > & GetGemInfo ( ) const;

};
