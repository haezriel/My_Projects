#include <stdio.h>
#include <fcntl.h>
#include <gdbm.h>
#include <string.h>

main()
{
  GDBM_FILE db; // database
  datum key,data;
  int status;
  char buffer[120],buffer2[120];

// open database
  db=gdbm_open("database",512,GDBM_READER|GDBM_WRCREAT,0600,0); // read/write, create, owner access

// store/read some words
  printf("Enter s to store, r to retrieve, d to dump, ^D to quit: ");
  fflush(stdout);

  while (NULL != fgets(buffer,120,stdin)){
// parse simple commands
    switch(buffer[0]){
      case 's': // store some data
// read the key
        printf("Enter key: ");fflush(stdout);
        fgets(buffer,120,stdin);
        key.dptr=buffer;key.dsize=strlen(key.dptr)+1;

// read the data
        printf("Enter data: ");fflush(stdout);
        fgets(buffer2,120,stdin);
        data.dptr=buffer2;data.dsize=strlen(data.dptr)+1;

// store it!
        gdbm_store(db,key,data,GDBM_REPLACE);
        break; // data is stored

      case 'r': // retrieve data

// read the key
        printf("Enter key: ");fflush(stdout);
        fgets(buffer,120,stdin);
        key.dptr=buffer;key.dsize=strlen(key.dptr)+1;

// and fetch it
        data=gdbm_fetch(db,key);
        if (data.dsize > 0){
          printf("%s\n",data.dptr); // found it
        } else {
          printf("Key \"%s\" not found\n",data.dptr); // key not found :(
        }
        break;

      case 'd': // show all keys

// read the first key
        key=gdbm_firstkey(db);
        while (key.dptr != NULL){ // key is valid
          data=gdbm_fetch(db,key);
          printf("%s%s\n",key.dptr,data.dptr); // show the key/data pair
          key=gdbm_nextkey(db,key); // and fetch the next key
        }
        break;
    }
    printf("\nEnter s to store, r to retrieve, d to dump, ^D to quit: ");
    fflush(stdout);
  }

// all done!
  printf("\n");
  gdbm_close(db);
}

