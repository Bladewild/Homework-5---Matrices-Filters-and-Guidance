#include "hw5_grader.h"

int main()
{
  const MatrixWrap<int>::type test1({{5, 2}, {-2, -1}});
  const MatrixWrap<int>::type test2({{-1, 2}, {3, -2}});
  int result[2][2] = {{1, 6}, {-1, -2}};

  const MatrixWrap<int>::type student_result = test1 * test2;
  for (auto i = 0u; i < 2; i++) {
    for (auto j = 0u; j < 2; j++) {
      if (student_result(i, j) != result[i][j]) {
        return 1;
      }
    }
  }
  return 0;
}
