#include "Product.h"

/**
 * Initializes and returns a pointer to a t_product typede
 * variable
 * @param  name     char* the name of the product
 * @param  category char* product category
 * @param  quantity int
 * @param  year     int
 * @param  month    int
 * @param  day      int
 * @return          t_product* :a pointer to a t_product
 */
t_product *create_product(char *name, char *category,
                          int quantity, int day, int month,
                          int year)
{
  t_product *p;

  p = (t_product*)malloc(sizeof(t_product));
  p->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(p->name, name);
  p->category = (char*)malloc(sizeof(char) * (strlen(category) + 1));
  strcpy(p->category, category);
  p->quantity = quantity;
  p->date.day = day;
  p->date.month = month;
  p->date.year = year;
  p->next = NULL;

  return p;
}
/**
 * Frees a t_product from the memory
 * @param p t_product* pointer to the structure to be freed
 */
void free_product(t_product *p)
{
  free(p->name);
  free(p->category);
  free(p);
}

char* get_name(t_product *p)
{
  return p->name;
}

char* get_category(t_product *p)
{
  return p->category;
}

int get_quantity(t_product *p)
{
  return p->quantity;
}

t_date get_date(t_product *p)
{
  return p->date;
}

void add_quantity(t_product *p, int quantity)
{
  p->quantity += quantity;

}

void to_string(t_product *p, char *str)
{
  sprintf(str, "\nProduct: %s\nCategory: %s\nQuantity: %i\nExpires in: %i.%i.%i\n",
          p->name, p->category, p->quantity, p->date.day, p->date.month, p->date.year);
}

void swap_products(t_product *p1, t_product *p2)
{
    char *aux_c;
    int aux_i;
  // t_product *aux_p;

    aux_c = p1->name;
    p1->name = p2->name;
    p2->name = aux_c;

    aux_c = p1->category;
    p1->category = p2->category;
    p2->category = aux_c;

    aux_i = p1->quantity;
    p1->quantity = p2->quantity;
    p2->quantity = aux_i;

    aux_i = p1->date.day;
    p1->date.day = p2->date.day;
    p2->date.day = aux_i;

    aux_i = p1->date.month;
    p1->date.month = p2->date.month;
    p2->date.month = aux_i;

    aux_i = p1->date.year;
    p1->date.year = p2->date.year;
    p2->date.year = aux_i;

    //free (aux_c);
    // aux_p = p1->next;
    // p1->next = p2->next;
    // p2->next = aux_p;
}
