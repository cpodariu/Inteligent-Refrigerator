#include "ProductRepository.h"

/**
 * Creates, Initializes and returns a repo
 * @return the repo
 */
t_product_repo *create_repo()
{
  t_product_repo *v = (t_product_repo*)malloc(sizeof(t_product_repo));
  v->products = NULL;
  v->opr = NULL;
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
void add_product_r(t_product_repo *v, t_product *p, int control, int is_update)
{
    //static int test = 0;
  //  test++;
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

    if (control == 0)
    {
      t_opr *opr = init_opr();
      add_opr(opr, p, "add", is_update);
      if (v->opr == NULL)
      {
        v->opr = opr;
        //if (v->opr == NULL)
          //printf("* %i \n", test);
      }
      else if (v->opr->prev == NULL)
      {
        v->opr->prev = opr;
        opr->next = v->opr;
        v->opr = opr;
        //printf("! %i \n", test);
      }
      else
      {
        free_all_opr_left(v->opr->prev);
        v->opr->prev = opr;
        opr->next = v->opr;
        v->opr = opr;
      }
    }
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
int remove_product(t_product_repo *v, char* name, int control, int is_update)
{
  t_product *p = v->products;
  t_product *aux;

  if (p == NULL)
    return 0;
  if (!strcmp(p->name, name))
  {
    if (control == 0)
    {
      t_opr *opr = init_opr();
      add_opr(opr, p, "remove", is_update);
      if (v->opr == NULL)
      {
        v->opr = opr;
        //if (v->opr == NULL)
        //  printf("*\n");
      }
      else if (v->opr->prev == NULL)
      {
        v->opr->prev = opr;
        opr->next = v->opr;
        v->opr = opr;
      }
      else
      {
        free_all_opr_left(v->opr->prev);
        v->opr->prev = opr;
        opr->next = v->opr;
        v->opr = opr;
      }
    }

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

      if (control == 0)
      {
        t_opr *opr = init_opr();
        add_opr(opr, aux, "remove", is_update);
        //printf("%s\n", aux->name);
        if (v->opr == NULL)
        {
          v->opr = opr;
          //if (v->opr == NULL)
          //  printf("*\n");
        }
        else if (v->opr->prev == NULL)
        {
          v->opr->prev = opr;
          opr->next = v->opr;
          v->opr = opr;
          //printf("*\n");
        }
        else
        {
          free_all_opr_left(v->opr->prev);
          v->opr->prev = opr;
          opr->next = v->opr;
          v->opr = opr;
        }
      }

      free_product(aux);
      v->length -= 1;
      return 1;
    }
    p = p->next;
  }
  return 0;
}

/**
 * Undoes the lpo
 * @param v the repository
 */
void undo(t_product_repo *v)
{
  if (v->opr != NULL)
  {
    if (v->opr->is_update == 0)
    {
      do_opr(v->opr, v);
      v->opr = v->opr->next;
    }
    else
    {
      do_opr(v->opr, v);
      do_opr(v->opr->next, v);
      v->opr = v->opr->next->next;
    //  printf("*");
    }
  }
}

/**
 * redoes lpo
 * @param v the repository
 */
void redo(t_product_repo *v)
{
  if (v->opr->prev != NULL)
  {
    if (v->opr->prev->is_update == 0)
    {
    do_opr(v->opr->prev, v);
    v->opr = v->opr->prev;
    }
    else
    {
      //printf("**\n");
      do_opr(v->opr->prev, v);
      do_opr(v->opr->prev->prev, v);
      v->opr = v->opr->prev->prev;
      printf("**\n");
    }
  }
}

//--------------------TESTS--------------------

void init_product_repo_test(t_product_repo *v)
{
    t_product *p = create_product((char*)"Milk", (char*)"dairy", 10, 25, 3, 2017);
    add_product_r(v, p, 0, 0);
}

void test_add()
{
  t_product_repo *v = create_repo();

  init_product_repo_test(v);
  assert(get_length(v) == 1);

  t_product *p = create_product((char*)"Cheese", (char*)"dairy", 5, 22, 3, 2017);
  add_product_r(v, p, 0, 0);
  assert(get_length(v) == 2);

  p = create_product((char*)"Milk", (char*)"dairy", 5, 25, 3, 2017);
  add_product_r(v, p, 0, 0);
  assert(get_length(v) == 2);
  assert(find(v, (char*)"Milk")->quantity == 15);

  free_repo(v);
}

void test_remove()
{
  t_product_repo *v = create_repo();

  init_product_repo_test(v);
  t_product *p = create_product((char*)"Cheese", (char*)"dairy", 5, 22, 3, 2017);
  add_product_r(v, p, 0, 0);
  remove_product(v, (char*)"Cheese", 0, 0);
  assert(get_length(v) == 1);
}

void test_find()
{
  t_product_repo *v = create_repo();

  init_product_repo_test(v);
  t_product *p = create_product((char*)"Cheese", (char*)"dairy", 5, 22, 3, 2017);
  add_product_r(v, p, 0, 0);
  assert(find(v, (char*)"Cheese")->quantity == 5);
}

void tests_product_repo()
{
  test_add();
  test_remove();
  test_find();
}
