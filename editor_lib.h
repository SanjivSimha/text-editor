#pragma once

typedef struct ll_text {
  char *text;
  struct ll_text *next;
} ll_text;

typedef struct ll_text_stack {
  ll_text *lines;
  struct ll_text_stack *next;
} ll_text_stack;

ll_text *append_text(ll_text *list, char *text);

ll_text *insert_text(ll_text *list, char *text, int position);

ll_text *delete_text(ll_text *list, int position);

ll_text *replace_text(ll_text *list, char *text, int position);

ll_text *duplicate_ll_text(ll_text *list);

int ll_text_length(ll_text *list);

void save_to_file(ll_text *list, const char *filename);

ll_text_stack *new_stack_empty_text(void);

ll_text_stack *load_from_file(const char *filename);

ll_text_stack *push_duplicate(ll_text_stack *stack);

ll_text_stack *push_empty(ll_text_stack *stack);

ll_text_stack *pop_stack(ll_text_stack *stack);

void chomp(char *s);

#define UNUSED(x) (void)(x)
