`📘 Address Book Application in C`

A console-based Address Book application written in C that allows users to manage contacts efficiently.
The project demonstrates structured programming, file handling, modular design, and searching/sorting logic.

🚀 Concepts Used

1. Structures in C
2. File Handling (fopen, fread, fwrite, fclose)
3. Modular Programming
4. Arrays
5. Searching Algorithms
6. Sorting Algorithms
7. Menu-Driven Console Application

📌 Features

✅ Create Contact
🔍 Search Contact (supports multiple matches)
✏️ Edit Contact
❌ Delete Contact
📋 List All Contacts
💾 Save Contacts to File
🚪 Exit Safely


AddressBook/
├── main.c          # Menu and program control
├── contact.h       # Structures & function declarations
├── contact.c       # Contact operations implementation
├── sorting.h       # Sorting function declarations
├── sorting.c       # Sorting implementations (if used)
└── contacts.dat    # Data file (created after saving)

🖥️ Usage

When you run the program, you’ll see:

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit
Enter your choice:

🎬 Visual Demo (Console Walkthrough)
➤ Create Contact

Enter your choice: 1
Enter Name: John Doe
Enter Phone: 1234567890
Enter Email: john@example.com
Contact added successfully!

➤ List Contacts

Enter your choice: 5

Contacts:
1. Name: John Doe
   Phone: 1234567890
   Email: john@example.com

➤ Search Contact

Enter your choice: 2
Enter name to search: John

Search Results:
1. John Doe

Enter the index to view details: 1
Name: John Doe
Phone: 1234567890
Email: john@example.com

➤ Edit Contact

Enter your choice: 3
Enter name of contact to edit: John

Enter new phone: 9876543210
Enter new email: john.doe@example.com
Contact updated successfully!

➤ Delete Contact

Enter your choice: 4
Enter name of contact to delete: John
Contact deleted successfully!

➤ Save Contacts

Enter your choice: 6
Saving and Exiting...
Contacts saved to file.