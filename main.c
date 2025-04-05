#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define ROW 'K'
#define COL 20
#define MAXFILM 7
#define MAXCINEMA 7
#define MAXDATE 4
#define MAXTIME 6
#define MAXSEAT 200
typedef struct {
    char nameFilm[50], genre[50], age[5], duration[15];
    float rate;
}film;

typedef struct ticket{ // linkedlist for queue
    char fullname[50], id[5], movieTitle[100], mall[100], cinema[100], time[100], date[100], seat[50];
    int paymentStatus, isRefund;
    struct ticket *next;
}ticket;

typedef struct {
    char nameMall[40], nameCinema[20], id[10];
}cinema;

typedef struct {
    char date[30], id[30];
}date;

typedef struct {
    char time[20];
}time;

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

void availableSeat(int *rowArr, int *colArr, char seat[MAXFILM][MAXCINEMA][MAXDATE][MAXTIME][ROW][COL], int *filmArr, int *cinemaArr, int *dateArr, int *timeArr){
    int tempFilmArr = *filmArr, tempCinemaArr = *cinemaArr, tempDateArr = *dateArr, tempTimeArr = *timeArr, tempRowArr = *rowArr, tempColArr = *colArr;
    // printf("%d %d %d %d %d %d", tempFilmArr, tempCinemaArr, tempDateArr, tempTimeArr, *rowArr, *colArr);
    int capacity = 0;
    for (int i = 'A'; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if(seat[tempFilmArr][tempCinemaArr][tempDateArr][tempTimeArr][i][j] == 'O'){
                capacity++;
            }
        }
    }
    
    printf("|===================================================================================|\n");
    printf("| AVAILABLE : \"O\"%68c\n", '|');
    printf("| BOOKED    : \"X\"%68c\n|%84c\n", '|', '|');
    printf("| CAPACITY  : %d/%-66d|\n", capacity, MAXSEAT);
    for(int j = 0; j < COL+1; j++){
        printf("|===");
    }
    printf("|\n");
    printf("|   ");
    for(int j = 0; j < COL+1; j++){
        if(j > 0){
            printf("| %-2d", j-1);
        }
    }
    printf("|\n");
    for(int j = 0; j < COL+1; j++){
        printf("|===");
    }
    printf("|\n");
    for(int i = 'A'; i < ROW; i++){
        printf("| %c ", i);
        for(int j = 0; j < COL; j++){
          
            printf("| %c ", seat[tempFilmArr][tempCinemaArr][tempDateArr][tempTimeArr][i][j]);
        }
        printf("|\n");
        for(int i = 0; i < COL+1; i++){
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
            printf("\nWhich col would you like to book to enjoy the movie? (0 - %d)\nChoose your option: ", COL - 1);
            scanf(" %[^\n]", temp);
            strtoint(temp);
            if(strtoint(temp) < 0 || strtoint(temp) >= COL){
                printf("\nPlease input between (0 - %d)\nPress any key to continue\n", COL - 1);
                getch();
            }
        }while(strtoint(temp) < 0 || strtoint(temp) >= COL);
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
void buyTicket(ticket **node, ticket **head, ticket **tail, film *filmData, cinema *cinemaData, date *dateData, time *timeData, int *maxFilm,int *maxCinema, int *maxDate, int *maxTime, char *userFilm, char *userMall, char *userCinema, char *userDate, char *userTime, char *temp, int *filmArr, int *cinemaArr, int *dateArr, int *timeArr, int *rowArr, int *colArr, int *seatFlag, char seat[MAXFILM][MAXCINEMA][MAXDATE][MAXTIME][ROW][COL]){
    char yn, seatCountString[50];
    do{
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
        strcpy(userFilm, filmData[strtoint(temp)-1].nameFilm);
        strcpy((*node)->movieTitle, userFilm);
    
        *filmArr = strtoint(temp)-1;
        do{
            int counter = 0;
            printf("|====|===============================|==================|\n"); //cinema[]
            printf("| NO |              MALL             |      CINEMA      |\n");
            printf("|====|===============================|==================|\n");
            for(int i = 0; i < *maxCinema; i++){
                counter++;
                printf("| %-3d| %-30s| %-16s |\n", counter, cinemaData[i].nameMall, cinemaData[i].nameCinema);
            }
            printf("|====|===============================|==================|\n\n");
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
        
        *cinemaArr = strtoint(temp)-1;
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
        // printf("UserTime: %s", userTime);
        strcpy((*node)->time, userTime);
        
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
                    availableSeat(rowArr, colArr, seat, filmArr, cinemaArr, dateArr, timeArr);
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
                        printf("\n|=======================================|\n");
                        printf("|           SEAT CONFIRMATION           |\n");
                        printf("|=======================================|\n");
                        printf("Your seat reservation : %s", seatCountString);
                        
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
        }while(bookFlag == 0 || bookFlag == 1);
        
        if (*head == NULL){
            *head = *node;
            (*node)->next = NULL; 
        }else{
            (*tail)->next = *node;
            (*node)->next = NULL; 
        }   
        *tail = *node;
        printf("\nHASIL LINKEDLIST\n\n");                  //printing nodes
        *node = *head;
        while((*node) != NULL){
            printf("user film: %s\n", (*node)->movieTitle);
            printf("user mall: %s\n", (*node)->mall);
            printf("user cinema: %s\n", (*node)->cinema);
            printf("user date: %s\n", (*node)->date);
            printf("user time: %s\n", (*node)->time);
            printf("user seat: %s\n\n", (*node)->seat);
            *node = (*node)->next;
        }
        getch();
        printf("\nwant again? (Y/n): ");
        scanf(" %c", &yn);
        yn = tolower(yn);
    }while(yn == 'y');
    while((*head)!= NULL){
        *node = *head;
        *head = (*head)->next;
        free(*node);
    }
    printf("nodes cleared\n");
    

}

void nowShowing(char *temp, ticket **node, ticket **head, ticket **tail, int *seatFlag, int *ticketCount, char seat[MAXFILM][MAXCINEMA][MAXDATE][MAXTIME][ROW][COL]){
    int i = 0, maxFilm, choose = 0, iCinema = 0, maxCinema, maxDate, maxTime, cinemaArr, filmArr, dateArr, timeArr, rowArr, colArr;
    char userFilm[50], userMall[50], userCinema[50], userDate[50], userTime[30]; 
    film filmData[12]; 
    cinema cinemaData[18];
    date dateData[4];
    time timeData[6];   
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
            fscanf(openCinema, " %[^#]#%[^#]#%[^\n]", &cinemaData[iCinema].nameMall, &cinemaData[iCinema].nameCinema, &cinemaData[iCinema].id);
            iCinema++;
            maxCinema = iCinema;
        }
        fclose(openCinema);
        FILE *openDate = fopen("./date.txt", "r");
        iCinema = 0;
        while(!feof(openDate)){
            fscanf(openDate, " %[^#]#%[^\n]\n", &dateData[iCinema].date, &dateData[iCinema].id);
            iCinema++;
            maxDate = iCinema;
        }
        fclose(openDate);
        int i = 0;
        FILE *openTime = fopen("./time.txt", "r");
        while(!feof(openTime)){
            fscanf(openTime, " %[^\n]", timeData[i].time);
            i++;
            maxTime = i;
        }
        // for(int iaja = 0; iaja < maxDate; iaja++){
        //     printf("%s\n",timeData[iaja].time);
        // }
       
        printf("|==============================|\n");
        printf("|            OPTION            |\n");
        printf("|===|==========================|\n");
        printf("| 1.| BUY TICKET               |\n");
        printf("| 2.| ADD TO WATCH LIST        |\n");
        printf("| 3.| BACK TO MAIN MENU        |\n");
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
                buyTicket(node, head, tail, filmData, cinemaData, dateData, timeData, &maxFilm, &maxCinema, &maxDate, &maxTime, userFilm, userMall, userCinema, userDate, userTime, temp, &filmArr, &cinemaArr, &dateArr, &timeArr, &rowArr, &colArr, seatFlag, seat);
                *ticketCount++;
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
    ticket *node, *tail, *head = NULL;
    char temp[100], seat[MAXFILM][MAXCINEMA][MAXDATE][MAXTIME][ROW][COL];
    for (int a = 0; a < MAXFILM; a++){
        for (int b = 0; b < MAXCINEMA; b++){
            for(int c = 0; c < MAXDATE; c++){
                for(int d = 0; d < MAXTIME; d++){
                    for(int e = 0; e < ROW; e++){
                        for(int f = 0; f < COL; f++){
                            seat[a][b][c][d][e][f] = 'O';
                        }
                    }
                }
            }
        }
    }
    int choose, seatFlag = 0, ticketCount = 0;
    do{
        printf("\nWelcome, \"fullname\"\n");
        printf("Logged in as \"username\"\n");
        printf("\n\"Welcome to M-Tix - Your Ultimate Movie Ticketing Companion!!\"\n\n");
        printf("Say goodbye to long queues and last-minute ticket hassles! \nM-Tix makes it easier than ever to book your favorite movies online, anytime, anywhere. \nBrowse the latest showtimes, pick your preferred seats, and secure your tickets in just a few taps.\n\n");
        printf("|==============================|\n");
        printf("|            OPTION            |\n");
        printf("|===|==========================|\n");
        printf("| 1 | NOW SHOWING              |\n");
        printf("| 2 | COMING SOON              |\n");
        printf("| 3 | WATCH LIST               |\n");
        printf("| 4 | MY TICKETS               |\n");
        printf("| 5 | TICKET HISTORY           |\n");
        printf("| 6 | LOG OUT                  |\n");
        printf("|===|==========================|\n");
        do{
            printf("Choose your option: ");
            scanf(" %[^\n]", temp);
            // strtoint(temp);
            if(strtoint(temp) < 1 || strtoint(temp) > 6){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) > 6);
        choose = strtoint(temp);
        switch (choose){
            case 1:{
                nowShowing(temp, &node, &head, &tail, &seatFlag, &ticketCount, seat);
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

