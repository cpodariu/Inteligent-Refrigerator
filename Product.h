#ifndef PRODUCT_H
#define PRODUCT_H
# include "Date.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_product
{
  char *name;
  char *category;
  int quantity;
  t_date date;
  struct s_product *next;
} t_product;

t_product *create_product(char *name, char *category,
int quantity, int year, int month, int day);
void free_product(t_product *p);
char* get_name(t_product *p);
char* get_category(t_product *p);
int get_quantity(t_product *p);
t_date get_date(t_product *p);
void add_quantity(t_product *p, int quantity);
void to_string(t_product *p, char *str);
void swap_products(t_product *p1, t_product *p2);

#endif /* end of include guard: PRODUCT_H */
