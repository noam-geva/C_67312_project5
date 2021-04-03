#ifndef PROJECT_5_MATRIX_H
#define PROJECT_5_MATRIX_H

#include <cstdio>
#include <iostream>
#include "MatrixException.h"


#define INVALID_DIMENSION "Invalid matrix dimensions.\n"
#define DIVISION_BY_ZERO "Division by zero.\n"
#define INVALID_INDEXES "Index out of range.\n"
#define INVALID_STREAM "Error loading from input stream.\n"
#define BAD_ALLOC  "Allocation failed.\n"

/**
 *
 */
class Matrix{
    int rows_;
    int cols_;
    int size_;
    float *matrix;
public:
   /**
    * ctor and default ctor
    * @param rows
    * @param cols
    */
    explicit Matrix(const int rows = 1, const int cols = 1) : rows_(rows), cols_(cols), size_(cols * rows){
        if (cols <= 0 || rows <=0){
            throw MatrixException(INVALID_DIMENSION);
        }
       try {
        this->matrix = new float[this->size_];
        } catch (std::bad_alloc &err){
           throw MatrixException(BAD_ALLOC);
       }
        for (int ix = 0 ; ix < size_ ; ix++){
                this->matrix[ix] = 0;// initialize to 0
            }
    }

    /**
     * cpy ctor
     * @param mat
     */
    Matrix( const Matrix &mat) {
        this->cols_ = mat.cols_;
        this->rows_ = mat.rows_;
        this->size_ = mat.size_;
        try {
            this->matrix = new float[this->size_];
        } catch (std::bad_alloc &err){
            throw MatrixException(BAD_ALLOC);
        }
        for (int ix = 0 ; ix < this->size_ ; ix++){
                this->matrix[ix]= mat.matrix[ix];
            }
    }

    /**
     *dtor
     */
    ~Matrix() {
        delete[] this->matrix;
    }

    /**
     *rows getter
     * @return
     */
    int GetRows() const noexcept;

    /**
     *cols getter
     * @return
     */
    int GetCols() const noexcept;


    /**
     *vectorize takes a matrix and turn it into a single dimension matrix.
     * step 1:
     * create temps
     * step 2:
     * create a new single col that get every element in order
     * IMPORTANT - deleting old not used rows!!!
     * step 3:
     * fix dimensions
     * rearrange matrix to hold the single vector
     */
    Matrix&  Vectorize() noexcept;

    /**
     *prints the elements neatly and in order
     * best explain by a demonstration:
     *     (1,2,3)
     * A = (4,5,6)
     *     (7,8,9)
     * A.print
     * 1 2 3\n
     * 4 5 6\n
     * 7 8 9
     */
    void Print() const noexcept;


    /**
     * @param rhs another matrix
     * @return a new alloc matrix
     */
    Matrix& operator=(const Matrix &rhs);


    /**
     * return a reference to the multiplied matrix
     * @param rhs
     * @return
     */
    Matrix operator*(const Matrix& rhs) const;


    /**
    * return a reference to the multiplied matrix by a scalar on the right
    * @param rhs
    * @return
    */
    Matrix operator*(float c) const noexcept;

    /**
    * return a reference to the multiplied matrix by a scalar on the left
    * @param rhs
    * @return
    */
    friend Matrix operator*(float c,const Matrix& mat) noexcept;

    /**
     * a *= b <=> a = a * b
     * @param rhs
     * @return
     */
    Matrix& operator*=(const Matrix& rhs);

    /**
     * a *= c <=> a = a*c
     * @param c is a scalar
     * @return
     */
    Matrix& operator*=(float c) noexcept;

    /**
     * check c != 0
     * a/c = a*(1/c)
     * @param c
     * @return
     */
    Matrix operator/(float c) const;

    /**
     * assign a/c to a
     * division ny zero is checked in operator/
     * @param c
     * @return
     */
    Matrix& operator/=(float c);

    /**
     * checks dimensions validity
     * @param rhs
     * @return
     */
    Matrix operator+(const Matrix &rhs) const;

    /**
     * validity will be checked in operator+
     * @param rhs
     * @return
     */
    Matrix& operator+=(const Matrix &rhs);


    /**
     * for each elem in matrix add c
     * @param c
     * @return
     */
    Matrix& operator+=(float c) noexcept;

    /**
     *
     * @param row_ix
     * @param col_jx
     * @return
     */
    float operator()(int row_ix, int col_jx) const;

    /**
     *
     * @param row_ix
     * @param col_jx
     * @return
     */
    float& operator()(int row_ix, int col_jx);

    /**
     *  single index const
     * @param ix
     * @return
     */
    float operator[](int ix) const;

    /**
     * single index
     * @param ix
     * @return
     */
    float& operator[](int ix);

    /**
     *  a == b
     * @param rhs
     * @return
     */
    bool operator==(const Matrix& rhs) const noexcept;

    /**
     * a != b
     * @param rhs
     * @return
     */
    bool operator!=(const Matrix& rhs) const noexcept;

    /**
     *matrix to a stream
     * @param out
     * @param mat
     * @return
     */
    friend std::ostream &operator<<(std::ostream &out, const Matrix& mat);

    /**
     *
     * @param in
     * @return
     */
    friend void operator>>(std::istream &input, Matrix& mat);

};


#endif //PROJECT_5_MATRIX_H
