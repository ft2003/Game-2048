#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20


struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int score;
    int rank;
};

struct User users[100];
struct User currentuser;
int scores[15];
int num_users = 0;
int size=0;
int login=0;
int scoreboard=0;
int guest=0;
int exite=0;
int start=0;
int ExitGame=0;
int won=0;
void init_board(int board[][size], int size);
void draw_board(int board[][size], int size, int score);
void generate_random_tile(int board[][size], int size);
int move_left(int board[][size], int size, int* score);
int move_right(int board[][size], int size, int* score);
int move_up(int board[][size], int size, int* score);
int move_down(int board[][size], int size, int* score);
int check_game_over(int board[][size], int size);
void cheat(int i,int j,int val);
int isPowerOfTwo(int n);


void addscore(int score){
    int static count=0;
    scores[count]=score;
    count++;

}

void addUser(struct User user){
    int static counter=0;
    users[counter]=user;
    counter++;
    num_users=counter;
}

int username_exists(char* username) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

int correct_password(char* username,char *password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if(strcmp(users[i].password, password) == 0){
                return 1;
            }
        }
    }
    return 0;
}

void showScoreboard(){
    int temp=0;
    for(int i=0;i<sizeof(scores);i++){
        for (int j = i+1; j < num_users; j++) {
           if(scores[i] > scores[j]) {
               temp = scores[i];
               scores[i] = scores[j];
               scores[j] = temp;
           }
    }
}

    for(int i=0;i<10;i++){
        for(int j=0;j<num_users;j++){
            if(scores[i]==users[j].score){
                printf("%d- %s - %d\n",i+1,users[j].username,users[j].score);
                users[j].rank=i+1;
            }
        }
    }
}

void Ranking(){
    int temp=0;
    for(int i=0;i<sizeof(scores);i++){
        for (int j = i+1; j < num_users; j++) {
           if(scores[i] > scores[j]) {
               temp = scores[i];
               scores[i] = scores[j];
               scores[j] = temp;
           }
    }
}

    for(int i=0;i<sizeof(scores);i++){
        for(int j=0;j<num_users;j++){
            if(scores[i]==users[j].score){
                users[j].rank=i+1;
            }
        }
    }
}

void showRank(struct User user){
    Ranking;
    printf("%d - %s - %d",user.rank,user.username,user.score);
}

void takeCommand(char *token){
    if(strcmp(token,"signup")==0){
        struct User new_user;
        for (int i=0;i<3;i++){
            if(i==1)
                strcpy(new_user.username,token);
            else if(i==2)
                strcpy(new_user.password,token);

            token = strtok(NULL, " ");
        }
        if (strlen(new_user.username) == 0 || strlen(new_user.password) == 0) {
        printf("Error: Username or password cannot be empty.\n");

        }
        else if(username_exists(new_user.username)){
            printf("username already exists!\n");
        } else{
            addUser(new_user);
            printf("you signed up successfully!\n");
        }

    } else if(strcmp(token,"login")==0){
        struct User new_user1;
        for (int i=0;i<3;i++){
            if(i==1)
                strcpy(new_user1.username,token);
            else if(i==2)
                strcpy(new_user1.password,token);

            token = strtok(NULL, " ");
        }
        if (strlen(new_user1.username) == 0 || strlen(new_user1.password) == 0) {
        printf("Error: Username or password cannot be empty.\n");

        }
        else if(!username_exists(new_user1.username)){
            printf("username not found!\n");
        } else if(!correct_password(new_user1.username,new_user1.password)){
            printf("password incorrect!\n");
        } else{
            printf("\nyou logged in successfully!\n");
            printf("welcome to my 2048 game!!!\n");
            currentuser=new_user1;
            login=1;
        }

    } else if(strcmp(token,"guest")==0){
        printf("\nyou entered the game as a guest!\n");
        printf("welcome to my 2048 game!!!\n");
        guest=1;
    }else if(strcmp(token,"start")==0){
    for (int i = 0; i < 2; i++){
        if(i == 1){
            int tableSize = atoi(token);
            if(tableSize < 3){
                printf("invalid size, size must be bigger than 2\n");
            }else{
                size = tableSize;
                printf("size of the table has been saved\n");
                start=1;
            }
        }
        token = strtok(NULL, " ");
    }
}else if(strcmp(token,"scoreboard")==0){
        printf("\nyou entered scoreboard menu!\n");
        showScoreboard;
        scoreboard=1;
    }else if(strcmp(token,"logout")==0){
        if(login==1){
            printf("\nyou logged out!\n");
            login=0;
        }
    }else if(strcmp(token,"myrank")==0){
        if(guest==1){
            printf("you are guest!");
        }else{
            showRank(currentuser);
        }
    }else if(strcmp(token,"back")==0){
        if(scoreboard==1){
            printf("you are back to main menu!\n");
            scoreboard=0;
        }

    }else if(strcmp(token,"exit")==0){
        exite=1;

    }else{
        printf("invalid command\n");
    }


}



int main() {

    char command[50];

    printf("\t\t\t\t-----WELCOM TO 2048 GAME-----\t\t\t\t");
    printf("\nPlease signup or login or enter as a guest!\n\n");

    fgets(command,sizeof(command),stdin);
    char *token = strtok(command, " ");

    takeCommand(token);
    char *token1;


    while(exite!=1){
        fgets(command,sizeof(command),stdin);
        token1= strtok(command, " ");

        takeCommand(token1);
        if (start==1)
        {
            int board[size][size];
            int score = 0;
            char ch;
            char nextln;
            srand(time(0));


            init_board(board, size);
            generate_random_tile(board, size);
            generate_random_tile(board, size);
            draw_board(board, size, score);
            while(1)
            {
                fgets(command,sizeof(command),stdin);
                char *token2 = strtok(command, " ");
                if(strcmp(token2,"exit")==0)
                {
                    start=0;
                    printf("you ended the game!");
                    break;

                }if(strcmp(token2,"left")==0)
                {
                    score += move_left(board, size, &score);

                }else if(strcmp(token2,"right")==0)
                {
                    score += move_right(board, size, &score);

                }else if (strcmp(token2,"up")==0)
                {
                    score += move_up(board, size, &score);
                }else if (strcmp(token2,"down")==0)
                {
                    score += move_down(board, size, &score);
                }else if (strcmp(token2,"put")==0)
                {
                    int dirI,dirJ,value;
                    for (int i = 0; i < 4; i++){
                        if(i == 1)
                        {
                            dirI = atoi(token2);
                        }else if(i==2)
                        {
                            dirJ = atoi(token2);
                        }else if(i==3)
                        {
                            value = atoi(token2);
                        }
                        token2 = strtok(NULL, " ");
                    }

                    cheat(dirI,dirJ,value);
                }else{
                    printf("invalid command\n");
                }
                if (check_game_over(board, size)) {
                    printf("\nyou lost!\n");
                    break;
                }
                if (score == 1000)
                {
                    if(!won)
                    {
                        printf("\nyou won!");
                        won=1;
                    }


                }

                generate_random_tile(board, size);
                draw_board(board, size, score);
            }
            if (!guest){
                currentuser.score=score;
                printf("your score is %d\n",currentuser.score);
            }

        }
    }


    return 0;

 }



 void cheat(int i , int j , int val)
 {
    if(i>size || j > size)
    {
        printf("coordinate out of range!\n");
    }else if(!isPowerOfTwo(val))
    {
        printf("invalid value!\n");
    }else
    {

    }
 }


 int isPowerOfTwo(int n)
{
    if (n == 0)
        return 0;
    while (n != 1) {
        if (n % 2 != 0)
            return 0;
        n = n / 2;
    }
    return 1;
}


void init_board(int board[][size], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            board[i][j] = 0;
        }
    }
}

void draw_board(int board[][size], int size, int score) {
    int i, j;
    printf("2048 Game\n\n");
    printf("Score: %d\n\n", score);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                printf("     .");
            }
            else {
                printf(" %5d", board[i][j]);
            }
        }
        printf("\n\n");
    }

}


void generate_random_tile(int board[][size], int size) {
    int i, j, r;
    do {
        i = rand() % size;
        j = rand() % size;
    } while (board[i][j] != 0);
    r = (rand() % 10 < 9) ? 2 : 4;
    board[i][j] = r;
}


int move_left(int board[][size], int size, int* score) {
    int i, j, k, flag = 0;
    for (i = 0; i < size; i++) {
        k = 0;
        for (j = 0; j < size; j++) {
            if (board[i][j] != 0) {
                if (k != j) {

                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                    flag = 1;
                }
                if (k > 0 && board[i][k] == board[i][k-1]) {

                    board[i][k-1] *= 2;
                    *score += board[i][k-1];
                    board[i][k] = 0;
                    k--;
                    flag = 1;
                }
                k++;
            }
        }
    }
    return flag;
}

int move_right(int board[][size], int size, int* score) {
    int i, j, k, flag = 0;
    for (i = 0; i < size; i++) {
        k = size - 1;
        for (j = size - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                if (k != j) {

                    board[i][k] = board[i][j];
                    board[i][j] = 0;
                    flag = 1;
                }
                if (k < size - 1 && board[i][k] == board[i][k+1]) {

                    board[i][k+1] *= 2;
                    *score += board[i][k+1];
                    board[i][k] = 0;
                    k++;
                    flag = 1;
                }
                k--;
            }
        }
    }
    return flag;
}


int move_up(int board[][size], int size, int* score) {
    int i, j, k, flag = 0;
    for (j = 0; j < size; j++) {
        k = 0;
        for (i = 0; i < size; i++) {
            if (board[i][j] != 0) {
                if (k != i) {

                    board[k][j] = board[i][j];
                    board[i][j] = 0;
                    flag = 1;
                }
                if (k > 0 && board[k][j] == board[k-1][j]) {

                    board[k-1][j] *= 2;
                    *score += board[k-1][j];
                    board[k][j] = 0;
                    k--;
                    flag = 1;
                }
                k++;
            }
        }
    }
    return flag;
}

int move_down(int board[][size], int size, int* score) {
    int i, j, k, flag = 0;
    for (j = 0; j < size; j++) {
        k = size - 1;
        for (i = size - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                if (k != i) {

                    board[k][j] = board[i][j];
                    board[i][j] = 0;
                    flag = 1;
                }
                if (k < size - 1 && board[k][j] == board[k+1][j]) {

                    board[k+1][j] *= 2;
                    *score += board[k+1][j];
                    board[k][j] = 0;
                    k++;
                    flag = 1;
                }
                k--;
            }
        }
    }
    return flag;
}


int check_game_over(int board[][size], int size) {
    int i, j, flag = 1;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                flag = 0;
                break;
            }
            if (i > 0 && board[i][j] == board[i-1][j]) {
                flag = 0;
                break;
            }
            if (j > 0 && board[i][j] == board[i][j-1]) {
                flag = 0;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }
    return flag;
}
