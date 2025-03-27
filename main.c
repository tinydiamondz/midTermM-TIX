#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nameFilm[50], genre[50], duration[15], age[5], location[50];
    int year;
}film;


void insertFilm(){
    int i = 0, maxFilm;
    film filmData[8];    
    FILE *openFilm = fopen("./filmList.txt", "r");
    while(!feof(openFilm)){
        fscanf(openFilm," %[^#]#%d#%[^#]#%[^#]#%[^#]#%[^\n]", &filmData[i].nameFilm, &filmData[i].year, &filmData[i].genre, &filmData[i].duration, &filmData[i].age, &filmData[i].location);
        i++;
        maxFilm = i;
    }
    fclose(openFilm);
    int counter = 0;
    printf("|=======================================================================================================================================|\n");
    printf("|                                                             NOW SHOWING                                                               |\n");
    printf("|====|==============================|===============|=============================|==================|=========|========================|\n");
    printf("| NO.|             NAME             | RELEASED YEAR |            GENRE            |     DURATION     |   AGE   |    CINEMA LOCATION     |\n");
    printf("|====|==============================|===============|=============================|==================|=========|========================|\n");
    for(i = 0; i < maxFilm; i++){
        counter++;
        printf("| %-3d| %-29s| %-14d| %-28s| %-17s| %-8s| %-23s|\n", counter, filmData[i].nameFilm, filmData[i].year, filmData[i].genre, filmData[i].duration, filmData[i].duration, filmData[i].location);
    }
    if(counter != 0){
        printf("|====|==============================|===============|=============================|==================|=========|========================|\n");
    }
}   

void pilihKursi(){
    //
}
void pembayaran(){
    // QUE FILM
};

int main(){
    int i;
    int day = 0;
    do{
        printf("Hey, movie lovers! M-Tix is here to make your movie night easier. Book your tickets in a snap and enjoy the magic of cinema!");
        
        
        // while(day != 3){
        //     printf("3.next day");
        //     day++;
        // }
        // if(day == 3){
        //     printf("3.Exit");
        // }
    
    
        switch (i){
            case 1:{
                insertFilm();
            }
                break;
            case 2:{
                // pembayaran();
            }
                break;      
            case 3:{
                if(day == 3){
                    exit(0);
                }
            }
                break;  
        }    
    }while(day!= 4);
}

