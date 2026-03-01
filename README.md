`📘 Address Book Application in C`

A console-based Address Book application written in C that allows users to manage contacts efficiently.
The project demonstrates structured programming, file handling, modular design, and searching/sorting logic.

`🚀 Concepts Used`

1. Structures in C
2. File Handling (fopen, fread, fwrite, fclose)
3. Modular Programming
4. Arrays
5. Searching Algorithms
6. Sorting Algorithms
7. Menu-Driven Console Application

`📌 Features`
- ✅ Create Contact   
- 🔍 Search Contact (supports multiple matches)    
- ✏️ Edit Contact    
- ❌ Delete Contact    
- 📋 List All Contacts    
- 💾 Save Contacts to File    
- 🚪 Exit Safely    

`📂 Project Structure`
```
AddressBook/
├── main.c          # Menu and program control
├── contact.h       # Structures & function declarations
├── contact.c       # Contact operations implementation
├── sorting.h       # Sorting function declarations
├── sorting.c       # Sorting implementations (if used)
└── contacts.dat    # Data file (created after saving)
```


`🖥️ Usage`

When you run the program, you’ll see:

```Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit
Enter your choice:
```

`📚 Function Overview`  
| Function                                    | Description                                    |
| ------------------------------------------- | ---------------------------------------------  |
| `initialize(AddressBook *ab)`               | Initializes the address book                   |
| `createContact(AddressBook *ab)`            | Adds new contact                               |
| `searchContact(AddressBook *ab, int loc[])` | Searches contact by name, phone number, email  |
| `editContact(AddressBook *ab)`              | Edits existing contact                         |
| `deleteContact(AddressBook *ab)`            | Deletes a contact                              |
| `listContacts(AddressBook *ab)`             | Displays all contacts                          |
| `saveContactsToFile(AddressBook *ab)`       | Saves contacts to file                         |


`🔮 Future Improvements`  
-Dynamic memory allocation (remove 100-contact limit)  
-Case-insensitive search  
-UI improvement with colored terminal output  
-Password protection  
-Binary file encryption  
