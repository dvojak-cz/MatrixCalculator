#pragma once

#include <map>
#include "CMatrix.h"

class CSparseMatrix final : public CMatrix
{
private:
    /// Matrix_orig as map of null values.
    std::map < std::pair < unsigned , unsigned > , T > m_Map;
public:
    /**
     * Sets up m_Rows and m_Columns.
     *
     * @param rows Number of rows.
     * @param columns Numer of columns.
     *
     * @throw err::invalid_dimensions In case sites of matrix are equal to zero.
     */
    CSparseMatrix ( unsigned int rows , unsigned int columns );
    /**
    * Access value on certain position.
    *
    * @param row Row index.
    * @param col Column index.
    *
    * @throw err::invalid_dimensions In case one of arguments is out of RANGE.
    *
    * @return Value from certain position.
    */
    T operator () ( unsigned int row , unsigned int col ) const final;
    /**
     * Clone matrix.
     * 
     * @return Matrix.
     */
    [[nodiscard]] std::shared_ptr < CMatrix > Clone ( ) const final;
    /**
     * Transpose matrix
     *
     * @return New transposed matrix.
     */
    [[nodiscard]] std::shared_ptr < CMatrix > Transpose ( ) const final;
    /**
     * Merge horizontally two matrices together.
     *
     * @param rhs Second matrix to merge.
     * @param rightOrder true if merge this with rhs, false if rhs merge this
     *
     * @throw err::invalid_dimensions In case matrices has not same number of rows.
     *
     * @return New merged matrix.
     */
    [[nodiscard]] std::shared_ptr < CMatrix > mergeHorizontally ( const CMatrix & rhs , bool rightOrder = true ) const final;
    /**
     * Merge horizontally two verticaly together.
     *
     * @param rhs Second matrix to merge.
     * @param rightOrder true if merge this with rhs, false if rhs merge this
     *
     * @throw err::invalid_dimensions In case matrices has not same number of columns.
     *
     * @return New merged matrix.
     */
    [[nodiscard]] std::shared_ptr < CMatrix > mergeVertically ( const CMatrix & rhs , bool rightOrder = true ) const final;

    /**
     * Update m_NumberOfNulls
     */
    void CountNumberOfNulls ( ) final;
    /**
     * Create new matrix from a que.
     *
     * @param deque Que of items in matrix
     *
     * @return New Matrix.
     */
    std::shared_ptr < CMatrix > CreateNew ( std::deque < T > & deque ) final;
};
