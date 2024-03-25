#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для представления кандидата
struct Candidate {
    string name;
    int votes;

    Candidate(string n) {
        name = n;
        votes = 0;
    }
};

// Поиск длины самого длинного имени кандидата
int candidatesLongestName(vector<Candidate>& candidates){
    int candidates_longest_name_length = 0;
    for(int i = 0; i < candidates.size(); i++){
        if (candidates[i].name.length() > candidates_longest_name_length){
            candidates_longest_name_length = candidates[i].name.length();
        }
    }
    return candidates_longest_name_length;
}

// Вывод результатов голосования
void outputElection(vector<Candidate>& candidates){
    int candidates_longest_name_length = candidatesLongestName(candidates);
    cout << "\nLongest name is " << candidates_longest_name_length << " symbols" << endl;

    cout << "\nElection results:" << endl;
    for (int i = 0; i < 16+candidates_longest_name_length; i++) {
        cout << "@";
    }
    cout << endl;
    for (int i = 0; i < candidates.size(); i++) {
        cout << "@ " << i + 1 << ". " << candidates[i].name << ": " << candidates[i].votes << " votes";
        int needed_spaces_amount = 0;
        needed_spaces_amount = candidates_longest_name_length - candidates[i].name.length();
        for (int j = 0; j < needed_spaces_amount + 1; j++){
            cout << " ";
        }
        cout << "@" << endl;
    }
    for (int i = 0; i < 16+candidates_longest_name_length; i++) {
        cout << "@";
    }
}

// Добавленное объявление функции replaceCandidates
void replaceCandidates(vector<Candidate>& candidates);

// Проведение голосования
void conductElection(vector<Candidate>& candidates) {
    cout << "Voting for the choice of the headman!" << endl;

    cout << "Candidates:" << endl;
    for (int i = 0; i < candidates.size(); i++) {
        cout << i + 1 << ". " << candidates[i].name << endl;
    }

    bool replaceCandidatesRequested = false;
    while (true) {
        if (replaceCandidatesRequested) {
            replaceCandidates(candidates);
            replaceCandidatesRequested = false;
        }

        cout << "Enter the number of the candidate you want to vote for (0 - end voting):";
        int choice;
        cin >> choice;

        if (choice < 0 || choice > candidates.size()) {
            cout << "Invalid choice!" << endl;
            continue;
        }
        else if (choice == 0) {
            break;
        }

        candidates[choice - 1].votes++;

        // После каждой итерации отдачи голоса спрашиваем, хочет ли пользователь изменить кандидатов
        char replaceChoice;
        cout << "Do you want to replace candidates? (y/n): ";
        cin >> replaceChoice;
        if (replaceChoice == 'y' || replaceChoice == 'Y') {
            replaceCandidatesRequested = true;
            continue;  // Перезапускаем голосование, чтобы применить изменения в кандидатах
        }
    }

    sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) {
        return a.votes > b.votes;
    });

    outputElection(candidates);
}

// Добавленная функция для замены одного кандидата
void replaceCandidates(vector<Candidate>& candidates) {
    cout << "Replacing a candidate...\n";
    
    // Сброс результатов
    for (int i = 0; i < candidates.size(); ++i) {
        candidates[i].votes = 0;
    }
    
    // Вывод текущих кандидатов
    cout << "Current candidates:\n";
    for (int i = 0; i < candidates.size(); ++i) {
        cout << i + 1 << ". " << candidates[i].name << endl;
    }

    // Запрос номера кандидата для замены
    int candidateIndex;
    cout << "Enter the number of the candidate you want to replace: ";
    cin >> candidateIndex;
    --candidateIndex; // Adjust index to match array indexing

    // Проверка на корректность введенного номера кандидата
    if (candidateIndex < 0 || candidateIndex >= candidates.size()) {
        cout << "Invalid candidate number!\n";
        return;
    }

    // Запрос нового имени для выбранного кандидата
    string newName;
    cout << "Enter the new name for candidate #" << candidateIndex + 1 << ": ";
    cin >> newName;

    // Замена имени выбранного кандидата
    candidates[candidateIndex].name = newName;
}