#include "header.h"


int main(){
    trie *tr = trie_create();

    char key[100];
    int value;

    FILE *file = fopen("data.txt", "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    while (fscanf(file, "%s %d", key, &value) != EOF)
    {
        trie_insert(tr, key, value);
    }

    fclose(file);

    printf("Hello. Let's test this ordered map.\n");

    int point;

    while (true)
    {
        printf("[1] Show tries.\n");
        printf("[2] Delete a key.\n");
        printf("[3] Exit.\n\n");

        printf("[Input this number]:  ");
        scanf("%d", &point);
        printf("\n");

        if (point == 1)
        {
            printf("[Ordered map after parsing data.txt]:\n\n");
            int count;
            keyValueNode *ordered_map = trie_get_ordered_map(tr, &count);

            for (int i = 0; i < count; i++)
            {
                printf("%s ---> %d\n", ordered_map[i].key, ordered_map[i].value);
            }

            printf("\n");
            free(ordered_map);
        }
        else if (point == 2)
        {
            printf("\n");
            printf("\n[Enter the element to delete the key]: ");
            scanf("%99s", key);

            tr = trie_delete(tr, key);
        }
        else if (point == 3)
        {
            break;
        }
    }
    return 0;
}