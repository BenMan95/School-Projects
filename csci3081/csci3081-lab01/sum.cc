#include <iostream>

int main() {

  double first_num, second_num, sum;

  printf("Enter first number: ");
  std::cin >> first_num;
  printf("Enter second number: ");
  std::cin >> second_num;

  sum = first_num + second_num;

  printf("%f + %f = %.2f", first_num, second_num, sum);

  return 0;

}
