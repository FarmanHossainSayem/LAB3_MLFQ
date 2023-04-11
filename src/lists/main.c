/*
  test_list demonstrates how to work with linked lists.  You should
  read the headers in both list.h and list.c to understand how Pintos
  implements doubly-linked lists.  Linked lists are how threads are
  gathered in various lists like the ready_list and threads that wait
  on semaphores.

*/
#include <stdio.h>
#include <stdlib.h>
#include "list.c"

// Simlple example of struct that will be
// linked via the elem member
struct mystruct {
  char *word;
  struct list_elem elem;  // forms the links (prev,next) in the list
};

void check_list(struct list *lst) {
  if (list_empty(lst)) printf("list is empty\n");
  else printf("list has %d elements\n",list_size(lst));
}  

int test_list() {
  struct list wordlist;
  char *stuff[] = {
    "The","rain","in","Spain","falls",
    "mainly","in","the","plain.",NULL
  };
  int i;
  struct list_elem *e;
  
  list_init(&wordlist);

  check_list(&wordlist);   // should be empty
  // Append strings to the list.
  for (i = 0; stuff[i] != NULL; i++) {
    struct mystruct *s =
      (struct mystruct *) malloc(sizeof(struct mystruct));
    s->word = stuff[i];
    list_push_back (&wordlist, &s->elem); // onto end of list
  }
  check_list(&wordlist);  // should have 9 items

  // iterate over the list
  struct mystruct *entry;
  for (e = list_begin(&wordlist);
       e != list_end(&wordlist);
       e = list_next(e) ) {
    // how does list_entry work?
    entry = list_entry(e,struct mystruct,elem);
    /*
      printf("(e) %p\n",(e));
      printf("&(e)->next %p\n",&(e)->next);
      printf("offset %p\n", offsetof(struct mystruct,elem.next));
      printf("entry %p\n",entry);
      printf("sub %p\n", \
         (struct mystruct *) \
         ( (uint8_t *) &(e)->next - offsetof(struct mystruct,elem.next)));
    */
    printf("|%s|",entry->word);
  }
  printf("\n\n");

  // Now free allocated structs.
  for (e = list_begin(&wordlist);
       e != list_end(&wordlist);
       e = list_next(e) ) {
    struct list_elem * toremove = list_remove(e);
    entry = list_entry(e,struct mystruct,elem);
    free(entry);
  }  
  printf("List should be empty! ");
  check_list(&wordlist); 

  return (0);
}

int main() {

  test_list();
  
}

