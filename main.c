// ProgrammingStudio(01) 22200286_ 박서윤

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct st_class
{
	int code;	   // class code
	char name[30]; // class name
	int unit;	   // credites
	int grading;   // grading (1:A+~F, 2:P/F)
};

char kname[2][10] = {"A+~F", "P/F"}; // String for grading

// Functions provided
int loadData(struct st_class *c[]);							   // Load all class list from data file.
void printAllClasses(struct st_class *c[], int csize);		   // Print all class list
void findClasses(char *name, struct st_class *c[], int csize); // Search a class by name from the list
void saveAllClasses(struct st_class *c[], int csize);		   // Save all class list

// Functions for modifying
int addNewClass(struct st_class *c[], int csize); // Add a class into the list
void editClass(struct st_class *c[], int csize);  // Modify a class in the list

// Functions for making
int applyMyClasses(int my[], int msize, struct st_class *c[], int csize);  // Apply a class
void printMyClasses(int my[], int msize, struct st_class *c[], int csize); // Print my classes
void saveMyClass(int my[], int msize, struct st_class *c[], int csize);	   // Save my classes

// 메뉴
int main(void)
{
	int no;						  // menu number
	struct st_class *classes[50]; // Class list (max. 50 classes)

	int myclass[10]; // My classes (max. 10 classes of code)
	int mycount = 0; // Amount of my classes

	srand(time(0));
	int count = loadData(classes);
	printf("> Load %d classes.\n", count);

	while (1)
	{
		printf("\n> Menu 1.List 2.Add 3.Modify 4.Search 5.Apply 6.My classes 7.Save 0.Quit\n");
		printf(">> Menu? > ");
		scanf("%d", &no);

		if (no == 1)
		{
			printf("> 1.Class list (%d classes)\n", count);
			printAllClasses(classes, count);
		}
		else if (no == 2)
		{
			printf("> 2.Add a Class\n");
			count = addNewClass(classes, count);
		}
		else if (no == 3)
		{
			printf("> 3.Modify a Class\n");
			editClass(classes, count);
		}
		else if (no == 4)
		{
			printf("> 4.Search a Class\n");
			printf(">> Enter class name > ");
			char name[30];
			scanf("%s", name);
			findClasses(name, classes, count);
		}
		else if (no == 5)
		{
			printf("> 5.Apply a class\n");
			mycount = applyMyClasses(myclass, mycount, classes, count);
			printf("%d classes has been applied.\n", mycount);
		}
		else if (no == 6)
		{
			printf("> 6.My classes\n");
			printMyClasses(myclass, mycount, classes, count);
		}
		else if (no == 7)
		{
			printf("> 7.Save\n");
			saveMyClass(myclass, mycount, classes, count);
			printf("\n> All my classes ware saved to my_classes.txt.\n");
			saveAllClasses(classes, count);
			printf("\n> All of class list ware saved to classes.txt.\n");
		}
		else
			break;
	}
	return 0;
}

int loadData(struct st_class *c[])
{
	int count = 0;
	FILE *file;

	file = fopen("classes.txt", "r");
	while (!feof(file))
	{
		c[count] = (struct st_class *)malloc(sizeof(struct st_class));
		int r = fscanf(file, "%d %s %d %d", &(c[count]->code), c[count]->name, &(c[count]->unit), &(c[count]->grading));
		if (r < 4)
			break;
		count++;
	}
	fclose(file);
	return count;
}

// 클래스 보기
void printAllClasses(struct st_class *c[], int csize)
{
	for (int i = 0; i < csize; i++)
	{
		printf("[%d] %s [credit %d - %s]\n", c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading - 1]);
	}
}

// 클래스 저장
void saveAllClasses(struct st_class *c[], int csize)
{
	FILE *file;
	file = fopen("classes.txt", "w");
	for (int i = 0; i < csize; i++)
	{
		fprintf(file, "%d %s %d %d\n", c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);
}

// 기존 클래스 찾기(이름으로)
void findClasses(char *name, struct st_class *c[], int csize)
{
	int count = 0;

	printf("Searching (keyword : %s)\n", name);
	for (int i = 0; i < csize; i++)
	{
		if (strstr(c[i]->name, name))
		{
			printf("[%d] %s [credit %d - %s]\n", c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading - 1]);
			count++;
		}
	}
	printf("%d classes found.\n", count);
}

// 새로운 클래스 추가
int addNewClass(struct st_class *c[], int csize)
{
	int check = 0;

	struct st_class *p = (struct st_class *)malloc(sizeof(struct st_class));

	while (1)
	{
		check = 0;
		printf(">> code number > ");
		scanf("%d", &(p->code));
		for (int i = 0; i < csize; i++)
		{
			if (p->code == c[i]->code)
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
		{
			printf("Code duplicated! Retry.\n");
		}
		else if (check == 0)
			break;
	}
	printf(">> class name > ");
	scanf("%s", p->name);
	printf(">> credits > ");
	scanf("%d", &(p->unit));
	printf(">> grading (1: A+~F, 2: P/F) > ");
	scanf("%d", &(p->grading));

	c[csize] = p;
	return csize + 1;
}

// 기존 클래스 수정
void editClass(struct st_class *c[], int csize)
{
	struct st_class *p = NULL;
	int code;
	int check;
	int i = 0;
	while (1)
	{
		check = 0;
		printf(">> Enter a code of class > ");
		scanf("%d", &code);
		for (i = 0; i < csize; i++)
		{
			if (code == c[i]->code)
			{
				check = 1; 
				break;
			}
		}
		if (check == 1)
		{
			p = (struct st_class *)malloc(sizeof(struct st_class));
			p = c[i];
			break;
		}
		else if (check == 0)
		{
			printf("> No such class.\n");
		}
	}

	printf("> Current: [%d] %s [credits %d - %s]\n", p->code, p->name, p->unit, kname[p->grading - 1]);
	printf("> Enter new class name > ");
	scanf("%s", p->name);
	printf("> Enter new credits > ");
	scanf("%d", &(p->unit));
	printf("> Enter new grading(1:Grade, 2: P/F) > ");
	scanf("%d", &(p->grading));

	printf("> Modified.\n");
}

// 클래스 신청
int applyMyClasses(int my[], int msize, struct st_class *c[], int csize)
{
	int check = 1;
	int cc = 0;
	int check1 = 1;
	int check2 = 1;
	int cnum;
	while (1)
	{

		while (1)
		{
			check1 = 1;
			check2 = 1;
			printf(">> Enter a class code > ");
			scanf("%d", &cc);
			for (int i = 0; i < csize; i++)
			{
				if (cc == c[i]->code)
				{
					check1 = 0;
					cnum = i;
					break;
				}
			} 
			if (check1 == 0)
			{
				for (int i = 0; i < msize; i++)
				{
					if (cc == my[i])
					{
						check2 = 0;
						break;
					} 
				}
			}
			if (check1 == 1)
			{
				printf(">> No such code of class.\n");
			}
			else if (check2 == 0)
			{
				printf(">> It is already stored.\n");
			}
			else if (check1 == 0 && check2 == 1)
			{
				printf("[%d] %s [credits %d - %s]\n", c[cnum]->code, c[cnum]->name, c[cnum]->unit, kname[c[cnum]->grading - 1]);
				my[msize] = cc;
				msize++;
				break;
			}
		}

		printf("");
		printf(">>Add more?(1:Yes 2:No) > ");
		scanf("%d", &check);
		if (check == 2)
		{
			break;
		}
	}
	return msize;
}

// 내 클래스 출력
void printMyClasses(int my[], int msize, struct st_class *c[], int csize)
{
	int i, j;
	int alcredit = 0;
	for (i = 0; i < msize; i++)
	{
		for (j = 0; j < csize; j++)
		{
			if (my[i] == c[j]->code)
				break;
		}
		alcredit += c[j]->unit;
		printf("[%d] %s [credits %d - %s]\n", c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading - 1]);
	}
	printf("All : %d credits\n", alcredit);
}

// 내 클래스를 파일로 저장
void saveMyClass(int my[], int msize, struct st_class *c[], int csize)
{
	int j;
	FILE *file;
	file = fopen("my_classes.txt", "w");
	for (int i = 0; i < msize; i++)
	{
		for (j = 0; j < csize; j++)
		{
			if (my[i] == c[j]->code)
			{
				fprintf(file, "[%d] %s [credits %d - %s]\n", c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading - 1]);
				break;
			}
		}
	}
	fclose(file);
}
