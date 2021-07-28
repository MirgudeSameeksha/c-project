#include<stdio.h>
#include<stdlib.h>
#include<string.h>
enum state
{
    Home,
    Login
};
enum state currentstate = Home;

typedef struct user{
	char username[100];
	char password[100];
	char VehicleID[100];
	float price;
	struct user *next;
} user;
//user *h=NULL;
char currentuser[100];

user *AddUser(user *);
user *InitializeList(user *);
void CancelBooking(user *);
void BookVehicle(user *h);
void LoginUser(user *);
void CheckBooking(user *);
void WriteToFile(user *);
void ChangePassword(user *);
void Menu();
void LogoutUser();
void ExitProgram();


void main(){
	int n,choice,ch1;
	user *h=NULL;
	printf("\n\t\tWELCOME TO PIXAR LIGHTNING TRAVELS\n\n");
	h = InitializeList(h);
	while(1){
	if(currentstate==Home){

	printf("\n\t1.Create account\n" );
	printf("\n\t2.login account\n");
	printf("\n\t0.Exit\n");
	scanf("%d",&n);
	switch(n)
	{
		case 1: AddUser(h);
			break;
		case 2: LoginUser(h);
			break;
		case 0: exit(0);
			break;
		default: printf("\nInvalid choice\n");
			break;
		}
	}
	else if(currentstate==Login)
	{       system("CLS");
		printf("\n\t\tWELCOME TO PIXAR LIGHTNING TRAVELS\n\n");
		printf("\n\t1.Book Vehicle\n\t2.Check Bookings\n\t3.Cancel Bookings\n\t4.Change password\n\t5.Logout\n\t6.Menu\n\t0.Exit\n");
		printf("\nEnter your choice:");
		scanf("%d",&ch1);
		switch(ch1)
		{	case 1:
				BookVehicle(h);
				system("PAUSE");
				system("CLS");
				break;
			case 2:
				CheckBooking(h);
				system("PAUSE");
				system("CLS");
				break;
			case 3:
				CancelBooking(h);
				system("PAUSE");
				system("CLS");
				break;
			case 4:
				ChangePassword(h);
				system("PAUSE");
				system("CLS");
				break;
			case 5:
				LogoutUser(h);
				system("PAUSE");
				system("CLS");
				break;
			case 6:
				Menu();
				system("PAUSE");
				system("CLS");
				break;
			case 0:
				ExitProgram();
				exit(0);
				break;
			default:
				printf("Not a valid input at this stage\n");
				break;
	    }//switch

	}//elseif
}//while

}

void Menu(){
	system("CLS");
	printf("\n\t\t Road transport \n");
	printf("\n\tVehicleID\t\tno. of seats\tprice\n");
	printf("\t-------------------------------------------------\n");
	printf("\t[M#1]\tMater\t\t2\t\t12000\n\t[$2]\tSally\t\t2\t\t8000\n\t[Lree]\tLuigi\t\t4\t\t12000\n\t[G*4]\tGuido\t\t1\t\t12000\n\t[F5]\tFillmore\t6\t\t15000\n\t[Mc6]\tMack\t\t12\t\t20000\n\n");

}
void BookVehicle(user *h)
{   char choice;
    float price;
    float pricelist[] = {12000.0,8000.0,12000.0,12000.0,15000.0,20000.0};
    user *t = h;
    char VehicleID[100];
    while (h!= NULL)
    {
	if (!strcmp(h->username, currentuser))
	    break;
	h = h->next;
    }
    if (h == NULL)
	return;
    if (h->price != 0.0)
    {
	printf("You must cancel your previous Booking before booking a new one\n");
	return;
    }
    Menu();
    fflush(stdin);
    printf("\nEnter VehicleID (eg: M#1, Mc6)\n");
    scanf(" %[^\n]s", VehicleID);
    fflush(stdin);
    printf("\nWould You Like to Confirm Booking?\n[1] - Yes\n[2] - No\n");
    scanf("%c", &choice);

    if (choice != '1')
	return;
    if (strcmp(VehicleID, "M#1") == 0)
	price = pricelist[0];
    else if (strcmp(VehicleID, "$2") == 0)
	price = pricelist[1];
    else if (strcmp(VehicleID, "Lree") == 0)
	price = pricelist[2];
    else if (strcmp(VehicleID, "G*4") == 0)
	price = pricelist[3];
    else if (strcmp(VehicleID, "F5") == 0)
	price = pricelist[4];
    else if (strcmp(VehicleID, "Mc6") == 0)
	price = pricelist[5];
    else
    {
	printf("That Vehicle ID doesn't exist\n");
	return;
    }
    strcpy(h->VehicleID, VehicleID);
    h->price = price;
    WriteToFile(t);
    printf("Bookings Done!!\n");
    system("PAUSE");
}
user *InitializeList(user *h){
	user *t,*ptr,temp;
	FILE *fp;
	int x;
	float ff;
	fp=fopen("users.txt","r");
	if(fp==NULL)
		return NULL;
	if(fgetc(fp)==EOF)
		return NULL;

	rewind(fp);
	while(fscanf(fp,"%s %s %s %f", temp.username, temp.password, temp.VehicleID, &temp.price)!=EOF)
	{	ptr=(user *)malloc(sizeof(user));
		strcpy(ptr->username,temp.username);
		strcpy(ptr->password,temp.password);
		strcpy(ptr->VehicleID,temp.VehicleID);
		ptr->price=temp.price;
		ptr->next=NULL;
		if(h==NULL)
			h=t=ptr;
		else{
			h->next=ptr;
			h=ptr;
		}
	}
	fclose(fp);
	return t;
}
user *AddUser(user *h)
{   user *nw;
    user *t;
    nw = (user *)malloc(sizeof(user));
    fflush(stdin);
    t=h;
    printf("Enter username or email\n");
    scanf("%s", nw->username);
    while (h != NULL)
    {
	if (!strcmp(h->username, nw->username))
	{
	    printf("That email already exists\n");
	    return t;
	}
	h = h->next;
    }
    h = t;
    fflush(stdin);
    printf("Enter password:\n");
    scanf("%s", &nw->password);
    nw->next = NULL;
    strcpy(nw->VehicleID, "N/A");
    nw->price = 0.0;

    if (h == NULL)
    {
	h = t = nw;
    }
    else
    {
	while (h->next != NULL)
	{
	    h = h->next;
	}
	h->next = nw;
    }
    WriteToFile(t);
    return t;
}
void WriteToFile(user *h)
{
    FILE *fp;
    fp = fopen("users.txt", "w");
    while (h != NULL)
    {
	fprintf(fp, "%s %s %s %f\n", h->username, h->password, h->VehicleID, h->price);
	h = h->next;
    }
    fclose(fp);
}
void CheckBooking(user *h)
{   float total = 0.0;
    while (h != NULL)
    {
	if (!strcmp(h->username, currentuser))
	    break;
	h = h->next;
    }
    if (!strcmp(h->VehicleID, "\0") || h->price == 0.0)
    {
	printf("You did not booked any vehicle yet\n");
	return;
    }

    total = (h->price);
    printf("You have booked %s vehicle for Rs. %f\n", h->VehicleID,total);
}

void LoginUser(user *h)
{
    char username[100];
    char password[100];
    fflush(stdin);
    printf("\n\n");
    printf("\t\tEnter Email/Username:\n\t\t");
    scanf("%s", username);
    fflush(stdin);
    printf("\n\t\tEnter Password:\n\t\t");
    scanf(" %s", password);
    while (h != NULL)
    {
	if ((!strcmp(h->username, username)) && (!strcmp(h->password, password)))
	{
	    currentstate = Login;
	    strcpy(currentuser, username);

	    printf("\n\t\tLogin successful!\n");
	    system("PAUSE");
	    return;
	}
	else if ((!strcmp(h->username, username)) && (strcmp(h->password, password)))
	{
	    printf("Password mismatch\n");
	    return;
	}
	h = h->next;
    }
    printf("Sorry, no such user record was found\n");
}
void CancelBooking(user *h)
{   int flag = -1;
    user *t = h;
    while (h != NULL)
    {
	if (!strcmp(h->username, currentuser))
	    break;
	h = h->next;
    }
    if (h == NULL)
	printf("No such user\n");

    if (strcmp(h->VehicleID, "M#1") == 0)
	flag++;
    else if (strcmp(h->VehicleID, "$2") == 0)
	flag++;
    else if (strcmp(h->VehicleID, "Lree") == 0)
	flag++;
    else if (strcmp(h->VehicleID, "G*4") == 0)
	flag++;
    else if (strcmp(h->VehicleID, "F5") == 0)
	flag++;
    else if (strcmp(h->VehicleID, "Mc6") == 0)
	flag++;
    else
    {
	printf("You haven't booked any Vehicle yet\n");
	return;
    }
    if (flag == 0)
    {
	printf("Your Booking has been successfully cancelled\n");
	strcpy(h->VehicleID, "N/A");
	h->price = 0.0;
	WriteToFile(t);
    }
}


void LogoutUser()
{
    if (currentstate == Home || strcmp(currentuser, "\0") == 0)
    {
	printf("You must be logged in to logout\n");
	return;
    }
    strcpy(currentuser, "\0");
    currentstate = Home;
    printf("You have been successfully logged out\n");
}

void ExitProgram()
{   char exitprog;
    printf("Exiting...\n\nPress \"Enter\" to exit");
    fflush(stdin);
    scanf("%c", &exitprog);
}
void ChangePassword(user *h)
{
    user *t = h;
    char passcurr[100];
    fflush(stdin);
    printf("Enter your current password to continue:\n");
    scanf(" %[^\n]s", passcurr);
    while (h != NULL)
    {
	if (!strcmp(h->username, currentuser))
	    break;
	h = h->next;
    }
    if (h == NULL)
	return;
    if (!strcmp(passcurr, h->password))
    {
	printf("Enter new password:\n");
	scanf(" %[^\n]s", h->password);
    }
    WriteToFile(t);
}


