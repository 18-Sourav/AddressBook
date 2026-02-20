#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "contact.h"
#include "file.h"
#include "populate.h"

//char indexarr[50];
void displayall(AddressBook *addressBook) // to display the multiple contact
{
    printf("------ -------------- ---------------- -----------------\n");
    printf("Index\tName\t        Phone Number    Email-id\t\t\n");
    
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%d_\t_",i+1);
        printf("%s_\t_",addressBook->contacts[i].name);
        printf("%s_\t_",addressBook->contacts[i].phone);
        printf("%s_\t_\n",addressBook->contacts[i].email);
        
    }
    printf("------ -------------- ---------------- -----------------\n");
}
void displaycontact(Contact *contact,int i) // to display single contact
{
    
     
        printf("%d\t",i+1);
        printf("%s\t",contact->name);
        printf("%s\t",contact->phone);
        printf("%s\t\n",contact->email);

}
// writing three different types of comparator function based on the type of data that needs to be compared

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
    scanf("%d",&option);

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
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
   // saveContactsToFile(addressBook); // Save contacts to file
   // exit(EXIT_SUCCESS); // Exit the program
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
    

    printf("Enter the contact phone number\n");
    scanf("%19[^\n]",phonee);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phonee);
    getchar();
    // do the number validation
    
    
    printf("Enter the contact's email-id\n");
    scanf("%49[^\n]",addressBook->contacts[addressBook->contactCount].email);
    //do the email validation

    addressBook->contactCount++; 

    displaycontact(&addressBook->contacts[addressBook->contactCount-1],addressBook->contactCount-1);
    
}
char *searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int flag=0,count=0,newcount=0;
    char element[50];
    getchar();
    printf("Enter the contact details you want to search\n");
    scanf("%49[^\n]",element);
    int i=0;
    static char indexarr[50]={0};
    for(i;i<addressBook->contactCount;i++)
    {

        if(element[0]>='0'&& element[0]<='9') // searching based on phone number
        {
            if(strstr(addressBook->contacts[i].phone,element))
            {
              //printf("%d ",i);
              if(flag==0)
              {
                printf("------------- -------------  -----------\n");
                printf("Index\tName\t        Phone Number    Email-id\t\t\n");
              } 
              displaycontact(&addressBook->contacts[i],i); //print along with the index
              flag=1; // atleast one contact is found
              count++;
            
            }
        }
        else if(strstr(addressBook->contacts[i].name,element) || strstr(addressBook->contacts[i].email,element))
        {
           // printf("%d ",i);
           if(flag==0)
              {
                printf("------------- -------------  -----------\n");
                printf("Index\tName\t        Phone Number    Email-id\t\t\n");
              } 
            displaycontact(&addressBook->contacts[i],i); // print along with the index
            flag=1; // atleast one contact is found
            count++; // for multiple contacts we need to increase the indexing of the array
            
        } 
    }
    if(count!=newcount)// for multiple contacts
    {
        newcount=count;
        indexarr[count-1]=i; // saving the index of the found contact as the array element
    }

    if(!flag)
        printf("\n Entered Contact Details not found \n");

        return indexarr;  // return pointer to array as we dont know whether one data or multiple data is present with same nam

        

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    char newentry[50];
    int entry,i;
    
    char *ptr = searchContact(addressBook); // to collect the index array pointer
    printf("Enter the index you want to edit\n");
    scanf("%d",&i);
    printf("\nEnter the field you want to edit, Enter (1,2,3) \n 1. Name\n 2.Phone\n 3.Email\n");
    scanf("%d",&entry);
    getchar();
    printf("Enter the new data to be entered\n");
    scanf("%49[^\n]",newentry);
    switch(entry)
    {
         case 1:
                strcpy(addressBook->contacts[i-1].name,newentry);
                printf("Name updated sucessfully\n");
                break;
         
         case 2:
                strcpy(addressBook->contacts[i-1].phone,newentry);
                printf("Phone updated sucessfully\n");
                break;
         
         case 3:
                strcpy(addressBook->contacts[i-1].email,newentry);
                printf("Email updated sucessfully\n");
                break;
         default:
                printf("Enter your choice as 1,2,3\n");
    }    

    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
