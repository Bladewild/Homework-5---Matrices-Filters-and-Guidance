#include "hw5_grader.h"
int main()
{
  MatrixWrap<int>::type test1;
  std::istringstream in_str("0 4 1 6 5\n19 12 -11 4 2\n");
  int correct[2][5] = {{0, 4, 1, 6, 5}, {19, 12, -11, 4, 2}};
  in_str >> test1;
  for (auto i = 0u; i < 2; i++) {
    for (auto j = 0u; j < 5; j++) {
      if (correct[i][j] != test1(i,j)) {
        return 1;
      }
    }
  }
  return 0;
}
