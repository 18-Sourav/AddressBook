#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "contact.h"
#include "file.h"
#include "populate.h"

void displayall(AddressBook *addressBook) // List all the contacts
{
    printf("-----------------------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-25s\n", 
           "Index", "Name", "Phone Number", "Email-id");
    printf("-----------------------------------------------------------------------------\n");

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-25s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("-----------------------------------------------------------------------------\n");
}
void displaycontact(Contact *contact, int i)
{
    printf("| %-5d | %-20s | %-15s | %-25s |\n",
           i + 1,
           contact->name,
           contact->phone,
           contact->email);
}

/* writing three different types of comparator function based on the type of data that needs to be compared
 so that only one type of sorting fuctions works for all the type of sorting fields */

int contactbyname(Contact * a,Contact * b)// this is the comparator which is called when we are sorting by name.
{                                         // It takes two contact pointers and compares the names and return the value.
    return strcmp(a->name,b->name);
}
int contactbyphone(Contact * a,Contact * b)// this is the comparator which is called when we are sorting by phone.
{                                          // it compares two phone numbers using the contact pointer directly.
    return strcmp(a->phone,b->phone);
}
int contactbyemail(Contact * a,Contact * b)//this is the comparator which is called when we are sorting by email.
{                                          // it comapres two email id using the contact pointers directly.
    return strcmp(a->email,b->email);
}


void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    int option;
        
    printf("Sort the contcts based on \n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email.id\n");
    scanf("%d",&option); // Taking the input of sorting criteria

    // Now we are calling the sorting fuction with a comparator fuction based on the typr of the sorting criteria
    switch (option)
    {
        case 1: bubble_sort(addressBook, contactbyname);
                displayall(addressBook); // we call the contactbyname comparator soo we pass the address of the comparator function in the sorting call
                break;
        case 2: bubble_sort(addressBook, contactbyphone);
                displayall(addressBook); //we call the contactbyphone comparator soo we pass the address of the comparator function in the sorting call
                break;
        case 3: bubble_sort(addressBook, contactbyemail); // we call the contactbyemail comparator soo we pass the address of the comparator function in the sorting call
                displayall(addressBook);
                break;  
        default: printf("Enter correct option\n");                      
    }
}
void bubble_sort(AddressBook *addressBook, int (*cmp)(Contact *,Contact *))// in sorting we are having addressbook pointer and ""function pointer" which returns an int value
{                                                                         // we take two Contact pointers as input to the function pointer and compare the required type pf data
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (cmp(&addressBook->contacts[j],&addressBook->contacts[j+1])>0)// here we are doing function call and passing the address of the two contacts whose
            {                                                            // comparison needs to be done and if it is giving positive then swapping will be done
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            } 
        }
    }                                                                   
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int numbervalid(AddressBook *addressBook, char *phone) // Function to validate the entered phone number 
{
    // Checking the phone number is digits and having length 10
    int count=0, flag=0;
    for(int k=0;phone[k];k++)
    {
        if(phone[k]>='0' && phone[k] <='9')
            count++;
        else{    
            flag=1;
            break;
        }

    }
    // Checking for duplicate number
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0){// Checking if entered number already exists in addressbook or not
            flag=1;
            break;
        }

    }
    if(count!=10 || flag==1) 
        return 0; // Entered number is notcorrect 
    else
        return 1; // Entered number is correct
}
int emailvalid(AddressBook *addressBook, char *email)
{
    int at_index = -1;
    int dot_index = -1;
    int at_count = 0;
    int dot_count = 0;

    for(int i = 0; email[i]; i++)
    {
        if(email[i] == '@')
        {
            at_index = i; // storing the count of '@'
            at_count++;  // counting the count of the '@'
        }
        else if(email[i] == '.')
        {
            dot_index = i; // storing the index of '.'
            dot_count++;  // counting the occurence if '.'
        }
    }

    // Structure validation first

    if(at_count != 1) // more than one '@' is present
        return 0;

    if(dot_count != 1) // more than one "." is present
        return 0;

    if(at_index > dot_index) // "@" is coming after "."
        return 0;

    if(at_index == 0) // email starts with "@"
        return 0;

    if(dot_index - at_index <= 1) // No character in btwn "@" and "."
        return 0;

    if(email[dot_index + 1] == '\0') // No character after "."
        return 0;

    // Duplicate check after structure is valid
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, email) == 0)
            return 0;
    }

    return 1; // Valid Email 
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    char names[50],phonee[20],emaill[50];
    getchar(); 
    printf("Enter the contact name\n");
    scanf("%49[^\n]",names);
    strcpy(addressBook->contacts[addressBook->contactCount].name,names);
    getchar();
    
    while(1)
    {
        printf("Enter the contact phone number\n");
        
        scanf("%19[^\n]",phonee);
        getchar();
        // number validation funtion
        int valid= numbervalid(addressBook,phonee);
        if(valid)
        {
            printf("Entered number is correct\n");
            break;
        }
        printf("Please enter the correct number\n");
    }    
    
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phonee); // Copying the phone number to the database
    

    while(1)
    {
        printf("Enter the contact's email-id\n");
        
        scanf("%49[^\n]",emaill); // Taking the emmail input from the user
        getchar();

        //email validation
        int valid = emailvalid(addressBook,emaill);
            if(valid)
            {
                printf("Entered Email is correct \n");
                break;
            }
        printf("Entered email id is incorrect\n");    
        printf("Re-enter your email-id ");
    }        


    strcpy(addressBook->contacts[addressBook->contactCount].email,emaill); // Copying the email to the database

    addressBook->contactCount++;// updating the total count of the contacts

    // Displaying the created contact with all the details and current index
    displaycontact(&addressBook->contacts[addressBook->contactCount-1],addressBook->contactCount-1);
    
}
int searchContact(AddressBook *addressBook , int *index) 
{
    /* Define the logic for search */
    
    int flag=0,num;
    char element[50];
    getchar();// clearing the input buffer

    while(1)
    {
        printf("Enter the field you want to search\n 1.Name\n 2.Phone Number\n 3.Email\n");
        scanf("%d",&num);
        getchar();   // clear newline from the input buffer

        if(num > 0 && num <= 3) // Entered the correct input
            break;

        printf("Enter the correct choice\n");
    }
    switch(num)
    {
        case 1: printf("Enter the Contact name you want to search\n"); // Searching wrt name
                scanf("%49[^\n]",element);
                break;
        case 2: printf("Enter the Phone number you want to search\n"); // Searching wrt phone number
                scanf("%49[^\n]",element);
                break; 
        case 3: printf("Enter the Contact Email you want to search\n"); // Searching wrt email
                scanf("%49[^\n]",element);
                break;                       
    }
  
    
    for( int i=0;i<addressBook->contactCount;i++) // Running the loop in the entire addressbook
    {

        if(element[0]>='0'&& element[0]<='9') // searching based on phone number
        {
            if(strstr(addressBook->contacts[i].phone,element)) // comparing the searched phone number with the database phone number
            {
                
                if(flag==0)// So that only first itme this is printed that to when atleast one contact is matched
                {
                    printf("------------- -------------  -----------\n");
                    printf("Index\tName\t        Phone Number    Email-id\t\t\n");
                } 
                flag=1; // atleast one contact is found
                index[i] = 1; // making the same index as 1 in the array

                displaycontact(&addressBook->contacts[i],i); //print along with the index
               
               
                
            }
        }
        else if(strstr(addressBook->contacts[i].name,element) || strstr(addressBook->contacts[i].email,element))
        {
           
                if(flag==0)// So that only first itme this is printed that to when atleast one contact is matched
                {
                    printf("------------- -------------  -----------\n");
                    printf("Index\tName\t        Phone Number    Email-id\t\t\n");
                } 
                flag=1; // atleast one contact is found  
                index[i] = 1; // setting the index in the index array for modification

                displaycontact(&addressBook->contacts[i],i); //print along with the index
                           
        } 
       
    }
    return flag; // This will tell us that if atleast one contact was matched or not  
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    char newentry[50]; // To take input for data modification
    int index[50]; // array for storing the searched result
    int *ptr=index; // pointer for function call
    int entry,i;
    
    int res = searchContact(addressBook,ptr); // seaching the element to edit

    if(res) // to check for atleast one search result is found
    {
        while(1)
        {
            printf("Enter the index you want to edit\n");
            scanf("%d",&i);
            if((i > 0 && i <=addressBook->contactCount && ptr[i] == 1)) // checking if the entered index is matching the search results
            break;
            printf("Entered index is incorrect \n");
        } 
    }
    else
        printf("Entered data could not be found in the addressbook\n"); // if no search result is found 
    
    // Asking the field for edit     
    while(1)
    {
        printf("\nEnter the field you want to edit, Enter (1,2,3) \n 1. Name\n 2.Phone\n 3.Email\n");
        scanf("%d",&entry);
        getchar();
        
        if((i > 0 && i <=addressBook->contactCount && index[i] == 1)) // checking if the entered index is matching the search results i.e index value is 1 in the search array
          break;
        printf("Entered index is incorrect \n");
    }

    // Asking user to enter the new data for modification
    printf("Enter the new data to be entered\n");
    scanf("%49[^\n]",newentry);
    switch(entry)
    {
         case 1:printf("Enter the new name to be saved\n"); // To modify the name of a contact
                scanf("%49[^\n]",newentry);
                strcpy(addressBook->contacts[i-1].name,newentry);
                printf("Name updated sucessfully\n");
                break;
         
         case 2:printf("Enter the new Phone Number to be saved\n"); // To modify the phone number of a contact
                scanf("%49[^\n]",newentry);
                strcpy(addressBook->contacts[i-1].phone,newentry);
                printf("Phone updated sucessfully\n");
                break;
         
         case 3:printf("Enter the new email to be saved\n"); // To modify the email of a contact
                scanf("%49[^\n]",newentry);
                strcpy(addressBook->contacts[i-1].email,newentry);
                printf("Email updated sucessfully\n");
                break;
    }    
}

void deleteContact(AddressBook *addressBook)
{
    int index[50];
    int i;
    
    int res = searchContact(addressBook, index);

    if(res)
    {
        while(1)
        {
            printf("Enter the index you want to delete:\n");
            scanf("%d", &i);
            i--;

            if(i >= 0 && i < addressBook->contactCount && index[i] == 1) // Checking the index and search result
                break;

            printf("Entered index is incorrect\n");
        }

        // Deletion logic inside success block
        for(int j = i; j < addressBook->contactCount - 1; j++)
        {
            addressBook->contacts[j] = addressBook->contacts[j + 1]; // shifting for overwriting
        }

        addressBook->contactCount--; // reducing the total count of contacts
        printf("Contact deleted successfully\n");
    }
    else
    {
        printf("Entered data could not be found in the addressbook\n");
    }
}




