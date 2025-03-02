# Fake Coin Detection

## Description
This C++ program simulates a scenario where a set of coins contains a single fake coin that is lighter than the rest. The program uses a divide-and-conquer approach to efficiently determine the fake coin's index through a series of weight comparisons. The results are also written to an output file (`output.txt`).

## Features
- Generates a random set of coins with identical weights except for a single fake coin (if present).
- Implements a recursive binary search approach to identify the fake coin efficiently.
- Provides an option to include or exclude a fake coin randomly.
- Saves the results of the process in an output file.
- Allows multiple test runs with user input.

## Functions
### `int* createCoins(int numCoins, int& fakeCoinIndex, bool noFake = false)`
- Generates an array of coin weights.
- Randomly assigns a lighter weight to a single fake coin unless `noFake` is `true`.
- Returns the array of coin weights and the fake coin's index.

### `int findFake(int* coins, int start, int end, int& tries, bool hasFake, ofstream& outputFile)`
- Uses a recursive divide-and-conquer approach to find the fake coin by comparing weight sums.
- Logs the process to both the console and `output.txt`.
- Returns the index of the fake coin if found; otherwise, returns `-1`.

### `int main()`
- Handles user input to specify the number of coins.
- Generates coin weights and determines if a fake coin is present.
- Calls `findFake` to locate the fake coin.
- Displays and logs results.
- Offers an option to run the test again.

## Usage
1. Compile the program using a C++ compiler:
   ```sh
   g++ -o fake_coin fake_coin.cpp
   ```
2. Run the executable:
   ```sh
   ./fake_coin
   ```
3. Follow the prompts to enter the number of coins and analyze the results.

## Output
- The program prints the coin weights and detection results to the console.
- Results are saved in `output.txt`.

## Dependencies
- Standard C++ Libraries (`iostream`, `fstream`, `cstdlib`, `ctime`, `stdexcept`).

## Example Output
```
Enter the number of coins (at least 2): 8
Generated Weights: 12 12 12 11 12 12 12 12
Weighing coins 0 to 3 against 4 to 7
Weighing coins 0 to 1 against 2 to 3
Weighing coins 3 to 3 against 3 to 3
Fake coin detected at index: 3 in 3 steps.
```

## License
This project is open-source and free to use.

