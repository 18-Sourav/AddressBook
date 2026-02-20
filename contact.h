#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100



typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
char *searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void bubble_sort(AddressBook *addressBook, int (*cmp)(Contact *, Contact *));
int contactbyname(Contact *, Contact *);
int contactbyphone(Contact *, Contact *);
int contactbyemail(Contact *, Contact *);

#endif
