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
    printf("名前: ");
    scanf("%s", user->name);
    printf("ID: ");
    scanf("%d", &user->id);
    printf("身長 (cm): ");
    scanf("%f", &user->height);
    printf("体重 (kg): ");
    scanf("%f", &user->weight);
}

void printUserData(struct user *user) {
    printf("名前: %s\n", user->name);
    printf("ID: %d\n", user->id);
    printf("身長: %.2f cm\n", user->height);
    printf("体重: %.2f kg\n", user->weight);
}

void calculateBMI(struct user *user)
{
    float height_m = user->height / 100.0;
    float bmi = user->weight / (height_m * height_m);
    printf("BMI: %.2f\n", bmi);
}

int main() {

    int users_num;

    printf("利用者数を入力してください。\n");
    scanf("%d", &users_num);

    struct user users[users_num];

    for (int i = 0; i < users_num; i++)
    {
        printf("利用者 %d 人目の情報を入力してください。:\n", i + 1);
        inputuserdata(&users[i]);
    }
    
    printf("\n入力された利用者の情報:\n");
    for (int i = 0; i < users_num; ++i) {
        printf("%d人目の利用者:\n", i + 1);
        printUserData(&users[i]);
        calculateBMI(&users[i]);
        printf("\n");
    }

    return 0;
}
