#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define HEAP_SIZE 1024  // Taille totale  de la memoire allouable a un bloc simulé en octets

// Structure représentant un bloc mémoire dans notre heap
typedef struct Block {
    size_t size;       // Taille du bloc
    int free;          // 1 si libre, 0 si utilisé
    struct Block *next;
} Block;


// tableau de bloc alloue simulé
// uint8_t est un type des entiers non signes de 8 bits
static uint8_t heap[HEAP_SIZE];

// Pointeur vers le début de la liste des blocs
static Block *heap_start = NULL;

// Fonction d'initialisation du heap a 1024 octets
void init_heap() {

    heap_start = (Block*)heap; //le pointeur vers le premier heap
    heap_start->size = HEAP_SIZE - sizeof(Block); // j'enleve la taille occupee par la structure qui represente l'etat du heap
    heap_start->free = 1; // elle est initialement libre
    heap_start->next = NULL; // elle n'a pas de suivant
}

// Fonction pour allouer de la mémoire
void* my_malloc(size_t size) {
    Block *current = heap_start; // pointeur pour parcourir les differents block et verifier celle utilisable.

    while (current != NULL) {
        // on verifie d'abord si l'espace est libre te a plus de la memoire demande
        if (current->free && current->size >= size) {
            // Si on peut découper le bloc
            if (current->size > size + sizeof(Block)) {
                /*
                (uint8_t*)current : on convertit le pointeur current vers le type uint8_t*, c'est-à-dire un pointeur vers un octet (byte).

                Cette conversion permet d'effectuer une arithmétique sur le pointeur en bytes et non en éléments de type Block, garantissant un déplacement précis en mémoire.
                */

                Block *new_block = (Block*)((uint8_t*)current + sizeof(Block) + size); // on se place a la fin du bloc alloue
                new_block->size = current->size - size - sizeof(Block); // la taille de ce nouveau bloc
                new_block->free = 1; // on marque ce nouveau bloc comme libre
                new_block->next = current->next; // il pointe automatiquemet vers le bloc que celui qu'il a divise pointait
                current->next = new_block; // le pointeur courant pointe desormais vers le nouveau block
                current->size = size; // sa taille est celle alouee
            }
            current->free = 0; // on marque le block comme occupe
            return (void*)((uint8_t*)current + sizeof(Block));
        }
        current = current->next;
    }
    return NULL; // Pas assez de mémoire
}

// Fonction pour libérer de la mémoire
void my_free(void* ptr) {
    if (!ptr) return;
    Block *current = (Block*)((uint8_t*)ptr - sizeof(Block));
    current->free = 1;
    // Fusionner avec le bloc suivant si libre
    if (current->next && current->next->free) {
        current->size += sizeof(Block) + current->next->size;
        current->next = current->next->next;
    }
}

// Affiche l'état du heap
void print_heap() {
    Block *current = heap_start;
    printf("Heap state:\n");
    while (current != NULL) {
        printf("Block at %p: size=%zu, free=%d, next=%p\n",
               current, current->size, current->free, current->next);
        current = current->next;
    }
    printf("-------------------------\n");
}

// Exemple d'utilisation
int main() {
    init_heap();

    printf("la taille d'un bloc est : %d \n", sizeof(heap));

    printf("Initial heap:\n");
    print_heap();

    void *p1 = my_malloc(100);
    printf("After allocating 100 bytes (p1):\n");
    print_heap();

    void *p2 = my_malloc(200);
    printf("After allocating 200 bytes (p2):\n");
    print_heap();

    my_free(p1);
    printf("After freeing p1:\n");
    print_heap();

    void *p3 = my_malloc(50);
    printf("After allocating 50 bytes (p3):\n");
    print_heap();

    return 0;
}
