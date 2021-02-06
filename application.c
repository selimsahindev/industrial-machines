#include <stdio.h>

#define CLEAR system("cls");

enum Statuses {
	TODO = 1, DONE = 2, CANCELLED = 3
};

enum Types {
	Cutting = 1, Sewing = 2, Painting = 3
};

// Struct Definitions

struct Address {
	char street[80];
	int postalCode;
	char location[80];
};

struct Person {
	char name[80];
	struct Address address;
	char entryDate[20];
};

struct maintenanceData {
	struct Person;
	char date[20];
	char description[80];
	enum Statuses status;
};

struct machineData {
	char name[80];
	char brand[80];
	char serialNumber[80];
	char acquisionDate[20];
	enum Types type;
	struct Person responsiblePerson;
};

// Function Signatures

void displayMenu();
void menuNavigation();
void addNewMachine();
char* getTypeName(enum Types type);
char* getStatusName(enum Statuses status);
struct Person getPersonDataFromUser();
void addNewMaintenance();

void main() {
	int menuSelection = -1;
	
	while (menuSelection != 0) {
		displayMenu();

		scanf(" %d", &menuSelection);
		menuNavigation(menuSelection);
	}
}

void menuNavigation(int menuSelection) {
	switch(menuSelection) {
		case 1:
			CLEAR
			addNewMachine();
			break;
	}
}

void addNewMachine() {
	struct machineData newMachine;
	int typeInput;
	char verification;
	
	printf("\nEnter The Information Of The Machine You Want To Add\n\n");
	
	printf("\tName:  ");
	fflush(stdin);
	gets(newMachine.name);
	
	printf("\tBrand:  ");
	fflush(stdin);
	gets(newMachine.brand);
	
	printf("\tSerial Number:  ");
	fflush(stdin);
	gets(newMachine.serialNumber);
	
	printf("\tDate of Acquision (DD.MM.YYYY):  ");
	fflush(stdin);
	gets(newMachine.acquisionDate);
	
	printf("\n\t1- Cutting\t2- Sewing\t3- Painting");
	
	while (1) {
		printf("\n\n\tSelect the machine type:  ");
		scanf(" %d", &typeInput);
		
		if (typeInput < 1 || typeInput > 3) {
			printf("\n\tYou have chosen an invalid option. Please choose from the list above.");
		} else {
			newMachine.type = typeInput;
			break;
		}
	};
	
	CLEAR
	
	printf("\nDo you want to assign a responsible person to this machine? Y/N:  ");

	int i = 0;
	while(i < 4) {
		scanf(" %c", &verification);
		verification = tolower(verification);
		
		if (strchr("y", verification) != NULL) {
			getPersonDataFromUser();
			i++;
			CLEAR
		} else if (strchr("n", verification) != NULL) {
			break;
		} else {
			printf("\nYou have chosen an invalid option. Try again Y/N:  ");
			continue;
		}
		
		if (i > 0) {
			printf("\nDo you want to assign another person? Y/N:  ");
		}
	}
	
	printf("\n\n%s\n%s\n%s\n%s\n", newMachine.name, newMachine.brand, newMachine.serialNumber, newMachine.acquisionDate);
	printf("%s", getTypeName(newMachine.type));
	
	fflush(stdin);
	gets(newMachine.name);
}

struct Person getPersonDataFromUser() {
	struct Person person;
	
	CLEAR
	
	printf("\nCaution: It is only possible to assign maximum 4 people to a machine.\n");
	printf("\nEnter Required Information About The Person You Want To Add\n\n");

	printf("\tName:  ");
	fflush(stdin);
	gets(person.name);
	
	printf("\tCompany Entry Date (DD.MM.YYYY):  ");
	fflush(stdin);
	gets(person.entryDate);
	
	printf("\n\tProvide An Address For This Person\n\n");
	
	printf("\tStreet:  ");
	fflush(stdin);
	gets(person.address.street);
	
	printf("\tPostal Code (Numbers Only):  ");
	scanf(" %d", &person.address.postalCode);
	
	printf("\tLocation:  ");
	fflush(stdin);
	gets(person.address.location);
}

void addNewMaintenance() {
	/* ÖRNEK KOD
	int i = 0;
	while(i < 4) {
		scanf(" %c", &verification);
		verification = tolower(verification);
		
		if (strchr("y", verification) != NULL) {
			getPersonDataFromUser();
			i++;
			CLEAR
		} else if (strchr("n", verification) != NULL) {
			break;
		} else {
			printf("\nYou have chosen an invalid option. Try again Y/N:  ");
			continue;
		}
		
		if (i > 0) {
			printf("\nDo you want to assign another person? Y/N:  ");
		}
	}
	*/
}

char* getTypeName(enum Types type) {
	switch (type) {
		case Cutting: return "Cutting";
		case Sewing: return "Sewing";
		case Painting: return "Painting";
	}
}

char* getStatusName(enum Statuses status) {
	switch (status) {
		case TODO: return "TODO";
		case DONE: return "DONE";
		case CANCELLED: return "CANCELLED";
	}
}

void displayMenu() {	
	CLEAR
	
	printf("\n\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\n");
	printf("\n  1- Insert new machine   ");
	//printf("\n  2- Film Ekle            ");
	//printf("\n  3- Filmleri Listele     ");
	//printf("\n  4- Film Guncelle        ");
	//printf("\n  5- Film Sil             ");
	printf("\n  0- Exit\n\n");
	printf("\n\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\n");
	printf("Enter the number of the desired operation:  ");
}



















