#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

struct BetOption {
    string name;
    double odd;
    int stake;
};

void displayOptions(const vector<BetOption>& options) {
    cout << "\n======================================" << endl;
    cout << "          BETTING OPTIONS" << endl;
    cout << "======================================" << endl;
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i].name << " (Odd: " << options[i].odd << ")" << endl;
    }
    cout << "======================================\n";
}

bool checkArbitrage(const vector<BetOption>& options) {
    double totalProb = 0.0;
    for (const auto& opt : options) {
        totalProb += 1.0 / opt.odd;
    }
    return totalProb < 1.0;
}

void calculateStakes(vector<BetOption>& options, int totalStake) {
    double totalProb = 0.0;
    for (const auto& opt : options) {
        totalProb += 1.0 / opt.odd;
    }

    for (auto& opt : options) {
        opt.stake = round((totalStake * (1.0 / opt.odd)) / totalProb);
    }
}
int calculateTotalStakeForProfit(const vector<BetOption>& options, double expectedProfit) {
    double totalProb = 0;
    for (const auto& option : options) {
        totalProb += 1.0 / option.odd;
    }
    return round(expectedProfit / (1 - totalProb));
}

void displayStakes(const vector<BetOption>& options, int totalStake) {
    cout << "\n======================================" << endl;
    cout << "          OPTIMAL STAKES" << endl;
    cout << "======================================" << endl;
    cout << left << setw(15) << "Outcome" << setw(15) << "Stake (rub)" << setw(15) << "Gain (rub)" << endl;
    cout << "--------------------------------------" << endl;
    double guaranteedProfit = (options[0].stake * options[0].odd) - totalStake;
    for (const auto& option : options) {
        double gain = (option.stake * option.odd) - totalStake;
        cout << left << setw(15) << option.name << setw(15) << option.stake << setw(10) << gain << endl;
    }
    cout << "--------------------------------------" << endl;
    cout << "Total Stake: " << totalStake << " rub" << endl;
    cout << "======================================\n";
}

void adjustForExpectedProfit(vector<BetOption>& options, int expectedProfit) {
    int newTotalStake = calculateTotalStakeForProfit(options, expectedProfit);
    calculateStakes(options, newTotalStake);
    displayStakes(options, newTotalStake);
}

int main() {
    int numOptions;
    cout << "Enter the number of betting options: ";
    cin >> numOptions;

    vector<BetOption> options(numOptions);
    for (int i = 0; i < numOptions; ++i) {
        cout << "Enter name for option " << i + 1 << ": ";
        cin >> options[i].name;
        cout << "Enter odds for " << options[i].name << ": ";
        cin >> options[i].odd;
    }

    displayOptions(options);

    if (!checkArbitrage(options)) {
        cout << "No arbitrage opportunity found. Exiting..." << endl;
        return 0;
    }

    cout << "\nArbitrage opportunity detected! Choose an option:" << endl;
   

    int choice;
    while (true) {
        cout << "1. Change an odd name" << endl;
        cout << "2. Modify an odd value" << endl;
        cout << "3. Enter total stake amount" << endl;
        cout << "4. Adjust for expected profit" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option:";
        cin >> choice;
        if (choice == 1) {
            int editIdx;
            displayOptions(options);
            cout << "Enter the number of the odd name to change: ";
            cin >> editIdx;
            cout << "Enter new name: ";
            cin >> options[editIdx - 1].name;
        }
        else if (choice == 2) {
            int editIdx;
            displayOptions(options);
            cout << "Enter the number of the odd to modify: ";
            cin >> editIdx;
            cout << "Enter new odd value: ";
            cin >> options[editIdx - 1].odd;
        }
        else if (choice == 3) {
            int totalStake;
            cout << "Enter total stake amount: ";
            cin >> totalStake;
            calculateStakes(options, totalStake);
            displayStakes(options, totalStake);
        }
        else if (choice == 4) {
            int expectedProfit;
            cout << "Enter expected profit amount: ";
            cin >> expectedProfit;
            adjustForExpectedProfit(options, expectedProfit);
        }
        else if (choice == 5) {
            cout << "Exiting program..." << endl;
            break;
        }
    }
    return 0;
}
