// without the try buffer or most of the safeguards
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void clear_screen() {
    for (int i = 0; i < 50; i++) printf("\n");
}

void draw_hangman(int lives) {
    switch (lives) {
    case 6: // Empty
        printf("   +---------------+ \n");
        printf("   |               | \n");
        printf("   |               \n");
        printf("   |               \n");
        printf("   |               \n");
        printf("   |               \n");
        printf("   |               \n");
        printf("   |               \n");
        printf("   =======================\n");
        break;
    case 5: // Head
        printf("   +---------------+ \n");
        printf("   |               | \n");
        printf("   |            _______   \n");
        printf("   |           |       |   \n");
        printf("   |           |       |   \n");
        printf("   |           |_______| \n");
        printf("   |               \n");
        printf("   |               \n");
        printf("   |               \n");
        printf("   =======================\n");
        break;
    case 4: // Body
        printf("   +---------------+\n");
        printf("   |               |\n");
        printf("   |            _______   \n");
        printf("   |           |       |   \n");
        printf("   |           |       |   \n");
        printf("   |           |_______| \n");
        printf("   |               | \n");                        
        printf("   |            ___|___\n");
        printf("   |               |  \n");
        printf("   |               |   \n");
        printf("   |               |    \n");
        printf("   =======================\n");
        break;
    case 3: // Left Arm
        printf("   +---------------+\n");
        printf("   |               |\n");
        printf("   |           _______   \n");
        printf("   |      \\   |       |   \n");
        printf("   |       \\  |       |   \n");
        printf("   |        \\ |_______| \n");
        printf("   |         \\    |    \n");                        
        printf("   |          \\___|___\n");
        printf("   |              |  \n");
        printf("   |              |   \n");
        printf("   |              |    \n");
        printf("   =======================\n");
        break;
    case 2: // Right Arm
        printf("   +---------------+\n");
        printf("   |               |\n");
        printf("   |           _______   \n");
        printf("   |      \\   |       |   /\n");
        printf("   |       \\  |       |  / \n");
        printf("   |        \\ |_______| /\n");
        printf("   |         \\    |    /\n");                        
        printf("   |          \\___|___/\n");
        printf("   |              |  \n");
        printf("   |              |   \n");
        printf("   |              |    \n");
        printf("   =======================\n");
        break;
    case 1: // Left Leg
        printf("   +---------------+\n");
        printf("   |               |\n");
        printf("   |           _______   \n");
        printf("   |      \\   |       |   /\n");
        printf("   |       \\  |       |  / \n");
        printf("   |        \\ |_______| /\n");
        printf("   |         \\    |    /\n");                        
        printf("   |          \\___|___/\n");
        printf("   |              |   \n");
        printf("   |              |   \n");
        printf("   |              |    \n");
        printf("   |             / \n");
        printf("   |            /    \n");
        printf("   |           /    \n");
        printf("   |          /   \n");
        printf("   |         /    \n");
        printf("   =======================\n");
        break;
    case 0: // GAME OVER
        printf("   +---------------+\n");
        printf("   |               |\n");
        printf("   |            _______   \n");
        printf("   |           |       |    \n");
        printf("   |           | x   x |    \n");
        printf("   |           |_______|  \n");
        printf("   |               |     \n");                        
        printf("   |            ___|___ \n");
        printf("   |           /   |   \\ \n");
        printf("   |          /    |    \\ \n");
        printf("   |         /     |     \\ \n");
        printf("   |        /     / \\     \\ \n");
        printf("   |       /     /   \\     \\ \n");
        printf("   |            /     \\ \n");
        printf("   |           /       \\ \n");
        printf("   |          /         \\ \n");
        printf("   =======================\n");
        break;
    }
}

int main(void) {
    char secret_word[100];
    char guess_word[100];
    char guessed_letters[27] = ""; // 26 letters + null terminator
    char message[100] = "Enter a letter to guess (0 to Exit).";
    int lives = 6;
    char input;
    
    clear_screen(); 

    printf("Enter the Secret Word (recommended [6-9] letters) >> ");
    scanf("%s", secret_word);

    size_t word_length = strlen(secret_word);
    for(size_t i = 0; i < word_length; i++) {
        secret_word[i] = toupper((unsigned char)secret_word[i]);
    }
    for (size_t i = 0; i < word_length; i++) {
        guess_word[i] = '_';
    }
    guess_word[word_length] = '\0'; // Null terminate the string!

    while (lives > 0 && strcmp(secret_word, guess_word) != 0) {
        clear_screen();
        draw_hangman(lives);
        
        printf("\nWORD: ");
        for(size_t i=0; i<word_length; i++) {
            printf("%c ", guess_word[i]); // Print with spaces for readability
        }
        printf("\n\nLIVES: %d\n", lives);
        printf("GUESSED: ");

        size_t guessed_len = strlen(guessed_letters);
        for (size_t j = 0; j < guessed_len; j++) {
            printf("%c ", guessed_letters[j]);
        }
        printf("\n\n%s\nInput guess: ", message);
        scanf(" %c", &input); 

        input = (char)toupper(input);

        if (strchr(guessed_letters, input)) {
            sprintf(message, "WARNING: You already guessed '%c'.", input);
        }
        else {
            size_t len = strlen(guessed_letters);
            guessed_letters[len] = input;
            guessed_letters[len + 1] = '\0';

            if (strchr(secret_word, input)) {
                sprintf(message, "Good job! Found '%c'.", input);
                
                for (size_t i = 0; i < word_length; i++) {
                    if (secret_word[i] == input) {
                        guess_word[i] = input;
                    }
                }
            } else {
                lives--;
                sprintf(message, "Sorry, '%c' is not in the word.", input);
            }
        }
    }
    clear_screen();
    
    if (strcmp(secret_word, guess_word) == 0) {
        printf("W     W  IIIII  N   N  N   N  EEEEE  RRRR  \n");
        printf("W     W    I    NN  N  NN  N  E      R   R \n");
        printf("W  W  W    I    N N N  N N N  EEEE   RRRR  \n");
        printf("W W W W    I    N  NN  N  NN  E      R  R  \n");
        printf("WW   WW  IIIII  N   N  N   N  EEEEE  R   R \n");
        printf("\nWORD: %s\n\nYOU WIN! The word was: %s\n", guess_word, secret_word);
    } else {
        draw_hangman(lives);
        printf("\nGAME OVER! The word was: %s\n", secret_word);
    }
    printf("\nPress Enter to Exit...");
    getchar(); 
    getchar(); 
}