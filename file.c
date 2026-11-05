#include <stdio.h>
#include "file.h"

int saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;

    fp = fopen("contacts.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fp);
    return 1;
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp;

    fp = fopen("contacts.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    addressBook->contactCount = 0;

        while (addressBook->contactCount < MAX_CONTACTS &&
            fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",
                addressBook->contacts[addressBook->contactCount].name,
                addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp);

    printf("Contacts loaded successfully!\n");
}