#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_OPENING_FILE -1

typedef struct _person* position;

typedef struct _person {
	char fname[32], lname[32];
	int birth_year;
	position next;
} person;

int main()
{
	person head = { .fname = "", .lname = "", .birth_year = 0, .next = NULL };
}

position create_person(char* fname, char* lname, int year)
{
	position new_person = NULL;
	new_person = (position)malloc(sizeof(person));
	if (new_person == NULL)
	{
		printf("Alokacija memorije neuspjesna!\n");
		return NULL;
	}

	strcpy(new_person->fname, fname);
	strcpy(new_person->lname, lname);
	new_person->birth_year = year;
	new_person->next = NULL;

	return new_person;
}
void insert_after(position prev, position new)
{
	if (prev != NULL && new != NULL)
	{
		new->next = prev->next;
		prev->next = new;

	}
}

int prepend_list(position head, char* fname, char* lname, int year)
{
	position new_person = NULL;
	new_person = create_person(fname, lname, year);
	if (new_person == NULL)
	{
		printf("Alokacija memorije neuspjesna!\n");
		return ERROR_OPENING_FILE;
	}
	insert_after(head, new_person);

	return 0;
}

int print_list(position first)
{
	position temp = first;

	while (temp != NULL)
	{
		printf("%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
		temp = temp->next;
	}

	return 0;
}

position find_last(position head)
{
	position temp = head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return temp;
}

int append_list(position head, char* fname, char* lname, int year)
{
	position new_person = NULL, last = NULL;
	new_person = create_person(fname, lname, year);
	if (new_person == NULL)
	{
		printf("Alokacija memorije neuspjesna!\n");
		return ERROR_OPENING_FILE;
	}

	last = find_last(head);

	new_person->next = last->next;
	last->next = new_person;

	return 0;
}

position find_by_last(position first, char* lname)
{
	position temp = first;

	while (temp != NULL)
	{
		if (strcmp(temp->lname, lname) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

position find_previous(position head, position wanted)
{
	position temp = head;

	while (temp->next != NULL)
	{
		if (temp->next == wanted)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

position delete(position head, position wanted)
{
	position prev = NULL;

	if (head == wanted)
	{
		position toDelete = head;
		head = head->next;
		free(toDelete);
		return head;
	}

	prev = find_previous(head, wanted);

	if (prev != NULL)
	{
		position toDelete = prev->next;
		prev->next = toDelete->next;
		free(toDelete);
	}
	else
	{
		printf("Element nije pronadjen!\n");
	}

	return head;
}
/*trecizadatak*/
int insert_after_person(position target, char* fname, char* lname, int year)
{
    position new_person = create_person(fname, lname, year);

    if (new_person == NULL)
    {
        printf("Alokacija memorije neuspjesna!\n");
        return ERROR_OPENING_FILE;
    }

    insert_after(target, new_person);
    return 0;
}
int insert_before_person(position head, position target, char* fname, char* lname, int year)
{
    position new_person = create_person(fname, lname, year);
    if (new_person == NULL)
    {
        printf("Alokacija memorije neuspjesna!\n");
        return ERROR_OPENING_FILE;
    }

    if (head->next == target)
    {
        // Ako je ciljani element odmah iza head, koristimo prepend_list
        prepend_list(head, fname, lname, year);
    }
    else
    {
        position prev = find_previous(head, target);
        if (prev == NULL)
        {
            printf("Element nije pronadjen!\n");
            free(new_person);
            return ERROR_OPENING_FILE;
        }
        insert_after(prev, new_person);
    }

    return 0;
}
int save_list_to_file(position head, const char* filename)
{
	FILE* file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Greska prilikom otvaranja datoteke!\n");
		return ERROR_OPENING_FILE;
	}

	position temp = head->next; // preskačemo head, jer je to "prazni" početni element

	while (temp != NULL)
	{
		fprintf(file, "%s %s %d\n", temp->fname, temp->lname, temp->birth_year);
		temp = temp->next;
	}

	fclose(file);
	return 0;
}
int load_list_from_file(position head, const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Greska prilikom otvaranja datoteke!\n");
		return ERROR_OPENING_FILE;
	}

	char fname[32], lname[32];
	int birth_year;

	while (fscanf(file, "%s %s %d", fname, lname, &birth_year) == 3)
	{
		if (append_list(head, fname, lname, birth_year) == -1)
		{
			fclose(file);
			return ERROR_OPENING_FILE;
		}
	}

	fclose(file);
	return 0;
}