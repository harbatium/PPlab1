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

/// Поиск длины самого длинного имени кандидата
int canditatesLongestName(vector<Candidate>& candidates){
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
    int candidates_longest_name_length = canditatesLongestName(candidates);
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
// Проведение голосования
void conductElection(vector<Candidate>& candidates) {
    cout << "Voting for the choice of the headman!" << endl;

    cout << "Candidates:" << endl;
    for (int i = 0; i < candidates.size(); i++) {
        cout << i + 1 << ". " << candidates[i].name << endl;
    }

    while (true) {
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
    }

    sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) {
        return a.votes > b.votes;
    });

    outputElection(candidates);
}