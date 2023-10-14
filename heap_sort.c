#include<stdio.h>
#include<stdlib.h>

struct Student{
    char * name;
    int rollno;
    int cpi;

};


void heapify(struct Student *s, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && s[left].cpi > s[largest].cpi)
        largest = left;

    if (right < n && s[right].cpi > s[largest].cpi)
        largest = right;

    if (largest != i)
    {       
        struct Student temp = s[i];
        s[i] = s[largest];
        s[largest] = temp;

        heapify(s, n, largest);
    }
}


struct Student * heap_sort(struct Student * s, int n)
{
    for(int i = n/2-1; i>=0; i--)
    {
        heapify(s, n, i);
    }
    for(int i= n-1; i>=0; i--)
    {
        struct Student temp = s[0];
        s[0] = s[i];
        s[i] = temp;

        heapify(s, i, 0);

    }
}

int main()
{
    int n;
    printf("enter the number of students\n");
    scanf("%d", &n);
    struct Student * student = (struct Student *)malloc(sizeof(struct Student)*n);
    for (int i = 0; i < n; i++)
    {
        student[i].name = (char *)malloc(25); 
        printf("Enter the student name\n");
        scanf("%s", student[i].name);
        printf("Enter the student roll no\n");
        scanf("%d", &student[i].rollno);
        printf("Enter the student cpi\n");
        scanf("%d", &student[i].cpi);
    }

    heap_sort(student, n);
    printf("The students in sorted order of cpi are:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Name: %s\tRoll No: %d\tCPI: %d\n", student[i].name, student[i].rollno, student[i].cpi);
    }
    

    
    return 0;
}