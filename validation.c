#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validation.h"
#include "sorting.h"
// Function to validate the entered phone number 
int numbervalid(AddressBook *addressBook, char *phone) 
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