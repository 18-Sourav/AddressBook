#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validation.h"
#include "sorting.h"
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



// Bubble sorting
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