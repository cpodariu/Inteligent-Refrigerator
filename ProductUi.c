#include "ProductUi.h"

t_product_ui *create_ui(t_product_ctrl *c)
{
  t_product_ui *ui = (t_product_ui*)malloc(sizeof(t_product_ui));
  ui->ctrl = c;

  return ui;
}

void free_ui(t_product_ui *ui)
{
  free_controller(ui->ctrl);
  free(ui);
}

void add_product_ui(t_product_ui *ui)
{
  char name[25];
  char category[15];
  int quantity;
  int day;
  int month;
  int year;

  scanf("%s%s%i%i%i%i", name, category, &quantity, &day, &month, &year);
  add_product_c(ui->ctrl, name, category, quantity, day, month, year);
}

void print_menu()
{
  printf("\n**********************************************************\n");
  printf("add name category quantity day month year\n");
  printf("remove name\n");
  printf("print\n");
  printf("exit\n");
  printf("**********************************************************\n\n");
}

void print_fridge(t_product_ui *ui)
{
  t_product *p = ui->ctrl->repo->products;
  char *line;
  line = (char*)malloc(sizeof(char) * 200);

  while(p != NULL)
  {
    to_string(p, line);
    printf("%s", line);
    p = p->next;
  }
  printf("\n");
  //free(line);
}

void print_fridge2(t_product_ui *ui)
{
  char *command;
  char *line;
  t_product *p = ui->ctrl->repo->products;

  command = (char*)malloc(sizeof(char) * 100);
  line = (char*)malloc(sizeof(char) * 100);

  //scanf("%s", command);
  fgets(command, 99, stdin);
  if (command[0] == '\n')
  {
//    free(command);
//    free(line);
    return print_fridge(ui);
  }
  command[strcspn(command, "\r\n")] = 0;
  while(*command == ' ')
    command++;

  while(p != NULL)
  {
    if (strstr(p->name, command) != NULL)
    {
      to_string(p, line);
      printf("%s", line);
    }
    p = p->next;
  }
  printf("\n");
  // free(command);
  // free(line);
}

void remove_product_ui(t_product_ui *ui)
{
  char *command;

  command = (char *)malloc(sizeof(char) * 100);
  fgets(command, 99, stdin);
  command[strcspn(command, "\r\n")] = 0;
  while(*command == ' ')
    command++;
  if (remove_product_c(ui->ctrl, command) == 0)
    printf("Product not in repository\n");
  //free(command);
}

void update_ui(t_product_ui *ui)
{
  char name[25];
  char category[15];
  int quantity;
  int day;
  int month;
  int year;

  scanf("%s%s%i%i%i%i", name, category, &quantity, &day, &month, &year);
  if (remove_product_c(ui->ctrl, name) == 0)
  {
    printf("Product not in repository\n");
    return ;
  }
  add_product_c(ui->ctrl, name, category, quantity, day, month, year);
}

void print_reverse_by_category_ui(t_product_ui *ui)
{
  t_product *p = ui->ctrl->repo->products;
  char *category;

  category = (char*)malloc(sizeof(char) * 50);
  scanf("%s", category);
  print_reverse_by_category_ctrl(p, category);
}

void start_ui(t_product_ui *ui)
{
  char *command;
  command = (char*)malloc(sizeof(char) * 100);
  while(1)
  {
    scanf("%s", command);
    if (!strcmp(command, "add"))
      add_product_ui(ui);
    if (!strcmp(command, "remove"))
      remove_product_ui(ui);
    if (!strcmp(command, "print"))
      print_fridge2(ui);
    if (!strcmp(command, "exit"))
    {
      free_ui(ui);
      return;
    }
    if (!strcmp(command, "update"))
      update_ui(ui);
    if (!strcmp(command, "menu"))
      print_menu();
    if (!strcmp(command, "magic"))
      print_reverse_by_category_ui(ui);
  }
}
