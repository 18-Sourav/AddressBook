#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validation.h"
#include "sorting.h"

void displayall(AddressBook *addressBook) // To display all the contacts
{
    printf("-----------------------------------------------------------------------------\n");
    printf("%-6s | %-20s | %-15s | %-25s\n",
           "Index", "Name", "Phone Number", "Email-id");
    printf("-----------------------------------------------------------------------------\n");

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-6d | %-20s | %-15s | %-25s\n",
               i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    printf("-----------------------------------------------------------------------------\n");
}

// To display a single contact
void displaycontact(Contact *contact, int i)
{
    printf("| %-5d | %-20s | %-15s | %-25s |\n", i + 1,contact->name,contact->phone,contact->email);
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


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0; 
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    char names[50],phonee[20],emaill[50];
    getchar(); 
    printf("Enter the contact name : ");
    scanf("%49[^\n]",names);
    strcpy(addressBook->contacts[addressBook->contactCount].name,names);
    getchar();
    
    while(1)
    {
        printf("Enter the contact phone number : ");
        
        scanf("%19[^\n]",phonee);
        getchar();
        // number validation funtion
        int valid= numbervalid(addressBook,phonee);
        if(valid)
        {
            //printf("Entered number is correct\n");
            break;
        }
        printf("Entered phone number is incorrect\n");
       // printf("Please enter the correct number ");
    }    
    
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phonee); // Copying the phone number to the database
    

    while(1)
    {
        printf("Enter the contact's email-id : ");
        
        scanf("%49[^\n]",emaill); // Taking the emmail input from the user
        getchar();

        //email validation
        int valid = emailvalid(addressBook,emaill);
            if(valid)
            {
                //printf("Entered Email is correct \n");
                break;
            }
        printf("Entered email id is incorrect\n");    
        //printf("Re-enter your email-id : ");
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
        printf("Enter the field you want to search\n1.Name\n2.Phone Number\n3.Email \n");
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
            if((i > 0 && i <=addressBook->contactCount && ptr[i-1] == 1)) // checking if the entered index is matching the search results
            break;
            printf("Entered index is incorrect \n");
        } 
    }
    else
        printf("Entered data could not be found in the addressbook\n"); // if no search result is found 
    
    // Asking the field for edit     
    while(1)
    {
        printf("\nEnter the field you want to edit, Enter (1,2,3)\n1.Name\n2.Phone\n3.Email\n4.Return to main menu\n");
        scanf("%d",&entry);
        getchar();
        
        if((entry > 0 && entry <=4)) 
          break;
        printf("Entered index is incorrect \n");
    }

    switch(entry)
    {
         case 1:printf("Enter the new name to be saved\n"); // To modify the name of a contact
                
         scanf("%49[^\n]",newentry);
                strcpy(addressBook->contacts[i-1].name,newentry);
                printf("Name updated sucessfully.....\n");
                break;
         
         case 2:
                while(1)
                {
                    printf("Enter the new Phone Number to be saved\n"); // To modify the phone number of a contact
                    
                    scanf("%49[^\n]",newentry);
                    getchar();
                    // number validation funtion
                    int valid= numbervalid(addressBook,newentry);
                    if(valid)
                    {
                        strcpy(addressBook->contacts[i-1].phone,newentry);
                        printf("Phone number updated sucessfully.....\n");
                        break;
                    }
                    printf("Entered phone number is incorrect\n");
                }    
                break;
         
         case 3:
                while(1)
                {
                    printf("Enter the new email to be saved\n"); // To modify the email of a contact
                    scanf("%49[^\n]",newentry); // Taking the emmail input from the user
                    getchar();

                    //email validation
                    int valid = emailvalid(addressBook,newentry);
                        if(valid)
                        {
                            strcpy(addressBook->contacts[i-1].email,newentry);
                            printf("Email updated sucessfully..... \n");
                            break;
                        }
                    printf("Entered email id is incorrect\n");    
                    //printf("Re-enter your email-id : ");
                } 
                break;
         default:
                return;       
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
        printf("Contact deleted successfully......\n");
    }
    else
    {
        printf("Entered data could not be found in the addressbook\n");
    }
}




