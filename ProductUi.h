#ifndef PRODUCTUI_H
#define PRODUCTUI_H
#include "ProductController.h"

typedef struct{
  t_product_ctrl *ctrl;
} t_product_ui;

t_product_ui *create_ui(t_product_ctrl *c);
void print_menu();
void start_ui(t_product_ui *ui);
void print_fridge(t_product_ui *ui);
void remove_product_ui(t_product_ui *ui);
void update_ui(t_product_ui *ui);
void print_reverse_by_category_ui(t_product_ui *ui);
void print_soon_to_expire(t_product_ui *ui);

#endif /* end of include guard: PRODUCTUI_H */
