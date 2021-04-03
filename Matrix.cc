#include "Matrix.h"
#include <string>


/**
 * helper function that calculate a single element in a matrix given two matrices to multiply
 * assumption - valid dimension
 * @param left
 * @param right
 * @return
 */
float SingleElemMultiplication(const Matrix& left, const Matrix& right, int row, int col) {
    float sum = 0;
    for (int ix = 0 ; ix < left.GetCols(); ix++){ // could also work for ix < right.GetRows
        sum += left(row,ix) * right(ix,col);
    }
    return sum;
}


/**
 *rows getter
 * @return
 */
int Matrix::GetRows() const noexcept{
    return this->rows_;
}

/**
 *cols getter
 * @return
 */
int Matrix::GetCols() const noexcept{
    return this->cols_;
}

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
Matrix& Matrix::Vectorize() noexcept{
    this->rows_ = this->size_;
    this->cols_ = 1;
    return (*this);
}

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
void Matrix::Print() const noexcept{
    std::cout << (*this);
}

/**
  * @param rhs another matrix
  * @return a new alloc matrix
  */
Matrix& Matrix::operator=(const Matrix &rhs){
    if (this == &rhs){
        return *this;
    }
    delete[] this->matrix;
    this->cols_ = rhs.cols_;
    this->rows_ = rhs.rows_;
    this->size_ = rhs.size_;
    try {
        this->matrix = new float[this->size_];
    } catch (std::bad_alloc &err){
        throw MatrixException(BAD_ALLOC);
    }
    for( int ix = 0; ix < this->size_ ; ix++){
        this->matrix[ix] = rhs.matrix[ix];
    }
    return *this;
}

/**
  * return a reference to the multiplied matrix
  * in this operator it is easier to think of it as a 2d array
  * @param rhs
  * @return
  */
Matrix Matrix::operator*(const Matrix& rhs) const{
    if (this->cols_ != rhs.rows_){
        throw  MatrixException(INVALID_DIMENSION);
    }
    Matrix ret_mat(this->rows_, rhs.cols_);
    for (int row_ix = 0; row_ix < ret_mat.rows_ ; row_ix++){
        for (int col_ix = 0 ; col_ix < ret_mat.cols_ ; col_ix++){
            ret_mat(row_ix,col_ix) = SingleElemMultiplication(*this, rhs, row_ix, col_ix);
        }
    }
    return ret_mat;
}

/**
 * return a reference to the multiplied matrix by a scalar on the right
 * @param rhs
 * @return
 */
Matrix Matrix::operator*(float c) const noexcept{
    Matrix ret(this->rows_, this->cols_);
    for (int ix = 0; ix < this->size_; ix++){
            ret[ix] = (*this)[ix] * c;
    }
    return ret;
}

/**
 * return a reference to the multiplied matrix by a scalar on the left
 * @param rhs
 * @return
 */
Matrix operator*(float c, const Matrix & mat) noexcept{
    return mat*c;
}

/**
 * a *=b <=> a = a*b
 * @param rhs
 * @return
 */
Matrix &Matrix::operator*=(const Matrix &rhs) {
    *this = *this * rhs;
    return *this;
}

/**
 * a *= c <=> a = a*c
 * @param c is a scalar
 * @return
 */
Matrix& Matrix::operator*=(float c) noexcept{
    *this = *this * c;
    return *this;
}

/**
 * check c != 0
 * a/c = a*(1/c)
 * @param c
 * @return
 */
Matrix Matrix::operator/(float c) const {
    if (c == 0){
        throw MatrixException(DIVISION_BY_ZERO);
    }
    return *this * (1/c);
}

/**
* assign a/c to a
* division ny zero is checked in operator/
* @param c
* @return
*/
Matrix &Matrix::operator/=(float c) {
    *this = *this / c;
    return *this;
}

Matrix Matrix::operator+(const Matrix &rhs) const {
    if (this->cols_ != rhs.cols_ || this->rows_ != rhs.rows_){
        throw MatrixException(INVALID_DIMENSION);
    }
    Matrix ret(this->rows_, this->cols_);
    for (int ix = 0; ix < this->size_; ix++){
            ret[ix] += (*this)[ix] + rhs[ix];

    }
    return ret;
}

Matrix &Matrix::operator+=(const Matrix &rhs) {
    *this = *this + rhs;
    return *this;
}


Matrix& Matrix::operator+=(float c) noexcept {
    for (int ix = 0 ; ix < this->size_ ; ix++){
        (*this)[ix] += c;
    }
    return *this;
}

float Matrix::operator()(int row_ix, int col_jx) const {
    if(0 > row_ix || 0 > col_jx || row_ix >= this->rows_ || col_jx >= this->cols_){
        throw MatrixException(INVALID_INDEXES);
    }
    return this->matrix[((row_ix)* this->cols_ ) + (col_jx)];
}

float &Matrix::operator()(int row_ix, int col_jx) {
    if(0 > row_ix || 0 > col_jx || row_ix >= this->rows_ || col_jx >= this->cols_){
        throw MatrixException(INVALID_INDEXES);
    }
    return this->matrix[((row_ix)* this->cols_ ) + (col_jx)];
}

float Matrix::operator[](int ix) const {
    if (0 > ix || ix >= this->rows_ * this->cols_) {
        throw MatrixException(INVALID_INDEXES);
    }
    return this->matrix[ix];
}

float &Matrix::operator[](int ix) {
    if (0 > ix || ix >= this->rows_ * this->cols_) {
        throw MatrixException(INVALID_INDEXES);
    }
    return this->matrix[ix];
}

bool Matrix::operator==(const Matrix &rhs) const noexcept {
    if(this->cols_ != rhs.cols_ || this->rows_ != rhs.rows_) {
        return false;
    }
    for (int ix = 0 ; ix < this->size_ ; ix++){
        if ((*this)[ix] != rhs[ix]){
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &rhs) const noexcept {
    return !(*this == rhs);
}

std::ostream& operator<<(std::ostream &out, const Matrix& mat){
    if (!out){
        throw MatrixException(INVALID_STREAM);
    }
    for (int outer_ix = 0 ; outer_ix < mat.rows_ -1; outer_ix++){
        for(int inner_ix = 0 ; inner_ix < mat.cols_ -1; inner_ix++){
            out << mat(outer_ix,inner_ix) << " ";
        }
        out << mat(outer_ix,mat.cols_ -1) << std::endl;
    }
    for(int inner_ix = 0 ; inner_ix < mat.cols_ -1; inner_ix++){
        out << mat(mat.rows_ -1,inner_ix) << " ";
    }
    out << mat(mat.rows_-1,mat.cols_-1);
    return out;
}

void operator>>(std::istream &input, Matrix &mat) {
    if (!input){
        throw MatrixException(INVALID_STREAM);
    }
    for (int ix = 0 ; ix <mat.size_; ix++) {
            input >> mat.matrix[ix];
    }
}


