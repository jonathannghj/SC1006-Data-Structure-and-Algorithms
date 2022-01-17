#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int age;
    float height;
} Person;
int main()
{
    int num;
    scanf("%d", &num);

    Person *Student1 = (Person *) malloc(sizeof(Person) * num);

    for (int i = 0; i < num; i++)
    {
        Student1[i].age = i*5;
        Student1[i].height = i * 7.2;
    }

    for (int i = 0; i < num; i++)
    {
        printf("%d %f \n", Student1[i].age, Student1[i].height);
    }
    return 0;
}
