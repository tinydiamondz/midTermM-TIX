#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define ROW 12
#define COL 11
typedef struct {
    char nameFilm[50], genre[50], age[5], duration[15];
    float rate;
}film;

typedef struct ticket{ // linkedlist for queue
    char fullname[50], id[5], movieTitle[100], mall[100], cinema[100], time[100], date[100], seat[3];
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

// void seat(int *filmArr, int *cinemaArr, int *dateArr, int *timeArr){
//     int taken = 0, ij = 0;
//     char seat[12][18][4][6][12][11][5]; // bro are u fr?
//     printf("\nSeat status:\n\"X\" = TAKEN\n\"O\" = AVAILABLE\"\n");
//     for(int i = 'A'; i <= 'L'; i++){ // ---> for(int i = 'A'; i <= 'A'; i++)
//                                      // ---> for(int j = 0; j <= 0; j++)
//         char iChar[10];              // ---> taken = 1 , if (taken == 1){"booked" || cTaken = 'X'}
//         snprintf(iChar, sizeof(iChar), "%c", i);
//         for(int k = 0; k <= 10; k++){
//             printf("|========");   
//         }
//         printf("=|\n");
//         for(int j = 0; j <= 10; j++){
//             char cTaken, jChar[10];
//             snprintf(jChar, sizeof(jChar), "%d", j);
//             if(taken == 0){
//                 cTaken = 'O';
//                 printf("| %c%d \"%c\" ", i, j, cTaken);
//             }else if(taken == 1){
//                 cTaken = 'X';
//                 printf("| %c%d \"%c\" ", i, j, cTaken);
//             }
//             strcpy(seat[*filmArr][*cinemaArr][*dateArr][*timeArr][ij][j], "");
//             strcat(seat[ij][j], iChar);
//             strcat(seat[ij][j], jChar);
//         }
//         ij++;
//         printf("|\n");
//     }
//     for(int k = 0; k <= 10; k++){
//         printf("|========");   
//     }
//     printf("=|\n");
//     printf("|                                                                                                   |\n");
//     printf("|                                                                                                   |\n");
//     printf("|                                                                                                   |\n");
//     printf("|                                                                                                   |\n");
//     printf("|===============================|               SCREEN               |==============================|\n"); 
//     for(int i = 0; i< 12; i++){
//         for (int j = 0; j <11; j++){
//             printf("%s ", seat[i][j]);
//         }
//         printf("\n");
//     }
//     getch();
// }

void buyTicket(ticket **node, ticket **head, ticket **tail, film *filmData, cinema *cinemaData, date *dateData, time *timeData, int *maxFilm,int *maxCinema, int *maxDate, int *maxTime, char *userFilm, char *userMall, char *userCinema, char *userDate, char *userTime, char *temp, int *filmArr, int *cinemaArr, int *dateArr, int *timeArr){
    char yn;
    do{
        
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
        do{
            printf("|==================================|\n");
            printf("|               SEAT               |\n");
            printf("|===|==============================|\n");
            printf("| 1 | VIEW AVAILABlE SEAT          |\n");
            printf("| 2 | BOOK SEAT                    |\n");
            printf("|===|==============================|\n\n");
            printf("Choose your option: ");
            scanf(" %[^\n]", temp);
            strtoint(temp);
            if (strtoint(temp) < 1 || strtoint(temp) > 2){
                printf("\nPlease choose numbers from the list!\nPress any key to continue\n\n");
                getch();
            }
        }while(strtoint(temp) < 1 || strtoint(temp) > 2);
        if (*head == NULL){
            *head = *node;
            (*node)->next = NULL; 
        }else{
            (*tail)->next = *node;
            (*node)->next = NULL; 
        }   
        *tail = *node;
        // printf("HASIL LINKEDLIST\n\n");                  //printing nodes
        // *node = *head;
        // while((*node) != NULL){
        //     printf("user film: %s\n", (*node)->movieTitle);
        //     printf("user mall: %s\n", (*node)->mall);
        //     printf("user cinema: %s\n", (*node)->cinema);
        //     printf("user date: %s\n", (*node)->date);
        //     printf("user time: %s\n\n", (*node)->time);
        //     *node = (*node)->next;
        // }
        
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

void nowShowing(char *temp, ticket **node, ticket **head, ticket **tail){
    int i = 0, maxFilm, choose = 0, ticketCount = 0, iCinema = 0, maxCinema, maxDate, maxTime, cinemaArr, filmArr, dateArr, timeArr;
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
                buyTicket(node, head, tail, filmData, cinemaData, dateData, timeData, &maxFilm, &maxCinema, &maxDate, &maxTime, userFilm, userMall, userCinema, userDate, userTime, temp, &filmArr, &cinemaArr, &dateArr, &timeArr);
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
    ticket *node, *tail, *head;
    head = NULL;
    char temp[100];
    int choose;
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
                nowShowing(temp, &node, &head, &tail);
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

