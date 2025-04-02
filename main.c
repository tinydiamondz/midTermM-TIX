#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char nameFilm[50], genre[50], age[5], duration[15];
    float rate;
}film;

typedef struct ticket{ // linkedlist for queue
    char fullname[50], id[5], movieTitle[50], cinema[50], time[5], day[10], seat[3];
    int paymentStatus, isRefund;
    struct ticket *next;
}ticket;

typedef struct {
    char nameMall[40], nameCinema[20];
}cinema;

void seat(){
    int taken = 0, ij = 0;
    char seat[12][11][5];
    printf("\nSeat status:\n\"X\" = TAKEN\n\"O\" = AVAILABLE\"\n");
    for(int i = 'A'; i <= 'L'; i++){ // ---> for(int i = 'A'; i <= 'A'; i++)
                                     // ---> for(int j = 0; j <= 0; j++)
        char iChar[10];              // ---> taken = 1 , if (taken == 1){"booked" || cTaken = 'X'}
        snprintf(iChar, sizeof(iChar), "%c", i);
        for(int k = 0; k <= 10; k++){
            printf("|========");   
        }
        printf("=|\n");
        for(int j = 0; j <= 10; j++){
            char cTaken, jChar[10];
            snprintf(jChar, sizeof(jChar), "%d", j);
            if(taken == 0){
                cTaken = 'O';
                printf("| %c%d \"%c\" ", i, j, cTaken);
            }else if(taken == 1){
                cTaken = 'X';
                printf("| %c%d \"%c\" ", i, j, cTaken);
            }
            strcpy(seat[ij][j], "");
            strcat(seat[ij][j], iChar);
            strcat(seat[ij][j], jChar);
        }
        ij++;
        printf("|\n");
    }
    for(int k = 0; k <= 10; k++){
        printf("|========");   
    }
    printf("=|\n");
    printf("|                                                                                                   |\n");
    printf("|                                                                                                   |\n");
    printf("|                                                                                                   |\n");
    printf("|                                                                                                   |\n");
    printf("|===============================|               SCREEN               |==============================|\n");
    
    // for(int i = 0; i< 11; i++){
    //     for (int j = 0; j <11; j++){
    //         printf("%s ", seat[i][j]);
    //     }
    //     printf("\n");
    // }
    getch();
}

void buyTicket(film *filmData, cinema *cinemaData, int *maxFilm,int *maxCinema, char *userFilm, char *userMall, char *userCinema){
    int flagFilm = 0, flagMall = 0, counterCinema = 0;
    do{
    printf("What do you want to watch?\nFilm name   : ");
    scanf(" ()%[^\n]", userFilm);
        for(int i = 0; i < maxFilm; i++){
            if(strcmp(userFilm, filmData[i].nameFilm) == 0){
                flagFilm = 1;
            }
        }
        if(flagFilm == 0){
            printf("The movie is either unavailable or hasn't been released yet. Please try again later.\nPress any key to continue\n\n");
            getch();
        }
    } while(flagFilm == 0);
    printf("|====|===============================|==================|\n"); //cinema[]
    printf("|    |              MALL             |      CINEMA      |\n");
    printf("|====|===============================|==================|\n");
    for(int i = 0; i < *maxCinema; i++){
        counterCinema++;
        printf("| %-3d| %-30s| %-16s |\n", counterCinema, cinemaData[i].nameMall, cinemaData[i].nameCinema);
    }
    printf("|====|===============================|=================|\n");
    printf("Where do you want to watch?\nMall name  : ");
    scanf(" %[^\n]", userMall);
    for(int i = 0; i < maxCinema; i++){
        if(strcmp(userMall, cinemaData[i].nameMall) == 0){
            flagMall = 1;
        }
    }
    printf("Cinema Name");
    scanf(" %[^\n]", userCinema); // continue tommorow
    // if(userMall == cinemaData[0].nameMall){
        
    // }
    printf("Pick date");
    printf("Pick seat   : ");
     
}
void nowShowing(){
    int i = 0, maxFilm, choose = 0, ticketCount = 0, iCinema = 0, maxCinema;
    char userFilm[50], userMall[50], userCinema[50];
    film filmData[12]; 
    cinema cinemaData[18];   
    while(choose != 3){
        FILE *openFilm = fopen("./nowShowing.txt", "r");
        while(!feof(openFilm)){ //#s#d#s#.1f#%s
            fscanf(openFilm," %[^#]#%[^#]#%[^#]#%f#%[^\n]", &filmData[i].nameFilm, &filmData[i].duration, &filmData[i].genre, &filmData[i].rate, &filmData[i].age);
            i++;
            maxFilm = i;
        }
        fclose(openFilm);
        FILE *openCinema = fopen("./cinema.txt", "r");
        while(!feof(openCinema)){
            fscanf(openCinema, " %[^#]#%[^\n]", &cinemaData[iCinema].nameMall, &cinemaData[iCinema].nameCinema);
            iCinema++;
            maxCinema = iCinema;
        }
        fclose(openCinema);
        // for(int iaja = 0; iaja < maxCinema; iaja++){
        //     printf("| %-30s| %-15s |\n", cinemaData[iaja].nameMall, cinemaData[iaja].nameCinema);
        // }
        int counter = 0;
        printf("|===================================================================================|\n");
        printf("|                                     NOW SHOWING                                   |\n");
        printf("|====|==============================|================|===============|======|=======|\n");
        printf("| NO.|             NAME             |    DURATION    |     GENRE     | RATE |  AGE  |\n");
        printf("|====|==============================|================|===============|======|=======|\n");
        for(i = 0; i < maxFilm; i++){
            counter++;
            printf("| %-3d| %-29s| %-15s| %-14s| %-5.1f| %-6s|\n", counter, filmData[i].nameFilm, filmData[i].duration, filmData[i].genre, filmData[i].rate, filmData[i].age);
        }
        if(counter != 0){
            printf("|====|==============================|================|===============|======|=======|\n\n");
        }
        printf("|==============================|\n");
        printf("|            OPTION            |\n");
        printf("|===|==========================|\n");
        printf("| 1.| BUY TICKET               |\n");
        printf("| 2.| ADD TO WATCH LIST        |\n");
        printf("| 3.| BACK TO MAIN MENU        |\n");
        printf("|===|==========================|\n");
        printf("Choose your option: ");
        // printf("\nmaxFilm %d", maxFilm);
        scanf(" %d", &choose);
        switch(choose){
            case 1: {
                buyTicket(filmData, cinemaData, &maxFilm, &maxCinema, userFilm, userMall, userCinema);
                ticketCount++;
            }
            break;
            case 2: {
                //addWatchlist();
            }
            break;
            case 3: {
                choose = 3;
            }
            break;
        }
    }
}   

void mainMenu(){
    int choose;
    do{
        printf("\nWelcome, \"fullname\"\n");
        printf("Logged in as \"username\"\n");
        printf("\n\"Welcome to M-Tix - Your Ultimate Movie Ticketing Companion!!\"\n\n");
        printf("Say goodbye to long queues and last-minute ticket hassles! \nM-Tix makes it easier than ever to book your favorite movies online, anytime, anywhere. \nBrowse the latest showtimes, pick your preferred seats, and secure your tickets in just a few taps.\n\n");
        printf("|==============================|\n");
        printf("|            OPTION            |\n");
        printf("|===|==========================|\n");
        printf("| 1.| NOW SHOWING              |\n");
        printf("| 2.| COMING SOON              |\n");
        printf("| 3.| WATCH LIST               |\n");
        printf("| 4.| MY TICKETS               |\n");
        printf("| 5.| TICKET HISTORY           |\n");
        printf("| 6.| LOG OUT                  |\n");
        printf("|===|==========================|\n");
        printf("Choose your option: ");
        scanf(" %d", &choose);
        
        switch (choose){
            case 1:{
                nowShowing();
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

void accInfo(char *realName, char *regUser, char *passUser, char *email, char *phone, char *passEncrypt, int *flagReg, int *flagLog){
    strcpy(passEncrypt, "");
    printf("\n|===================================================|\n");
    printf("|                ACCOUNT INFORMATION                |\n");
    printf("|===|===============================================|\n");
    printf("| 1.| Full name    : %-31s|\n", realName);
    printf("| 2.| E-mail       : %-31s|\n", email);
    printf("| 3.| Phone number : %-31s|\n", phone);
    printf("| 4.| Username     : %-31s|\n", regUser);
    if(*flagReg == 0 ||*flagReg == 1  ){
        for(int i = 0; i < strlen(passUser); i++){
            strcat(passEncrypt, "*");
        }
    }
    if(*flagLog == 1){
        for(int i = 0; i < strlen(passUser); i++){
            strcat(passEncrypt, "*");
        }
    }
    printf("| 5.| Password     : %-31s|\n", passEncrypt);
    printf("|===|===============================================|\n");

}
void regAcc(char *realName, char *first,char *last,char *regUser,char *passUser,char *email,char *phone, char *passEncrypt, int *flag, int *flag2){ 
    int length;                                                                                                             //flag1 = flagReg, flag2 = flagLog
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
        printf("Password        : ");
        scanf(" %[^\n]", passUser);
        
        strcpy(realName, first);
        strcat(realName, " ");
        strcat(realName, last);
        
        accInfo(realName, regUser, passUser, email, phone, passEncrypt, flag, flag2); //call function accInfo()
        
        printf("\n");
        printf("\nIs your identity correct? (Y/n): ");
        scanf(" %c", &yn);
        yn = tolower(yn);
        if(yn == 'y'){
            break;
        }else{
            // strcpy(passEncrypt, "");
        }
        
    }
    
    printf("\nREGISTER SUCCESSFULLY\nPress any key to continue\n");
    getch();
    *flag = 1;
}

void logAcc(char *regUser, char *passUser, char *email, char *phone, char *passEncrypt, int *flagReg, int *flagLog){
    int choose;
    do{

        char regUser2[25], passUser2[25], email2[25], phone2[25]; 
        printf("\n|===========================|\n");
        printf("|        LOGIN ACCOUNT      |\n");
        printf("|===|=======================|\n");
        printf("| 1.| LOGIN BY USERNAME     |\n");
        printf("| 2.| LOGIN BY E-MAIL       |\n");
        printf("| 3.| LOGIN BY PHONE NUMBER |\n");
        printf("| 4.| BACK                  |\n");
        printf("|===|=======================|\n");
        printf("Choose your option: ");
        scanf(" %d", &choose);
        
        switch(choose){
            case 1: {
                int flag = 0;
                char yn;
                do{
                    printf("\n\n|==============================|\n");
                    printf("|       LOGIN BY ACCOUNT       |\n");
                    printf("|==============================|\n");
                    printf("\nUsername    : ");
                    scanf(" %[^\n]", regUser2);
                    printf("Password    : ");
                    scanf(" %[^\n]", passUser2);
                    if(strcmp(regUser2, regUser) == 0 && strcmp(passUser2, passUser) == 0){
                        mainMenu();
                        flag = 1;
                    }else{
                        printf("\nUsername or password doesn't matches.\nPlease try again\n");
                        printf("\nForget your password (Y/n): ");
                        scanf(" %c", &yn);
                        yn = tolower(yn);
                        if(yn == 'y'){
                            int flag = 0;
                            do{
                                // strcpy(passEncrypt, "");
                                printf("\nEnter new password      : "); 
                                scanf(" %[^\n]", passUser);
                                printf("Confirm new password    : "); 
                                scanf(" %[^\n]", passUser2);
                                if(strcmp(passUser2, passUser) != 0){
                                    printf("\nPassword doesn't matches, please try again\nPress any key to continue\n");
                                    flag = 0;
                                    getch();
                                }else{
                                    printf("\nPassword has been changed,\nPress any key to continue.");
                                    getch();
                                    flag = 1;
                                }
                            }while(flag == 0);
                            if (flag == 1){
                                break;
                            }
                        }
                    }
                } while(flag == 0);
            }
            break;
            case 2: {
                int flag = 0;
                char yn;
                do{
                    printf("\n\n|==============================|\n");
                    printf("|        LOGIN BY E-MAIL       |\n");
                    printf("|==============================|\n");
                    printf("\nE-Mail      : ");
                    scanf(" %[^\n]", email2);
                    printf("Password    : ");
                    scanf(" %[^\n]", passUser2);
                    if(strcmp(email, email2) == 0 && strcmp(passUser2, passUser) == 0){
                        mainMenu();
                        flag = 1;
                    }else{
                        printf("\nE-mail or password doesn't matches.\nPlease try again\n");
                        printf("\nForget your password (Y/n): ");
                        scanf(" %c", &yn);
                        yn = tolower(yn);
                        if(yn == 'y'){
                            int flag = 0;
                            do{
                                // strcpy(passEncrypt, "");
                                printf("\nEnter new password      : "); 
                                scanf(" %[^\n]", passUser);
                                printf("Confirm new password    : "); 
                                scanf(" %[^\n]", passUser2);
                                if(strcmp(passUser2, passUser) != 0){
                                    printf("\nPassword doesn't matches, please try again\nPress any key to continue\n");
                                    flag = 0;
                                    getch();
                                }else{
                                    printf("\nPassword has been changed,\nPress any key to continue.");
                                    getch();
                                    flag = 1;
                                }
                            }while(flag == 0);
                            if (flag == 1){
                                break;
                            }
                        }
                    }
                } while(flag == 0);
            }
            break;
            case 3:{
                int flag = 0;
                char yn;
                do{
                    printf("\n\n|===================================|\n");
                    printf("|       LOGIN BY PHONE NUMBER       |\n");
                    printf("|===================================|\n");
                    printf("\n\nPhone number    : ");
                    scanf(" %[^\n]", phone2);
                    printf("Password        : ");
                    scanf(" %[^\n]", passUser2);
                    if(strcmp(phone2, phone) == 0 && strcmp(passUser2, passUser) == 0){
                        mainMenu();
                        flag = 1;
                    }else{
                        printf("\nPhone or password doesn't matches.\nPlease try again\n");
                        printf("\nForget your password (Y/n): ");
                        scanf(" %c", &yn);
                        yn = tolower(yn);
                        if(yn == 'y'){
                            int flag = 0;
                            do{
                                // strcpy(passEncrypt, "");
                                printf("\nEnter new password      : "); 
                                scanf(" %[^\n]", passUser);
                                printf("Confirm new password    : "); 
                                scanf(" %[^\n]", passUser2);
                                if(strcmp(passUser2, passUser) != 0){
                                    printf("\nPassword doesn't matches, please try again\nPress any key to continue\n");
                                    flag = 0;
                                    getch();
                                }else{
                                    printf("\nPassword has been changed,\nPress any key to continue.");
                                    getch();
                                    flag = 1;
                                }
                            }while(flag == 0);
                            if (flag == 1){
                                break;
                            }
                        }
                    }
                } while(flag == 0);
            }
            break;
            case 4:{/*freenode*/}
            break;
            default:{
                printf("Option is not available, Please try again\n");
                printf("Press any key to continue");
                getch();
            }
        }
    }while(choose != 4);
}

void acc(){
    int choose, flagReg = 0, flagLog = 0;
    char realName[100], first[50], last[50], regUser[25], passUser[25], email[50], phone[50], passEncrypt[25] = "", yn;
    do{
        printf("\n        Welcome to M-Tix");
        printf("\n|==============================|\n");
        printf("|            OPTION            |\n");
        printf("|===|==========================|\n");
        printf("| 1.| ACCOUNT INFORMATION      |\n");
        printf("| 2.| REGISTER ACCOUNT         |\n");
        printf("| 3.| LOGIN ACCOUNT            |\n");
        printf("| 4.| EXIT                     |\n"); //*free all nodes
        printf("|===|==========================|\n");
        printf("Choose your option: ");
        scanf(" %d", &choose);
    
        switch(choose){
            case 1: {
                if(flagReg == 1){
                    accInfo(realName, regUser, passUser, email, phone, passEncrypt, &flagReg, &flagLog);
                    printf("Do you want to modify your account data? (Y/n): ");
                    scanf(" %c", &yn);
                    yn = tolower(yn);
                    if(yn == 'y'){
                        // strcpy(passEncrypt, "");
                        flagReg = 0;
                        regAcc(realName, first, last, regUser, passUser, email, phone, passEncrypt, &flagReg, &flagLog);
                    }
                }else{
                    printf("\nYou don't have an account.\nYou have to register account first!\n\nPress any key to continue\n");
                    getch();
                }
            }
            break;
            case 2:{
                if(flagReg == 1){
                    printf("\nYou already have an account.\nYou can login into your account or see you account information.\n\nPress any key to continue");
                    getch();
                }else{
                    regAcc(realName, first, last, regUser, passUser, email, phone, passEncrypt, &flagReg, &flagLog);
                }
            }
            break;
            case 3: {
                if(flagReg == 1){
                    logAcc(regUser, passUser, email, phone, passEncrypt, &flagReg, &flagLog);
                }else{
                    printf("\nYou haven't registered an account yet.\nPlease register an account first.\nPress any key to continue\n\n");
                    getch();
                }
                //freeNode();
            }
            break;
            case 4: {}
            break;
            default: {
                printf("Option is not available, Please try again\n\n");
                printf("Press any key to continue");
                getch();
            }
        }
    }while(choose != 4);
}

int main(){
    // acc();
    mainMenu();
    // seat();
}

