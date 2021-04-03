//
// Created by eldar on 28/12/2020.
//

#include <fstream>
#include <cassert>
#include "Matrix.h"
//#include "Filters.cc"

void test1() {
  Matrix m1_test(2, 2);
  Matrix m2_test(2, 3);
  Matrix m3_test;
  Matrix m1_correct(2,2);
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
  assert(m1_test == m1_correct && "MULTIPLY BY 3 AS A SCALAR TO ALL THE INDEXES");

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
  assert(m3_test.getCols() == m2_test.getCols());
  assert(m3_test.getRows() == m2_test.getRows());
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

  m3_test.vectorize();
  m3_correct.vectorize();

  assert(m3_test.getRows() == 6);
  assert(m3_test.getCols() == 1);

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
  m7_test.print();
  std::cout << std::endl;

  std::cin >> m7_test;
  std::cout << m7_test << std::endl << std::endl;

  std::cout << "PASSED FIRST TEST!!" << std::endl;
}

int main(int argc, char **argv) {
  test1();
  return 0;
}