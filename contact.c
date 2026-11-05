#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"


struct contact
{
    char fname[50];
    char sname[50];
};

void listContacts(AddressBook *addressBook, int list)
{
    Contact temp;

    do
    {
        printf("\n1. List by alphabetical\n");
        printf("2. List by number\n\n");

        printf("Enter choice = ");
        scanf("%d", &list);

    } while (list < 1 || list > 2);

    if (list == 1)
    {
        for(int i = 0; i < addressBook->contactCount - 1; i++)
        {
            for (int j = i + 1; j < addressBook->contactCount; j++)
            {
                if (strcmp(addressBook->contacts[i].name,
                           addressBook->contacts[j].name) > 0)
                {
                    temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
        }
    }
    else if (list == 2)
    {
        for (int i = 0; i < addressBook->contactCount - 1; i++)
        {
            for (int j = i + 1; j < addressBook->contactCount; j++)
            {
                if (strcmp(addressBook->contacts[i].phone,
                           addressBook->contacts[j].phone) > 0)
                {
                    temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
            }
        }
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nName  = %s\n", addressBook->contacts[i].name);
        printf("Phone = %s\n", addressBook->contacts[i].phone);
        printf("Email = %s\n", addressBook->contacts[i].email);
    }
}
void initialize(AddressBook *addressBook)
{
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    if (saveContactsToFile(addressBook))
    {
        printf("Contacts saved successfully!\n");
    }
    exit(EXIT_SUCCESS);              // Exit the program
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full. Cannot create more contacts.\n");
        return;
    }

    printf("\n");
    printf("Enter name= ");
    scanf(" %49[^\n]", addressBook->contacts[addressBook->contactCount].name);

    printf("Enter phone no.= ");
    scanf(" %19[^\n]", addressBook->contacts[addressBook->contactCount].phone);

    printf("Enter email= ");
    scanf(" %49[^\n]", addressBook->contacts[addressBook->contactCount].email);
    printf("\n");

    addressBook->contactCount++;

    printf("Contact created successfully!\n");
}


void searchContact(AddressBook *addressBook)
{
    int choice;
    char search[50];

    do
    {
        printf("1. Search by name\n");
        printf("2. Search by phone\n");
        printf("3. Search by email\n\n");

        printf("Enter choice = ");
        scanf("%d", &choice);
        printf("\n");
        

    } while (choice < 1 || choice > 3);

    printf("Enter search value = ");
    scanf(" %49[^\n]", search);
    printf("\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        char *p1 = search;
        char *p2;

        if (choice == 1)
        {
            p2 = addressBook->contacts[i].name;
        }
        else if (choice == 2)
        {
            p2 = addressBook->contacts[i].phone;
        }
        else
        {
            p2 = addressBook->contacts[i].email;
        }

        int found = strcmp(p1, p2) == 0;

        if (found)
        {
            printf("Contact found\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            return;
        }
    }

    printf("Contact not found\n");
}

void editContact(AddressBook *addressBook)
{
    int choice;
    char edit[50];
    char newValue[50];

    do
    {
        printf("\n1. Edit by name\n");
        printf("2. Edit by phone\n");
        printf("3. Edit by email\n\n");

        printf("Enter choice = ");
        scanf("%d", &choice);

    } while (choice < 1 || choice > 3);

    if (choice == 1)
    {
        printf("Enter current name = ");
    }
    else if (choice == 2)
    {
        printf("Enter current phone = ");
    }
    else
    {
        printf("Enter current email = ");
    }
    scanf(" %49[^\n]", edit);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        char *p1 = edit;
        char *p2;

        if (choice == 1)
        {
            p2 = addressBook->contacts[i].name;
        }
        else if (choice == 2)
        {
            p2 = addressBook->contacts[i].phone;
        }
        else
        {
            p2 = addressBook->contacts[i].email;
        }

        int found = 1;
        while (*p1 != '\0' && *p2 != '\0')
        {
            if (*p1 != *p2)
            {
                found = 0;
                break;
            }
            p1++;
            p2++;
        }

        if (*p1 != '\0' || *p2 != '\0')
        {
            found = 0;
        }

        if (found)
        {
            printf("\nContact found!\n\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n\n", addressBook->contacts[i].email);

            if (choice == 1)
            {
                printf("Enter new name = ");
                scanf(" %49[^\n]", newValue);
                strcpy(addressBook->contacts[i].name, newValue);
                printf("\n");
            }
            else if (choice == 2)
            {
                printf("Enter new phone = ");
                scanf("%19s", newValue);
                strcpy(addressBook->contacts[i].phone, newValue);
                printf("\n");
            }
            else
            {
                printf("Enter new email = ");
                scanf("%49s", newValue);
                strcpy(addressBook->contacts[i].email, newValue);
                printf("\n");
            }

            if (saveContactsToFile(addressBook))
            {
                printf("Contact edited and saved successfully!\n");
            }
            return;
        }
    }

    printf("Contact not found!\n");
}


void deleteContact(AddressBook *addressBook)
{
    int choice;
    char delete[50];

    /* Choose how to search */
    do
    {
        printf("\n1. Delete by name\n");
        printf("2. Delete by phone\n");
        printf("3. Delete by email\n\n");

        printf("Enter choice = ");
        scanf("%d", &choice);

    } while (choice < 1 || choice > 3);

    /* Take search value */
    printf("\n");
    printf("Enter delete value = ");
    scanf(" %49[^\n]", delete);

    /* Search contact */
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        char *p1 = delete;
        char *p2;

        if (choice == 1)
        {
            p2 = addressBook->contacts[i].name;
        }
        else if (choice == 2)
        {
            p2 = addressBook->contacts[i].phone;
        }
        else
        {
            p2 = addressBook->contacts[i].email;
        }

        int found = 1;

        /* Compare search string with contact field */
        while (*p1 != '\0' && *p2 != '\0')
        {
            if (*p1 != *p2)
            {
                found = 0;
                break;
            }

            p1++;
            p2++;
        }

        /* Check if both strings ended at the same time */
        if (*p1 != '\0' || *p2 != '\0')
        {
            found = 0;
        }

        if (found)
        {
            printf("\nContact found!\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);

            /* Shifting contact one position to the left */
            for (int j = i; j < addressBook->contactCount - 1; j++)
            {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }

            addressBook->contactCount--;

            if (saveContactsToFile(addressBook))
            {
                printf("Contact deleted successfully!\n");
            }

            return;
        }
    }

    printf("Contact not found!\n");
}