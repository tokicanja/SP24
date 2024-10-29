#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		new->next=prev->next;
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
		return -1;
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
		return -1;
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

