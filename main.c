#include <stdio.h>
#include <unistd.h>
#include "contact.h"

int main()
{

    for (int i = 1; i <= 100; i++)
    {
        // printf("[Loading...............%d%%]\n",i);
        printf("[Loading AddressBook............%d%%]\r\r", i);
        
        // sleep(1); //delay
        usleep(50000); // microsec delay

        fflush(stdout); // clean the buffer
    }
    /* Remove loading message after 100% */
    printf("\033[2K\r");
    
    int choice;
    int sortChoice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book


    do
    {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\t\t2. Search contact\n");
        printf("3. Edit contact\t\t\t4. Delete contact\n");     
        printf("5. List all contacts\t\t6. Save contacts\n");
        printf("7. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            listContacts(&addressBook,0);
            break;
            
        case 6:
            printf("Saving contacts...\n");
            if (saveContactsToFile(&addressBook))
            {
                printf("Contacts saved successfully!\n");
            }
            break;
        case 7:
            saveAndExit(&addressBook);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
