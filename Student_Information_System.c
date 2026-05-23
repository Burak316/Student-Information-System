#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "students.dat"
struct student{
    char *fullName;
    int studentID;
    int midterm;
    int assignment;
    int finalExam;
    double gpa;
    struct student *link;
};

void clearBuffer();
void addStudents(struct student **startPtr);
void listStudents(struct student *startPtr);
void searchEditDelete(struct student **startptr);
void loadStudents(struct student **startptr);
void saveStudents(struct student *startPtr);

void createFile();
int main(){

struct student *startPtr=NULL;
int choice;
loadStudents(&startPtr);
do{
    printf("STUDENT SYSTEM MENU\n");
    printf("0. Create file\n");
    printf("1. Add New Student\n");
    printf("2. List All Students\n");
    printf("3. Search, Edit, or Delete\n");
    printf("4. Exit\n"); 
    printf("Selection: ");


    if(scanf("%d",&choice)!=1){
        printf("Error: Invalid input. Please enter a number.\n");
            clearBuffer();
            choice = 0;
            continue;
    }
    switch(choice){
        case 0: createFile();
        break;

        case 1: addStudents(&startPtr);
        break;

        case 2: listStudents(startPtr);
        break;

        case 3: searchEditDelete(&startPtr);
        break;

        case 4: printf("\nExiting program...\n");
        break;

        default: printf("Invalid selection! Try again.\n");
    }
}while(choice!=4);
    return 0;
}
void createFile(){
    FILE *fptr=fopen(FILE_NAME,"wb");
    if(fptr==NULL){
        printf("\n[WARNING]: Data file not found! Please select Option 1 first to initialize the system.\n");
    return;
    }
    else{
        printf("File is created.\n");
        fclose(fptr); 
    
    }
}
void addStudents(struct student **startPtr){

FILE *fptr=fopen(FILE_NAME,"rb");
if(fptr==NULL){
    printf("\n[WARNING]: Data file not found! Please select Option 1 first to initialize the system.\n");
    return;
}
fclose(fptr);


struct student *newPtr=malloc(sizeof(struct student));
newPtr->link=NULL;
if(newPtr==NULL){
    printf("System full!\n");
    return;
}


    printf("Enter Student ID(1-100):\n");
    if(scanf("%d",&newPtr->studentID)!=1 || newPtr->studentID<1 || newPtr->studentID>100){
        printf("Error: Student ID must be between 1 and 100!\n");
        clearBuffer();
        free(newPtr);
        return;
    }
    
    struct student *tempPtr=*startPtr;
    while(tempPtr!=NULL){
        if(tempPtr->studentID==newPtr->studentID){
            printf("Warning: Student ID %d already exists. Rejected!\n", newPtr->studentID);
            free(newPtr);
            return;
        }
        tempPtr=tempPtr->link;
    }

        char tempBuffer[256];
        printf("Enter full name\n");
        clearBuffer();
        fgets(tempBuffer,sizeof(tempBuffer),stdin);
        for(int i=0;i<256;i++){
            if(tempBuffer[i]=='\n'){
                tempBuffer[i]='\0';
                break;
            }
        }
        if(tempBuffer[0]=='\0'){
           printf("Error: Name cannot be empty!\n");
        free(newPtr);
        return;
        }

        newPtr->fullName=malloc((strlen(tempBuffer)+1)*sizeof(char));
        if(newPtr->fullName==NULL){
            printf("Memory is full!\n");
            free(newPtr);
            return;
        }
        strcpy(newPtr->fullName,tempBuffer);

     printf("Enter midterm assignment final\n");
    if(scanf("%d %d %d",&newPtr->midterm,&newPtr->assignment,&newPtr->finalExam) !=3 || 
                                            newPtr->midterm<0 || newPtr->midterm>100 ||
                                            newPtr->assignment<0 || newPtr->assignment>100 ||
                                            newPtr->finalExam<0 || newPtr->finalExam>100){
            printf("Error: Grades must be between 0 and 100!\n");                           
            
            free(newPtr->fullName);
            free(newPtr);
            return;
        }

        newPtr->gpa=(newPtr->midterm*0.4)+(newPtr->assignment*0.1)+(newPtr->finalExam*0.5);

        struct student *previousPtr=NULL;
        struct student *currentPtr=*startPtr;

        while(currentPtr!=NULL && newPtr->studentID > currentPtr->studentID){
            previousPtr=currentPtr;
            currentPtr=currentPtr->link;
        }
        if(previousPtr==NULL){
            newPtr->link=*startPtr;
            *startPtr=newPtr;
        }
        else{
            previousPtr->link=newPtr;
            newPtr->link=currentPtr;
        }
        printf("Student added successfully.\n");
        
        saveStudents(*startPtr);
}

void listStudents(struct student *startPtr){

    FILE *fptr=fopen(FILE_NAME,"rb");
    if(fptr==NULL){
        printf("\n[WARNING]: Data file not found! Please select Option 1 first to initialize the system.\n");
        return;
    }
    fclose(fptr);
if(startPtr==NULL){
    printf("\n[System]: No records found in the list.\n");
        return;
}
struct student *currentPtr=startPtr;
printf("\n%-20s %-5s %-8s %-8s %-8s %-5s\n", "Full Name", "ID", "Mid", "Asgn", "Fin", "GPA");
while(currentPtr!=NULL){
    printf("%-20s %-5d %-8d %-8d %-8d %-5.2f\n",
               currentPtr->fullName, currentPtr->studentID,
               currentPtr->midterm, currentPtr->assignment,
               currentPtr->finalExam, currentPtr->gpa);
    currentPtr=currentPtr->link;
}
}

void searchEditDelete(struct student **startptr){
    FILE *fptr=fopen(FILE_NAME,"rb");
    if(fptr==NULL){
        printf("\n[WARNING]: Data file not found! Please select Option 1 first to initialize the system.\n");
        return;
    }
     fclose(fptr); 
    if(*startptr==NULL){
        printf("\n[System]: No records found in the list.\n");
        return;
    }

int ID,choice;
printf("Enter ID\n");
if(scanf("%d",&ID)!=1 ||ID<1 || ID>100){
    printf("Invalid ID\n");
    clearBuffer();
    return;
}

struct student *previousPtr=NULL;
struct student *currentPtr=*startptr;

while(currentPtr!=NULL){
    if(currentPtr->studentID==ID){
        printf("\nMatch Found: %s (ID: %d, Midterm: %d, Assignment: %d, Final: %d, GPA: %.2f)\n", 
                   currentPtr->fullName, currentPtr->studentID, 
                   currentPtr->midterm, currentPtr->assignment, 
                   currentPtr->finalExam, currentPtr->gpa);
                   printf("1. Edit Record  2. Delete Record  3. Cancel\nSelection: ");
                   if (scanf("%d", &choice) != 1) {
                printf("Invalid selection!\n");
                clearBuffer();
                return;
            }
            if(choice==1){
                char tempBuffer[256];
                printf("Enter new name\n");
                clearBuffer();
                fgets(tempBuffer,sizeof(tempBuffer),stdin);
                for(int i=0;i<256;i++){
                    if(tempBuffer[i]=='\n'){
                        tempBuffer[i]='\0';
                        break;
                    }
                }
                if(tempBuffer[0]=='\0'){
                    printf("Error: Name can not be empty!\n");
                    return;
                }
                free(currentPtr->fullName);
                currentPtr->fullName=malloc((strlen(tempBuffer)+1)*sizeof(char));

                if(currentPtr->fullName==NULL){
                    printf("Memory full!\n");
                    return;
                }
                strcpy(currentPtr->fullName,tempBuffer);

                printf("Enter New Grades (Mid, Asgn, Fin): ");
                if (scanf("%d %d %d", &currentPtr->midterm, &currentPtr->assignment, &currentPtr->finalExam) != 3) {
                    printf("Invalid grade input!\n");
                    clearBuffer();
                    return;
                }
                if (currentPtr->midterm < 0 || currentPtr->midterm > 100 || 
                    currentPtr->assignment < 0 || currentPtr->assignment > 100 || 
                    currentPtr->finalExam < 0 || currentPtr->finalExam > 100) {
                    printf("Error: Grades must be between 0 and 100!\n");
                    return;
                }
                currentPtr->gpa = (currentPtr->midterm * 0.4) + (currentPtr->assignment * 0.1) + (currentPtr->finalExam * 0.5);
                printf("Student record updated successfully.\n");
                saveStudents(*startptr);
            }
        else if(choice==2){
            if(previousPtr==NULL){
                *startptr=currentPtr->link;
            }
            else{
                previousPtr->link=currentPtr->link;
            }
            free(currentPtr->fullName);
            free(currentPtr);
                
                printf("Student deleted successfully.\n");
                saveStudents(*startptr);
        }
        else if (choice == 3) {
                printf("Operation cancelled.\n");
            } else {
                printf("Invalid selection!\n");
            }
            return;
    }
    previousPtr=currentPtr;
    currentPtr=currentPtr->link;
}
printf("Student with ID %d not found.\n", ID);
}

void saveStudents(struct student *startPtr){

FILE *fptr=fopen(FILE_NAME,"wb");
if(fptr==NULL){
    printf("Error: Could not open file for saving!\n");
        return;
}
 struct student *currentPtr=startPtr;
while(currentPtr!=NULL){
    

        fwrite(&currentPtr->studentID, sizeof(int), 1, fptr);
        fwrite(&currentPtr->midterm, sizeof(int), 1, fptr);
        fwrite(&currentPtr->assignment, sizeof(int), 1, fptr);
        fwrite(&currentPtr->finalExam, sizeof(int), 1, fptr);
        fwrite(&currentPtr->gpa, sizeof(double), 1, fptr);
         int nameLen=strlen(currentPtr->fullName)+1;
    fwrite(&nameLen,sizeof(int),1,fptr);
    fwrite(currentPtr->fullName,sizeof(char),nameLen,fptr);


 currentPtr=currentPtr->link;
}
fclose(fptr);
printf("[System]: Data saved to file successfully.\n");
}

void loadStudents(struct student **startPtr){
FILE *fptr=fopen(FILE_NAME,"rb");
if(fptr==NULL){
     printf("Error: Could not open file for loading!\n");
        return;
}
    
        while(1){
            struct student *newptr=malloc(sizeof(struct student));
            if(newptr==NULL){
                printf("Memory full!\n");
                break;
            }
            if(fread(&newptr->studentID,sizeof(int),1,fptr)==1){
                fread(&newptr->midterm,sizeof(int),1,fptr);
                fread(&newptr->assignment,sizeof(int),1,fptr);
                fread(&newptr->finalExam,sizeof(int),1,fptr);
                fread(&newptr->gpa,sizeof(double),1,fptr);
                

                int nameLen;
                fread(&nameLen,sizeof(int),1,fptr);
                newptr->fullName=malloc(nameLen*sizeof(char));
                if(newptr->fullName!=NULL){
                    fread(newptr->fullName,sizeof(char),nameLen,fptr);
                }
                newptr->link=NULL;
                if(*startPtr==NULL){
                    *startPtr=newptr;
                }
                else{
                struct student *currentPtr=*startPtr;
                while(currentPtr->link!=NULL){
                    currentPtr=currentPtr->link;
                }
                currentPtr->link=newptr;
            }
        }
            else{
                free(newptr);
                break;
            }
        }
fclose(fptr);
printf("[System]: Data loaded from file.\n");
}





void clearBuffer(){
    int c;
    while((c=getchar())!='\n' && c!= EOF);
}