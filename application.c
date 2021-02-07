#include <stdio.h>
#include <stdlib.h>

#define CLEAR system("cls");

enum Statuses {
	TODO = 1, DONE = 2, CANCELLED = 3
};

enum Types {
	Cutting = 1, Sewing = 2, Painting = 3
};

// Struct Definitions

typedef struct Address_t {
	char street[80];
	int postalCode;
	char location[80];
} Address;

typedef struct Person_t {
	char name[80];
	Address address;
	char entryDate[20];
} Person;

typedef struct Maintenance_t {
	Person person;
	char date[20];
	char description[80];
	enum Statuses status;
} Maintenance;

typedef struct Machine_t {
	char name[80];
	char brand[80];
	char serialNumber[80];
	char acquisionDate[20];
	enum Types type;
	Person responsiblePerson;
} Machine;

// Linked List Data Structure

typedef struct Node_t {
	Machine machine;
	struct Node_t * next;
} Node;

// Function Signatures

void displayMenu();
void menuNavigation();
Machine createNewMachine();
char* getTypeName(enum Types type);
char* getStatusName(enum Statuses status);
Person addResponsiblePerson();
void addNewMaintenance();
void writeMachinesBin();
void readMachinesBin();
void pushMachine(Machine newMachine);

// Global Variables

Node * machinesList;

void main() {
	int menuSelection = -1;
	
	// Initialize The Root Of Machines List As NULL
	machinesList = NULL;
	
	readMachinesBin();
	
	while (menuSelection != 0) {
		displayMenu();

		scanf(" %d", &menuSelection);
		
		switch(menuSelection) {
			case 1:
				pushMachine(createNewMachine());
				writeMachinesBin();
				break;
			case 2:
				listMachines();
				break;
		}
	}
}

void pushMachine(Machine newMachine) {
	// If the root itself is empty then create and fill it first
	if (machinesList == NULL) {
		machinesList = (Node *)malloc(sizeof(Node));
		machinesList->machine = newMachine;
		machinesList->next = NULL;
		return;
	}
	
	Node * iter = machinesList;
	
	while (iter->next != NULL) {
		iter = iter->next;
	}
	
	iter->next = (Node *)malloc(sizeof(Node));
	iter = iter->next;
	iter->machine = newMachine;
	iter->next = NULL;
}

Machine createNewMachine() {
	Machine newMachine;
	int typeInput;
	char verification;
	
	CLEAR
	
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
	
	while(1) {
		scanf(" %c", &verification);
		verification = tolower(verification);
		
		if (strchr("y", verification) != NULL) {
			newMachine.responsiblePerson = addResponsiblePerson();
			break;
		} else if (strchr("n", verification) != NULL) {
			break;
		} else {
			printf("\nYou have chosen an invalid option. Try again Y/N:  ");
		}
	}
	
	return newMachine;
}

Person addResponsiblePerson() {
	Person person;
	
	CLEAR
	
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
	
	return person;
}

void addNewMaintenance() {
	/* ÖRNEK KOD
	int i = 0;
	while(i < 4) {
		scanf(" %c", &verification);
		verification = tolower(verification);
		
		if (strchr("y", verification) != NULL) {
			addResponsiblePerson();
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

void listMachines() {
	Machine machine;
	Node * iter = machinesList;
	
	CLEAR
	
	while(iter != NULL) {
		machine = iter->machine;
		iter = iter->next;
		
		printf("\n%s", machine.name);
		printf("\n%s", getTypeName(machine.type));
		printf("\n%s", machine.brand);
		printf("\n%s", machine.serialNumber);
		printf("\n%s", machine.acquisionDate);
		printf("\n%s", machine.responsiblePerson.name);
		printf("\n%s", machine.responsiblePerson.entryDate);
		printf("\n%s", machine.responsiblePerson.address.street);
		printf("\n%d", machine.responsiblePerson.address.postalCode);
		printf("\n%s", machine.responsiblePerson.address.location);
		printf("\n");
	}
	
	char x[20];
	fflush(stdin);
	gets(x);
}

void writeMachinesBin() {
	FILE * binFile;
	binFile = fopen("machines.bin", "wb");
	
	Node * node = machinesList;
	
	while (node != NULL) {
		fwrite(&(node->machine), sizeof(Machine), 1, binFile);
		node = node->next;
	}
	
	fclose(binFile);
}

void readMachinesBin() {
	Machine machine;
	
	FILE * binFile;
	binFile = fopen("machines.bin", "rb");
	
	if (binFile == NULL) {
		fclose(binFile);
		return;
	}
	
	while (!feof(binFile)) {
		fread(&machine, sizeof(Machine), 1, binFile);
		
		pushMachine(machine);
	}
		
	fclose(binFile);
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
	printf("\n  1- Insert New Machine   ");
	printf("\n  2- List Machines        ");
	//printf("\n  3- Filmleri Listele     ");
	//printf("\n  4- Film Guncelle        ");
	//printf("\n  5- Film Sil             ");
	printf("\n  0- Exit\n\n");
	printf("\n\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\261\n");
	printf("Enter the number of the desired operation:  ");
}



















