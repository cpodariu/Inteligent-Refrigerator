#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H

#include "Product.h"
#include <assert.h>

typedef struct s_opr{
  char *cmd;
  char *name;
  char *category;
  int quantity;
  t_date date;
  struct s_opr *next;
  struct s_opr *prev;
} t_opr;

typedef struct
{
  t_product *products;
  t_opr *opr;
  int length;
} t_product_repo;

t_product_repo *create_repo();
void free_repo(t_product_repo *v);
t_product *find(t_product_repo *v, char* name);
int get_length(t_product_repo *v);
int remove_product(t_product_repo *v, char* name, int control);
void init_product_repo_test(t_product_repo *v);
void test_add();
void tests_product_repo();
t_product *get_products(t_product_repo *r);
void add_product_r(t_product_repo *v, t_product *p, int control);


t_opr *init_opr();
void free_opr(t_opr *opr);
void do_opr(t_opr *opr, t_product_repo *r);
void add_opr(t_opr *opr, t_product *p, const char *cmd);
void free_all_opr_left(t_opr *opr);
void undo(t_product_repo *v);
void redo(t_product_repo *v);

#endif /* end of include guard: PRODUCTREPOSITORY_H*/
