#include "ProductUi.h"

void make_tests()
{
  tests_product_repo();
  test_controller();
  test_date();
}

int main()
{
  make_tests();

  t_product_repo *repo = create_repo();
  t_product_ctrl *ctrl = create_ctrl(repo);

  add_product_c(ctrl, (char*)"Milk", (char*)"dairy", 25, 25, 3, 2017, 0);
  add_product_c(ctrl, (char*)"Chocolate", (char*)"sweets", 5, 3, 2, 2017, 0);
  add_product_c(ctrl, (char*)"Milk", (char*)"dairy", 5, 1, 1, 2018, 0);
  add_product_c(ctrl, (char*)"Apple", (char*)"fruit", 3, 3, 3, 2017, 0);
  add_product_c(ctrl, (char*)"Candy", (char*)"sweets", 10, 1, 1, 2018, 0);
  add_product_c(ctrl, (char*)"Cake", (char*)"sweets", 15, 1, 1, 2018, 0);
  add_product_c(ctrl, (char*)"Cupcake", (char*)"sweets", 20, 10, 10, 2028, 0);
  add_product_c(ctrl, (char*)"Cheese", (char*)"dairy", 100, 1, 1, 2018, 0);
  add_product_c(ctrl, (char*)"Orange", (char*)"fruit", 5, 3, 3, 2017, 0);
  add_product_c(ctrl, (char*)"Pear", (char*)"fruit", 1, 3, 3, 2017, 0);


  t_product_ui *ui = create_ui(ctrl);
  start_ui(ui);
  return 0;
}
