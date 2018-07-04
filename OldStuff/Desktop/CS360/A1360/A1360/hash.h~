/*Michael Allen-Bond
Programming Assignment 1
CS 360
Dr. Lang
*/

/*To use this hashtable, you only need 3 of the functions.  The rest are used internally, and while you 
may use them for specific purposes, they are not necessary for creating and using the hash table.

Table *hash(int N); - makes a new hashtable.

Table *hashadd(char *wordpair, Table *Hashtable); - inserts or iterates the value of the wordpair in the hashtable

void output(Table *Hashtable,int limit); - prints out the hash table, sorted, up to <limit> lines.

That's it.*/

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


Table *hash(int N);
/* Simple function, just makes an empty hashtable. Takes an integer as an argument, integer determines
the initial number of bucket pointers in the table.*/

typedef int (*compfn)(const void*, const void*); 
/* reference function pointing to my compare function.
	Did this to make qsort easier to deal with.*/
int comparevalues(Node *a, Node *b);
/*Actual compare function.  takes 2 nodes and compares the integer values in them.
qsort manages the argument input for this function.*/

Table *hashexpand(Table *Hashtable);
/*expands the hash table. takes a pointer to a hashtable as an argument. Returns a hash table*/

void output(Table *Hashtable,int limit);
/*places all of the hash table values into an array, sorts them, and then outputs them. 
<limit> is the number of items you want printed out.*/

Table *hashadd(char *wordpair, Table *Hashtable);
/*searches and adds the wordpair to the table, or increments its value if it is already
in the table.  takes a pair of words in a string and the hashtable as arguments. 
This function already implements hashsearch.*/

int hashsearch(char *wordpair, unsigned long long hashkey, Table *Hashtable);
/* searches the hash for a wordpair, returns 0 if found.  takes the wordpair, hashkey, and hashtable as arguments. 
Returns 0 if a match is found, 1 if not.*/

void freehash(Table *Hashtable);
/*Frees everything in the hashtable, and then frees the hashtable.*/

unsigned long long crc64(char* string);
/*returns the hashkey. takes a string as an Arg.  Dr. Lang's code.*/
