#include "Filters.h"
#include "cmath"


/** macros */
#define INITIAL_LEVEL_NUM 256
#define TOP_LEFT 0
#define TOP_MIDDLE 1
#define TOP_RIGHT 2
#define MIDDLE_LEFT 3
#define MIDDLE_MIDDLE 4
#define MIDDLE_RIGHT 5
#define BOTTOM_LEFT 6
#define BOTTOM_MIDDLE 7
#define BOTTOM_RIGHT 8


/**
 * fixes out of range elements and
 * @param mat
 * @param curr_max
 */
void SafetyCheck(Matrix &mat, float curr_max){
    int mat_size = mat.GetCols() * mat.GetRows();
    for (int mat_ix = 0; mat_ix < mat_size ; mat_ix++) {
        if (mat[mat_ix] < 0) {
            mat[mat_ix] = 0;
        }
        if (mat[mat_ix] > curr_max) {
            mat[mat_ix] = curr_max;
        }
    }
}

/**
 * helper function' will only be called in sobel for a matrix that is known to be 3X3
 * @param original_mat
 * @return
 */
Matrix Transpose(const Matrix &original_mat){
    int rows = original_mat.GetRows();
    int cols = original_mat.GetCols();
    Matrix ret_mat(cols, rows);
    for (int row_ix = 0; row_ix < cols; row_ix++){
        for (int  col_ix = 0 ; col_ix < rows; col_ix++){
            ret_mat(row_ix, col_ix) = original_mat(col_ix, row_ix);
        }
    }
    return ret_mat;
}

/**
 *calculates the element in position ix in the matrix post convolution.
 * assuming second is 3X3!!!
 * @param prime
 * @param second
 * @param ix
 * @return
 */
float SingleConvolution(const Matrix &prime, const Matrix &second, int ix) {
    float sum = prime[ix] * second[MIDDLE_MIDDLE];
    int cols = prime.GetCols();
    int top_middle_ix = ix - cols; // upper in the visual matrix
    int bottom_middle_ix = ix + cols; // lower in the visual matrix
    bool include_top = false;
    bool include_bottom = false;
    /**  check top row*/
    if (top_middle_ix >= 0) {
        sum += prime[top_middle_ix] * second[TOP_MIDDLE];
        include_top = true;
    }
    /**  check bottom row*/
    if (bottom_middle_ix < prime.GetRows() * cols) {
        sum += prime[bottom_middle_ix] * second[BOTTOM_MIDDLE];
        include_bottom = true;
    }
    /** check left column*/
    if (ix % cols > 0){
        sum += prime[ix - 1] * second[MIDDLE_LEFT];
        if (include_top){
            sum += prime[top_middle_ix - 1] * second[TOP_LEFT];
        }
        if (include_bottom){
            sum += prime[bottom_middle_ix - 1] * second[BOTTOM_LEFT];
        }
    }
    /** check right column*/
    if (ix % cols < cols - 1){
        sum += prime[ix + 1] * second[MIDDLE_RIGHT];
        if (include_top){
            sum += prime[top_middle_ix + 1] * second[TOP_RIGHT];
        }
        if (include_bottom){
            sum += prime[bottom_middle_ix + 1] * second[BOTTOM_RIGHT];
        }
    }
    return rintf(sum);
}


Matrix NonsafetyConvolution(const Matrix &prime, const Matrix &second) {
    Matrix ret_mat(prime.GetRows(),prime.GetCols()); // initialize the return value to the dimensions of primary
    int mat_size = prime.GetCols() * prime.GetRows();
    float curr;
    for (int mat_ix = 0; mat_ix < mat_size ; mat_ix++){
        curr = SingleConvolution(prime, second, mat_ix);
        ret_mat[mat_ix] = curr;
    }
    return ret_mat;

}


/**
 * the main calculation will be mad separately in single_convolution.
 * @param prime - matrix to change.
 * @param second - we may assume its dimensions are 3X3
 * @return ret_mat - ret_mat = prime convolution with second
 */
Matrix Convolution(const Matrix &prime, const Matrix &second) {
    Matrix ret_mat =NonsafetyConvolution(prime, second);
    SafetyCheck(ret_mat, INITIAL_LEVEL_NUM);
    return ret_mat;

}

/**
 * assumption from google docs:
 * 1- the new number of levels will be a power of 2.
 * 2- the new number of levels will not be larger than 256.
 *
 * @param image - represented by matrix
 * @param levels - new numbers of colors we wish to have
 * @return a new image(matrix) that shows the old image with the new number of levels of color.
 */
Matrix Quantization(const Matrix& image,int levels){
    Matrix ret_mat(image);
    int range_of_segments = INITIAL_LEVEL_NUM / levels;
    // according to the assumptions:
    // this calculation wil return a valid int (levels != 0 && INITIAL_LEVEL_NUM MOD levels = 0)
    auto *range_arr = new float[levels+1];
    auto *avg_arr = new float[levels];
    range_arr[0] = 0;
    for (int ix = 1 ; ix < levels+1; ix++){
        // initialize the arrays
        range_arr[ix] = (float)((ix) * range_of_segments);
        avg_arr[ix-1] = (range_arr[ix-1] + range_arr[ix])/2 -1;
    }
    int mat_size = image.GetCols() * image.GetRows();
    for (int mat_ix = 0; mat_ix < mat_size ; mat_ix++){
        for (int arr_ix = 0; arr_ix < levels; arr_ix++){
            if ( image[mat_ix] >= range_arr[arr_ix] && image[mat_ix] < range_arr[arr_ix + 1]){
                ret_mat[mat_ix] = avg_arr[arr_ix];
                break;
            }
        }
    }
    SafetyCheck(ret_mat, avg_arr[levels - 1]);
    delete[] range_arr;
    delete[] avg_arr;
    return ret_mat;
}

/**
 * part a: initialize a matrix for convolution
 * part b: convolution, safety check and return
 * @param image
 * @return
 */
Matrix Blur(const Matrix& image){
    //part a
    Matrix mini_mat(3,3);
    mini_mat[0] = 1;
    mini_mat[2] = 1;
    mini_mat[6] = 1;
    mini_mat[8] = 1;
    mini_mat[1] = 2;
    mini_mat[3] = 2;
    mini_mat[5] = 2;
    mini_mat[7] = 2;
    mini_mat[4] = 4;
    mini_mat /= 16;
    //part b
    Matrix ret_mat = Convolution(image, mini_mat);
    SafetyCheck(ret_mat, INITIAL_LEVEL_NUM);
    return ret_mat;
}

/**
 * part a: initialize a matrices for convolutions
 * part b: convolutions, safety check and return
 * @param image
 * @return
 */
Matrix Sobel(const Matrix& image){
    //part a
    Matrix ret_mat(image.GetRows(), image.GetCols());
    Matrix x_axis(3,3);
    x_axis[0] = 1;
    x_axis[1] = 0;
    x_axis[2] = -1;
    x_axis[3] = 2;
    x_axis[4] = 0;
    x_axis[5] = -2;
    x_axis[6] = 1;
    x_axis[7] = 0;
    x_axis[8] = -1;
    x_axis /= 8;
    Matrix y_axis(3, 3);
    y_axis = Transpose(x_axis);
    //part b
    ret_mat = NonsafetyConvolution(image,x_axis) + NonsafetyConvolution(image,y_axis);
    SafetyCheck(ret_mat, INITIAL_LEVEL_NUM);
    return ret_mat;
}
