#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <time.h>

#define N 3

unsigned long tick(void)
{
  unsigned long d;
  __asm__ __volatile__ ("rdtsc" : "=A" (d) );
  return d;
}
void test(void)
{
  long double test = 0.0;
  for(unsigned long i = 0; i < 10000; i++)
  test += 0.5;
}

struct book {
  int id;
  char name[20];
  char author[15];
  char ph[15];
  int page_quantity;
  char type[15];

  union {
    struct {
      char language[15];
      char branch[15];
      int yop;
    } tech;
    struct {
      char kind[15];
    } art;
  } add;
};

struct key {
  int id;
  int page_quantity;
}key;

void print(struct book* books, int quantity);
void sort(struct key* books, int quantity);
void sortTable(struct book books[], int quantity);
void sortvs(struct key* books, int quantity);
void sortTablevs(struct book books[], int quantity);
void filter(struct book* books, int quantity);
void printSorted(struct key* keyTable, struct book* books, int quantity);
int main() {
  int need_file = 0;
  printf("From file or manually (file - 1 / manually - 2): ");
  scanf("%d", &need_file);
  fflush(stdin);
  int quantity = 0;
  printf("Input books quantity: ");
  char _q[15];
  fgets(_q, 15, stdin);
  fflush(stdin);
  sscanf(_q, "%d", &quantity);
    
  struct book* booksAdd = (struct book*)malloc(sizeof(struct book) * (quantity-1));
  free(booksAdd);
  //fflush(stdin);
  struct book* books = (struct book*)malloc(sizeof(struct book) * quantity);
  struct key* keyTable = (struct key*)malloc(sizeof(struct key) * (quantity));

  unsigned long tb1, te1, tb2, te2;

  if (need_file == 1)
  {
    //printf("Input file name: ");
    //char fname[15];
    //fgets(fname, 15, stdin);
    //fflush(stdin);
    FILE *f;
    f = fopen("test.txt","r");
    for (int i = 0; i < quantity; i++)
    {
      books[i].id = i;
      fgets(books[i].name, 20, f);
      fgets(books[i].author, 15, f);
      fgets(books[i].ph, 15, f);
      fscanf(f,"%d\n", &books[i].page_quantity);
      fgets(books[i].type, 15, f);
      books[i].type[strcspn(books[i].type,"\n")] = 0;
      if (strcmp(books[i].type, "Artistic") == 0)
      {
        fgets(books[i].add.art.kind, 15, f);
      }
      else
      {
        fgets(books[i].add.tech.branch, 15, f);
        fgets(books[i].add.tech.language, 15, f);
        fscanf(f,"%d\n", &books[i].add.tech.yop);
      }
      keyTable[i].id = i;
      keyTable[i].page_quantity = books[i].page_quantity;
    }
  }
  else
  { 
    for (int i = 0; i < quantity; i++)
    {
      books[i].id = i;
      printf("Input book name: ");
      fgets(books[i].name, 20, stdin);
      fflush(stdin);
      printf("Input author name: ");
      fgets(books[i].author, 15, stdin);
      fflush(stdin);
      printf("Input publisher name: ");
      fgets(books[i].ph, 15, stdin);
      fflush(stdin);
      printf("Input page quantity: ");
      scanf("%d", &books[i].page_quantity);
      fflush(stdin);
      printf("Input the book type, technical or artistic: ");
      fgets(books[i].type, 15, stdin);
      fflush(stdin);
      books[i].type[strcspn(books[i].type,"\n")] = 0;
      if (strcmp(books[i].type, "Artistic") == 0)
      {
        printf("Input kind of a book: ");
        fgets(books[i].add.art.kind, 15, stdin);
        fflush(stdin);
      }
      else
      {
        printf("Input branch of a book: ");
        fgets(books[i].add.tech.branch, 15, stdin);
        fflush(stdin);
        printf("Input, domestic or translated book: ");
        fgets(books[i].add.tech.language, 15, stdin);
        fflush(stdin);
        printf("Input year of publication: ");
        scanf("%d", &books[i].add.tech.yop);
        fflush(stdin);
      }
      keyTable[i].id = i;
      keyTable[i].page_quantity = books[i].page_quantity;
    }
    print(books, quantity);
  }
  int add = 3;
  while (add != 0)
  {
    printf("Do u want to add / delete / filter / sort (key) / sort(table) / print a book? (1/2/3/4/5/6/quit=0): ");
    scanf("%d", &add);
    if (add == 1)
    {
      quantity++;
      booksAdd = (struct book*)malloc(sizeof(struct book) * (quantity-1));
      for (int i = 0; i < quantity - 1; i++)
        booksAdd[i] = books[i];
      free(books);
      books = (struct book*)malloc(sizeof(struct book) * quantity);
      for (int i = 0; i < quantity - 1; i++)
        books[i] = booksAdd[i];
      free(booksAdd);
      fflush(stdin);
      books[quantity-1].id = quantity-1;
      printf("Input book name: ");
      fflush(stdin);
      fgets(books[quantity-1].name, 20, stdin);
      fflush(stdin);
      printf("Input author name: ");
      fgets(books[quantity-1].author, 15, stdin);
      fflush(stdin);
      printf("Input publisher name: ");
      fgets(books[quantity-1].ph, 15, stdin);
      fflush(stdin);
      printf("Input page quantity: ");
      scanf("%d", &books[quantity-1].page_quantity);
      fflush(stdin);
      printf("Input the book type, technical or artistic: ");
      fgets(books[quantity-1].type, 15, stdin);
      fflush(stdin);
      books[quantity-1].type[strcspn(books[quantity-1].type,"\n")] = 0;
      if (strcmp(books[quantity-1].type, "Artistic") == 0)
      {
        printf("Input kind of a book: ");
        fgets(books[quantity-1].add.art.kind, 15, stdin);
        fflush(stdin);
      }
      else
      {
        printf("Input branch of a book: ");
        fgets(books[quantity-1].add.tech.branch, 15, stdin);
        fflush(stdin);
        printf("Input, domestic or translated book: ");
        fgets(books[quantity-1].add.tech.language, 15, stdin);
        fflush(stdin);
        printf("Input year of publication: ");
        scanf("%d", &books[quantity-1].add.tech.yop);
        fflush(stdin);
      }
      keyTable[quantity-1].id = quantity-1;
      keyTable[quantity-1].page_quantity = books[quantity-1].page_quantity;
      print(books, quantity);
    }
    else if(add == 2)
    {
      printf("Input id of a book: ");
      int kill_id = 0;
      fflush(stdin);
      scanf("%d", &kill_id);
      //printf("\n%d\n", kill_id);
      booksAdd = (struct book*)malloc(sizeof(struct book) * (quantity));
      int j = 0;
      int flag = 0;
      for (int i = 0; i < quantity; i++)
        if (books[i].id != kill_id)
        {
          //printf("\n%d %d\n", books[i].id, j);
          booksAdd[j] = books[i];
          j++;
        }
        else
          flag = 1;
      if (flag == 1) 
        quantity--;
      //print(booksAdd, quantity);
      free(books);
      books = (struct book*)malloc(sizeof(struct book) * quantity);
      for (int i = 0; i < quantity; i++)
        books[i] = booksAdd[i];
      free(booksAdd);
      print(books, quantity);
    }
    else if(add == 3)
      filter(books, quantity);
    else if(add == 4)
    {
      printf("\n Sorted. \n");
      tb1 = tick();
      sort(keyTable, quantity);
      te1 = tick();
      printSorted(keyTable, books, quantity);
      printf("\ntime = %lu\n", (te1 - tb1) / N);
      printf("\n Sorted by choice. \n");
      tb1 = tick();
      sortvs(keyTable, quantity);
      te1 = tick();
      printSorted(keyTable, books, quantity);
      printf("\ntime = %lu\n", (te1 - tb1) / N);
    }
    else if(add == 5)
    {
      booksAdd = (struct book*)malloc(sizeof(struct book) * (quantity));
      for (int i = 0; i < quantity; i++)
        booksAdd[i] = books[i];
      printf("\n Sorted. \n");
      tb2 = tick();
      sortTable(booksAdd, quantity);
      te2 = tick();
      print(booksAdd, quantity);
      printf("\ntime = %lu\n", ((te2 - tb2) / N));
      printf("\n Sorted by choice. \n");
      tb2 = tick();
      sortTablevs(booksAdd, quantity);
      te2 = tick();
      print(booksAdd, quantity);
      printf("\ntime = %lu\n", ((te2 - tb2) / N));
      //free(booksAdd);
    }
    else if(add == 6)
    {
      print(books, quantity);
    }
  }
  getch();
  return 0;
}

void printSorted(struct key* keyTable, struct book* books, int quantity)
{
  for (int i = 0; i < quantity; i++)
  {
    books[keyTable[i].id].name[strcspn(books[keyTable[i].id].name,"\n")] = 0;
    books[keyTable[i].id].author[strcspn(books[keyTable[i].id].author,"\n")] = 0;
    books[keyTable[i].id].ph[strcspn(books[keyTable[i].id].ph,"\n")] = 0;
    books[keyTable[i].id].type[strcspn(books[keyTable[i].id].type,"\n")] = 0;
    books[keyTable[i].id].add.tech.branch[strcspn(books[keyTable[i].id].add.tech.branch,"\n")] = 0;
    books[keyTable[i].id].add.tech.language[strcspn(books[keyTable[i].id].add.tech.language,"\n")] = 0;
    books[keyTable[i].id].add.art.kind[strcspn(books[keyTable[i].id].add.art.kind,"\n")] = 0;
    if (strcmp(books[keyTable[i].id].type, "Artistic") == 0)
      printf("%2d %20s %20s         %20s %7d %15s                                  %15s\n", books[keyTable[i].id].id, books[keyTable[i].id].name, books[keyTable[i].id].author, books[keyTable[i].id].ph, books[keyTable[i].id].page_quantity, books[keyTable[i].id].type, books[keyTable[i].id].add.art.kind);
    else
      printf("%2d %20s %20s %7d %20s %7d %15s %15s %15s %15s\n", books[keyTable[i].id].id, books[keyTable[i].id].name, books[keyTable[i].id].author, books[keyTable[i].id].add.tech.yop, books[keyTable[i].id].ph, books[keyTable[i].id].page_quantity, books[keyTable[i].id].type, books[keyTable[i].id].add.tech.branch, books[keyTable[i].id].add.tech.language, books[keyTable[i].id].add.art.kind);
  }
}

void filter(struct book* books, int quantity)
{
  int year = 0;
  printf("Input minimum year of publication (filter): ");
  scanf("%d", &year);
  fflush(stdin);
  char br[15];
  char lg[15];
  printf("Input branch of a book (filter): ");
  scanf("%15s", br);
  printf("Input language of a book (filter): ");
  scanf("%15s", lg);

  char name[20] = "Name";
  char author[15] = "Author";
  char yop[15] = "Year";
  char ph[15] = "Publishing";
  char page_quantity[15] = "Pages";
  char type[15] = "Type";
  char branch[15] = "Branch";
  char language[15] = "language";
  char id[3] = "id";
  printf("%2s %20s %20s %7s %20s %7s %15s %15s %15s\n", id, name, author, yop, ph, page_quantity, type, branch, language);
  for (int i = 0; i < quantity; i++)
    if (books[i].add.tech.yop >= year)
    {
      if (strcmp(books[i].add.tech.branch,br) == 0)
      {
        if (strcmp(books[i].add.tech.language,lg) == 0)
        {
          books[i].name[strcspn(books[i].name,"\n")] = 0;
          books[i].author[strcspn(books[i].author,"\n")] = 0;
          books[i].ph[strcspn(books[i].ph,"\n")] = 0;
          books[i].type[strcspn(books[i].type,"\n")] = 0;
          books[i].add.tech.branch[strcspn(books[i].add.tech.branch,"\n")] = 0;
          books[i].add.tech.language[strcspn(books[i].add.tech.language,"\n")] = 0;
          if (strcmp(books[i].type, "Artistic") == 0)
            printf("%2d %20s %20s         %20s %7d %15s                                  %15s\n", books[i].id, books[i].name, books[i].author, books[i].ph, books[i].page_quantity, books[i].type, books[i].add.art.kind);
          else
            printf("%2d %20s %20s %7d %20s %7d %15s %15s %15s %15s\n", books[i].id, books[i].name, books[i].author, books[i].add.tech.yop, books[i].ph, books[i].page_quantity, books[i].type, books[i].add.tech.branch, books[i].add.tech.language, books[i].add.art.kind);
        }
      }
    }
}

void sort(struct key* books, int quantity)
{
  for (int i = 0; i < quantity; i++)
    for (int j = 0; j < quantity - 1; j++)
      if (books[j].page_quantity < books[j+1].page_quantity)
      {
        struct key number = books[j];
        books[j] = books[j+1];
        books[j+1] = number;
      }
}

void sortvs(struct key* books, int quantity)
{
  for (int i = 0; i < quantity; i++)
  {
    int minPosition = i;
    for (int j = i + 1; j < quantity; j++)
      if (books[minPosition].page_quantity < books[j].page_quantity)
        minPosition = j;
    struct key number = books[minPosition];
    books[minPosition] = books[i];
    books[i] = number;
  }
}

void sortTablevs(struct book books[], int quantity)
{
  for (int i = 0; i < quantity; i++)
  {
    int minPosition = i;
    for (int j = i + 1; j < quantity; j++)
      if (books[minPosition].page_quantity < books[j].page_quantity)
        minPosition = j;
    struct book number = books[minPosition];
    books[minPosition] = books[i];
    books[i] = number;
  }
}

void sortTable(struct book books[], int quantity)
{
  for(int i = 0; i < quantity; i++)
    for(int j = 0; j < quantity; j++)
      if (books[j].page_quantity < books[j+1].page_quantity)
      {
        struct book number = books[j];
        books[j] = books[j+1];
        books[j+1] = number;
      }
}

void print(struct book* books, int quantity)
{
  char name[20] = "Name";
  char author[15] = "Author";
  char yop[15] = "Year";
  char ph[15] = "Publishing";
  char page_quantity[15] = "Pages";
  char type[15] = "Type";
  char branch[15] = "Branch";
  char language[15] = "language";
  char kind[15] = "kind";
  char id[3] = "id";
  printf("%2s %20s %20s %7s %20s %7s %15s %15s %15s %15s\n",id, name, author, yop, ph, page_quantity, type, branch, language, kind);
  for (int i = 0; i < quantity; i++)
  {
    books[i].name[strcspn(books[i].name,"\n")] = 0;
    books[i].author[strcspn(books[i].author,"\n")] = 0;
    books[i].ph[strcspn(books[i].ph,"\n")] = 0;
    books[i].type[strcspn(books[i].type,"\n")] = 0;
    books[i].add.tech.branch[strcspn(books[i].add.tech.branch,"\n")] = 0;
    books[i].add.tech.language[strcspn(books[i].add.tech.language,"\n")] = 0;
    books[i].add.art.kind[strcspn(books[i].add.art.kind,"\n")] = 0;
    if (strcmp(books[i].type, "Artistic") == 0)
      printf("%2d %20s %20s         %20s %7d %15s                                  %15s\n", books[i].id, books[i].name, books[i].author, books[i].ph, books[i].page_quantity, books[i].type, books[i].add.art.kind);
    else
      printf("%2d %20s %20s %7d %20s %7d %15s %15s %15s %15s\n", books[i].id, books[i].name, books[i].author, books[i].add.tech.yop, books[i].ph, books[i].page_quantity, books[i].type, books[i].add.tech.branch, books[i].add.tech.language, books[i].add.art.kind);
  }
}