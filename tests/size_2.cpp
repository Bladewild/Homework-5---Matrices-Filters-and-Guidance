#include "hw5_grader.h"

int main()
{
  MatrixWrap<int>::type test2({{1, 5, 7, 3, 7, 5, 3, 6}});
  if (test2.rows() != 1) {
    return 1;
  }
  if (test2.cols() != 8) {
    return 1;
  }
  return 0;
}
