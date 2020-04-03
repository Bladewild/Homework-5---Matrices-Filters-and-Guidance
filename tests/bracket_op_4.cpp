#include "hw5_grader.h"

int main()
{
  const MatrixWrap<int>::type test1({{4, 7, 9, 18, 22}});
  if (test1(0,2) != 9) {
    return 1;
  }
  return 0;
}
