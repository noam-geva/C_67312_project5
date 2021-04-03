//
// Created by eldar on 28/12/2020.
//

#include <fstream>
#include <cassert>
#include "Matrix.h"
#include "Filters.h"
#include "MatrixException.h"

#define MSG_DIMENSIONS "Invalid matrix dimensions.\n"
#define MSG_DIVISION "Division by zero.\n"
#define MSG_INDEX "Index out of range.\n"
#define MSG_ALLOCATION "Allocation failed.\n"
#define MSG_INPUT "Error loading from input stream.\n"

void test1() {
  Matrix m1_test(2, 2);
  Matrix m2_test(2, 3);
  Matrix m3_test;
  Matrix m1_correct(2, 2);
  Matrix m2_correct(2, 3);
  Matrix m3_correct;
  Matrix ID(2, 2);

  ID[0] = 1;
  ID[3] = 1;

  m1_correct[0] = 0;
  m1_correct[1] = 0;
  m1_correct[2] = 0;
  m1_correct[3] = 0;
  assert(m1_test == m1_correct && "INITIAL VALUE 0");

  m3_correct[0] = 0;
  assert(m3_test == m3_correct && "INITIAL VALUE 0, 1x1 DEFAULT SIZE");

  m1_test += 1;
  m2_test += 2;

  m1_correct[0] = 1;
  m1_correct[1] = 1;
  m1_correct[2] = 1;
  m1_correct[3] = 1;
  assert(m1_test == m1_correct && "ADDING 1 AS A SCALAR TO ALL THE INDEXES");

  m1_test *= 3;
  m2_test *= 4;

  m1_correct[0] = 3;
  m1_correct[1] = 3;
  m1_correct[2] = 3;
  m1_correct[3] = 3;
  assert(
      m1_test == m1_correct && "MULTIPLY BY 3 AS A SCALAR TO ALL THE INDEXES");

  m1_test /= 3;
  m2_test /= 2;

  m1_correct[0] = 1;
  m1_correct[1] = 1;
  m1_correct[2] = 1;
  m1_correct[3] = 1;
  assert(m1_test == m1_correct && "DIVIDE BY 3 AS A SCALAR TO ALL THE INDEXES");

  m3_test = m2_test;
  m3_correct = m3_test;

  m2_correct[0] = 4;
  m2_correct[1] = 4;
  m2_correct[2] = 4;
  m2_correct[3] = 4;
  m2_correct[4] = 4;
  m2_correct[5] = 4;

  m3_correct[0] = 4;
  m3_correct[1] = 4;
  m3_correct[2] = 4;
  m3_correct[3] = 4;
  m3_correct[4] = 4;
  m3_correct[5] = 4;
  assert(m3_test.GetCols() == m2_test.GetCols());
  assert(m3_test.GetRows() == m2_test.GetRows());
  assert(m3_test == m2_test);

  m3_test += 1;

  m3_correct[0] = 5;
  m3_correct[1] = 5;
  m3_correct[2] = 5;
  m3_correct[3] = 5;
  m3_correct[4] = 5;
  m3_correct[5] = 5;
  assert(m3_correct == m3_test);

  m2_test += m3_test;

  m2_correct[0] = 9;
  m2_correct[1] = 9;
  m2_correct[2] = 9;
  m2_correct[3] = 9;
  m2_correct[4] = 9;
  m2_correct[5] = 9;

  m3_test.Vectorize();
  m3_correct.Vectorize();

  assert(m3_test.GetRows() == 6);
  assert(m3_test.GetCols() == 1);

  m3_correct[0] = 5;
  m3_correct[1] = 5;
  m3_correct[2] = 5;
  m3_correct[3] = 5;
  m3_correct[4] = 5;
  m3_correct[5] = 5;
  assert(m3_test == m3_correct);

  Matrix m4_test = m1_test * 3;
  Matrix m4_correct(2, 2);

  m4_correct[0] = 3;
  m4_correct[1] = 3;
  m4_correct[2] = 3;
  m4_correct[3] = 3;
  assert(m4_correct == m4_test);

  Matrix m5_test = m1_test * m2_test;
  Matrix m5_correct(2, 3);

  m5_correct[0] = 18;
  m5_correct[1] = 18;
  m5_correct[2] = 18;
  m5_correct[3] = 18;
  m5_correct[4] = 18;
  m5_correct[5] = 18;
  assert(m5_test == m5_correct);

  Matrix m6_test = 3 * m4_test;
  Matrix m6_correct(2, 2);

  m6_correct[0] = 9;
  m6_correct[1] = 9;
  m6_correct[2] = 9;
  m6_correct[3] = 9;
  assert(m6_correct == m6_test);

  m1_test *= m1_test;
  m1_correct[0] = 2;
  m1_correct[1] = 2;
  m1_correct[2] = 2;
  m1_correct[3] = 2;

  assert(m1_test == m1_correct);

  m1_test = m1_test * ID;
  assert(m1_test == m1_correct);

  Matrix m7_test(3, 2);
  Matrix m8_test(m2_test);
  assert(m8_test == m2_test);

  m7_test += 1;
  m2_test *= m7_test;

  m1_correct[0] = 27;
  m1_correct[1] = 27;
  m1_correct[2] = 27;
  m1_correct[3] = 27;

  assert(m2_test == m1_correct);

  m7_test *= m8_test;
  Matrix m7_correct(3, 3);

  m7_correct[0] = 18;
  m7_correct[1] = 18;
  m7_correct[2] = 18;
  m7_correct[3] = 18;
  m7_correct[4] = 18;
  m7_correct[5] = 18;
  m7_correct[6] = 18;
  m7_correct[7] = 18;
  m7_correct[8] = 18;
  assert(m7_correct == m7_test);

  std::cout << m7_test << std::endl << std::endl;
  m7_test.Print();
  std::cout << std::endl;

  std::cin >> m7_test;
  std::cout << m7_test << std::endl << std::endl;

  std::cout << "PASSED FIRST TEST!!" << std::endl;
}

void test2() {
  Matrix m1_test(4, 4);
  for (int elem_i = 0; elem_i < 16; ++elem_i) {
    m1_test[elem_i] = (float) (elem_i * 16);
  }

  Matrix m1_correct(4, 4);
  const Matrix m2_test(m1_test);

  std::cout << "Before Quantization:" << std::endl << m2_test << std::endl << std::endl;
  m1_test = Quantization(m2_test, 8);
  std::cout << "Afer Quantization:" << std::endl << m1_test << std::endl << std::endl;

  m1_correct[0] = 15;
  m1_correct[1] = 15;
  m1_correct[2] = 47;
  m1_correct[3] = 47;
  m1_correct[4] = 79;
  m1_correct[5] = 79;
  m1_correct[6] = 111;
  m1_correct[7] = 111;
  m1_correct[8] = 143;
  m1_correct[9] = 143;
  m1_correct[10] = 175;
  m1_correct[11] = 175;
  m1_correct[12] = 207;
  m1_correct[13] = 207;
  m1_correct[14] = 239;
  m1_correct[15] = 239;
  assert(m1_test == m1_correct);

  m1_test = Quantization(m2_test, 16);
  m1_correct[0] = 7;
  m1_correct[1] = 23;
  m1_correct[2] = 39;
  m1_correct[3] = 55;
  m1_correct[4] = 71;
  m1_correct[5] = 87;
  m1_correct[6] = 103;
  m1_correct[7] = 119;
  m1_correct[8] = 135;
  m1_correct[9] = 151;
  m1_correct[10] = 167;
  m1_correct[11] = 183;
  m1_correct[12] = 199;
  m1_correct[13] = 215;
  m1_correct[14] = 231;
  m1_correct[15] = 247;
  assert(m1_test == m1_correct);

  m1_test = Quantization(m2_test, 1);
  for (int kI = 0; kI < m2_test.GetCols() * m2_test.GetRows(); ++kI) {
    m1_correct[kI] = 127;
  }
  assert(m1_test == m1_correct);

  //std::cout << m1_test << std::endl << std::endl;

  std::cout << "PASSED SECOND TEST!!" << std::endl;
}

void test3(){
  Matrix m1_test(4, 4);
  for (int elem_i = 0; elem_i < 16; ++elem_i) {
    m1_test[elem_i] = (float) (elem_i * 16);
  }

  Matrix m1_correct(4, 4);
  const Matrix m2_test(m1_test);

  //std::cout << m1_test << std::endl << std::endl;
  m1_test = Blur(m2_test);

  m1_correct[0] = 15;
  m1_correct[1] = 28;
  m1_correct[2] = 40;
  m1_correct[3] = 36;
  m1_correct[4] = 52;
  m1_correct[5] = 80;
  m1_correct[6] = 96;
  m1_correct[7] = 80;
  m1_correct[8] = 100;
  m1_correct[9] = 144;
  m1_correct[10] = 160;
  m1_correct[11] = 128;
  m1_correct[12] = 99;
  m1_correct[13] = 140;
  m1_correct[14] = 152;
  m1_correct[15] = 120;
  assert(m1_test == m1_correct);

  //std::cout << m1_test << std::endl << std::endl;

  std::cout << "PASSED THIRD TEST!!" << std::endl;
}

void test4() {
  Matrix m1_test(4, 4);
  for (int elem_i = 0; elem_i < 16; ++elem_i) {
    m1_test[elem_i] = (float) (elem_i * 16);
  }

  Matrix m1_correct(4, 4);
  const Matrix m2_test(m1_test);

  //std::cout << m1_test << std::endl << std::endl;
  m1_test = Sobel(m2_test);

  m1_correct[11] = 32;
  m1_correct[13] = 60;
  m1_correct[14] = 68;
  m1_correct[15] = 140;
  assert(m1_test == m1_correct);

  //std::cout << m1_test << std::endl << std::endl;

  std::cout << "PASSED FOURTH TEST!!" << std::endl;
}

void test5(){
  Matrix m1_test(2,2);
  Matrix m1_correct(2, 2);
  m1_test(0,0) = 1;
  m1_test(1,1) = 1;
  m1_correct[0] = 1;
  m1_correct[3] = 1;
  assert(m1_correct == m1_test);

  try {
    m1_test[4];
    assert(false && "Allowed off matrix indexing");
  }
  catch (MatrixException &e) {
    std::string a = MSG_INDEX;
    if (e.what() != a)
    {
      assert(false && "INCORRECT MSG");
    }
  }

  try {
    m1_test[-1];
    assert("Allowed off matrix indexing" && false);
  }
  catch (MatrixException &e) {
    std::string a = MSG_INDEX;
    if (e.what() != a)
    {
      assert(false && "INCORRECT MSG");
    }
  }

  try {
    m1_test(1, 3);
    assert(false && "Allowed off matrix indexing");
  }
  catch (MatrixException &e) {
    std::string a = MSG_INDEX;
    if (e.what() != a)
    {
      assert(false && "INCORRECT MSG");
    }
  }

  try {
    m1_test(3, 1);
    assert(false && "Allowed off matrix indexing");
  }
  catch (MatrixException &e) {
    std::string a = MSG_INDEX;
    if (e.what() != a)
    {
      assert(false && "INCORRECT MSG");
    }
  }

  try {
    Matrix m2_test(0, 3);
    assert(false && "Allowed 0 rows matrix");
  }
  catch (MatrixException &e) {
    std::string a = MSG_DIMENSIONS;
    if (e.what() != a)
    {
      assert(false && "INCORRECT MSG");
    }
  }

  try {
    Matrix m2_test(-1, 3);
    assert(false && "Allowed -1 rows matrix");
  }
  catch (MatrixException &e) {
    std::string a = MSG_DIMENSIONS;
    if (e.what() != a)
    {
      assert(false && "INCORRECT MSG");
    }
  }

  try {
    Matrix m2_test(100000000000, 3);
    std::cout << "no bad alloc occurred increase number" << std::endl;
  }
  catch (MatrixException &e) {
    std::string a = MSG_ALLOCATION;
    if (e.what() != a)
    {
      assert(false && "INCORRECT MSG");
    }
  }

  try {
    Matrix m2_test(3, 3);
    m2_test /= 0;
    assert(false && "Allowed division by 0");
  }
  catch (MatrixException &e) {
    std::string a = MSG_DIVISION;
    if (e.what() != a)
    {
      assert(false && "INCORRECT MSG");
    }
  }

  try {
    Matrix m2_test(1, 1);
    Matrix m3_test(2, 2);
    m2_test *= m3_test;
    assert(false && "Allowed invalid multiplication");
  }
  catch (MatrixException &e) {
    std::string a = MSG_DIMENSIONS;
    if (e.what() != a)
    {
      assert(false && "INCORRECT MSG");
    }
  }

  std::cout << "PASSED FIFTH TEST!!" << std::endl;
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  std::cout << "PASSED ALL TEST!!" << std::endl;
  return 0;
}