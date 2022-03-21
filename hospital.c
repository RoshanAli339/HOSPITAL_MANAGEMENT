#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//a structure for storing the information of a patient
typedef struct
{	
	char name[30], address[150], blood[3], disease[10],p_id[30];
	long contact;
	float height, weight;
}
patient;

//a structure for storing the information of a doctor
typedef struct
{
	char name[30], address[150], qualifications[20], speciality[30], d_id[30];
	long contact;
}
doctor;

patient p;
doctor d;

long pid(char *name);
void add_patient();
void patient_list();
void patient_count();
void patient_search();
void patient_update();
void add_doctor();

int main()
{	

	int choice;

    while(1)
    {
	    printf("\t\t\t\t*****HOSPITAL******\n");
	    printf("1.Add new patient\n2.Get patient list\n3.Get count of patients\n4.Search for a patient\n5.Add new doctor\n6.Update patient information\n7.Exit\n");
	    //prompting the user to enter their choice after printing the menu
	    printf("Enter your choice as per the serial number: ");
	    scanf("%d",&choice);
	
	    //checking the choice and executing the respective function
	    switch (choice) 
	    {
		    case 1:
			    add_patient();
			    break;
		    case 2:
			    patient_list();
			    break;
		    case 3:
			    patient_count();
			    break;
		    case 4:
			    patient_search();
			    break;
		    case 5:
			    add_doctor();
			    break;
		    case 6:
			    patient_update();
			    break;
            case 7:
                printf("\t\t\t\t\t\t***********THANK YOU*************\n");
                return 0;
		    default:
			    printf("INVALID INPUT!\n");
	    }
    }
	
	printf("\t\t\t\t******THANK YOU******\n");
	return 0;
}

//for creating a id for both patients and doctors based on their name
long pid(char *name)
{
	long id = 0;
	for (int i = 0; i < strlen(name); ++i)
	{
		id = id * 10 + (name[i] - 26);
	}
	return id;
}

//for adding a new patient
void add_patient()
{
	long patient_id;
	//a file pointer to open the patients list file and store data to it
	FILE *patient_list = fopen("PATIENT_LIST.txt", "a+");
	if(patient_list == NULL)
	{
		//checking if the file could open or not and printing and error message if it doesn't
		printf("Error in opening PATIENT_LIST file!\n");
		return;
	}
	//asking for name of patient
	printf("\nEnter name of patient: ");
	scanf(" %[^\n]%*c",p.name);
	//getting the patient id using the pid function
	patient_id = pid(p.name);
	
	printf("Enter disease of patient: ");
	scanf(" %[^\n]%*c", p.disease);
	
	sprintf(p.p_id, "P%ld", patient_id);

	//writing name with patient id to the patients list	
	fprintf(patient_list, "%s : %s , Disease: %s\n", p.p_id, p.name, p.disease);
	
	fclose(patient_list);

	printf("Enter address of patient: ");
	scanf(" %[^\n]%*c", p.address);
	
	printf("Enter patient's blood group(ex: O+/AB+/A-): ");
	scanf(" %s", p.blood);
	
	printf("Enter contact number of patient: ");
	scanf(" %ld", &p.contact);
	
	printf("Enter height of patient in feet: ");
	scanf(" %f", &p.height);
	
	printf("Enter weight of patient in kilograms: ");
	scanf(" %f", &p.weight);
	
	//a string to store the name of the file to be created by using the patient id
	char file[30];
	strcpy(file, p.p_id);
	strcat(file, ".txt");
	
	//creating a new file for the patient using the patient id
	FILE *patient_file = fopen(file, "w");
	if (patient_file == NULL)
	{
		printf("Error in creating the patient file!\n");
		return;
	}
	//writing information to the patient to the patients file
	fprintf(patient_file, "Name: %s\n", p.name);
	fprintf(patient_file, "Patient ID: %s\n", p.p_id);
	fprintf(patient_file, "Disease: %s\n", p.disease);
	fprintf(patient_file, "Blood group: %s\n", p.blood);
	fprintf(patient_file, "Contact number: %ld\n", p.contact);
	fprintf(patient_file, "Address: %s\n", p.address);
	fprintf(patient_file, "Height: %.2fFT\n", p.height);
	fprintf(patient_file, "Weight: %.2fKG\n", p.weight);
	
	fclose(patient_file);

	printf("Patient added successfully!\nPlease make a note of the patient id for future purposes: %s\n", p.p_id);
}

//for printing the list of patients
void patient_list()
{
	//a file pointer to open the patients list file
	FILE *fptr = fopen("PATIENT_LIST.txt", "a+");

	if (fptr == NULL)
	{
		printf("Error in opening file!\n");
		return;
	}

	char str;
	
	printf("\nThe list of patients currently admitted: \n\n");
	//printing each character from the patients list file and printing them until EOF(End of File)
	while ((str = fgetc(fptr)) != EOF)
	{
		printf("%c", str);
	}
}

//for printing the number of patients
void patient_count()
{
	//to count the number of patients
	int count = 0;

	//a file pointer for reading the patients list file
	FILE *fptr = fopen("PATIENT_LIST.txt", "r");
	
	if(fptr == NULL)
	{
		printf("Error in opening file!!\n");
		return;
	}

	char str;
	//reading through the file and increasing the number of patients when there is a new line character
	while((str = fgetc(fptr)) != EOF)
	{
		if(str == '\n')
			count++;
	}

	printf("\nThe number of patients currently admitted in the hospital is: %d\n", count);
}

//to search for a patient using the patient's ID
void patient_search()
{
	//a string to store the file name of patient 
	char patient[30];

	//asking for the patient id
	printf("\fEnter the patient id: ");
	scanf(" %[^\n]%*c", patient);
	strcat(patient, ".txt");

	//a file pointer to open the patients file using his Patient ID
	FILE *fptr = fopen(patient, "r");
	
	//the file opens successfully if it exists and prints an error if not
	if(fptr == NULL)
	{
		printf("Patient details not found. Please check patient id and enter again!\n");
		return;
	}
	
	printf("\nPatient details found!\n\n");
	
	char str;

	//printing the details of patient from the file
	while((str = fgetc(fptr)) != EOF)
	{
		printf("%c", str);
	}

	fclose(fptr);
}

//for updating a patients function
void patient_update()
{
	long patientid;
	char spid[30];
	//asking for the patient id
	printf("Enter the patient id: ");
	scanf(" %ld", &patientid);
	sprintf(spid, "%ld.txt", patientid);
	
	//file pointers for opening the patients file and a temporary file to store the updated values
	FILE *fptr = fopen(spid, "a+");
	FILE *temp = fopen("temporary.txt", "a+");
	if (fptr == NULL)
	{
		printf("Error!! Please check your patient id!\n");
		fclose(fptr);
		return;
	}
	if (temp == NULL)
	{
		printf("Error in updating values! Please try again!\n");
		fclose(temp);
		return;
	}
	
	int ch, count  = 1;

	//asking for what value the patient wants to change or update
	printf("\n\t1.Name\n\t2.Disease\n\t3.Blood group\n\t4.Contact number\n\t5.Height\n\t6.Weight\n");
	printf("Please enter the serial number of the value you wish to change: ");
	scanf(" %d", &ch);
	
	//checking the choice of user and doing respective tasks
	switch (ch)
	{
		case 1:
			printf("\nEnter the new name: ");
			scanf(" %[^\n]%*c", p.name);
			break;
		case 2:
			printf("\nEnter the disease name: ");
			scanf(" %[^\n]%*c", p.disease);
			ch++;
			break;
		case 3:
			printf("\nEnter the blood group(ex: O-/A-/AB+) :");
			scanf(" %[^\n]%*c", p.blood);
			ch++;
			break;
		case 4:
			printf("\nEnter the new mobile number: ");
			scanf(" %ld", &p.contact);
			ch++;
			break;
		case 5:
			printf("\nEnter the new height of patient: ");
			scanf(" %f", &p.height);
			ch++;
			break;
		case 6:
			printf("\nEnter the new weight of patient: ");
			scanf(" %f", &p.weight);
			ch++;
			break;
		default:
			printf("Error!! Please give a valid input!\n");
	}
	
	char str;
	int flag = 0;

	//writing to the temporary file 
	while ((str = fgetc(fptr)) != EOF)
	{
		//checking if the current line is the one to be changed and also if it has been changed before or not
		if (ch == count && flag == 0)
		{
			switch(ch)
			{
				case 1:
					fprintf(temp, "Name: %s\n", p.name);
					break;
				case 3:
					fprintf(temp, "Disease: %s\n", p.disease);
					break;
				case 4:
					fprintf(temp, "Blood group: %s\n", p.blood);
					break;
				case 5:
					fprintf(temp, "Contact number: %ld\n", p.contact);
					break;
				case 6:
					fprintf(temp, "Height: %fFT\n", p.height);
					break;
				case 7:
					fprintf(temp, "Weight: %fKG\n", p.weight);
					break;
				default:
					printf("Error in updating information!!! Please try again!");
			}
			flag = 1;
		}
		//writing to the temporary file the other parameters
		else if (ch != count)
		{
			fputc(str,temp);
			if(str == '\n')
				count++;
		}
		else if (str == '\n')
			count++;
	}
	
	fclose(fptr);
	fclose(temp);
	
	//file pointers to copy information from the temporary file to the original patients file
	FILE *TEMP = fopen("temporary.txt","r");
	if (TEMP == NULL)
	{
		printf("Error in updating information!\n");
		fclose(TEMP);
		return;
	}
	FILE *patient_file = fopen(spid, "w");
	if (patient_file == NULL)
	{
		printf("Error in updating information!\n");
		fclose(TEMP);
		return;
	}
	
	while ((str = fgetc(TEMP)) != EOF)
	{
		fputc(str, patient_file);
	}
	
	fclose(patient_file);
	fclose(TEMP);
		
	//deleting the temporary file
	if(remove("temporary.txt") == 0)
		printf("\nDetails updated successfully!!\n");
	else
		printf("\nError in updating information!!\n");
}

//for adding a new doctor
void add_doctor()
{
	//a file pointer to open the doctors list file
	FILE *fptr = fopen("DOCTOR_LIST.txt", "a+");
	long doctor_id;
	if (fptr == NULL)
	{
		printf("Error in adding a new doctor!!\n");
		fclose(fptr);
		return;
	}
	
	//asking for the information of the doctor
	printf("\nEnter name of doctor: ");
	scanf(" %[^\n]%*c", d.name);
	doctor_id = pid(d.name);
	sprintf(d.d_id, "D%ld", doctor_id);
	
	printf("Enter qualifications of doctor: ");
	scanf(" %[^\n]%*c", d.qualifications);

	printf("Enter medical speciality of the doctor: ");
	scanf(" %[^\n]%*c", d.speciality);
	
	//writing to the doctors file the doctors id, name, qualification and speciality
	fprintf(fptr, "%s : Dr.%s %s , Specialist in: %s\n", d.d_id, d.name, d.qualifications, d.speciality);
	fclose(fptr);

	printf("Enter address of the doctor: ");
	scanf(" %[^\n]%*c", d.address);

	printf("Enter contact number of doctor: ");
	scanf(" %ld", &d.contact);
	
	//a string to the store the file name of doctor using the doctors ID
	char file[30];
	strcpy(file, d.d_id);
	strcat(file, ".txt");
	
	// a file pointer for creating a file for the doctor
	FILE *doctor_file = fopen(file, "a+");
	if(doctor_file == NULL)
	{
		printf("Error in adding new doctor!!\n");
		fclose(doctor_file);
		return;
	}

	//writing information of doctor to the doctors file
	fprintf(doctor_file, "Name: %s\n", d.name);
	fprintf(doctor_file, "Doctor ID: %s\n", d.d_id);
	fprintf(doctor_file, "Qualifications: %s\n", d.qualifications);
	fprintf(doctor_file, "Specilist in: %s\n", d.speciality);
	fprintf(doctor_file, "Contact number: %ld\n", d.contact);
	fprintf(doctor_file, "Address: %s\n", d.address);

	fclose(doctor_file);

	printf("Doctor added successfully!\nPlease make a note  of the doctor's ID for future purposes: %s\n",d.d_id);
}
