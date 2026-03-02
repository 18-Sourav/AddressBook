#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.csv", "w");
    if (fptr == NULL)
    {
        printf("Error: Unable to open file for writing.\n");
        return;
    }
    // Write CSV header
    fprintf(fptr, "Name,Phone,Email\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.csv", "r");
    if (fptr == NULL)
    {
        printf("File not found. Starting with empty address book.\n");
        addressBook->contactCount = 0;
        return;
    }
    char line[150];
    // Skip header line
    fgets(line, sizeof(line), fptr);

    addressBook->contactCount = 0; // resetting the count

    while (fgets(line, sizeof(line), fptr) && 
       addressBook->contactCount < MAX_CONTACTS) // Checking the maximum limit
    {
        if (sscanf(line, "%49[^,],%19[^,],%49[^\n]",
                   addressBook->contacts[addressBook->contactCount].name,
                   addressBook->contacts[addressBook->contactCount].phone,
                   addressBook->contacts[addressBook->contactCount].email) == 3) // skips any corrupted line in the file while reading and moves to the next line
                                                                                // And whilw we again save the data to file the data would be perfectly ordered and without any blanks
        {
            addressBook->contactCount++;
        }
    }

    fclose(fptr);
}
