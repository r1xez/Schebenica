#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;


string caesarCipher(string text, int shift) {
    for (char& c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        }
    }
    return text;
}


vector<string> readWordsFromFile(const string& filename, int shift) {
    vector<string> words;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open the file!" << endl;
        return words;
    }

    string word;
    while (getline(file, word)) {
        word = caesarCipher(word, -shift); 
        words.push_back(word);
    }

    return words;
}


int main() {
    int difficulty;

   
    while (true) {
        cout << "Choose difficulty level (1 - Easy, 2 - Medium, 3 - Hard): ";
        cin >> difficulty;

        if (difficulty == 1 || difficulty == 2 || difficulty == 3) {
            break; 
        }
        else {
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }

    string filename;

    
    switch (difficulty) {
    case 1: filename = "easy.txt"; break;
    case 2: filename = "medium.txt"; break;
    case 3: filename = "hard.txt"; break;
    default:
        cout << "Invalid choice, defaulting to Easy." << endl;
        filename = "easy.txt";
        break;
    }

    int shift = 3; 

    
    vector<string> words = readWordsFromFile(filename, shift);

    if (words.empty()) {
        cout << "No words found in the file!" << endl;
        return 1;
    }

   
    srand(static_cast<unsigned int>(time(0)));
    string wordToGuess = words[rand() % words.size()];

   
    string guessedWord(wordToGuess.length(), '_');
    int attempts = 10;  
    string guessedLetters = ""; 

    cout << "Guess the word: " << guessedWord << endl;

    clock_t startTime = clock();

    while (attempts > 0 && guessedWord != wordToGuess) {
        char guess;
        cout << "Enter a letter: ";
        cin >> guess;

        
        if (guessedLetters.find(guess) != string::npos) {
            cout << "You already guessed that letter!" << endl;
            continue;  
        }

        guessedLetters += guess;  

        // Перевірка, чи є буква в слові
        bool found = false;
        for (size_t i = 0; i < wordToGuess.length(); ++i) {
            if (wordToGuess[i] == guess) {
                guessedWord[i] = guess;  
                found = true;
            }
        }

        if (!found) {
            --attempts;  
            cout << "Incorrect guess. " << attempts << " attempts left." << endl;
        }

        cout << "Current word: " << guessedWord << endl;

        
        if (guessedWord == wordToGuess) {
            cout << "You guessed the word: " << wordToGuess << endl;
            break;
        }
    }

    clock_t endTime = clock();
    double elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;

    if (guessedWord == wordToGuess) {
        cout << "Congratulations! You guessed the word!" << endl;
        cout << "Time taken: " << elapsedTime << " seconds." << endl;
        cout << "Attempts used: " << (10 - attempts) << endl;
    }
    else {
        cout << "You failed to guess the word. The word was: " << wordToGuess << endl;
        cout << "Time taken: " << elapsedTime << " seconds." << endl;
        cout << "Attempts used: " << (10 - attempts) << endl;
    }

    return 0;
}
