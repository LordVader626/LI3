#ifndef interativo_h
#define interativo_h

typedef struct pages PAGES;

void interativo();
void load(WINDOW *menuWin, char *full_query, char *queryType, char *dataset, char *second_word);

#endif