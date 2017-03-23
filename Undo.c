#include "ProductRepository.h"

t_opr *init_opr()
{
  t_opr *opr;
  opr = (t_opr*)malloc(sizeof(t_opr));
  opr->cmd = (char*)malloc(sizeof(char) * 50);
  opr->name = (char*)malloc(sizeof(char) * 50);
  opr->category = (char*)malloc(sizeof(char) * 50);
  opr->next = NULL;
  opr->prev = NULL;
  return opr;
}

void add_opr(t_opr *opr, t_product *p, const char *cmd)
{
  strcpy(opr->cmd, cmd);
  strcpy(opr->name, p->name);
  strcpy(opr->category, p->category);
  opr->quantity = p->quantity;
  opr->date.day = p->date.day;
  opr->date.month = p->date.month;
  opr->date.year = p->date.year ;
}

void free_opr(t_opr *opr)
{
  free(opr->cmd);
  free(opr->name);
  free(opr);
}

void do_opr(t_opr *opr, t_product_repo *r)
{
  if (!strcmp(opr->cmd, "remove"))
  {
    add_product_r(r, create_product(opr->name, opr->category,
    opr->quantity, opr->date.year, opr->date.month, opr->date.day));
  }
  if (!strcmp(opr->cmd, "add"))
  {
    remove_product(r, opr->name);
  }
}

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
