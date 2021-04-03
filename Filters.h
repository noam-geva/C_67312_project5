
#ifndef SOL_FILTERS_H
#define SOL_FILTERS_H

#include "Matrix.h"



/**
 * assumption from google docs:
 * 1- the new number of levels will be a power of 2.
 * 2- the new number of levels will not be larger than 256.
 *
 * @param image - represented by matrix
 * @param levels - new numbers of colors we wish to have
 * @return a new image(matrix) that shows the old image with the new number of levels of color.
 */
Matrix Quantization(const Matrix& image,int levels);

Matrix Blur(const Matrix& image);

Matrix Sobel(const Matrix& image);


#endif //SOL_FILTERS_H
