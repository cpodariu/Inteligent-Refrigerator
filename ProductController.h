#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "ProductRepository.h"

typedef struct
{
  t_product_repo *repo;
} t_product_ctrl;

t_product_ctrl *create_ctrl(t_product_repo *r);
void free_controller(t_product_ctrl *c);
void add_product_c  (t_product_ctrl *c, char* name, char* category,
                    int quantity, int day, int month, int year, int is_update);
t_product_repo *get_repo(t_product_ctrl *c);
void sort_repository(t_product_ctrl *c);
int remove_product_c(t_product_ctrl *c, char *name, int is_update);
void init_controller_repo_test(t_product_ctrl *c);
void test_add_c();
void test_sort_repo();
void test_controller();
void print_reverse_by_category_ctrl(t_product *p, char *category);
t_product *get_products_c(t_product_ctrl *c);
void undo_c(t_product_ctrl *c);
void redo_c(t_product_ctrl *c);
#endif /* end of include guard: CONTROLLER_H */
