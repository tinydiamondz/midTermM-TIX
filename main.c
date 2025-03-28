#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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

void mainMenu(){
    int choose;
    do{
        printf("|==============================|\n");
        printf("|            OPTION            |\n");
        printf("|===|==========================|\n");
        printf("| 1.| NOW SHOWING              |\n");
        printf("| 2.| COMING SOON              |\n");
        printf("| 3.| WATCH LIST               |\n");
        printf("| 4.| MY TICKETS               |\n");
        printf("| 5.| TICKET PURCHASED HISTORY |\n");
        printf("| 6.| LOG OUT                  |\n");
        printf("|===|==========================|\n");
        printf("Choose your option: ");
        scanf(" %d", &choose);
        
        switch (choose){
            case 1:{
                insertFilm();
            }
                break;
            case 2:{
                // pembayaran();
            }
                break;      
            case 3:{
                // >.<
            }
                break;  
        }    
    }while(choose != 4);
}

void regAcc(char *realName, char *first,char *last,char *regUser,char *passUser,char *email,char *phone, int *flag){
    int length;
    char yn;
    while(true){
        
        printf("\n|========================|\n");
        printf("|    REGISTER ACCOUNT    |\n");
        printf("|========================|\n\n");
        printf("Your first name : ");
        scanf(" %[^\n]", first);
        printf("Your last name  : ");
        scanf(" %[^\n]", last);
        while(true){
            printf("Your e-mail     : ");
            scanf(" %[^\n]", email);
            length = strlen(email);
            if((strncmp(&email[length - 4], ".com", 4) == 0) || (strncmp(&email[length - 6], ".co.id", 6) == 0) || (strncmp(&email[length - 6], ".ac.id", 6) == 0)){
                break;
            }else{
                printf("\nInvalid e-mail\n");
                printf("Example : email@gmail.com\n");
                printf("          email@student.umn.ac.id\n");
                printf("          email@yahoo.co.id\n");
                printf("Please try again\nPress any key to continue");
                getch();
                printf("\n\n");
            }
        }
        while(true){
            int j = 0; // flag aja sih
            printf("Phone number    : ");
            scanf(" %[^\n]", phone);
            for(int i = 0; i < strlen(phone); i++){
                if(!isdigit(phone[i]) == 1){
                    printf("\nPhone number must be an integer. Please try again.\nPress any key to continue");
                    j = 0;
                    getch();
                    printf("\n\n");
                    break;
                }else{
                    j = 1;
                }
            }
            if(j == 1){
                break;
            }
        }
        printf("Username        : ");
        scanf(" %[^\n]", regUser);
        printf("Password:       : ");
        scanf(" %[^\n]", passUser);
        
        printf("\n|==============|\n");
        printf("| CONFIRMATION |\n");
        printf("|==============|\n\n");
        strcpy(realName, first);
        strcat(realName, " ");
        strcat(realName, last);
        printf("1. Full name    : %s\n", realName);
        printf("2. E-mail       : %s\n", email);
        printf("3. Phone number : %s\n", phone);
        printf("4. Username     : %s\n", regUser);
        printf("5. Password     : ");
        for(int i = 0; i < strlen(passUser); i++){
            printf("*");
        }
        printf("\n");
        printf("\nis your identity correct? (Y/n)");
        scanf(" %c", &yn);
        yn = tolower(yn);
        if(yn == 'y'){
            break;
        }
    }
    
    printf("\n\nREGISTER SUCCESSFULLY\nPress any key to continue");
    getch();
    *flag = 1;
}

void logAcc(char *regUser, char *passUser, char *email, char *phone){
    int choose;
    char regUser2[25], passUser2[25]; 
    printf("\n|===========================|\n");
    printf("|        LOGIN ACCOUNT      |\n");
    printf("|===|=======================|\n");
    printf("| 1.| LOGIN BY USERNAME     |\n");
    printf("| 2.| LOGIN BY E-MAIL       |\n");
    printf("| 3.| LOGIN BY PHONE NUMBER |\n");
    printf("|===|=======================|\n");
    printf("Choose your option: ");
    scanf(" %d", &choose);
    
    switch(choose){
        case 1: {
            int flag = 0;
            do{
                printf("\nUsername  : ");
                scanf(" %[^\n]", regUser2);
                printf("Password    : ");
                scanf(" %[^\n]", passUser2);
                if(strcmp(regUser2, regUser) == 0 && strcmp(passUser2, passUser) == 0){
                    printf("login success\n"); // tar disini function
                    flag = 1;
                }else{
                    printf("\nUsername or password doesn't matches.\nPlease try again\n\nPress any key to continue\n");
                    getch();
                    flag = 0;
                }
            } while(flag == 0);
        }
        break;
    }
}

void acc(){
    int choose, flagReg = 0;
    char realName[100], first[50], last[50], regUser[25], passUser[25], email[50], phone[50];
    do{
        
        printf("\"Welcome to M-Tix - Your Ultimate Movie Ticketing Companion!!\"\n\n");
        printf("Say goodbye to long queues and last-minute ticket hassles! \nM-Tix makes it easier than ever to book your favorite movies online, anytime, anywhere. \nBrowse the latest showtimes, pick your preferred seats, and secure your tickets in just a few taps.\n\n");
    
        printf("|==============================|\n");
        printf("|            OPTION            |\n");
        printf("|===|==========================|\n");
        printf("| 1.| REGISTER ACCOUNT         |\n");
        printf("| 2.| LOGIN ACCOUNT            |\n");
        printf("| 3.| EXIT                     |\n"); //*free all nodes
        printf("|===|==========================|\n");
        printf("Choose your option: ");
        scanf(" %d", &choose);
    
        switch(choose){
            case 1: {
                if(flagReg == 1){
                    printf("\nYou have registered an account.\nYou have to log in to your account\n\nPress any key to continue");
                    getch();
                }else{
                    regAcc(realName, first, last, regUser, passUser, email, phone, &flagReg);
                }
            }
            break;
            case 2:{
                if(flagReg == 1){
                    logAcc(regUser, passUser, email, phone);
                }else{
                    printf("\nYou haven't registered an account yet.\nPlease register an account first.\n\nPress any key to continue\n");
                    getch();
                }
            }
            break;
            case 3: {
                //freeNode();
            }
            break;
            default: {
                printf("Option is not available, Please try again\n");
                printf("Press any key to continue");
                getch();
            }
        }
    }while(choose != 3);
}

int main(){
    acc();
}

