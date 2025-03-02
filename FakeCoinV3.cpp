#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

int* createCoins(int numCoins, int& fakeCoinIndex, bool noFake = false) {
    if (numCoins < 2) {
        throw invalid_argument("Number of coins must be at least 2.");
    }

    int* coinWeights = new int[numCoins];
    int realWeight = rand() % 11 + 10; // Random weight between 10 and 20

    if (noFake) {
        fakeCoinIndex = -1; // No fake coin
        for (int i = 0; i < numCoins; i++) {
            coinWeights[i] = realWeight;
        }
    }
    else {
        fakeCoinIndex = rand() % numCoins; // Pick a random fake coin
        int fakeWeight = realWeight - 1;   // Fake coin is lighter

        for (int i = 0; i < numCoins; i++) {
            coinWeights[i] = realWeight;
        }
        coinWeights[fakeCoinIndex] = fakeWeight; // Assign the fake coin
    }

    return coinWeights;
}

int findFake(int* coins, int start, int end, int& tries, bool hasFake, ofstream& outputFile) {
    if (start == end) {
        if (hasFake) {
            cout << "Fake coin found at index: " << start << "\n";
            outputFile << "Fake coin found at index: " << start << "\n";
        }
        return start;
    }

    int mid = (end - start + 1) / 2;
    int leftSum = 0, rightSum = 0;

    int leftEnd = start + mid - 1;
    int rightStart = start + mid;
    int rightEnd = min(rightStart + mid - 1, end);

    cout << "Weighing coins " << start << " to " << leftEnd
        << " against " << rightStart << " to " << rightEnd << "\n";
    outputFile << "Weighing coins " << start << " to " << leftEnd
        << " against " << rightStart << " to " << rightEnd << "\n";

    for (int i = start; i <= leftEnd; i++) leftSum += coins[i];
    for (int i = rightStart; i <= rightEnd; i++) rightSum += coins[i];

    tries++;

    if (leftSum < rightSum) {
        return findFake(coins, start, leftEnd, tries, hasFake, outputFile);
    }
    else if (leftSum > rightSum) {
        return findFake(coins, rightStart, rightEnd, tries, hasFake, outputFile);
    }
    else {
        if (rightEnd + 1 <= end) {
            return findFake(coins, rightEnd + 1, end, tries, hasFake, outputFile);
        }
        else {
            return -1; // No fake coin found
        }
    }
}

int main() {
    srand(time(0)); // Seed random number generator
    char choice;
    ofstream outputFile("output.txt"); // Open file for writing

    if (!outputFile) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    do {
        int numCoins;

        while (true) {
            cout << "Enter the number of coins (at least 2): ";
            cin >> numCoins;

            if (cin.fail() || numCoins < 2) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Please enter a valid number (at least 2).\n";
            }
            else {
                cin.ignore(1000, '\n');
                break;
            }
        }

        try {
            int fakeCoinIndex;
            bool noFake = (rand() % 10 < 3); // Randomly decide whether to include a fake coin
            int* coins = createCoins(numCoins, fakeCoinIndex, noFake);

            cout << "Generated Weights: ";
            outputFile << "Generated Weights: ";
            for (int i = 0; i < numCoins; i++) {
                cout << coins[i] << " ";
                outputFile << coins[i] << " ";
            }
            cout << "\n";
            outputFile << "\n";

            if (fakeCoinIndex == -1) {
                cout << "There is no fake coin.\n";
                outputFile << "There is no fake coin.\n";
            }

            int tries = 0;
            int foundIndex = findFake(coins, 0, numCoins - 1, tries, fakeCoinIndex != -1, outputFile);

            if (fakeCoinIndex != -1 && foundIndex != -1) {
                cout << "\nFake coin detected at index: " << foundIndex
                    << " in " << tries << " steps.\n\n";
                outputFile << "\nFake coin detected at index: " << foundIndex
                    << " in " << tries << " steps.\n\n";
            }
            else if (fakeCoinIndex == -1) {
                cout << "All coins have the same weight. No fake coin detected.\n\n";
                outputFile << "All coins have the same weight. No fake coin detected.\n\n";
            }

            delete[] coins;
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
            outputFile << "Error: " << e.what() << "\n";
        }

        do {
            cout << "\nDo you want to try again? (Y/N): ";
            cin >> choice;
            choice = toupper(choice);
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                choice = ' ';
            }
        } while (choice != 'Y' && choice != 'N');

    } while (choice == 'Y');

    outputFile.close();
    return 0;
}