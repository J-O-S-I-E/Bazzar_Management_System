#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* for toupper function - used to convert characters to upper/lowercase */

#define MAX_CHARS 100
#define NUM_RECORDS_IN_FILE 50
#define DATA_CAPACITY 100
#define entry_cost 20

typedef enum {false,true} boolean;


struct VendorData {
    char vendorID[MAX_CHARS];
    char firstName[MAX_CHARS];
    char lastName[MAX_CHARS];
    char business_name[MAX_CHARS];
    char stall_category[MAX_CHARS];
    char contactNumber[MAX_CHARS];
    int stallID;
    char vendor_password[MAX_CHARS];
};

struct Vendor_Inventory {
    char vendorID[MAX_CHARS];
    int stallID;
    int num_items;
    struct Items {
        char itemName[MAX_CHARS];
    } items[DATA_CAPACITY];
};

struct CustomerData {
    char customerID[MAX_CHARS];
    char firstName[MAX_CHARS];
    char lastName[MAX_CHARS];
    char gender[MAX_CHARS];
    char contactNumber[MAX_CHARS];
    int num_tickets_bought;
    char customer_password[MAX_CHARS];
};

struct VendorData vendor[DATA_CAPACITY];
struct CustomerData customer[DATA_CAPACITY];
struct Vendor_Inventory inventory[DATA_CAPACITY];
int mm_option;

int num_records_vendors;
int num_records_customers;
int num_records_inventory;
int i;
char vendorId[25];
char customerId[25];

void write_in_file() {

    FILE *customerInfoFile= fopen("Customer_Information.txt","w");

    if (customerInfoFile == NULL) {
        exit(1);
    }

    for(i=0; i<num_records_customers; i++) {
        fprintf(customerInfoFile,"%s %s %s %s %s %d %s\n",
                customer[i].customerID,
                customer[i].firstName,
                customer[i].lastName,
                customer[i].gender,
                customer[i].contactNumber,
                customer[i].num_tickets_bought,
                customer[i].customer_password);


    }
    fprintf(customerInfoFile, "XXX");
    while(!(feof(customerInfoFile)));
    fclose(customerInfoFile);

    FILE * vendorInfoFile= fopen("Vendor_Information.txt","w");

    if(vendorInfoFile == NULL) {
        printf("Error");
        exit(1);
    }
    for(i=0; i,num_records_vendors; i++) {
        fprintf(vendorInfoFile,"%s %s %s %s %s %s %d %s\n",
                vendor[i].vendorID,
                vendor[i].firstName,
                vendor[i].lastName,
                vendor[i].business_name,
                vendor[i].stall_category,
                vendor[i].contactNumber,
                vendor[i].stallID,
                vendor[i].vendor_password);
    }
    fprintf(vendorInfoFile,"XXX");
    while(!(feof(vendorInfoFile)));
    fclose(vendorInfoFile);

    FILE * vendorInventFile = fopen("Inventory_Information.txt","w");
    if(vendorInventFile == NULL) {
        printf("Error");
        exit(1);
    }
    int j;
    for(i=0; i<num_records_inventory; i++) {
        fprintf(vendorInventFile,"%s %d %d",
                inventory[i].vendorID,
                inventory[i].stallID,
                inventory[i].num_items);

        for (j=0; j<inventory[i].num_items; j++) {
            fscanf(vendorInventFile, "%s",
                   &inventory[j].items[i].itemName);

        }
        fprintf(vendorInventFile,"\n");
    }
    fprintf(vendorInventFile,"XXX");
    while(!(feof(vendorInventFile)));
    fclose(vendorInventFile);
}

int loadDATA() {

    int i;
    char id1[4];
    char id2[4];
    char id3[4];

    FILE * customerInfoFile = fopen("Customer_Information.txt","r");

    if(customerInfoFile == NULL) {
        printf("Error: Could not find Customer_Information file.\n");
        exit(1);
    }
    fscanf(customerInfoFile,"%s",&id1);

    while( strcmp (id1, "XXX") != 0) {
        strcpy (customer[num_records_customers].customerID, id1);

        fscanf(customerInfoFile, "%s %s %s %s %d %s",
               &customer[num_records_customers].firstName,
               &customer[num_records_customers].lastName,
               &customer[num_records_customers].gender,
               &customer[num_records_customers].contactNumber,
               &customer[num_records_customers].num_tickets_bought,
               &customer[num_records_customers].customer_password);

        num_records_customers++;

        fscanf(customerInfoFile,"%s",&id1);
    }

    fclose(customerInfoFile);

    FILE * vendorInfoFile= fopen("Vendor_Information.txt","r");

    if(vendorInfoFile == NULL) {
        printf("Error");
        exit(1);
    }
    fscanf(vendorInfoFile,"%s",&id2);

    while( strcmp (id2, "XXX") != 0) {

        strcpy (vendor[num_records_vendors].vendorID, id2);

        fscanf(vendorInfoFile,"%s %s %s %s %s %d %s",
               &vendor[num_records_vendors].firstName,
               &vendor[num_records_vendors].lastName,
               &vendor[num_records_vendors].business_name,
               &vendor[num_records_vendors].stall_category,
               &vendor[num_records_vendors].contactNumber,
               &vendor[num_records_vendors].stallID,
               &vendor[num_records_vendors].vendor_password);

        num_records_vendors++;

        fscanf(vendorInfoFile,"%s",&id2);
    }

    fclose(vendorInfoFile);

    FILE * vendorInventFile = fopen("Inventory_Information.txt","r");
    if(vendorInventFile == NULL) {
        printf("Error");
        exit(1);
    }

    fscanf(vendorInventFile,"%s",&id3);

    while( strcmp (id3, "XXX") != 0) {

        strcpy (inventory[num_records_inventory].vendorID, id3);

        fscanf(vendorInventFile,"%d %d",
               &inventory[num_records_inventory].stallID,
               &inventory[num_records_inventory].num_items);

        for (i=0; i<inventory[num_records_inventory].num_items; i++) {
            fscanf(vendorInventFile, "%s",
                   &inventory[num_records_inventory].items[i].itemName);

        }

        num_records_inventory++;
        fscanf(vendorInventFile,"%s",&id3);
    }

    fclose(vendorInventFile);

}


int admin_entry() {
    system("cls");
    char code[25];
    printf("Welcome to the sign in Screen.\nEnter your Credentials\n");
    printf("-----------------------------------\n");
    printf("Please enter password:");
    scanf("%s",&code);
    const char password[8]="abc";

    if (strcmp(code,password)==0 ) {
        printf("\nAccess Granted..........\n");
        system("pause");
        system("cls");
        return 1;
    } else {
        printf("\nAccess Denied...........\n");
        system("pause");
        system("cls");
        return 0;

    }
}

int vendor_entry() {
    int i;
    system("cls");
    char code[25];
    char ID[25];
    printf("Welcome to the sign in Screen.\nEnter your Credentials\n");
    printf("-----------------------------------\n");
    printf("Please enter user ID:");
    scanf("%s",&ID);
    int k;
    for (k = 0; k < strlen(ID); k++) {
        ID[k] = toupper(ID[k]);
    }
    printf("Please enter password:");
    scanf("%s",&code);


    for(i=0; i<num_records_vendors; i++) {
        if((strcmp(ID,vendor[i].vendorID)==0) && (strcmp(code,vendor[i].vendor_password)==0 )) {
            printf("\nAccess Granted..........\n");
            strcpy(vendorId,vendor[i].vendorID);
            return 1;
        }
    }
    if (i == num_records_vendors) {
        printf("\nAccess Denied...........\n");
        return 0;
    }
}

int customer_entry() {
    int i;
    system("cls");
    char code[25];
    char ID[25];
    printf("Welcome to the sign in Screen.\nEnter your Credentials\n");
    printf("-----------------------------------\n");
    printf("Please enter user ID:");
    scanf("%s",&ID);
    int k;
    for (k = 0; k < strlen(ID); k++) {
        ID[k] = toupper(ID[k]);
    }
    printf("Please enter password:");
    scanf("%s",&code);

    for(i=0; i<num_records_customers; i++) {
        printf("%s %s - %s %s\n", ID,customer[i].customerID,code,customer[i].customer_password );
        if((strcmp(ID,customer[i].customerID)==0) && (strcmp(code,customer[i].customer_password)==0 )) {
            printf("\nAccess Granted..........\n");
            strcpy(customerId,customer[i].customerID);
            return 1;
        }
    }
    if (i == num_records_customers) {
        printf("\nAccess Denied...........\n");
        return 0;
    }
}

void exit_message() {
    system("cls");
    printf("\n********EXIT THE PROGRAM********");
    printf("\n--------------------------------");
    printf("\nTHANK YOU FOR USING THE SYSTEM!\n\nHOPE TO SEE YOU THERE ^-^");
    printf("\n--------------------------------\n");
    write_in_file();
    system("pause");
    exit(1);

}
int add_vendor() {

    printf("\n--------NEW USER REGISTRATION-------");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\tVendor Personal Information\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Vendor ID: ");
    scanf("%s",&vendor[num_records_vendors].vendorID);
    //printf("%s %s", vendor[i].vendorID, vendor[i-1].vendorID);
    printf("\nFirst Name: ");
    scanf("%s",&vendor[num_records_vendors].firstName);
    printf("\n Last name: ");
    scanf("%s",&vendor[num_records_vendors].lastName);
    printf("\nBusiness Name: ");
    scanf("%s",&vendor[num_records_vendors].business_name);
    printf("\nContact Number: ");
    scanf("%s",&vendor[num_records_vendors].contactNumber);
    printf("\nPassword: ");
    scanf("%s",&vendor[num_records_vendors].vendor_password);

    printf("\n~~~~~~~~~~~~Stall Information~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Stall Category: ");
    scanf("%s",&vendor[num_records_vendors].stall_category);
    printf("\nStall ID: ");
    scanf("%d",&vendor[num_records_vendors].stallID);

    num_records_vendors++;


//Fix this part. You don't need a loop.

        strcpy(inventory[num_records_inventory].vendorID,vendor[num_records_vendors].vendorID);
        inventory[num_records_inventory].stallID=vendor[num_records_vendors].stallID;
        inventory[num_records_inventory].num_items=0;
        strcpy(vendorId,vendor[num_records_vendors].vendorID);

        num_records_inventory++;

    return 1;
}
int add_customer() {


    //for(i=num_records_customers;i<num_records_customers+1;i++)

    printf("\n--------NEW USER REGISTRATION--------\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nCustomer Personal Information\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("Customer ID: ");
    scanf("%s",&customer[num_records_customers].customerID);
    printf("\nFirst Name: ");
    scanf("%s",&customer[num_records_customers].firstName);
    printf("\nLast Name: ");
    scanf("%s",&customer[num_records_customers].lastName);
    printf("\nGender: ");
    scanf("%s",&customer[num_records_customers].gender);
    printf("\nContact Number: ");
    scanf("%s",&customer[num_records_customers].contactNumber);
    printf("\nPassword: ");
    scanf("%s",&customer[num_records_customers].customer_password);

    customer[num_records_customers].num_tickets_bought=0;
    strcpy(customerId,customer[i].customerID);

    num_records_customers++;
    return 1;
}

void edit_record(int mm_option) {
    system("cls");
    if (mm_option==2) {
        for(i=0; i<num_records_customers; i++) {
            if((strcmp(customerId,customer[i].customerID))==0) {
                printf("\n\n-----ARE YOU SURE YOU WANT TO EDIT THIS RECORD-----\n");
                char ans;
                printf("\t-----PPLEASE ENTER YOUR ANSWER-----\nY - YES\t\t N - NO\nChoice =  ");
                fflush(stdin);
                scanf("%c",&ans);

                if(ans == 'y' || ans == 'Y') {

                    printf("\n**********EDIT CUSTOMER RECORDS**********");
                    printf("\n-----------------------------------------\n");
                    printf("First Name: ");
                    scanf("%s",&customer[i].firstName);
                    printf("\nLast Name: ");
                    scanf("%s", &customer[i].lastName);
                    printf("\nGender: ");
                    scanf("%s",&customer[i].gender);
                    printf("\nContact Number: ");
                    scanf("%s",&customer[i].contactNumber);

                    printf("\n\nConfirmed Editing\n\n");
                    system("pause");
                    system("cls");
                } else {
                    printf("\n\n---->Route back to Your Main Menu<----");
                    system("pause");
                    system("cls");
                }


            }
        }
    } else if (mm_option==3) {

        for(i=0; i<num_records_vendors; i++) {
            if((strcmp(vendorId,vendor[i].vendorID))==0) {
                printf("\n\n-----ARE YOU SURE YOU WANT TO EDIT THIS RECORD-----\n");
                char ans;
                printf("\t-----PPLEASE ENTER YOUR ANSWER-----\nY - YES\t\t N - NO\nChoice =  ");
                fflush(stdin);
                scanf("%c",&ans);

                if(ans == 'y' || ans == 'Y') {
                    printf("\n**********EDIT VENDOR RECORDS**********");
                    printf("\n---------------------------------------\n");
                    printf("First Name: ");
                    scanf("%s",vendor[i].firstName);
                    printf("\nLast Name: ");
                    scanf("%s",vendor[i].lastName);
                    printf("\nContact Number: ");
                    scanf("%s",vendor[i].contactNumber);
                    printf("\nBusiness Name: ");
                    scanf("%s",vendor[i].business_name);

                    printf("\n\nConfirmed Editing\n\n");
                    system("pause");
                    system("cls");

                } else {
                    printf("\n\n---->Route back to Your Main Menu<----");
                    system("pause");
                    system("cls");
                }
            }
        }

    }
}

void customer_delete(int mm_option) {
    if (mm_option==1) {

        printf("Enter Customer ID to View : ");
        scanf("%s",&customerId);

        int k;
        for (k = 0; k < strlen(customerId); k++) {
            customerId[k] = toupper(customerId[k]);
        }
    }

    for(i=0; i<num_records_customers; i++) {
        if((strcmp(customerId,customer[i].customerID)==0) ) {
            printf("\n----------------------------------------------------------------------------");
            printf("\nCustomer Information");
            printf("\n----------------------------------------------------------------------------");
            printf("\nName of Customer: %s %s",customer[i].firstName,customer[i].lastName);
            printf("\nGender: %s",customer[i].gender);
            printf("\nContact Number: %s",customer[i].contactNumber);
            printf("\nTickets Purchased: %d",customer[i].num_tickets_bought);
            printf("\n----------------------------------------------------------------------------");

            printf("\n\n-----ARE YOU SURE YOU WANT TO DELETE THIS RECORD-----\n");
            char ans;
            printf("-----PPLEASE ENTER YOUR ANSWER-----\n Y - YES\t\t N - NO\nChoice =  ");
            fflush(stdin);
            scanf("%c",&ans);

            if(ans == 'y' || ans == 'Y') {
                printf("No problem, This record shall me deleted for you.");

                if(i == num_records_customers-1) {
                    num_records_customers--;
                } else {
                    int t;
                    for(t=i; t<num_records_customers-1; t++) {
                        struct CustomerData temp;

                        temp=customer[t];
                        customer[t]=customer[t+1];
                        temp=customer[t];
                    }
                    num_records_customers--;
                }

            } else {
                printf("\n\n---->Route back to Your Main Menu<----");
            }
        }
    }
}


void vendor_delete(int mm_option) {

    if (mm_option==1 || mm_option==2) {
        printf("Enter Vender ID to View : ");
        scanf("%s",&vendorId);

        int k;
        for (k = 0; k < strlen(vendorId); k++) {
            vendorId[k] = toupper(vendorId[k]);
        }
    }
    for(i=0; i<num_records_vendors; i++) {
        if((strcmp(vendorId,vendor[i].vendorID)==0) ) {
            printf("\n----------------------------------------------------------------------------");
            printf("\nVendor Information");
            printf("\n----------------------------------------------------------------------------");
            printf("\nName of Vendor: %s %s",vendor[i].firstName,vendor[i].lastName);
            printf("\nName of Business: %s",vendor[i].business_name);
            printf("\nContact Number: %s",vendor[i].contactNumber);
            printf("\nStall ID: %d",vendor[i].stallID);
            printf("\nStall category: %s",vendor[i].stall_category);
            printf("\n----------------------------------------------------------------------------");

            printf("\n\n-----ARE YOU SURE YOU WANT TO DELETE THIS RECORD-----\n\tYOUR INVENTORY WILL ALSO BE DELETED");
            char ans;
            printf("\n-----PPLEASE ENTER YOUR ANSWER-----\n Y - YES\t\t N - NO\nChoice =  ");
            fflush(stdin);
            scanf("%c",&ans);

            if(ans == 'y' || ans == 'Y') {
                printf("No problem, This record shall me deleted for you.");
                if(i == num_records_vendors-1) {
                    num_records_vendors--;
                } else {
                    int t;
                    for(t=i; t<num_records_vendors-1; t++) {
                        struct VendorData temp;

                        temp=vendor[t];
                        vendor[t]=vendor[t+1];
                        temp=vendor[t];
                    }
                }
                num_records_vendors--;
                int s;
                for (s=0; s<num_records_inventory; s++) {
                    if((strcmp(vendorId,inventory[i].vendorID)==0) ) {
                        if(s==num_records_inventory-1) {
                            num_records_inventory--;
                        } else {
                            struct Vendor_Inventory temp1;

                            temp1=inventory[s];
                            inventory[s]=inventory[s+1];
                            temp1=inventory[s];
                        }
                    }
                    num_records_inventory--;
                }

            }
        }
    }
}

int admin_menu() {

    int choice;

    printf("\n---------------------------------------------");
    printf("\n~~~~~~~~~WELCOME TO ADMIN MAIN MENU~~~~~~~~~~");
    printf("\n---------------------------------------------");

    printf("\n\t 1 - View Customer Records");              /* < func. req # */
    printf("\n\t 2 - View Vendor Records");          /* < func. req # */
    printf("\n\t 3 - View Ticket Sales");    /* < func. req # */
    printf("\n\t 4 - View Vendors Inventories");            /* < func. req # */
    printf("\n\t 5 - Sort Customer Records");    /* < func. req # */
    printf("\n\t 6 - Delete Customer Records");
    printf("\n\t 7 - Sort Vendor Records");    /* < func. req # */
    printf("\n\t 8 - Delete Vendor Records");            /* < func. req # */
    printf("\n\t 9 - Exit System");

    printf("\n\nOption: ");
    fflush(stdin);
    scanf("%d",&choice);
    return choice;
}

int vendor_menu() {
    int choice;

    printf("\n--------------------------------------------");
    printf("\n~~~~~~~~~WELCOME TO VENDOR MAIN MENU~~~~~~~~~");
    printf("\n---------------------------------------------");

    printf("\n\t 1 - Add to Your Inventory");          /* < func. req # */
    printf("\n\t 2 - View Your Inventories");            /* < func. req # */
    printf("\n\t 3 - View Your Personal Information");            /* < func. req # */
    printf("\n\t 4 - Edit Your Personal Information");
    printf("\n\t 5 - Delete Your Information");
    printf("\n\t 6 - Exit System");

    printf("\n\nOption: ");
    scanf("%d",&choice);
    return choice;
}

int customer_menu() {
    int choice;

    printf("\n-------------------------------------------------");
    printf("\n~~~~~~~~~WELCOME TO CUSTOMERS MAIN MENU~~~~~~~~~~");
    printf("\n-------------------------------------------------");

    printf("\n\t 1 - View Your Personal Information");
    printf("\n\t 2 - Purchase A Ticket");   /* < func. req # */
    printf("\n\t 3 - View Vendors Records");
    printf("\n\t 4 - Edit Your Personal Information");
    printf("\n\t 5 - Delete Your Information");
    printf("\n\t 6 - Exit System");

    printf("\n\nOption: ");
    scanf("%d",&choice);
    return choice;
}

void customer_records(int mm_option) {

    int i;

    if (mm_option==1) {

        system("cls");
        printf("Enter Customer ID to View : ");
        scanf("%s",&customerId);

        int k;
        for (k = 0; k < strlen(customerId); k++) {
            customerId[k] = toupper(customerId[k]);
        }
    }

    for(i=0; i<num_records_customers; i++) {
        if((strcmp(customerId,customer[i].customerID)==0) ) {
            printf("\n----------------------------------------------------------------------------");
            printf("\nCustomer Information");
            printf("\n----------------------------------------------------------------------------");
            printf("\nName of Customer: %s %s",customer[i].firstName,customer[i].lastName);
            printf("\nGender: %s",customer[i].gender);
            printf("\nContact Number: %s",customer[i].contactNumber);
            printf("\nTickets Purchased: %d",customer[i].num_tickets_bought);
            printf("\n----------------------------------------------------------------------------\n\n");
            system("pause");
            system("cls");

        }
    }

}

void vendor_records(int mm_option) {

    if (mm_option==1 || mm_option==2) {
        system("cls");
        printf("Enter Vender ID to View : ");
        scanf("%s",&vendorId);

        int k;
        for (k = 0; k < strlen(vendorId); k++) {
            vendorId[k] = toupper(vendorId[k]);
        }
    }

    for(i=0; i<num_records_vendors; i++) {
        if((strcmp(vendorId,vendor[i].vendorID)==0) ) {
            printf("\n----------------------------------------------------------------------------");
            printf("\nVendor Information");
            printf("\n----------------------------------------------------------------------------");
            printf("\nName of Vendor: %s %s",vendor[i].firstName,vendor[i].lastName);
            printf("\nName of Business: %s",vendor[i].business_name);
            printf("\nContact Number: %s",vendor[i].contactNumber);
            printf("\nStall ID: %d",vendor[i].stallID);
            printf("\nStall Category: %s",vendor[i].stall_category);
            printf("\n----------------------------------------------------------------------------\n\n");
            system("pause");
            system("cls");



        }
    }
}

void purchase_ticket() {
    system("cls");
    int tickets;

    for(i=0; i<num_records_customers; i++) {
        if((strcmp(customerId,customer[i].customerID)==0) ) {
            printf("\n------------------------------------------");
            printf("\n\t\tTICKET");
            printf("\n\t   Christmas Bazaar");
            printf("\n------------------------------------------");
            printf("\n\n\nVenue: Holy Name Convent, Port of Spain");
            printf("\nDate of Event: Saturday 5th November,2023");
            printf("\nTime of Event: 12pm to 6pm");
            printf("\nAdmission Cost: $20");
            printf("\n------------------------------------------");
            printf("\nEnter the Number of Tickets: ");
            scanf("%d",&tickets);
            printf("\nCharges: %d",tickets*entry_cost);
            printf("\n\n------------------------------------------");
            printf("\nConfirm Ticket");
            printf("\n------------------------------------------");


            printf("\n\nFree Secured Parking Available\n SEE YOU THERE :)");

            customer[i].num_tickets_bought=tickets;

        }
    }
}

void ticket_sales() {

    int total=0;
    system("cls");

    printf("\t   __________ Total Ticket Sales____________\n");
    printf("\nCustomer ID\t Customer Name\t\t Purchased Tickets\tCost");
    for(i=0; i<num_records_customers; i++) {

        printf("\n    %-3s \t %-11s %-10s \t %d \t\t %-8d",
               customer[i].customerID,
               customer[i].firstName,
               customer[i].lastName,
               customer[i].num_tickets_bought,
               customer[i].num_tickets_bought*entry_cost);

        total=total+(customer[i].num_tickets_bought*entry_cost);

    }
    printf("\n\n\n\t\t\t\t\t\t\t\tTotal Cost");
    printf("\n\n\t\t\t\t\t\t\t\t%d\n\n",total);
    system("pause");
    system("cls");

}

void customer_sort() {
    int j;
    struct CustomerData temp;

    boolean somethingSwapped;
    system("cls");

    for (i=0; i<num_records_customers; i++) {
        somethingSwapped = false;
        for(j=0; j<num_records_customers-1-i; j++) {
            if((strcmp(customer[j].customerID,customer[j+1].customerID)>0)) {
                temp = customer[j];
                customer[j] = customer[j+1];
                customer[j+1] = temp;
                somethingSwapped=true;
            }
        }
        if(somethingSwapped==false) {
            break;
        }
    }


    printf("\t\t   __________ Sorted Customer Records____________\n\n");
    printf("\nCustomer ID\t Customer Name \t\tGender \t\tContact \tPurchased Tickets");

    for(i=0; i<num_records_customers; i++) {
        printf("\n%-8s       %-10s  %-10s   %-13s %-25s %-d",
               customer[i].customerID,
               customer[i].firstName,
               customer[i].lastName,
               customer[i].gender,
               customer[i].contactNumber,
               customer[i].num_tickets_bought);
    }
    printf("\n\n\n");
    system("pause");
    system("cls");
}

void vendor_sort() {
    int j;
    struct VendorData temp;
    boolean somethingSwapped;
    system("cls");

    for (i=0; i<num_records_vendors; i++) {
        somethingSwapped = false;
        for(j=1; j<num_records_vendors-i-1; j++) {
            if((strcmp(vendor[j].vendorID,vendor[j+1].vendorID)>0)) {
                temp=vendor[j];
                vendor[j]=vendor[j+1];
                vendor[j+1]=temp;
                somethingSwapped=true;
            }
        }
        if(somethingSwapped==false) {
            break;
        }
    }
    printf("\t\t\t__________ Sorted Vendor Records____________\n\n");
    printf("\nVendor ID\t Vendor Name \t\tBusiness name    \tStall Category \t\tStall ID");

    for(i=0; i<num_records_vendors; i++) {
        printf("\n%-8s         %-9s %-12s %-17s \t%-25s %-d",
               vendor[i].vendorID,
               vendor[i].firstName,
               vendor[i].lastName,
               vendor[i].business_name,
               vendor[i].stall_category,
               vendor[i].stallID);
    }
    printf("\n\n\n");
    system("pause");
    system("cls");
}

void add_invent() {

    int amount,j;
    for (i=0; i<num_records_inventory; i++) {

        if((strcmp(vendorId,inventory[i].vendorID)==0) ) {
            printf("-----------------------------------------------------------");
            printf("\n```````````````````ADD TO YOUR INVENTORY```````````````````");
            printf("\n-----------------------------------------------------------");
            printf("\nEnter the number of items to add to your inventory.\n\nAmount:");
            scanf("%d",&amount);

            inventory[i].num_items=inventory[i].num_items+amount;
            printf("\n\nEnter the name of the items:");

            for (j=0; j<amount; j++) {
                scanf("\n%s",&inventory[i].items[inventory[i].num_items-j].itemName);
            }
        }
        printf("\nAll Items are entered!! ^-^");
        system("pause");
        system("cls");
    }

}

void view_inventories() {
    int i, j,k;
    system("cls");
    printf("\t__________ Vendor Inventories____________\n\n");
    printf("\nVendor_ID   Business_Name   Stall_Category    Stall_ID    Inventory_Items");

    for(k=0; k<num_records_vendors; k++) {
        {
            for (i=0; i<num_records_inventory; i++)
                if(strcmp(inventory[i].vendorID,vendor[k].vendorID)==0) {
                    printf("\n   %-3s \t    %-14s  %-21s %d",
                           inventory[i].vendorID,
                           vendor[k].business_name,
                           vendor[k].stall_category,
                           inventory[i].stallID);

                    for (j=0; j<inventory[i].num_items; j++) {
                        if (j == 0) {
                            printf("\t      %s\n", inventory[i].items[j].itemName);
                        } else {
                            printf("\t\t\t\t\t\t\t      %s\n", inventory[i].items[j].itemName);
                        }

                    }
                }

        }


    }
    system("pause");
    system("cls");
}

void your_invent(char vendorId[]) {

    int j;
    printf("\t\t\t__________ Your Vendor Inventory____________\n\n");
    printf("\nVendor_ID   Business_Name   Stall_Category    Stall_ID    Inventory_Items");

    for (i=0; i<num_records_inventory; i++) {
        if((strcmp(vendorId,vendor[i].vendorID)==0) ) {
            printf("\n   %-3s \t    %-14s  %-21s %d",
                   inventory[i].vendorID,
                   vendor[i].business_name,
                   vendor[i].stall_category,
                   inventory[i].stallID);

            for (j=0; j<inventory[i].num_items; j++) {
                if (j == 0)
                    printf("\t      %s\n", inventory[i].items[j].itemName);
                else
                    printf("\t\t\t\t\t\t\t      %s\n", inventory[i].items[j].itemName);

            }
        }
    }
}

void handle_Admin() {

    int temp;
    int flag;

    if (admin_entry()!=1) {
        printf("Incorrect password... returning to root menu.\n");
        system("pause");
        system("cls");
    } else {
        flag=1;
        while (flag==1) {

            temp = admin_menu();

            switch(temp) {
            case 1:
                customer_records(1);       //1 for admin 0 otherwise

                break;
            case 2:
                vendor_records(1); //1 for admin 0 otherwise
                break;
            case 3:
                ticket_sales();
                break;
            case 4:
                view_inventories();
                break;
            case 5:
                customer_sort();
                break;
            case 6:
                customer_delete(1);
                break;
            case 7:
                vendor_sort();
                break;
            case 8:
                vendor_delete(1);
                break;
            case 9:
                exit_message();
            default:
                printf("\nYou did not enter an option that can be processed.\n"
                       "Returning to the previous menu...");
                system("pause");
                system("cls");
                flag = 0;
            }
        }
    }

}

void handle_Customer() {
    int user_type;

    printf("\n~~~~~~~------------------------------~~~~~~~");
    printf("\n~~~~~~~~~~~~~~Christmas Bazaar~~~~~~~~~~~~~~");
    printf("\n~~~~~~~------------------------------~~~~~~~");
    printf("\nVenue: Holy Name Convent, Port of Spain");
    printf("\nDate of Event: Saturday 5th November, 2023");
    printf("\nTime of Event: 12pm to 6pm");
    printf("\n~~~~~~~------------------------------~~~~~~~");
    printf("\n\n Select User Type");
    printf("\n\t 1 - New Customer");
    printf("\n\t 2 - Existing Customer");
    printf("\n\t 9 - Exit");
    printf("\n\nOption: ");

    scanf("%d",&user_type);

    int flag;

    if (user_type==9) {
        exit_message();
    }
    if (user_type==1) {
        if(add_customer()==1) {
            if (customer_entry()==1) {
                flag=2;
            } else {
                printf("Invalid Optiond Entered...............\n");
                system("pause");
                system("cls");
                handle_Customer();
            }
        }
    } else if (user_type==2) {
        if (customer_entry()==1) {
            flag=2;
        } else {
            printf("Invalid Option Entered...............\n");
            system("pause");
            system("cls");
            handle_Customer();
        }
    } else {
        printf("Invalid Option Entered...............\n");
        system("pause");
        system("cls");
        handle_Customer();
    }

    while (flag=2) {
        int temp=customer_menu();
        switch(temp) {
        case 1:
            customer_records(2);
            break;
        case 2:
            purchase_ticket();
            break;
        case 3:
            vendor_records(2);
            break;
        case 4:
            edit_record(2);
            break;
        case 5:
            customer_delete(2);
            break;
        case 6:
            exit_message();
        default:
            printf("You did not enter an option that can be processed.\n"
                   "Returning to the previous menu...");
            flag = 0;
        }
    }

}

void handle_Vendor() {
    int flag;
    int user_type;

    printf("\n~~~~~~~------------------------------~~~~~~~");
    printf("\n~~~~~~~~~~~~~~Christmas Bazaar~~~~~~~~~~~~~~");
    printf("\n~~~~~~~------------------------------~~~~~~~");
    printf("\nVenue: Holy Name Convent, Port of Spain");
    printf("\nDate of Event: Saturday 5th November, 2023");
    printf("\nTime of Event: 12pm to 6pm");
    printf("\n~~~~~~~------------------------------~~~~~~~");
    printf("\n\n\tSelect User Type");
    printf("\n\t 1 - New Vendor");
    printf("\n\t 2 - Existing Vendor");
    printf("\n\t 9 - Exit");
    printf("\n\nOption: ");

    scanf("%d",&user_type);

    if (user_type==9) {
        exit_message();
    }
    if (user_type==1) {
        if (add_vendor()==1) {
            if (vendor_entry()==1) {
                flag=3;
            } else {
                printf("Invalid Option Entered...............\n");
                system("pause");
                system("cls");
                handle_Vendor();
            }

        } else {
            printf("Invalid Option Entered...............\n");
            system("pause");
            system("cls");
            handle_Customer();
        }
    } else if (user_type==2) {
        if (vendor_entry()==1) {
            flag=3;
        } else {
            printf("Invalid Option Entered...............\n");
            system("pause");
            system("cls");
            handle_Vendor();
        }
    } else {
        printf("Invalid Option Entered...............\n");
        system("pause");
        system("cls");
        handle_Customer();
    }
    while(flag==3) {
        int temp=vendor_menu();
        switch(temp) {
        case 1:
            add_invent();
            break;
        case 2:
            your_invent(vendorId);
            break;
        case 3:
            vendor_records(3);
            break;
        case 4:
            edit_record(3);
            break;
        case 5:
            vendor_delete(3);
        case 6:
            exit_message();
        default:
            printf("You did not enter an option that can be processed.\n"
                   "Returning to the previous menu...");
            flag = 0;
        }
    }

}


int main () {

    num_records_customers = 0;
    num_records_vendors = 0;
    num_records_inventory = 0;
    loadDATA();



    int mm_option;

    while (mm_option != 9) {
        if (mm_option == 1) {
            handle_Admin();
        } else if (mm_option == 2) {
            handle_Customer();
        } else if (mm_option == 3) {
            handle_Vendor();
        }
        printf("\n~~~~~~~------------------------------~~~~~~~");
        printf("\n~~~~~~~~~~~~~~Christmas Bazaar~~~~~~~~~~~~~~");
        printf("\n~~~~~~~------------------------------~~~~~~~");
        printf("\nVenue: Holy Name Convent, Port of Spain");
        printf("\nDate of Event: Saturday 5th November, 2023");
        printf("\nTime of Event: 12pm to 6pm");
        printf("\n~~~~~~~------------------------------~~~~~~~");
        printf("\n\n\tSelect User Type");
        printf("\n\t 1 - Admin");
        printf("\n\t 2 - Customer");   /* < func. req # */
        printf("\n\t 3 - Vendor");
        printf("\n\t 9 - Exit");

        printf("\n\nOption: ");
        scanf("%d",&mm_option);
    }

    if (mm_option == 9) {
        exit_message();
    }

    return 0;
}

