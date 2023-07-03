#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
int sizeOfTable=0;
int login=0;
int scoreboard=0;
int guest=0;
int exite=0;

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
        if(username_exists(new_user.username)){
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
        if(!username_exists(new_user1.username)){
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
        for (int i=0;i<2;i++){
            if(i==1){
                if(atoi(token)<3){
                    printf("invalid size, size must be bigger than 2\n");
                }else{
                    strcpy(sizeOfTable,atoi(token));
                    printf("size o the table has been saved\n");
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

    int a=0;
    while(exite!=1){
        //if(command=="exit"){
          //  break;
        //}
        fgets(command,sizeof(command),stdin);
        token1= strtok(command, " ");


        takeCommand(token1);

        a++;
    }

    for(int i=0;i<num_users;i++){
        printf("%s\n",users[i].password);
    }


    return 0;

 }



