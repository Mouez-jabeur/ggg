#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void displayWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.size(); ++i) {
        if (guessed[i]) {
            cout << word[i];
        } else {
            cout << '_';
        }
        cout << ' ';
    }
    cout << endl;
}

bool isWordGuessed(const vector<bool>& guessed) {
    for (bool b : guessed) {
        if (!b) return false;
    }
    return true;
}

int main() {
    vector<string> words = {"programming", "hangman", "challenge", "computer", "developer"};
    srand(static_cast<unsigned int>(time(nullptr)));
    string word = words[rand() % words.size()];
    vector<bool> guessed(word.size(), false);
    int attempts = 6;
    char guess;
    vector<char> incorrectGuesses;

    cout << "Welcome to Hangman!" << endl;

    while (attempts > 0 && !isWordGuessed(guessed)) {
        cout << "Word: ";
        displayWord(word, guessed);

        cout << "Incorrect guesses: ";
        for (char c : incorrectGuesses) {
            cout << c << ' ';
        }
        cout << endl;

        cout << "Attempts remaining: " << attempts << endl;
        cout << "Enter your guess: ";
        cin >> guess;

        bool correctGuess = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess && !guessed[i]) {
                guessed[i] = true;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            incorrectGuesses.push_back(guess);
            attempts--;
        }
    }

    if (isWordGuessed(guessed)) {
        cout << "Congratulations! You've guessed the word: " << word << endl;
    } else {
        cout << "You've run out of attempts. The word was: " << word << endl;
    }

    return 0;
}

