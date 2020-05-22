#pragma once

#include <memory>
#include <deque>

/**
 * Abstract class representing matrix.
 */
class CMatrix
{
    typedef double T;

    friend class CDenseMatrix;

    friend class CSparseMatrix;

    friend class CLinear;

private:
    /// minimal ratio of null and not-null values in sparse matrix
    constexpr const static double sc_SparseNullStatic = 0.5f;
    /// number of decimal places, that will be printed in the resoult
    constexpr const static unsigned sc_NumberOfDecimalPlaces = 2;
protected:
    /// spaces needed to print abs. maximal value in matrix
    unsigned m_spaceNeededToPrintMaxVal = 0;
    /// Default init value
    const T c_InitValue = 0;
    /// Number of nuls in matrix
    unsigned m_NumberOfNulls = 0;
    /// Number of rows in a matrix
    unsigned m_Rows;
    /// Number of columns in a matrix
    unsigned m_Columns;
public:
    /**
     * Sets up m_Rows and m_Columns.
     *
     * @param rows Number of rows.
     * @param columns Numer of columns.
     *
     * @throw err::invalid_dimensions In case sites of matrix are equal to zero.
     */
    CMatrix ( unsigned rows , unsigned columns );

    /**
     * Clone matrix.
     * @return Matrix.
     */
    [[nodiscard]] virtual std::shared_ptr < CMatrix > Clone ( ) const = 0;
    /**
     * Transpose matrix
     *
     * @return New transposed matrix.
     */
    [[nodiscard]] virtual std::shared_ptr < CMatrix > Transpose ( ) const = 0;
    /**
     * Create new matrix from a que.
     *
     * @param deque Que of items in matrix
     *
     * @throw err::invalid_dimensions In case sites of matrix are equal to zero.
     *
     * @return New Matrix.
     */
    virtual std::shared_ptr < CMatrix > CreateNew ( std::deque < T > & deque ) = 0;
    /**
     * Update m_NumberOfNulls
     */
    virtual void CountNumberOfNulls ( ) = 0;

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
    virtual T operator () ( unsigned row , unsigned col ) const;
    /**
     * Cut out part of the matrix.
     *
     * @param row0 Begging row index. (will be in output)
     * @param coll0 Begging column index. (will be in output)
     * @param row1 Ending row index. (will not be in output)
     * @param coll1 Ending column index. (will not be in output)
     *
     * @throw err::invalid_dimension In case arguments are incorrect.
     *
     * @return New matrix.
     */
    [[nodiscard]] std::shared_ptr < CMatrix > Cut ( unsigned row0 , unsigned coll0 , unsigned row1 , unsigned coll1 ) const;
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
    virtual std::shared_ptr < CMatrix > mergeHorizontally ( const CMatrix & rhs , bool rightOrder = true ) const;
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
    virtual std::shared_ptr < CMatrix > mergeVertically ( const CMatrix & rhs , bool rightOrder = true ) const;

    /**
     * Add two matrices together.
     *
     * @param rhs Matrix to add.
     *
     * @throw err::invalid_dimensions In case matrices has not same invalid_dimensions.
     *
     * @return New matrix (sum).
     */
    std::shared_ptr < CMatrix > operator + ( const CMatrix & rhs ) const;
    /**
    * Subtract two matrices.
    *
    * @param rhs Matrix to subtract.
    *
    * @throw err::invalid_dimensions In case matrices has not same invalid_dimensions.
    *
    * @return New matrix.
    */
    std::shared_ptr < CMatrix > operator - ( const CMatrix & rhs ) const;
    /**
    * Multiply two matrices.
    *
    * @param rhs Matrix to multiply.
    *
    * @throw err::invalid_dimensions In case number of columns of the first matrix is not same as number of rows of the second matrix.
    *
    * @return New matrix.
    */
    std::shared_ptr < CMatrix > operator * ( const CMatrix & rhs ) const;
    /**
     * Operator for printing matrix to the stream.
     *
     * @param os Output stream.
     * @param matrix Matrix to PRINT.
     *
     * @return Output stream.
     */
    friend std::ostream & operator << ( std::ostream & os , const CMatrix & matrix );
    /**
     * Print matrix to the stream
     *
     * @param os Output stream
     * @param toFile true in case we PRINT matrix to stream (prints dimensions and do not format output).
     *
     * @return Output stream.
     */
    std::ostream & Print ( std::ostream & os , bool toFile = false ) const;
    /**
     * Scan new matrix from the stream.
     *
     * @param is Input Stream.
     * @param row Number of rows.
     * @param coll Number of columns.
     *
     * @throw err::input_stream () in case of error while reading.
     *
     * @return New Matrix.
     */
    static std::shared_ptr < CMatrix > Scan ( std::istream & is , unsigned row , unsigned coll );
    /**
     * Generate new matrix.
     *
     * @param deque Que of items in matrix.
     * @param nulCounter Number of zeros in matrix.
     * @param row Number of rows.
     * @param coll Number of columns.
     *
     * @return New Matrix.
     */
    static std::shared_ptr < CMatrix > generateNew ( std::deque < T > & deque , unsigned int nulCounter , unsigned int row , unsigned int coll );
};
