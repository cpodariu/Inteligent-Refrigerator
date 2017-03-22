#ifndef PRODUCTREPOSITORY_H
#define PRODUCTREPOSITORY_H
#include "Product.h"
#include <assert.h>

typedef struct
{
  t_product *products;
  int length;
} t_product_repo;

t_product_repo *create_repo();
void free_repo(t_product_repo *v);
t_product *find(t_product_repo *v, char* name);
void add_product_r(t_product_repo *v, t_product *p);
int get_length(t_product_repo *v);
int remove_product(t_product_repo *v, char* name);
void init_product_repo_test(t_product_repo *v);
void test_add();
void tests_product_repo();
t_product *get_products(t_product_repo *r);


#endif /* end of include guard: PRODUCTREPOSITORY_H*/
