# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include "db.h"

typedef struct Person { 
	char name[20];	//Have to implement some caracteritic for each
} person;

bool isindatabase(char name[20], FILE *database)
{	
	person answer;
	bool find = false;
	while((fread(&answer, sizeof(person), 1, database)) && !find)
	{
		if (strcmp(answer.name, name)==0)
		{
			find = true;
		}
	}
	return find;
}

static void print(FILE *f)
{
  f = fopen("database.obj", "rb");
  fseek(f, 0, SEEK_CUR);

  person a;
  printf("\n");
  printf("Print database : \n");

  for(int i = 0; i < 4; i++)
  {
    fread(&a,sizeof(person), 1, f);
    printf("%s\n", a.name);
  }

  fclose(f);
}

void serialization(char newname[20], FILE *database) // serialize data into file
{
  person new;
  strcpy(new.name,newname);
  fwrite(&new, sizeof(person), 1, database); // write into file
}


void modify(char oldname[20], char n[20]) //deserialize database
{
  FILE *database = fopen("database.obj","r+b");
  fseek(database, 0, SEEK_SET);
  person answer;
  int c = -1;

  while(fread(&answer, sizeof(person), 1, database))
  {
    c++;
    if (strcmp(answer.name, oldname)==0)
    {
      fseek(database, c - sizeof(person), SEEK_CUR); 
      person modif;
      strcpy(modif.name,n);
      fwrite(&modif, sizeof(person), 1, database);
      printf("Modified with success\n");
    }
  }
}

void remov(char name[25])
{
  FILE *database, *ndb;
  database = fopen("database.obj", "r+b");
  ndb = fopen("d.obj", "w+b");
  fseek(database, 0, SEEK_SET);
  person answer;
  int c = 0;
  int i = 0;
  while (fread(&answer, sizeof(person), 1, database)) 
  {
    i++;
    if (strcmp(name, answer.name) == 0) 
    {
      printf("A record with requested name found and deleted.\n");
      c = 1;
    } 
    else 
    {
      fwrite(&answer, sizeof(person), 1, ndb);
    }
  }
  
  fseek(database, i - sizeof(person), SEEK_CUR); 
  
  person nul;
  strcpy(nul.name,"");  
  fwrite(&nul, sizeof(person), 1, ndb);
  
  if (c == 0) 
  {
    printf("No record(s) found with the requested name: %s\n", name);
  }

  fclose(database);
  fclose(ndb);

  remove("database.obj");
  rename("d.obj", "database.obj");
}


void ergo()
{
	printf("##############   ICU   ##############\n");
	printf("############ Les pilotes ############");
	printf("\n");
	printf("--------- Facial Recognition ---------\n\n");
}

void ManageDatabase()
{
	int choice;
	printf("Choose an option : \n");
	printf("1 - Initialize with basic person faces\n");
        printf("2 - Add a person\n");
	printf("3 - Remove a person\n");
 	printf("4 - Modify a person\n");
	printf("5 - Print database\n");
	FILE *db = fopen("database.obj","wb");
	scanf("%d",&choice);
	if (choice == 1) //Add a basic number of people
	{
		char maxou[20] = "Maxime";
        	char bapt[20] = "Baptiste";
        	char coco[20] = "Corentin";
        	char adri[20] = "Adrien";

        	//FILE *init_db = fopen("database.obj","wb");
        	serialization(maxou,db);
        	serialization(bapt, db);
        	serialization(coco, db);
        	serialization(adri, db);
        	printf("Serializatio: ok\n");
		printf("Init database: ok");
        	fclose(db);
        	print(db);
        	//deserialization(maxou);
        	printf("\n");
        	modify(maxou, "john");
        	print(db);
        	printf("\n");
        	//remov();
        	//print(init_db);
	}
	if (choice == 2)//Add working good
	{
		//FILE *db = fopen("database.obj","wb");
		printf("Enter a name : ");
		char name[20];
		scanf("%s",name);
		if (isindatabase(name,db))
		{
			printf("%s is aleady in database", name);
		}
		else
		{
			serialization(name,db);
			printf("Add with success");
		}
		
	}
	if (choice == 3) //Remove working
	{
		char name[20];
		printf("Enter a name : ");
		scanf("%s",name);
		remov(name);
		
	}
	if (choice == 4) // some problem here but it's basically working or not :p
	{
		printf("Enter a name to modif : ");
		char namemodif[20];
		scanf("%s",namemodif);
		printf("Enter the new name : ");
		char newname[20];
		scanf("%s",newname);
		modify(namemodif,newname);
	}
	if (choice == 5)
	{
		//FILE *db = fopen("database.obj","wb");
		print(db);
	}
	
	//An option for print database will be there soon :)

}
int main(int argc,char **argv)
{
	int choice;
	ergo();


	printf("Choose an option : \n");
	printf("1 - Manage database\n");

	scanf("%d",&choice);
	if(choice == 1)
	{
		ManageDatabase();
	}

	return 0;
	
}
