#include "./test.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// int main (){
//   S21::vector<int> s;
// return 0;
// }