#include <stdio.h>
#include <string.h>

struct user
{
    char name[100];
    int id;
    float height;
    float weight;
};

void inputuserdata(struct user *user)
{
    printf("���O: ");
    scanf("%s", user->name);
    printf("ID: ");
    scanf("%d", &user->id);
    printf("�g�� (cm): ");
    scanf("%f", &user->height);
    printf("�̏d (kg): ");
    scanf("%f", &user->weight);
}

void printUserData(struct user *user) {
    printf("���O: %s\n", user->name);
    printf("ID: %d\n", user->id);
    printf("�g��: %.2f cm\n", user->height);
    printf("�̏d: %.2f kg\n", user->weight);
}

void calculateBMI(struct user *user)
{
    float height_m = user->height / 100.0;
    float bmi = user->weight / (height_m * height_m);
    printf("BMI: %.2f\n", bmi);
}

int main() {

    int users_num;

    printf("���p�Ґ�����͂��Ă��������B\n");
    scanf("%d", &users_num);

    struct user users[users_num];

    for (int i = 0; i < users_num; i++)
    {
        printf("���p�� %d �l�ڂ̏�����͂��Ă��������B:\n", i + 1);
        inputuserdata(&users[i]);
    }
    
    printf("\n���͂��ꂽ���p�҂̏��:\n");
    for (int i = 0; i < users_num; ++i) {
        printf("%d�l�ڂ̗��p��:\n", i + 1);
        printUserData(&users[i]);
        calculateBMI(&users[i]);
        printf("\n");
    }

    return 0;
}
