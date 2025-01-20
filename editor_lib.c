#include "editor_lib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ll_text *append_text(ll_text *list, char *text) {
  ll_text *head_node = (ll_text *)malloc(sizeof(ll_text));
  if (!head_node){
	  return NULL;
  }
  head_node->text = strdup(text);
  if (!head_node->text){
	  free(head_node);
	  return NULL;
  }
  head_node->next = NULL;
  if (!list) {
	  return head_node;
  }
  ll_text *start = list;
  while (start->next != NULL){
	  start = start->next;
  }
  start->next = head_node;
  return list;
}

void save_to_file(ll_text *list, const char *filename) {
  FILE *outfile = fopen(filename, "w");
  for (ll_text *here = list; here; here = here->next) {
    fprintf(outfile, "%s\n", here->text);
  }
  fclose(outfile);
}

int ll_text_length(ll_text *list) {
  int length = 0;
  while (list != NULL){
	  length++;
	  list = list->next;
  }
  return length;
}

ll_text *insert_text(ll_text *list, char *text, int position) {
  ll_text *head_node = (ll_text *)malloc(sizeof(ll_text));
  if (!head_node){
	  return NULL;
  }
  head_node->text = strdup(text);
  if (!head_node->text){
	  free(head_node);
	  return NULL;
  }
  if (position == 0){
	  head_node->next = list;
	  return head_node;
  }
  ll_text *active = list;
  for (int i = 0; i < position-1; i++){
	  active = active->next;
  }
  head_node->next = active->next;
  active->next = head_node;
  return list;
}

ll_text *delete_text(ll_text *list, int position) {
  if (!list){
	  return NULL;
  }
  if (position == 0){
	  ll_text *head = list->next;
	  free(list->text);
	  free(list);
	  return head;
  }
  ll_text *active = list;
  for (int i = 0; i < position-1; i++){
	  active = active->next;
  }
  ll_text *delete_node = active->next;
  active->next = delete_node->next;
  free(delete_node->text);
  free(delete_node);
  return list;
}

ll_text *replace_text(ll_text *list, char *text, int position) {
  ll_text *active = list;
  for (int i = 0; i < position; i++){
	  active = active->next;
  }
  free(active->text);
  active->text = strdup(text);
  if (!active->text){
	  return NULL;
  }
  return list;
}

ll_text *duplicate_ll_text(ll_text *list) {
  if (!list){
	  return NULL;
  }
  ll_text *nlist = (ll_text *)malloc(sizeof(ll_text));
  if (!nlist){
	  return NULL;
  }
  nlist->text = strdup(list->text);
  if (!nlist->text){
	  free(nlist);
	  return NULL;
  }
  nlist->next = NULL;
  ll_text *new_pointer = nlist;
  ll_text *old_pointer = list->next;
  while (old_pointer){
	  ll_text *node_new = (ll_text *)malloc(sizeof(ll_text));
	  if (!node_new){
		  ll_text *t = nlist;
		  while(t){
			  ll_text *node_next = t->next;
			  free(t->text);
			  free(t);
			  t = node_next;
		  }
		  return NULL;
	  }
	  node_new->text = strdup(old_pointer->text);
	  if (!node_new->text){
		  free(node_new);
		  ll_text *t = nlist;
		  while(t){
			  ll_text *node_next = t->next;
			  free(t->text);
			  free(t);
			  t = node_next;
		  }
		  return NULL;
	  }
	  node_new->next = NULL;
	  new_pointer->next = node_new;
	  new_pointer = node_new;
	  old_pointer = old_pointer->next;
  }
  return nlist;
}

ll_text_stack *load_from_file(const char *filename) {
  ll_text *lines = NULL;
  ll_text_stack *stack = calloc(1, sizeof(ll_text_stack));
  char buf[1024];
  FILE *infile = fopen(filename, "r");
  while (fgets(buf, 1024, infile)) {
    chomp(buf);
    lines = append_text(lines, buf);
  }
  stack->lines = lines;
  return stack;
}

ll_text_stack *new_stack_empty_text(void) {
  ll_text_stack *stack = calloc(1, sizeof(ll_text_stack));
  stack->lines = NULL;
  return stack;
}

ll_text_stack *push_duplicate(ll_text_stack *stack) {
  ll_text_stack *new_stack = malloc(sizeof(ll_text_stack)); 
  if (new_stack == NULL){
	  return NULL;
  }
  new_stack->lines = duplicate_ll_text(stack->lines);
  if (new_stack->lines == NULL){
	  free(new_stack);
	  return stack;
  }
  new_stack->next = stack;
  return new_stack;
}

ll_text_stack *push_empty(ll_text_stack *stack) {
  ll_text_stack *new_stack = malloc(sizeof(ll_text_stack));
  if(new_stack == NULL){
	  return NULL;
  }
  new_stack->lines = NULL;
  new_stack->next = stack;
  return new_stack;
}

ll_text_stack *pop_stack(ll_text_stack *stack) {
  if (stack == NULL){
	  return NULL;
  }
  ll_text_stack *new_head = stack->next;
  ll_text *active = stack->lines;
  while (active != NULL){
	  ll_text *node_next = active->next;
	  free(active->text);
	  free(active);
	  active = node_next;
  }
  free(stack);
  return new_head;
}

void chomp(char *s) {
  for (int i = 0; s[i]; i++) {
    if (s[i] == '\n' || s[i] == '\r') {
      s[i] = '\0';
      break;
    }
  }
}
