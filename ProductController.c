#include "ProductController.h"

/**
 * Creates the controller
 * @param  r a product repository
 * @return   the newly created controller
 */
t_product_ctrl *create_ctrl(t_product_repo *r)
{
  t_product_ctrl *c = (t_product_ctrl*)malloc(sizeof(t_product_ctrl));
  c->repo = r;

  return c;
}

t_product *get_products_c(t_product_ctrl *c){
  return get_products(c->repo);
}

/**
 * Takes a controller and frees the memory from it
 * @param c the controller to be freed
 */
void free_controller(t_product_ctrl *c)
{
  free_repo(c->repo);
  free(c);
}

/**
 * Adds a product to the repository
 * @param c        the controller
 * @param name     char*
 * @param category char*
 * @param quantity int
 * @param day      int
 * @param month    int
 * @param year     int
 */
void add_product_c  (t_product_ctrl *c, char* name, char* category,
                    int quantity, int day, int month, int year, int is_update)
{
  t_product *p = create_product(name, category, quantity, day, month, year);
  add_product_r(c->repo, p, 0, is_update);
  sort_repository(c);
}

/**
 * Returns the repository of a controller
 * @param  c the controller
 * @return   the repository
 */
t_product_repo *get_repo(t_product_ctrl *c)
{
  return c->repo;
}

/**
 * Sorts the repository in a give controller
 * @param c the controller
 */
void sort_repository(t_product_ctrl *c)
{
  int ok;
  t_product *p;

  if (c->repo->length < 2)
    return ;
  ok = 1;
  while(ok)
  {
    ok = 0;
    p = c->repo->products;
    while(p->next != NULL)
    {
      if (p->quantity > p->next->quantity)
      {
        swap_products(p, p->next);
        ok = 1;
      }
      p = p->next;
    }
  }
}

/**
 * Removes a product
 * @param  c    the controller
 * @param  name The name of the product to be removed
 * @return      1- if the product was removed, 0 if it does not exist
 */
int remove_product_c(t_product_ctrl *c, char *name, int is_update)
{
  return remove_product(c->repo, name, 0, is_update);
}

void print_reverse_by_category_ctrl(t_product *p, char *category)
{
  char *str;

  str = (char*)malloc(sizeof(char) * 200);
  if (p->next != NULL)
    print_reverse_by_category_ctrl(p->next, category);
  if (!strcmp(p->category, category))
  {
    to_string(p, str);
    printf("%s\n", str);
  }
}

void undo_c(t_product_ctrl *c)
{
  undo(c->repo);
  sort_repository(c);

}

void redo_c(t_product_ctrl *c)
{
  redo(c->repo);
  sort_repository(c);

}

//----------------TESTS----------

void init_controller_repo_test(t_product_ctrl *c)
{
  add_product_c(c, (char*)"Pear", (char*)"fruit", 3, 2, 3, 2015, 0);
}

void test_add_c()
{
  t_product_repo *v = create_repo();
  t_product_ctrl *c = create_ctrl(v);

  init_controller_repo_test(c);
  assert(get_length(c->repo) == 1);
  add_product_c(c, (char*)"Apple", (char*)"fruit", 3, 2, 3, 2015, 0);
  assert(get_length(c->repo) == 2);
}

void test_sort_repo()
{
  t_product_repo *v = create_repo();
  t_product_ctrl *c = create_ctrl(v);

  init_controller_repo_test(c);
  add_product_c(c, (char*)"Apple", (char*)"fruit", 100, 2, 3, 2015, 0);
  sort_repository(c);
  assert(!strcmp(c->repo->products->name, "Pear"));
}

void test_controller()
{
  test_add_c();
  test_sort_repo();
}
