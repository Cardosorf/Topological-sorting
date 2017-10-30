#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _list{
    int key;
    struct _list* next;
}list;

typedef struct _degree{
    int id;
    int entry;
}degree;

void init_adjacent_list(list* adjacent_list, int vertices);
void init_list(list* lists);
void init_degree(degree* degrees, int vertices);
void entries_adjacent_list(list* adjacent_list, int vertices);
void creat_adjacent_list(list* adjacent_list, int value, int index);
void topological_sorting(list* adjacent_list, degree* degree_array, int vertices);


int main(int argc, char *argv[])
{

    list* adjacent_list;
    degree* degree_array;
    int vertices, edges;

    puts("Insira o numero de vertices e arestas.");

    scanf("%d %d", &vertices, &edges);
    do{} while (getchar() != '\n');

    adjacent_list = (list*)malloc(sizeof(list)*vertices);
    degree_array = (degree*)malloc(sizeof(degree)*vertices);

    if(!adjacent_list || !degree_array){
        puts("Erro de alocacao");
        exit(0);
    }

    init_adjacent_list(adjacent_list, vertices);
    init_degree(degree_array, vertices);
    entries_adjacent_list(adjacent_list, vertices);
    topological_sorting(adjacent_list, degree_array, vertices);


    printf("Hello World!\n");

    free(adjacent_list);
    free(degree_array);
    return 0;
}


void init_adjacent_list(list* adjacent_list, int vertices){
    int i;
    for(i = 0; i < vertices; i++){
        adjacent_list[i].key= (int)NULL;
        adjacent_list[i].next = NULL;
    }
}


void init_list(list* lists){
    lists->key= (int)NULL;
    lists->next = NULL;
}

void init_degree(degree* degrees, int vertices){
    int i;
    for(i = 0; i < vertices; i++){
        degrees[i].id = 0;
        degrees[i].entry = 0;
    }
}


void entries_adjacent_list(list* adjacent_list, int vertices){
    char temp[100];
    char* ptr;
    int value;
    int contador = 0;


    while(contador < vertices){
        puts("Insira o vertice e suas respectivas arestas, caso o vertice possua (Os dados devem ser digitados com espacos).");
        if(contador == 0){
            puts("Exemplos de como digitar os dados:");
            puts("Exemplo_1 (vertice 5 possui as arestas 4 e 3): 5 4 3");
            puts("Exemplo_2 (vertice 6 nao possui arestas): 6");
        }
        fgets(temp, 100, stdin);
        if(temp[(int)(strlen(temp)-1)] == '\n'){
            temp[(int)(strlen(temp)-1)]= '\0';
        }

        adjacent_list[contador].key = (int)strtol(temp, &ptr, 10);

        while(strlen(ptr) != 0){
            value  = (int)strtol(ptr, &ptr, 0);
            creat_adjacent_list(adjacent_list, value, contador);
        }
        contador++;
    }
}


void creat_adjacent_list(list* adjacent_list, int value, int index){
    list* new_list;
    list* pt_list;

    new_list = (list*)malloc(sizeof(list*));
    pt_list = (list*)malloc(sizeof(list*));

    if(!pt_list || !new_list){
        puts("Erro de alocacao na memoria.");
        exit(0);
    }

    init_list(new_list);
    new_list->key = value;
    pt_list = &adjacent_list[index];

    if(pt_list->next == NULL)
        pt_list->next = new_list;

    else{
        while(pt_list->next != NULL){
            pt_list = pt_list->next;
        }
        pt_list->next = new_list;
    }
}


void topological_sorting(list* adjacent_list, degree* degree_array, int vertices){
    int i, j, k, u;
    int index;
    int ordered[vertices];
    int counter = 0;
    list* pt_list;
    pt_list = (list*)malloc(sizeof(list*));



    for(i = 0; i < vertices; i++){
        degree_array[i].id = adjacent_list[i].key;
    }

    for(i = 0; i < vertices; i++){
        pt_list = &adjacent_list[i];
        pt_list = pt_list->next;

        while(pt_list != NULL){
            index = pt_list->key;
            for(j = 0; j < vertices; j++){
                if(degree_array[j].id == index){
                    degree_array[j].entry = degree_array[j].entry + 1;
                }
            }
            pt_list = pt_list->next;
        }
    }

    puts("entrei");
    for(i = 0; i < vertices; i++){
        printf("%d\n", degree_array[i].entry);
    }
    puts("");
    index = 0;


    for(i = 0; i < vertices; i++){
        ordered[i] = (int)NULL;
    }

    //        for(i = 0; i < vertices; i++){
    //            if(ordered[i] == 0){
    //                ordered[i] = 2;
    //            }
    //            break;
    //        }

    //printf("%d\n", ordered[index]);


    while(1){
        for(i = 0; i < vertices; i++){
            if(degree_array[i].entry == 0){
                degree_array[i].entry = -1;
                counter = counter + 1;
                for(j = 0; j < vertices; j++){
                    if(ordered[j] == 0){
                        ordered[j] = degree_array[i].id;
                        break;
                    }
                }

            }
        }
        printf("%d counter\n", counter);

        for(i = 0; i < counter; i++){
            for(j = 0; j < vertices; j++){
                if(adjacent_list[j].key == ordered[i]){
                    pt_list = &adjacent_list[j];
                    pt_list = pt_list->next;
                    while(pt_list != NULL){
                        for(k = 0; k < vertices; k++){
                             if (degree_array[k].id == pt_list->key){
                                 degree_array[k].entry = degree_array[k].entry - 1;
                             }
                        }
                        pt_list = pt_list->next;
                    }
                }
            }

        }

        if(counter >= 4 ){
            break;
        }
    }
    /*
    while(1){
        counter = 0;

        for(i = 0; i < vertices; i++){
            if(degree_array[i].entry == -1){
                counter++;
            }
        }

        if(counter == vertices)
            break;








        //        for(i = 0; i < vertices; i++){
        //            if(degree_array[i].entry == 0){
        //                for(j = 0; j < vertices; j++){
        //                    if(ordered[j] == 0){
        //                        ordered[j] = degree_array[i].id;
        //                        //degree_array[i].entry = -1;

        //                        for(u = 0; u < vertices; u++){
        //                            if(adjacent_list[u].key == degree_array[i].id){
        //                                pt_list = &adjacent_list[u];
        //                                pt_list = pt_list->next;
        //                                while(pt_list != NULL){
        //                                    for(k = 0; k < vertices; k++){
        //                                        if (degree_array[k].id == pt_list->key){
        //                                            degree_array[k].entry = degree_array[k].entry - 1;
        //                                        }
        //                                    }
        //                                    pt_list = pt_list->next;
        //                                }
        //                            }
        //                        }

        //                        degree_array[i].entry = -1;
        // //                        printf("%d ordered\n", ordered[j]);
        //                        break;
        //                    }
        //                }
        //                //colocar para achar nos adjacentes as arestas dos q deram zero

        //            }
        //            //            if(degree_array[i].entry == -1)
        //            //                counter++;
        //        }

        //        for(j = 0; j < vertices; j++){
        //            if(adjacent_list[j].key == degree_array[i].id){
        //                pt_list = &adjacent_list[j];
        //                pt_list = pt_list->next;
        //                while(pt_list != NULL){
        //                    for(k = 0; k < vertices; k++){
        //                        if (degree_array[k].id == pt_list->key){
        //                            degree_array[k].entry = degree_array[k].entry - 1;
        //                        }
        //                    }

        //                    pt_list = pt_list->next;
        //                }
        //            }
        //        }





        //        for(j = 0; j < vertices; j++){
        //            if(degree_array[j].entry == -1)
        //                counter++;
        //        }
        printf("%d counter\n", counter );
        puts("oiiiii");


    }

    /* for(i = 0; i < vertices; i++){
            if(degree_array[i].entry == 0){
                for(j = 0; j < vertices; j++){
                    if(ordered[j] == 0){
                        ordered[j] = degree_array[i].id;
                        degree_array[i].entry = -1;
                        printf("%d ordered\n", ordered[j]);
                        break;
                    }
                }
//                degree_array[i].entry = -1;

              puts("to aki?");

              for(j = 0; j < vertices; j++){
                  if(adjacent_list[j].key == degree_array[i].id){
                      pt_list = &adjacent_list[j];
                      pt_list = pt_list->next;
                      while(pt_list != NULL){
                          for(k = 0; k < vertices; k++){
                              if (degree_array[k].id == pt_list->key){
                                  degree_array[k].entry = degree_array[k].entry - 1;
                              }
                          }

                        pt_list = pt_list->next;
                      }
                  }
              }

            }



//            degree_array[i].entry = -1;
        }   */

    for(i = 0; i < vertices; i++){
        printf("%d\n", ordered[i]);
    }


    puts("entrei");
    for(i = 0; i < vertices; i++){
        printf("%d\n", degree_array[i].entry);
    }


}
