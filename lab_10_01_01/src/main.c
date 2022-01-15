#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "films.h"
#include "list.h"

#define MIN_ARGS 3
#define MAX_ARGS 3

typedef enum
{
    wrong_action,
    reverse_action,
    sort_action
} action_t;

action_t define_action(const char *str)
{
    if (!strcmp(str, "s"))
        return sort_action;
    if (!strcmp(str, "r"))
        return reverse_action;
    return wrong_action;
}

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);  
    films_t films;
    size_t count_films;
    action_t action;
    
    if (argc > MAX_ARGS || argc < MIN_ARGS)
        return EXIT_FAILURE;
    
    if ((action = define_action(argv[2])) == wrong_action)
        return EXIT_FAILURE;
    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
        return EXIT_FAILURE;
    
    count_films = cnt_films(f);
    if (!count_films)
    {
        fclose(f);
        return EXIT_FAILURE;
    }

    if (films_malloc(&films, count_films))
    {
        fclose(f);
        return EXIT_FAILURE;
    }

    if (films_fread(f, &films))
    {
        films_free(&films);
        fclose(f);
        return EXIT_FAILURE;
    }
    fclose(f);

    node_t *head = list_create_node(films.data);
    if (!head)
    {
        films_free(&films);
        return EXIT_FAILURE;
    }
    for (size_t i = 1; i < count_films; i++)
    {
        node_t *node = list_create_node(films.data + i);
        if (!node)
        {
            list_free_all(&head);
            films_free(&films);
            return EXIT_FAILURE;
        }
        list_push(&head, node);
    }

    switch (action)
    {
        case reverse_action:
            list_fprint(stdout, head, film_fwrite);
            break;
        case sort_action:
            {
                node_t *new_head = sort(head, film_cmp_years);
                if (!new_head)
                {
                    list_free_all(&head);
                    films_free(&films);
                    return EXIT_FAILURE;
                }
                list_fprint(stdout, new_head, film_fwrite);
                list_free_all(&new_head);
                break;
            }               
        default:
            break;
    }

    list_free_all(&head);
    films_free(&films);
                  
    return EXIT_SUCCESS;
}

