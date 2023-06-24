#include <stdio.h>
#include <string.h>

int charToInt(char c) {
    return (int)(c - 'a' + 1);
}

char intToChar(int n) {
    return (char)(n - 1 + 'a');
}

void performOperation(char* s1, char* s2, char op) {
    int result[9];
    int len1 = 0;
    int len2 = 0;

    // Convert strings to integer arrays
    for (int i = 0; s1[i] != '\0'; i++) {
        result[i] = charToInt(s1[i]);
        len1++;
    }
    for (int i = 0; s2[i] != '\0'; i++) {
        result[i] += charToInt(s2[i]);
        len2++;
    }

    // Perform the operation on each cell independently
    if (len1 != len2) {
        int maxLen = (len1 > len2) ? len1 : len2;
        for (int i = len1; i < maxLen; i++) {
            result[i] = result[i - 1];
        }
        for (int i = len2; i < maxLen; i++) {
            result[i] = result[i - 1];
        }
    }

    for (int i = 0; i < len1 && i < len2; i++) {
        switch (op) {
            case '+':
                result[i] = (result[i] <= 26) ? result[i] : charToInt(s1[i]);
                break;
            case '-':
                result[i] = (result[i] > 0) ? result[i] : charToInt(s1[i]);
                break;
            case '*':
                result[i] %= 26;
                break;
            case '/':
                result[i] = (result[i] != 0) ? result[i] : charToInt(s1[i]);
                break;
            default:
                printf("Invalid operator: %c\n", op);
                return;
        }
    }

    // Convert the resulting array back to a string
    for (int i = 0; i < len1 && i < len2; i++) {
        s1[i] = intToChar(result[i]);
    }
    s1[len1] = '\0';

    // Print the output
    printf("%s %c %s => %s\n", s1, op, s2, s1);
}

int main() {
    char s1[10], s2[10], op[2];
    char keyphrase[] = "exit";

    printf("Welcome to the String Math Program!\n");
    printf("Instructions:\n");
    printf("Enter input in the format SOS\n");
    printf("S represents a string (1-9 lowercase letters)\n");
    printf("O represents a mathematical symbol (+ - * /)\n");
    printf("To exit the program, enter the keyphrase: %s\n", keyphrase);

    while (1) {
        printf("input: ");
        scanf("%9s", s1);
        if (strcmp(s1, keyphrase) == 0) {
            printf("Exiting the program...\n");
            break;
        }
        scanf("%1s", op);
        scanf("%9s", s2);

        if (strlen(s1) > 9 || strlen(s2) > 9) {
            printf("Error: Strings must have at most 9 characters\n");
            continue;
        }
        if (strlen(s1) == 0 || strlen(s2) == 0 || strlen(op) == 0) {
            printf("Error: Invalid input format\n");
            continue;
        }
        if (s1[0] < 'a' || s1[0] > 'z' || s2[0] < 'a' || s2[0] > 'z') {
            printf("Error: Strings must consist of lowercase letters\n");
            continue;
        }
        if (op[0] != '+' && op[0] != '-' && op[0] != '*' && op[0] != '/') {
            printf("Error: Invalid operator\n");
            continue;
        }

        performOperation(s1, s2, op[0]);
    }

    

    return 0;
}
