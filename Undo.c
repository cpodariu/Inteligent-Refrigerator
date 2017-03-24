#include "ProductRepository.h"

/**
 * Initializes an opr type
 * @return t_opr
 */
t_opr *init_opr()
{
  t_opr *opr;
  opr = (t_opr*)malloc(sizeof(t_opr));
  opr->cmd = (char*)malloc(sizeof(char) * 50);
  opr->name = (char*)malloc(sizeof(char) * 50);
  opr->category = (char*)malloc(sizeof(char) * 50);
  opr->next = NULL;
  opr->prev = NULL;
  opr->is_update = 0;
  return opr;
}

/**
 * copies the data from a product into an opr
 * @param opr the t_opr variable
 * @param p   the product
 * @param cmd what kind of operation it is
 */
void add_opr(t_opr *opr, t_product *p, const char *cmd, int is_update)
{
  strcpy(opr->cmd, cmd);
  strcpy(opr->name, p->name);
  strcpy(opr->category, p->category);
  opr->quantity = p->quantity;
  opr->date.day = p->date.day;
  opr->date.month = p->date.month;
  opr->date.year = p->date.year ;
  opr->is_update = is_update;
}

/**
 * frees the memory from an opr
 * @param opr the opr
 */
void free_opr(t_opr *opr)
{
  free(opr->cmd);
  free(opr->name);
  free(opr);
}

/**
 * does the reverse of an operation
 * @param opr [description]
 * @param r   [description]
 */
void do_opr(t_opr *opr, t_product_repo *r)
{
  if (!strcmp(opr->cmd, "remove"))
  {
    //printf ("wuut%s\n",opr->name);
    add_product_r(r, create_product(opr->name, opr->category,
    opr->quantity, opr->date.day, opr->date.month, opr->date.year), 1, opr->is_update);
    strcpy(opr->cmd, "add");
  }
  else if (!strcmp(opr->cmd, "add"))
  {
    //printf("%s\n", opr->name);
    remove_product(r, opr->name, 1, opr->is_update);
    strcpy(opr->cmd, "remove");
  }
}

/**
 * frees an opr and all oprs previous to it
 * @param opr pointer to first opr
 */
void free_all_opr_left(t_opr *opr)
{
  if (opr->prev == NULL)
    free_opr(opr);
  else
    {
      free_all_opr_left(opr->prev);
      free_opr(opr);
    }
}
