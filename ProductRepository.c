#include "ProductRepository.h"

/**
 * Creates, Initializes and returns a repo
 * @return the repo
 */
t_product_repo *create_repo()
{
  t_product_repo *v = (t_product_repo*)malloc(sizeof(t_product_repo));
  v->products = NULL;
  v->length = 0;

  return v;
}

t_product *get_products(t_product_repo *r)
{
  return (r->products);
}


/**
 * Frees a repo from memory
 * @param v the repo to be freed
 */
void free_repo(t_product_repo *v)
{
  t_product *p;
  t_product *next;

  p = v->products;
  if (p != NULL)
    while(p->next != NULL)
    {
      next = p->next;
      free_product(p);
      p = next;
    }
  free_product(p);
  free(v);
}

/**
 * Loks up a product with the given name
 * @param  v    the repo where to look
 * @param  name the name of the product
 * @return      the product, or NULL if the product was not found
 */
t_product *find(t_product_repo *v, char* name)
{
  t_product *p = v->products;
  if (p == NULL)
    return NULL;
  while (p->next != NULL)
  {
    if (!strcmp(p->name, name))
      return p;
    p = p->next;
  }
  if (!strcmp(p->name, name))
    return p;
  return NULL;
}

/**
 * Adds a new product to the repo
 * @param v the repo
 * @param p the product to be added
 */
void add_product_r(t_product_repo *v, t_product *p)
{
    t_product *prod;
  //  printf("%s\n",p->name);
    if (find(v, p->name) != NULL)
    {
      prod = find(v, p->name);
      prod->quantity += p->quantity;
      return ;
    }
    p->next = v->products;
    v->products = p;
    v->length++;
}
//
// void add_product_r_2(t_product_repo *v, t_product *p)
// {
//   t_product *prod;
//
//   if (find(v, p->name) != NULL)
//   {
//     prod = find(v, p->name);
//     prod->quantity += p->quantity;
//     return ;
//   }
//   prod = v->products;
//   while (prod->next != NULL && prod->next->quantity < p->quantity)
//   {}
// }

/**
 * Finds the number of products in a repo
 * @param  v the repo
 * @return   the number of elements
 */
int get_length(t_product_repo *v)
{
    return v->length;
}

/**
 * Remove the product with name @name from the repo
 * @param  v    the repository
 * @param  name the name of the product to be removed
 * @return      1 - removed succesfully; 0 - product not found
 */
int remove_product(t_product_repo *v, char* name)
{
  t_product *p = v->products;
  t_product *aux;

  if (p == NULL)
    return 0;
  if (!strcmp(p->name, name))
  {
    free_product(p);
    v->products = v->products->next;
    v->length-=1;
    return 1;
  }
  while (p->next != NULL)
  {
    if (!strcmp(p->next->name, name))
    {
      aux = p->next;
      p->next = p->next->next;
      free(aux);
      v->length -= 1;
      return 1;
    }
    p = p->next;
  }
  return 0;
}

//--------------------TESTS--------------------

void init_product_repo_test(t_product_repo *v)
{
    t_product *p = create_product((char*)"Milk", (char*)"dairy", 10, 25, 3, 2017);
    add_product_r(v, p);
}

void test_add()
{
  t_product_repo *v = create_repo();

  init_product_repo_test(v);
  assert(get_length(v) == 1);

  t_product *p = create_product((char*)"Cheese", (char*)"dairy", 5, 22, 3, 2017);
  add_product_r(v, p);
  assert(get_length(v) == 2);

  p = create_product((char*)"Milk", (char*)"dairy", 5, 25, 3, 2017);
  add_product_r(v, p);
  assert(get_length(v) == 2);
  assert(find(v, (char*)"Milk")->quantity == 15);

  free_repo(v);
}

void test_remove()
{
  t_product_repo *v = create_repo();

  init_product_repo_test(v);
  t_product *p = create_product((char*)"Cheese", (char*)"dairy", 5, 22, 3, 2017);
  add_product_r(v, p);
  remove_product(v, (char*)"Cheese");
  assert(get_length(v) == 1);
}

void test_find()
{
  t_product_repo *v = create_repo();

  init_product_repo_test(v);
  t_product *p = create_product((char*)"Cheese", (char*)"dairy", 5, 22, 3, 2017);
  add_product_r(v, p);
  assert(find(v, (char*)"Cheese")->quantity == 5);
}

void tests_product_repo()
{
  test_add();
  test_remove();
  test_find();
}
