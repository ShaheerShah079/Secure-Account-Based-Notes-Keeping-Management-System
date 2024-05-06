#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
void top_heading(){
	system("CLS");
	printf("\t\t\t\tSecure Accounts Based Notes Keeping Management System\n");
}

// sign up function
int signUp_account(){
	char email[50],password[50];
	
	printf("Press 1 to Skip Sign Up at any field(Email/password).\n");
	
	printf("\tEnter Email Address Max Length(50) : ");
	scanf("%s",email);
	if(email[0]=='1'&& strlen(email)==1){
		return 1;
	}	
	
	printf("\tEnter Password Max Length(50) : ");
	scanf("%s",password);
	if(password[0]=='1' && strlen(password)==1){
		return 1;
	}	
	
	FILE *signUp_PTR=fopen("AccountsFile.txt","a");
	fputs(email,signUp_PTR);
	fputc('\n',signUp_PTR);
	fputs(password,signUp_PTR);	
	fputc('\n',signUp_PTR);
	fclose(signUp_PTR);
	return 0;
}

int logIn_account(){
	char logIn_email[50],logIn_password[50];
	
	// get whole data of account(email/pasword)in array from text file 
	int account_data_length=-1; 
	char account_data[50][50];
	get_whole_file_data(account_data,&account_data_length);
	
	
	logIn_again:
		
		get_email_password(logIn_email,logIn_password);
		// check the user email password is exist in the file 
		// 0. means account exist
		// 1. email correct password wrong
		// 2. email password both wrong
		int is_login=traversing_file_for_user_account(account_data,logIn_email,logIn_password,&account_data_length);
		top_heading();
		if(is_login==0){
			printf("Log In Succesfully....\n");
			note_book_manipulation(logIn_email);
			return 0;
		}
		else if(is_login==1){
			top_heading();
			printf("Email is right but wrong password\n");
	 	 	goto logIn_again;
		}
		else{
			return 1;
		}	
}

void get_whole_file_data(char data[][50],int* length){
	FILE *signIn_PTR=fopen("AccountsFile.txt","r");
	if (signIn_PTR == NULL) {
		fclose(signIn_PTR);
        return;
    }
	char *ptr=NULL;
	do{
		(*length)++;
		ptr=fgets(data[*length],49,signIn_PTR);
		if(ptr==NULL){
			fclose(signIn_PTR);
			break;
		}
		//beacause at row *length the last element is \n and there length is one more then the existing length of string
		//// that fail string string comparison
		data[*length][strlen(data[*length])-1]='\0';
		
	}while(1);
}


void get_email_password(char logIn_email[50],char logIn_password[50]){
		printf("\tEnter User Email Max Length(50) : ");   
	    scanf("%s",logIn_email);
	    
		printf("\tEnter User Password Max Length(50) : ");
	    get_asterisk_password(logIn_password);
}

void get_asterisk_password(char password[50]){
	char temp_password_char;
	int i;
	for(i=0;i<50;i+=1){
		temp_password_char=getch();
		if(temp_password_char==13)
		{
			break;
		}
		else if(temp_password_char==8){
			password[i-1]='\0';
			i-=2;
		}
		else{
			password[i]=temp_password_char;
			printf("*");
		}
	}
	password[i]='\0';
	printf("\n");
}

int traversing_file_for_user_account(char account_data[][50],char logIn_email[50],char logIn_password[50],int *account_data_length){
		int i;
		for (i=0;i<*account_data_length;i+=2)
	    {	
	    	if((strcmp(logIn_email,account_data[i])==0) && (strcmp(logIn_password,account_data[i+1])==0))
	     	{
	    		return 0;
	 	 	}
	 	 	else if((strcmp(logIn_email,account_data[i])==0) && (strcmp(logIn_password,account_data[i+1])!=0)){
				return 1;
	 	 	}
		}
		return -1;
}

void note_book_manipulation(char logIn_email[50]){
	
	char file_name[50],mode_check,file[50];
	
	generate_text_file_name(logIn_email,file_name);
	
	notes_mode:
	
	printf("\t\t\t\t\t\t HELLO: %s\n",logIn_email);			
	printf("Press 1 To (Only Read) Notes.\nPress 2 To Update Notes.\nPress 3 To Clear Previous Notes and Write New Ones.\n4 To Log out\n");
	mode_check=getch();
	
	if(mode_check=='1'){
		top_heading();
		int is_read=read_notes(file_name);
		
		if(is_read==1){
			printf("Cant Read as There is nothing in the Notes\n");
		}else{
			printf("\n");
			ruller_line();
			printf("Enjoy Reading your Notes...\n");
		}
		goto notes_mode;
	}
	else if(mode_check=='2'){
		top_heading();
		printf("Update Your Notes....\n");
		
		int is_update=update_notes(file_name);
		
		top_heading();
		
		if(is_update==1){
			printf("Cant Update Notes\n");
		}
		else{
			printf("Notes Updated....\n");
		}
		goto notes_mode;
	}
	else if(mode_check=='3'){
		top_heading();
		printf("Write Notes.....\n");
		
		int is_write=write_notes(file_name);
		top_heading();
		
		if(is_write==1){
			printf("Cant Write in Notes\n");
		}	
		else{
			printf("Note Written");
		}
			goto notes_mode;
	}
	else{
		
	}
}

void generate_text_file_name(char array1[50],char array2[50])
{
	strcpy(array2,array1);
	array2[strlen(array1)]='.';
	array2[(strlen(array1)+1)]='t';
	array2[(strlen(array1)+2)]='x';
	array2[(strlen(array1)+3)]='t';
	array2[(strlen(array1)+4)]='\0';
}

int read_notes(char fileopen[50]){
	FILE *note_book_PTR=fopen(fileopen,"r");
	
	char read_file[50];
	if(note_book_PTR==NULL)
	{
		return 1;	
	}
	ruller_line();
	while(fgets(read_file,49,note_book_PTR)!=NULL)
	{	
		printf("%s",read_file);
	}
	fclose(note_book_PTR);
	return 0;
}

void ruller_line(){
	printf("______________________________________________________________________________________________________________________\n\n");
}

int update_notes(char file_name[50]){
	FILE *note_book_PTR=fopen(file_name,"a");		
		if(note_book_PTR==NULL)
		{
			return 1;	
		}
	char update_file[50];
	int flag=0;
	do
	{
		fgets(update_file,49,stdin);
		if(update_file[0]==10 && flag==1 && strlen(update_file)==1){
			fclose(note_book_PTR);
			return 0;
		}
		if(update_file[0]!=10 && strlen(update_file)!=1){
		fputs(update_file,note_book_PTR);	
		}	
		flag=1;	
	}while(1);
}


int write_notes(char fileopen[50]){	
	FILE *note_book_PTR=fopen(fileopen,"w");
	char write_file[50];
	int i=0;
	if(note_book_PTR==NULL)
	{
		return 1;	
	}
	do
	{
		fgets(write_file,49,stdin);
		if(strlen(write_file)==1&& i==1 &&write_file[0] == 10){
			fclose(note_book_PTR);
			return 0;
		}
		if(strlen(write_file)!=1&&write_file[0] != 10){
		fputs(write_file,note_book_PTR);	
		}
		i=1;
	}while(1) ;    
}

int main()
{
	top_heading();
	top:	
	
	printf("\tPress 1 for Sign Up.\n\tPress 2 for Log In.\n\tPress 3 To Close Application.\n");
    char signUp_check=getch();
	
	if(signUp_check=='1')
	{
		top_heading();
		
		int is_signup=signUp_account();
		
		top_heading();
		
		if(is_signup==0){
		printf("Account Created Succesfully.....\n");	
		}
		else{
			printf("Sign Up Failed.....\n");	
		}
		
		goto top;	
	}
	else if(signUp_check=='2')
	{
		top_heading();
		
		int is_logIn=logIn_account();
		
		top_heading();
		
		if(is_logIn==1){
			printf("Invalid Email Password.....\n");
		}
		else{
			printf("Account Log out Successfully\n");
		}
		goto top;
	}  
	else{
		top_heading();
		printf("Apllication CLosed...\nThank you for Coming...\n");
		exit(0);
	}
	return 0;
}
