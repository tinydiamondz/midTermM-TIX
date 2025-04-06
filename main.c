#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#define ROW 'K'
#define COL 21
#define MAXFILM 7
#define MAXCINEMA 7
#define MAXDATE 4
#define MAXTIME 6
#define MAXSEAT 200
#define MAXFEEDBACK 15
typedef struct {
    char nameFilm[50], genre[50], age[5], duration[15];
    float rate;
}film;

typedef struct ticket{ // linkedlist for queue
    char fullname[50], id[50], movieTitle[100], mall[100], cinema[100], time[100], date[100], seat[50], idCinema[10];
    int paymentStatus, isRefund, price;
    struct ticket *next;
}ticket;

typedef struct {
    char nameMall[40], nameCinema[20], id[10];
    int price;
}cinema;

typedef struct {
    char date[30], id[30];
}date;

typedef struct {
    char time[20], id[20];
}times;

typedef struct {
    char nameFilm[50], genre[50], age[5], duration[15];
    float rate;
}soon;

typedef struct {
    char nameFilm[50], genre[50], age[5], duration[15];
    float rate;
}watchLists;

typedef struct history{
    char film[50], cinema[50], mall[50], id[50], date[40], time[40], fullname[100], seat[50];
    int price;
    struct history *next; 
}history;

typedef struct {
    char fullname[100], comment[55];
    float rate;
}feedback;

char *onlyStr(char *temp){
    int flag = 0;
    do{
        for(int i = 0; i < strlen(temp); i++){
            if(isdigit(temp[i]) == 0){
                flag = 1;
            }else{
                flag = 0;
                break;
            }
        }
        if(flag == 0){
            printf("Input must string! Please try again!!\nChoose your option: ");
            scanf(" %[^\n]", temp);
        }else{
            break;
        }
    } while(flag == 0);
    return temp;
}

int strtoint(char *temp){ //purpose function ini, untuk ngubah string to int, biar gaada sensitive case;
    while(true){
        int flag = 0;
        
        for(int i = 0; i < strlen(temp); i++){
            if(isdigit(temp[i]) == 0){
                printf("\nInput must integers! Please try again.\n\n");
                
                flag = 0;
                printf("Choose your option: ");
                scanf(" %[^\n]", temp);
                break;
            }else{
                flag = 1;
            }
        }
        if(flag == 1){
            break;
        }
    }
    return atoi(temp);
}

void availableSeat(ticket **node, ticket **head, ticket **tail, int *rowArr, int *colArr, char seat[MAXFILM][MAXCINEMA][MAXDATE][MAXTIME][ROW][COL], int *filmArr, int *cinemaArr, int *dateArr, int *timeArr){
    int tempFilmArr = *filmArr, tempCinemaArr = *cinemaArr, tempDateArr = *dateArr, tempTimeArr = *timeArr, tempRowArr = *rowArr, tempColArr = *colArr;
    // printf("%d %d %d %d %d %d", tempFilmArr, tempCinemaArr, tempDateArr, tempTimeArr, *rowArr, *colArr);
    int capacity = 0;
    for (int i = 'A'; i < ROW; i++){
        for (int j = 1; j < COL; j++){
            if(seat[tempFilmArr][tempCinemaArr][tempDateArr][tempTimeArr][i][j] == ' '){
                capacity++;
            }
        }
    }
    
    printf("|===================================================================================|\n");
    printf("| FILM           : %-65s|\n", (*node)->movieTitle);
    printf("| CINEMA         : %-65s|\n", (*node)->cinema);
    printf("| MALL           : %-65s|\n", (*node)->mall);
    printf("| DATE           : %-65s|\n", (*node)->date);
    printf("| TIME           : %-65s|\n|%84c\n", (*node)->time, '|');
    printf("| BOOKED         : \"X\"%63c\n", '|');
    printf("| AVAILABLE SEAT : %d / %-59d|\n", capacity, MAXSEAT);
    for(int j = 1; j < COL+1; j++){
        printf("|===");
    }
    printf("|\n");
    printf("|   ");
    for(int j = 1; j < COL+1; j++){
        if(j > 1){
            printf("| %-2d", j-1);
        }
    }
    printf("|\n");
    for(int j = 1; j < COL+1; j++){
        printf("|===");
    }
    printf("|\n");
    for(int i = 'A'; i < ROW; i++){
        printf("| %c ", i);
        for(int j = 1; j < COL; j++){
          
            printf("| %c ", seat[tempFilmArr][tempCinemaArr][tempDateArr][tempTimeArr][i][j]);
        }
        printf("|\n");
        for(int i = 1; i < COL+1; i++){
            printf("|===");
        }
        printf("|\n");
    }                                                                                           
    printf("|                                                                                   |\n");
    printf("|                                                                                   |\n");
    printf("|                                                                                   |\n");
    printf("|=========================|             SCREEN             |========================|\n");
    printf("\nPress any key to continue.\n");
    getch();
}

void bookSeat(int *rowArr, int *colArr, char seat[MAXCINEMA][MAXFILM][MAXDATE][MAXTIME][ROW][COL], int *filmArr, int *cinemaArr, int *dateArr, int *timeArr, char *temp, int *bookFlag, int *seatCount, char *seatCountString){
    int tempFilmArr = *filmArr, tempCinemaArr = *cinemaArr, tempDateArr = *dateArr, tempTimeArr = *timeArr, tempRowArr, tempColArr;
    while (true){
        while(true){
            printf("Which row would you like to book to enjoy the movie? (A - %c)\nChoose your option: ", ROW - 1);
            scanf(" %[^\n]", temp);
            onlyStr(temp);
            if(strlen(onlyStr(temp)) == 1){
                if(onlyStr(temp)[0] >= 'A' && onlyStr(temp)[0] < ROW){
                    break;
                }else{
                    printf("\nPlease input between (A - %c)\nPress any key to continue\n\n", ROW - 1);
                    getch();
                }
            }else{
                printf("\nPlease input between (A - %c)\nPress any key to continue\n\n", ROW - 1);
                getch();
            }
        }
        // printf("ROW user: %c",onlyStr(temp)[0]); getch();
        *rowArr = onlyStr(temp)[0];
        do{
            printf("\nWhich col would you like to book to enjoy the movie? (1 - %d)\nChoose your option: ", COL - 1);
            scanf(" %[^\n]", temp);
            strtoint(temp);
            if(strtoint(temp) < 1 || strtoint(temp) >= COL){
                printf("\nPlease input between (1 - %d)\nPress any key to continue\n", COL - 1);
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) >= COL);
        // printf("COL USER : %d", strtoint(temp));
        *colArr = strtoint(temp);
        tempRowArr = *rowArr; 
        tempColArr = *colArr;
        if(seat[tempFilmArr][tempCinemaArr][tempDateArr][tempTimeArr][tempRowArr][tempColArr] == 'X'){
            printf("\nOops! This seat's taken. Pick a different one.\nPress any key to continue\n");
            getch();
        }else{
            seat[tempFilmArr][tempCinemaArr][tempDateArr][tempTimeArr][tempRowArr][tempColArr] = 'X';
            // printf(" seat count = %d", *seatCount); getch();
            if(*seatCount == 0){
                snprintf(seatCountString, sizeof(seatCountString), "%c%d", tempRowArr, tempColArr);
            }else{
                char str[10];
                snprintf(str, sizeof(str), "%c%d", tempRowArr, tempColArr);
                strcat(seatCountString, ", ");
                strcat(seatCountString, str);
            }
            break;
        }
    }
    (*seatCount)++;
    printf("\nBooking complete.\nPress any key to continue\n");
    getch();
    *bookFlag = 1;
}

void buyTicket(char *realName, ticket **node, ticket **head, ticket **tail, film *filmData, cinema *cinemaData, date *dateData, times *timeData, int *maxFilm,int *maxCinema, int *maxDate, int *maxTime, char *userFilm, char *userMall, char *userCinema, char *userDate, char *userTime, char *temp, int *filmArr, int *cinemaArr, int *dateArr, int *timeArr, int *rowArr, int *colArr, int *seatFlag, char seat[MAXFILM][MAXCINEMA][MAXDATE][MAXTIME][ROW][COL]){
    char yn, seatCountString[50];
    int filmID, cinemaID, dateID, timeID;
    do{
        int tempPrice = 0;
        int seatCount = 0;
        *node = (ticket *) malloc (sizeof(ticket));
        
        int flagFilm = 0, flagMall = 0, flagCinema = 0;
        int counter = 0;
        do{
            printf("|===================================================================================|\n");
            printf("|                                    NOW SHOWING                                    |\n");
            printf("|====|==============================|================|===============|======|=======|\n");
            printf("| NO.|             NAME             |    DURATION    |     GENRE     | RATE |  AGE  |\n");
            printf("|====|==============================|================|===============|======|=======|\n");
            for(int i = 0; i < *maxFilm; i++){
                counter++;
                printf("| %-3d| %-29s| %-15s| %-14s| %-5.1f| %-6s|\n", counter, filmData[i].nameFilm, filmData[i].duration, filmData[i].genre, filmData[i].rate, filmData[i].age);
            }
            if(counter != 0){
                printf("|====|==============================|================|===============|======|=======|\n");
            }
            printf("|                                   BUYING TICKET                                   |\n");
            printf("|===================================================================================|\n\n");
            printf("What do you want to watch? Pick your film by selecting those numbers!");
            printf("\nChoose your option: ");
            scanf(" %[^\n]", temp);
            strtoint(temp); //kita jadiin function ini jadi array ye kan?
            if (strtoint(temp) < 1 || strtoint(temp) > 12 ){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) > 12 );
        filmID = (strtoint(temp)-1);
        strcpy(userFilm, filmData[strtoint(temp)-1].nameFilm);
        strcpy((*node)->movieTitle, userFilm);
        *filmArr = strtoint(temp)-1;
        do{
            int counter = 0;
            printf("|====|===============================|==================|=============|\n"); //cinema[]
            printf("| NO |              MALL             |      CINEMA      |    PRICE    |\n");
            printf("|====|===============================|==================|=============|\n");
            for(int i = 0; i < *maxCinema; i++){
                counter++;
                printf("| %-3d| %-30s| %-16s | Rp %-9d|\n", counter, cinemaData[i].nameMall, cinemaData[i].nameCinema, cinemaData[i].price);
            }
            printf("|====|===============================|==================|=============|\n");
            printf("Pick your favorite place to watch the movie!\n");
            printf("Choose your option: ");
            scanf(" %[^\n]", temp);
            strtoint(temp);
            if(strtoint(temp) < 1 || strtoint(temp) > 18){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) > 18);
        strcpy(userMall, cinemaData[strtoint(temp)-1].nameMall);    
        strcpy(userCinema, cinemaData[strtoint(temp)-1].nameCinema);    
        strcpy((*node)->mall, userMall);
        strcpy((*node)->cinema, userCinema);
        (*node)->price = cinemaData[strtoint(temp)-1].price;
        tempPrice = cinemaData[strtoint(temp)-1].price;
        cinemaID = (strtoint(temp)-1);
        *cinemaArr = strtoint(temp)-1;
        strcpy((*node)->id, cinemaData[strtoint(temp)-1].id);
        do{
            printf("|====|==========================|\n");
            printf("| NO |      AVAILABLE DATE      |\n");
            printf("|====|==========================|\n");
            counter = 1;
            for(int i = 0; i < *maxDate; i++){
                printf("| %-3d| %-25s|\n", counter, dateData[i].date);
                counter++;
            }    
            printf("|====|==========================|\n\n");
            printf("Choose the best date to enjoy your movie!\n");
            printf("Choose your option: ");
            scanf(" %[^\n]", temp);
            strtoint(temp);
            if(strtoint(temp) < 1 || strtoint(temp) > 4){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) > 4);
        strcpy(userDate, dateData[strtoint(temp)-1].date);
        strcpy((*node)->date, userDate);
        dateID = (strtoint(temp)-1);
        *dateArr = strtoint(temp)-1;
        do{
            printf("|======================|\n");
            printf("|         TIME         |\n");
            printf("|===|==================|\n");
            counter = 1;
            for(int i = 0; i < *maxTime; i++){
                printf("| %-2d| %-17s|\n", counter, timeData[i].time);
                counter++;
            }
            printf("|===|==================|\n\n");
            printf("Choose the best time to enjoy your movie\nChoose your option: ");
            scanf(" %[^\n]", temp);
            strtoint(temp);
            if(strtoint(temp) < 1 || strtoint(temp) > 6){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) > 6);
        strcpy(userTime, timeData[strtoint(temp)-1].time);
        strcpy((*node)->time, userTime);
        timeID = (strtoint(temp)-1);
        // printf("UserTime: %s", userTime);
        
        *timeArr = strtoint(temp)-1;    
        // seat(filmArr, cinemaArr, dateArr, timeArr);
        int bookFlag = 0;
        do{
            printf("|==================================|\n");
            printf("|               SEAT               |\n");
            printf("|===|==============================|\n");
            printf("| 1 | VIEW AVAILABLE SEAT          |\n");
            printf("| 2 | BOOK SEAT                    |\n");
            printf("| 3 | SEAT CONFIRMATION            |\n");
            printf("|===|==============================|\n\n");
            printf("Choose your option: ");
            scanf(" %[^\n]", temp);
            strtoint(temp);
            if (strtoint(temp) < 1 || strtoint(temp) > 3){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
            switch(strtoint(temp)){
                case 1: {
                    availableSeat(node, head, tail, rowArr, colArr, seat, filmArr, cinemaArr, dateArr, timeArr);
                }
                break;
                case 2: {
                    bookSeat(rowArr, colArr, seat, filmArr, cinemaArr, dateArr, timeArr, temp, &bookFlag, &seatCount, seatCountString);
                    *seatFlag = 1;
                }
                break;
                case 3: {
                    if(bookFlag == 0){
                        printf("Confirmation is only available after the booking has been made.\nPress any key to continue\n");
                        getch();
                    }else if(bookFlag == 1){
                        char yn;
                        printf("\n|=================================================================|\n");
                        printf("|                        SEAT CONFIRMATION                        |\n");
                        printf("|=================================================================|\n");
                        printf("| YOUR SEAT RESERVATION: %-41s|\n", seatCountString);
                        printf("|=================================================================|\n");
                    
                        
                        printf("\nPlease confirm your seat selection. Is everything correct? (Y/n): ");
                        scanf(" %c", &yn);
                        yn = tolower(yn);
                        if(yn == 'y'){
                            printf("\nYour seat has been successfully reserved. Thank you for your booking!\nPress any key to continue\n");
                            getch();
                            bookFlag = 2;
                            strcpy((*node)->seat, seatCountString);
                        }
                    }
                }
                break;
            }
            
            ((*node)->price) = tempPrice * seatCount;
            strcpy((*node)->id, dateData[dateID].id); 
            strcat((*node)->id, "-");
            strcat((*node)->id, cinemaData[cinemaID].id);
            strcat((*node)->id, "-");
            strcat((*node)->id, timeData[timeID].id);
            strcat((*node)->id, "-");
            strcat((*node)->id, filmData[filmID].age);
            strcpy((*node)->fullname, realName);
        }while(bookFlag == 0 || bookFlag == 1);
        
        if (*head == NULL){
            *head = *node;
            (*node)->next = NULL; 
        }else{
            (*tail)->next = *node;
            (*node)->next = NULL; 
        }   
        *tail = *node;
        
        printf("|====================================================|\n");
        printf("|                       TICKET                       |\n");
        printf("|===|================================================|\n");       
        printf("| 1 | TICKET ID   : %-33s|\n", ((*node)->id));
        printf("| 2 | YOUR NAME   : %-33s|\n", ((*node)->fullname));
        printf("| 3 | FILM        : %-33s|\n", (*node)->movieTitle);
        printf("| 4 | MALL        : %-33s|\n", (*node)->mall);
        printf("| 5 | CINEMA      : %-33s|\n", (*node)->cinema);
        printf("| 6 | DATE        : %-33s|\n", (*node)->date);
        printf("| 7 | TIME        : %-33s|\n", (*node)->time);
        printf("| 8 | SEAT        : %-33s|\n", (*node)->seat);
        printf("| 9 | TOTAL PRICE : Rp %-30d|\n", (*node)->price);
        printf("|===|================================================|\n");       
        printf("\nTicket confirmed! Want to buy another one?(Y/n): ");
        scanf(" %c", &yn);
        yn = tolower(yn);
    }while(yn == 'y');
}

void nowShowing(char *realName, char *temp, film *filmData, ticket **node, ticket **head, ticket **tail, int *seatFlag, int *ticketCount, char seat[MAXFILM][MAXCINEMA][MAXDATE][MAXTIME][ROW][COL]){
    int i = 0, maxFilm, choose = 0, iCinema = 0, maxCinema, maxDate, maxTime, cinemaArr, filmArr, dateArr, timeArr, rowArr, colArr;
    char userFilm[50], userMall[50], userCinema[50], userDate[50], userTime[30]; 
    cinema cinemaData[MAXCINEMA];
    date dateData[MAXDATE];
    times timeData[MAXTIME];   
    while(choose != 2){
        FILE *openFilm = fopen("./nowShowing.txt", "r");
        while(!feof(openFilm)){ //#s#d#s#.1f#%s
            fscanf(openFilm," %[^#]#%[^#]#%[^#]#%f#%[^\n]", filmData[i].nameFilm, filmData[i].duration, filmData[i].genre, &filmData[i].rate, filmData[i].age);
            i++;
            maxFilm = i;
        }
        fclose(openFilm);
        i = 0;
        FILE *openCinema = fopen("./cinema.txt", "r");
        while(!feof(openCinema)){
            fscanf(openCinema, " %[^#]#%[^#]#%d#%[^\n]", cinemaData[i].nameMall, cinemaData[i].nameCinema, &cinemaData[i].price, cinemaData[i].id);
            i++;
            maxCinema = i;
        }
        fclose(openCinema);
        i = 0;
        FILE *openDate = fopen("./date.txt", "r");
        while(!feof(openDate)){
            fscanf(openDate, " %[^#]#%[^\n]", dateData[i].date, dateData[i].id);
            i++;
            maxDate = i;
        }
        fclose(openDate);
        i = 0;
        FILE *openTime = fopen("./time.txt", "r");
        while(!feof(openTime)){
            fscanf(openTime, " %[^#]#%[^\n]", timeData[i].time, timeData[i].id);
            i++;
            maxTime = i;
        }
        i = 0;
        // for(int iaja = 0; iaja < maxDate; iaja++){
        //     printf("%s\n",timeData[iaja].time);
        // }
        int counter = 0;
        printf("|===================================================================================|\n");
        printf("|                                    NOW SHOWING                                    |\n");
        printf("|====|==============================|================|===============|======|=======|\n");
        printf("| NO.|             NAME             |    DURATION    |     GENRE     | RATE |  AGE  |\n");
        printf("|====|==============================|================|===============|======|=======|\n");
        for(int i = 0; i < MAXFILM; i++){
            counter++;
            printf("| %-3d| %-29s| %-15s| %-14s| %-5.1f| %-6s|\n", counter, filmData[i].nameFilm, filmData[i].duration, filmData[i].genre, filmData[i].rate, filmData[i].age);
        }
        if(counter != 0){
            printf("|====|==============================|================|===============|======|=======|\n");
        }
        counter = 0;
        printf("\n|==============================|\n");
        printf("|            OPTION            |\n");
        printf("|===|==========================|\n");
        printf("| 1 | BUY TICKET               |\n");
        printf("| 2 | BACK TO MENU             |\n");
        printf("|===|==========================|\n");
        do{
            printf("Choose your option: ");
            scanf(" %[^\n]", temp);
            strtoint(temp);
            // printf("\nmaxFilm %d", maxFilm);
            
            if(strtoint(temp) < 1 || strtoint(temp) > 3){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) > 3);
        
        choose = strtoint(temp);
        switch(choose){
            case 1: {
                buyTicket(realName, node, head, tail, filmData, cinemaData, dateData, timeData, &maxFilm, &maxCinema, &maxDate, &maxTime, userFilm, userMall, userCinema, userDate, userTime, temp, &filmArr, &cinemaArr, &dateArr, &timeArr, &rowArr, &colArr, seatFlag, seat);
                (*ticketCount)++;
            }
            break;
            case 2: {
                choose = 2;
            }
            break;
        }
    }
}   
    
void comingSoon(){
        soon soonData[MAXFILM];
        FILE *openSoon = fopen("./comingSoon.txt","r");
        int i = 0;
        while(!feof(openSoon)){
            fscanf(openSoon, " %[^#]#%[^#]#%[^#]#%f#%[^\n]", &soonData[i].nameFilm, &soonData[i].duration, &soonData[i].genre, &soonData[i].rate, &soonData[i].age);
            i++;
        }
        fclose(openSoon);
        int counter = 0;
    printf("|===================================================================================|\n");
    printf("|                                    COMING SOON                                    |\n");
    printf("|====|==============================|================|===============|======|=======|\n");
    printf("| NO.|             NAME             |    DURATION    |     GENRE     | RATE |  AGE  |\n");
    printf("|====|==============================|================|===============|======|=======|\n");
    for(int i = 0; i < MAXFILM; i++){
        counter++;
        printf("| %-3d| %-29s| %-15s| %-14s| %-5.1f| %-6s|\n", counter, soonData[i].nameFilm, soonData[i].duration, soonData[i].genre, soonData[i].rate, soonData[i].age);
    }
    if(counter != 0){
        printf("|====|==============================|================|===============|======|=======|\n");
    }
    printf("Press any key to continue\n");
    getch();
}

void deleteTicket(ticket **node, ticket **head, ticket **tail){
    if((*head) == NULL){
        printf("\nUnable to delete ticket. Your ticket queue is currently empty.\nPress any key to contine\n\n");
        getch();
    }else{
        *node = *head;
        (*head) = (*head)->next; 
        free(*node);
        printf("\nThe ticket has been successfully removed from your queue list.\nPress any key to continue\n\n");
        getch();
    }
}

void pay(char *temp, ticket **node, ticket **head, ticket **tail, history **hNode, history **hHead, history **hTail, int *totalHistory){
    char yn;
    *node = *head;
    int paymentSuccess;
    while(true){
        paymentSuccess = 0;
        printf("|====================================================|\n");
        printf("|                 TICKET CONFIRMATION                |\n");
        printf("|===|================================================|\n");       
        printf("| 1 | TICKET ID   : %-33s|\n", (*node)->id);
        printf("| 2 | YOUR NAME   : %-33s|\n", (*node)->fullname);
        printf("| 3 | FILM        : %-33s|\n", (*node)->movieTitle);
        printf("| 4 | MALL        : %-33s|\n", (*node)->mall);
        printf("| 5 | CINEMA      : %-33s|\n", (*node)->cinema);
        printf("| 6 | DATE        : %-33s|\n", (*node)->date);
        printf("| 7 | TIME        : %-33s|\n", (*node)->time);
        printf("| 8 | SEAT        : %-33s|\n", (*node)->seat);
        printf("| 9 | TOTAL PRICE : Rp %-30d|\n", (*node)->price);
        printf("|===|================================================|\n");       
        printf("*Tickets that have already been booked cannot be modified. \nIf you'd like to make any changes, please delete the ticket and book a new one.\n\n");
        printf("Kindly review your ticket information. Is everything correct? (Y/n): ");
        scanf(" %c", &yn);
        yn = toupper(yn);
        if(yn != 'Y'){
            break;
        }
        do{
            printf("\n\n|==============================|\n");
            printf("|        PAYMENT METHOD        |\n");
            printf("|===|==========================|\n");
            printf("| 1 | BANK VIRTUAL ACCOUNT     |\n");
            printf("| 2 | PAY ON SITE              |\n");
            printf("| 3 | BACK TO MYTICKET         |\n");
            printf("|===|==========================|\n");
            printf("Choose your option: ");
            scanf(" %[^\n]", temp);
            strtoint(temp);
            if(strtoint(temp) > 2 || strtoint(temp) < 1){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
        }while(strtoint(temp) > 2 || strtoint(temp) < 1);
        int choose = strtoint(temp);
        if(choose == 3){
            break;
        }
        switch (choose){
            case 1: {
                while(true){
                    srand(time(NULL));
                    char userInput[100];
                    char format[100] = "710000010";
                    unsigned int randNum = ((rand() % 9999 + 1000) % (rand() % 9999 + 1000) % (rand() % 9999 + 1000) % (rand() % 9999 + 1000)) + 1000;
                    char randStr[10];
                    snprintf (randStr, sizeof(randStr), "%u", randNum);
                    strcat(format, randStr);
                    printf("\n\n|==================================================|\n");
                    printf("|            PAYMENT VIA VIRTUAL ACCOUNT           |\n");
                    printf("|===|==============================================|\n");
                    printf("| 1 | TOTAL PRICE     : Rp %-24d|\n", (*node)->price);
                    printf("| 2 | VIRTUAL ACCOUNT : %-27s|\n", format);
                    printf("|===|==============================================|\n");
                    printf("Use this virtual account number to make the payment via your mobile banking.\nM-Bank Virtual Account: ");
                    scanf(" %[^\n]", userInput);
                    if(strcmp (userInput, format) != 0){
                        printf("\nIncorrect virtual account number. Please make sure to enter the correct number.\nPress any key to continue\n\n");
                        getch();
                    }else{
                        int otpFlag = 4;
                        while (true){
                            randNum = ((rand() % 999999 + 100000) % (rand() % 999999 + 100000) % (rand() % 999999 + 100000) % (rand() % 999999 + 100000)) + 100000;
                            printf("\nYour OTP is %u\n", randNum);
                            strcpy(randStr, "");
                            snprintf (randStr, sizeof(randStr), "%u", randNum);
                            printf("\nEnter your OTP : ");
                            scanf(" %[^\n]", userInput);
                            getchar();
                            if(strcmp(userInput, randStr) != 0){
                                otpFlag --;
                                if(otpFlag == 0){
                                    printf("\nYou have exceeded the maximum number of attempts. Please restart the payment process.\nPress any key to continue");
                                    paymentSuccess = 0;
                                    getch();
                                    break;
                                }
                                printf("\nIncorrect OTP, Please make sure sure to enter the OTP (%d Attempts left)\nPress any key to continue\n", otpFlag);
                                getch();
                            }else{
                                printf("\nYour ticket was successfully purchased!\n\nPress any key to continue\n\n");
                                getch();
                                paymentSuccess = 1;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            break;
            case 2: {
                while (true){
                    printf("|=======================================================|\n");
                    printf("|                  PAYMENT VIA ON-SITE                  |\n");
                    printf("|===|===================================================|\n");
                    printf("| 1 |  Please proceed to the cinema's ticket counter    |\n");         
                    printf("|   |  to complete your payment.                        |\n");         
                    printf("|===|===================================================|\n");
                    printf("| 2 | Show your TICKET ID to the cashier                |\n");
                    printf("|   | >> TICKET ID: %-36s|\n", (*node)->id);
                    printf("|===|===================================================|\n");
                    
                    printf("Have you already provided your Ticket ID to the cinema staff? (Y/n): ");
                    scanf(" %c", &yn);
                    getchar();
                    yn = tolower(yn);
                    if(yn == 'y'){
                        int otpFlag = 4;
                        while(true){
                            
                            char userInput[100];
                            unsigned int randNum = ((rand() % 999999) + 100000 % (rand() % 999999) + 100000 % (rand() % 999999) + 100000 % (rand() % 999999) + 100000 % (rand() % 999999) + 100000) + 100000;
                            char randStr[10];
                            strcpy(randStr, (*node)->idCinema);
                            snprintf(randStr, sizeof(randStr), "%u", randNum);
                            
                            printf("\nVerification code: %s\n", randStr); 
                            printf("\nYou've received a verification code from the cinema staff.\nEnter it below to confirm your ticket: ");
                            scanf(" %[^\n]", userInput);
                            getchar();
                            if(strcmp(userInput, randStr) != 0){
                                otpFlag--;
                                if(otpFlag == 0){
                                    printf("\nYou have exceeded the maximum number of attempts. Please restart the payment process.\nPress any key to continue");
                                    getch();
                                    break;
                                    paymentSuccess = 0;
                                }else{
                                    printf("\nIncorrect OTP, Please make sure sure to enter the OTP (%d Attempts left)\nPress any key to continue\n", otpFlag);
                                    getch();
                                    paymentSuccess = 0;
                                }
                            }else{
                                printf("\nYour ticket was successfully purchased!\n\nPress any key to continue\n\n");
                                getch();
                                paymentSuccess = 1;
                                break;
                            }
                        }
                        break;
                    }else{
                        printf("\nPlease make sure to show your Ticket ID to the cinema staff before proceeding with verification.\n\n");
                        getch();
                    }
                }
            }
            break;
        }
        
        if(paymentSuccess == 1){
            break;
        }
    }
    if(paymentSuccess == 1){
        *hNode = (history *) malloc(sizeof(history));
        (*totalHistory)++;
        strcpy((*hNode)->id, (*node)->id);
        strcpy((*hNode)->fullname, (*node)->fullname);
        strcpy((*hNode)->film, (*node)->movieTitle);
        strcpy((*hNode)->cinema, (*node)->cinema);
        strcpy((*hNode)->mall, (*node)->mall);
        strcpy((*hNode)->date, (*node)->date);
        strcpy((*hNode)->time, (*node)->time);
        strcpy((*hNode)->seat, (*node)->seat);
        (*hNode)->price = (*node)->price;

        if(*hHead == NULL){
            *hHead = *hNode;
            (*hNode)->next = NULL;
        }else{
            (*hTail)->next = (*hNode);
            (*hNode)->next = NULL;
        }
        (*hTail) = *hNode;
    
        (*node) = *head;
        *head = (*head)->next;
        free(*node);
        *node = *head;
    }
}   

void myTicket(char *realName, char *temp, ticket **node, ticket **head, ticket **tail, history **hNode, history **hHead, history **hTail, int *ticketCount, int *totalHistory){
    int choose = 0;
    while(choose != 3){
        printf("|====================================================|\n");
        printf("|                    TICKET QUEUE                    |\n");
        *node = *head;
        int counter = 0;
        
        if((*node) == NULL){
            printf("|====================================================|\n");       
            printf("|        YOUR TICKET QUEUE IS CURRENTLY EMPTY        |\n");
            printf("|====================================================|\n");       
        }else{
            printf("|===|================================================|\n");       
        }
        while((*node) != NULL){
            counter++;
            printf("| %-2d| TICKET ID : %-35s|\n",counter , ((*node)->id));
            printf("|   | YOUR NAME   : %-33s|\n", (*node)->fullname);
            printf("|   | FILM        : %-33s|\n", (*node)->movieTitle);
            printf("|   | MALL        : %-33s|\n", (*node)->mall);
            printf("|   | CINEMA      : %-33s|\n", (*node)->cinema);
            printf("|   | DATE        : %-33s|\n", (*node)->date);
            printf("|   | TIME        : %-33s|\n", (*node)->time);
            printf("|   | SEAT        : %-33s|\n", (*node)->seat);
            printf("|   | TOTAL PRICE : Rp %-30d|\n", (*node)->price);
            printf("|===|================================================|\n");       
            (*node) = (*node)->next;
        }
        printf("\n\n*Tickets that have already been booked cannot be modified. \nIf you'd like to make any changes, please delete the ticket and book a new one.");
        do{
            printf("\n|==============================|\n");
            printf("|            OPTION            |\n");
            printf("|===|==========================|\n");
            printf("| 1 | DELETE TICKET            |\n");
            printf("| 2 | PAY                      |\n");
            printf("| 3 | BACK TO MENU             |\n");
            printf("|===|==========================|\n");
            printf("Choose your option: ");
            scanf(" %[^\n]", temp);
            strtoint(temp);
            if(strtoint(temp) < 1 || strtoint(temp) > 3){
                printf("\nPlease choose numbers from the list!\nPress any key to continue");
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) > 3);
        choose = strtoint(temp);
        switch(choose){
            case 1: {
                deleteTicket(node, head, tail);
            }
            break;
            case 2: {
                *node = *head;
                if(*node != NULL){ 
                    pay(temp, node, head, tail, hNode, hHead, hTail, totalHistory);
                }else{
                    printf("\nYou don't have any ticket to pay!\nPress any key to continue\n\n");
                    getch();
                }
            }
            break;
        }
    }
}

void ticketHistory(history **hNode, history **hHead, history **hTail, int *totalHistory){
    *hNode = *hHead;
    FILE *openHistory = fopen("./historyFilm.txt","w");
    while((*hNode) != NULL){
        fprintf(openHistory, "%s#%s#%s#%s#%s#%s#%s#%s#%d\n", (*hNode)->id, (*hNode)->fullname, (*hNode)->film, (*hNode)->mall, (*hNode)->cinema, (*hNode)->date, (*hNode)->time, (*hNode)->seat, (*hNode)->price);
        (*hNode) = (*hNode)->next;
    }
    fclose(openHistory);
    (*hNode) = (*hHead);
    printf("|==============================================================|\n");
    printf("| NO |                TICKET PURCHASED HISTORY                 |\n");
    printf("|====|=========================================================|\n");
    int counter = 0;
    for(int i = 0; i < *totalHistory; i++){
        counter++;
        printf("| %-2d | TICKET ID   : %-42s|\n", counter, (*hNode)->id);
        printf("|    | YOUR NAME   : %-42s|\n", (*hNode)->fullname);
        printf("|    | FILM        : %-42s|\n",(*hNode)->film);
        printf("|    | MALL        : %-42s|\n",(*hNode)->mall);
        printf("|    | CINEMA      : %-42s|\n",(*hNode)->cinema);
        printf("|    | DATE        : %-42s|\n",(*hNode)->date);
        printf("|    | TIME        : %-42s|\n",(*hNode)->time);
        printf("|    | SEAT        : %-42s|\n",(*hNode)->seat);
        printf("|    | TOTAL PRICE : Rp %-39d|\n",(*hNode)->price);
        printf("|====|=========================================================|\n");
        (*hNode) = (*hNode)->next;
    }
    (*hNode) = (*hHead);
    printf("Press any key to continue\n");
    getch();
}

void mainMenu(char *realName, char *userReg){
    film filmData[MAXFILM]; 
    ticket *node, *tail, *head = NULL;
    history *hNode, *hTail, *hHead = NULL;
    feedback userFeed[MAXFEEDBACK];
    int totalHistory = 0;
    int maxFeedback;
    char temp[100], seat[MAXFILM][MAXCINEMA][MAXDATE][MAXTIME][ROW][COL];
    for (int a = 0; a < MAXFILM; a++){
        for (int b = 0; b < MAXCINEMA; b++){
            for(int c = 0; c < MAXDATE; c++){
                for(int d = 0; d < MAXTIME; d++){
                    for(int e = 0; e < ROW; e++){
                        for(int f = 0; f < COL; f++){
                            seat[a][b][c][d][e][f] = ' ';
                        }
                    }
                }
            }
        }
    }

    int choose, seatFlag = 0, ticketCount = 0;
    do{
        printf("\nWelcome, %s\n", realName);
        printf("Logged in as %s\n", userReg);
        printf("\n\"Welcome to M-Tix - Your Ultimate Movie Ticketing Companion!!\"\n\n");
        printf("Say goodbye to long queues and last-minute ticket hassles! \nM-Tix makes it easier than ever to book your favorite movies online, anytime, anywhere. \nBrowse the latest showtimes, pick your preferred seats, and secure your tickets in just a few taps.\n\n");
        printf("|========================================|\n");
        printf("|                 OPTION                 |\n");
        printf("|===|====================================|\n");
        printf("| 1 | NOW SHOWING                        |\n");
        printf("| 2 | COMING SOON                        |\n");
        printf("| 3 | MY TICKETS                         |\n");
        printf("| 4 | TICKET HISTORY                     |\n");
        printf("| 5 | RATE YOUR EXPERIENCE WITH M-TIX    |\n");
        printf("| 6 | EXIT                               |\n");
        printf("|===|====================================|\n");
        do{
            printf("Choose your option: ");
            scanf(" %[^\n]", temp);
            getchar();            // strtoint(temp);
            if(strtoint(temp) < 1 || strtoint(temp) > 6){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) > 6);
        choose = strtoint(temp);
        switch (choose){
            case 1:{
                nowShowing(realName, temp, filmData, &node, &head, &tail, &seatFlag, &ticketCount, seat);
            }
            break;
            case 2:{
               comingSoon(temp);
            }
            break;      
            case 3:{
                myTicket(realName, temp, &node, &head, &tail, &hNode, &hHead, &hTail, &ticketCount, &totalHistory);
            }
            break;  
            case 4: {
                if(totalHistory == 0){
                    printf("\nYour ticket history is currently empty.\nPress any key to continue\n\n");
                    getch();
                }else{
                    ticketHistory(&hNode, &hHead, &hTail, &totalHistory);
                }
            }
            break;
            case 5: {
                char rateStr[10];
                char comment[100];
                float rateFloat;
                
                FILE *openFeedback = fopen("./feedback.txt", "a+");
                while(true){
                    int i = 0;
                    while(!feof(openFeedback)){
                        fscanf(openFeedback, "%[^#]#%f#%[^\n]\n", userFeed[i].fullname, &userFeed[i].rate, userFeed[i].comment);
                        i++;
                        maxFeedback = i;
                    }
                    int counter = 0;
                    printf("\n|===================================================================|\n");
                    printf("|                        SHARE YOUR FEEDBACK                        |\n");
                    printf("|====|==============================================================|\n");
                    for(int i = 0; i < maxFeedback; i++){
                        counter++;
                        printf("| %-2d | NAME       : %-48s|\n", counter, userFeed[i].fullname);     
                        printf("|    | RATE       : %-48.1f|\n", userFeed[i].rate);        
                        printf("|    | FEEDBACK   : %49s\n", "|");        
                        printf("|    | %-61s|\n", userFeed[i].comment);        
                        printf("|====|==============================================================|\n");
                    }
                    printf("Rate your experience using this app!\n\n");
                    printf("Rate: ");
                    scanf(" %f", &rateFloat);
                    
                    if(rateFloat > 5 || rateFloat < 1){
                        printf("\nPlease input rate from (1 - 5)\n\n");
                        getch();
                    }else{
                        break;
                    }
                }
                while(true){
                    printf("\nWe'd love to hear your thoughts! How was your experience using M-Tix? (Max 50 Characters)\n");
                    printf("\nComments: ");
                    scanf(" %[^\n]", comment);
                    getchar();
                    if(strlen(comment) > 50){
                        printf("\nOops! Please keep your feedback under 50 characters.\nPress any key to continue\n\n");
                        getch();
                    }else if(strlen(comment) == 0){
                        printf("\nPlease help us to improve our application by sharing your experience :)\nPress any key to continue\n\n");
                        getch();
                    }else{
                        printf("\nThanks for your feedback, we will improve our app as soon as possible.\n\n");
                        getch();
                        break;
                    }
                }
                fprintf(openFeedback, "%s#%f#%s\n", realName, rateFloat, comment);
                fclose(openFeedback);
            }
            break;
        }
        if (choose == 6) {
            printf("You have successfully logged out. See you next time!\n");
            node = head;
            while(head!= NULL){
                head = head->next;
                free(node);
                node = head;
            }
            hNode = hHead;
            node = NULL;
            head = NULL;
            tail = NULL;
            while(hHead!= NULL){
                hHead = hHead->next;
                free(hNode);
                hNode = hHead;
            }
            hNode = NULL;
            hHead = NULL;
            hTail = NULL;
            getch();
        }
    }while(choose != 6);
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

void logAcc(char *realName, char *regUser, char *passUser, char *email, char *phone, char *passEncrypt, int *flagReg, int *flagLog){
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
                    printf("|       LOGIN BY USERNAME      |\n");
                    printf("|==============================|\n");
                    printf("\nUsername    : ");
                    scanf(" %[^\n]", regUser2);
                    printf("Password    : ");
                    scanf(" %[^\n]", passUser2);
                    if(strcmp(regUser2, regUser) == 0 && strcmp(passUser2, passUser) == 0){
                        mainMenu(realName, regUser);
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
                        mainMenu(realName, regUser);
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
                        mainMenu(realName, regUser);
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
                    logAcc(realName, regUser, passUser, email, phone, passEncrypt, &flagReg, &flagLog);
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
    acc();
    // mainMenu();
    // seat();
}

