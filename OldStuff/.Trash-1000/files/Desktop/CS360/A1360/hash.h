typedef struct _node{

   void *value;
   char *key;
   struct _node *next;
} Node;

typedef struct _table{
   int count;
   int size;
   struct _node *array;
} Table;

void hash(char *);
void hashadd(char *);
