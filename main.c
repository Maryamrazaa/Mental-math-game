#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

#define MAX_NAME_LENGTH 50
#define HIGH_SCORE_FILE "highscores.txt"


int loadHighScore() {
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    if (!file) return 0;
    int highscore = 0;
    fscanf(file, "%d", &highscore);
    fclose(file);
    return highscore;
}


void saveHighScore(int score) {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (file) {
        fprintf(file, "%d", score);
        fclose(file);
    }
}


int askQuestion(int level) {
    int a, b, answer, userAnswer;
    char op;
    int correct = 0;

   
    switch (level) {
        case 1:
            a = rand() % 10 + 1;
            b = rand() % 10 + 1;
            break;
        case 2:
            a = rand() % 50 + 10;
            b = rand() % 50 + 10;
            break;
        case 3:
            a = rand() % 100 + 20;
            b = rand() % 100 + 20;
            break;
        default:
            a = rand() % 10 + 1;
            b = rand() % 10 + 1;
    }

   
    switch (rand() % 4) {
        case 0:
            op = '+';
            answer = a + b;
            break;
        case 1:
            op = '-';
            answer = a - b;
            break;
        case 2:
            op = '*';
            answer = a * b;
            break;
        case 3:
            op = '/';
         
            b = b == 0 ? 1 : b;
            answer = a / b;
            break;
    }

    printf(CYAN "\nSolve: %d %c %d = ", a, op, b);
    printf(RESET);
    clock_t start_time = clock();
    scanf("%d", &userAnswer);
    clock_t end_time = clock();

    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    if (userAnswer == answer) {
        printf(GREEN "Correct!\n" RESET);
        correct = 1;
    } else {
        printf(RED "Wrong! Correct answer was %d\n" RESET, answer);
    }

    return correct;
}

int main() {
    char name[MAX_NAME_LENGTH];
    int level, totalQuestions;
    int score = 0, highScore;
    int i;
    time_t start, end;

    srand(time(NULL));
    
    highScore = loadHighScore();


    printf(YELLOW "=== Mental Math Quiz Game ===\n" RESET);
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline

    printf("\nChoose Level:\n");
    printf("1. Easy\n2. Medium\n3. Hard\n> ");
    scanf("%d", &level);

    printf("\nEnter number of questions: ");
    scanf("%d", &totalQuestions);
    if (totalQuestions <= 0) totalQuestions = 5;

    printf("\n" YELLOW "Starting quiz for %s...\n" RESET, name);
    sleep(1);
    system("clear");

    time(&start);

    for (i = 0; i < totalQuestions; i++) {
        printf(YELLOW "\nQuestion %d:\n" RESET, i + 1);
        if (askQuestion(level)) {
            score += 10;
        }
        sleep(1);
    }

    time(&end);
    double timeTaken = difftime(end, start);

   
    printf(CYAN "\n=== Quiz Completed ===\n" RESET);
    printf("Name: %s\n", name);
    printf("Your Score: %d out of %d\n", score, totalQuestions * 10);
    printf("Time Taken: %.2f seconds\n", timeTaken);
    printf("High Score: %d\n", highScore);

    
    if (score > highScore) {
        printf(GREEN "Congratulations! New High Score!\n" RESET);
        saveHighScore(score);
        highScore = score;
    }

  
    if (score == totalQuestions * 10) {
        printf(GREEN "Excellent job!\n" RESET);
    } else if (score >= (totalQuestions * 10) * 0.6) {
        printf(YELLOW "Good effort!\n" RESET);
    } else {
        printf(RED "Keep practicing!\n" RESET);
    }

   
    printf("\nWould you like to try again? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        main();
    } else {
        printf(CYAN "\nThanks for playing!\n" RESET);
    }

    return 0;
}
