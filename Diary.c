#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
void first();
void add_reminders();
void reminders();
void birthdays();
void see_birth();
void day_description();
void description();
void add_passwords();
void passwords();
void encrypt(char* password, int key);
void decrypt(char* password, int key);
void main(){
    //Creating a personal diary in C
    //The Login system
    int choice = 0;
    char name[50];
    char password[100],file_password[100];
    char input_password[100];
    int key = 3; //encryption key
    FILE *fp;
    time_t t;//to display current time and date
    time(&t);
    printf("Welcome to Your Personal Diary <3 \n");
    printf("Todays's date and time  ->  %s",ctime(&t));//current time and date printed
    printf("Please enter your user name: \n");
    fgets(name,50,stdin);
    xyz://part of goto statement
    printf("Enter 1 to sign up and 2 to log into your account: \n");
    scanf("%d",&choice);//User makes a choice to login or get himself registered
    switch (choice) {
        case 1:
            printf("Create a strong password: ");
            for(int i=0;i<100;i++){
                password[i] = getch();
                if(password[i] == '\r'){
                    password[i] = '\0';
                    break;
                }
                printf("*");
            }
            encrypt(password, key);//Password goes for encryption
            // Open the file in write mode
            fp = fopen("Pass.txt", "w");//password gets written in the file
            fprintf(fp, "%s", password);
            fclose(fp);
            printf("\n\n\nYay! Registration Successful!\n");
            break;
        case 2://Here code checks if the both passwords are same or not
            // Open the file in read mode
            printf("\nEnter your password to log into your account: \n");
            fp = fopen("Pass.txt", "r");
            fscanf(fp,"%s",file_password);
            fclose(fp);
            decrypt(file_password, key);
            while(1){
                for(int i=0;i<100;i++){
                    input_password[i] = getch();
                    if(input_password[i] == '\r'){
                        input_password[i] = '\0';
                        break;
                     }
                     printf("*");
                }
                if(strcmp(input_password,file_password) == 0){
                    printf("\nAccess Granted!\n");
                    break;
                }//to compare passwords
                else{
                    printf("\nAccess Denied! Enter your password again\n");
                    continue;
                }
            }
            break;
        default:
            printf("\nEnter a valid number\n");
            goto xyz;
            break;
    }
    //Options that can be accessesed
    printf("\n Select the feature you want to use as per your need: \n");
    printf("\n\n");
    printf("\n    [1]ADD YOUR REMINDERS       \n");
    printf("\n    [2]SEE YOUR REMINDERS       \n");
    printf("\n    [3]ADD BIRTHDAYS            \n");
    printf("\n    [4]SEE SAVED BIRTHDAYS      \n");
    printf("\n    [5]DAY DESCRIPTION          \n");
    printf("\n    [6]SEE YOUR DAY DESCRIPTIONS \n");
    printf("\n    [7]ADD IMPORTANT PASSWORDS  \n");
    printf("\n    [8]SEE SAVED PASSWORDS      \n");
    printf("\n\n");
    while(1){
        first();
    }
}
//Function to encrypt the password of user
void decrypt(char* password, int key) {
    int len = strlen(password);
    for(int i = 0; i < len; i++) {
        password[i] = (password[i] - key) % 128;
    }
}
//Function to decrypt password of the user
void encrypt(char* password, int key) {
    int len = strlen(password);
    for(int i = 0; i < len; i++) {
        password[i] = (password[i] + key) % 128;
    }
}
//Function in which person can add his reminders
void add_reminders(){
    int key = 3;
    FILE *ptr,*fp;
    printf("\nIn this section you can save your meeting schedule or plans etc.");
    printf("\n[1]Add meetings\n[2]Add plans or trips\n");
    int a =0;
    printf("\nEnter a number between 1 and 2\n"
           "\n1 to add reminders and 2 to add your trip plans\n");
    scanf("%d\n",&a);
    switch(a){
    case 1:
        ptr = fopen("E.txt","w");
        char meet[1000];
        fgets(meet,sizeof(meet),stdin);//user enters his details of meeting
        fprintf(ptr,"%s",meet);
        fclose(ptr);
        break;
    case 2:
        ptr = fopen("E.txt","w");
        char plan[1000];
        fgets(plan,sizeof(plan),stdin);//Use enters details of plan
        fprintf(ptr,"%s",plan);
        fclose(ptr);
        break;
    default:
        printf("Enter a valid number\n");
    }
    fclose(ptr);
    fp = fopen("Reminders.txt","a+");
    ptr = fopen("E.txt","r");
    char c;
    while(!(feof(ptr))){
        c = fgetc(ptr);
        c = (c+key)%128;//everything written gets encrypted
        fputc(c,fp);
    }
    fclose(ptr);
    fclose(fp);

}
void reminders(){//reminders and trips plan can be seen here
    FILE *ptr;
    char c;
    int key = 3;
    ptr = fopen("Reminders.txt","r");//File opened in read mode
    if(ptr == NULL)
        printf("NO FILE FOUND\n");
    else{
        printf("Your detailed meetings or plans are:\n");
        c = fgetc(ptr);
        while((!feof(ptr))){
            c = (c - key) % 128;//everything gets decrypted and shown to user
            printf("%c",c);
            c = fgetc(ptr);
        }
        fclose(ptr);
    }

}
void birthdays(){//User can enter birthdays to remember
    printf("\nEnter birthdays\n");
    char b[2],c;
    int key = 3;
    fgets(b,2,stdin);
    FILE *ptr,*fp;
    fp = fopen("E.txt","w");
    char birth[100000];
    fgets(birth,100000,stdin);
    fprintf(fp,"%s",birth);
    fclose(fp);
    fp = fopen("E.txt","r");
    ptr = fopen("Birthdays.txt","a+");//Main file opened in append mode
    while(!(feof(fp))){
        c = fgetc(fp);
        c += key;//password gets encrypted
        fputc(c,ptr);
    }
    fclose(fp);
    fclose(ptr);

    printf("Ok!Saved in the file");

}

void day_description(){//User can enter day-descriptions
    int key = 3;
    char c;
    printf("\nEnter your day description\n");
    FILE *ptr,*fp;
    ptr = fopen("E.txt","w");
    char des[100000];
    printf("How was your day?\n");
    fgets(des,2,stdin);
    fgets(des,sizeof(des),stdin);
    fprintf(ptr,"%s",des);
    fclose(ptr);
    fp = fopen("Day-Description.txt","a+");//file opened in append mode
    ptr = fopen("E.txt","r");
    while(!(feof(ptr))){
        c = fgetc(ptr);
        c += 3;//encryption takes place
        fputc(c,fp);
    }
    printf("\nOk Saved");
    fclose(fp);
    fclose(ptr);

}
void description(){
    FILE *ptr;
    char c;
    int key = 3;
    ptr = fopen("Day-Description.txt","r");
    if(ptr == NULL)
        printf("NO FILE FOUND\n");
    else{
        printf("Your past day descriptions are:\n");
        while(!(feof(ptr))){
            c = fgetc(ptr);
            c -= key;//decryption takes place and user can view his past descriptions
            printf("%c",c);
        }
        fclose(ptr);
    }

}
void add_passwords(){ //Passwords can be added by the user
    printf("Here you can add your important passwords:\n");
    FILE *ptr,*fp;
    char pass[100000],c;
    int key = 3;
    ptr =fopen("E.txt","w");
    if(ptr == NULL)
        printf("No such file exists\n");
    else{
        printf("Enter your passwords\n");
        fgets(pass,3,stdin);
        fgets(pass,sizeof(pass),stdin);
        fprintf(ptr,"\n%s",pass);
        fclose(ptr);
    }
    fp = fopen("Passwords.txt","a+");//File opened in append mode
    ptr = fopen("E.txt","r");
    while(!(feof(ptr))){
        c = fgetc(ptr);
        c += key;//encryption takes place and gets in the file
        fputc(c,fp);
    }
    fclose(fp);
    fclose(ptr);
    printf("Ok! Saved successfully!\n");

}
void passwords(){//user can see his old written passwords
    FILE *ptr;
    int key = 3;
    ptr = fopen("Passwords.txt","r");
    if(ptr == NULL){
        printf("\n NO FILE FOUND\n");
    }
    else{
        printf("\nYour saved passwords are:\n");
        char c;
        c= fgetc(ptr);
        while(!(feof(ptr))){
            c -= key;
            printf("%c",c);//decryption takes place and prints on the screen
            c = fgetc(ptr);
       }
    }

}
void see_birth(){//Birthdays entered by the user after encryption can be seen
    int key = 3;
    printf("Here you can see your saved birthdays\n");
    printf("Press enter to see\n");
    FILE *ptr;
    ptr = fopen("Birthdays.txt","r");
    char birth[100000];
    char c;
    c = fgetc(ptr);
    while(!(feof(ptr))){
        c -= key;//decryption takes place
        printf("%c",c);//Content of file gets printed on the screen
        c = fgetc(ptr);
    }
    fclose(ptr);

}
void first(){//This function is to show user the available options
    int option =0;
    //If user enters an invalid number the program comes back here to again let the user enter a number
    while(option != -1){
        printf("\n Enter 1 to add new reminders.\n Enter 2 to see your reminders."
        "\n Enter 3 to add the birthdays you want to remember."
        "\n Enter 4 to see your saved birthdays.\n Enter 5 to add your day description."
        "\n Enter 6 to see your day description.\n Enter 7 to add your important passwords"
        "\n Enter 8 to see your saved passwords \n "  "Enter -1 to exit the Diary. \n");
        printf("\n Enter a number to go to desired menu.\n");
        scanf("%d",&option);
        if(option == -1){//If user enters -1 then code terminates
            printf("\nGoodbye!Thanks for using your very own personal diary <3 \n");
            exit(0);
        }//if user does not enter -1 then these are the available options
        switch(option){
            case 1:{
                add_reminders();
                break;
            }
            case 2:{
                reminders();
                break;
            }
            case 3:{
                birthdays();
                break;
            }
            case 4:{
                see_birth();
                break;
            }
            case 5:{
                day_description();
                break;
            }
            case 6:{
                description();
                break;
            }
            case 7:{
                add_passwords();
                break;
            }
            case 8:{
                passwords();
                break;
            }
            default:{
                printf("\nPlease enter a valid number\n");
                continue;
            }
        }
    }
}




