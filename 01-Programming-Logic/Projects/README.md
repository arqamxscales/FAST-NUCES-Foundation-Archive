# CS1006 Semester Project - Expense Calculator (C++)

This project implements the monthly expense calculator described in the semester project.

## Features
- Start screen with **NU FAST in dots** pattern.
- Menu-based options:
  1. Utility bill - Electricity
  2. Food items
  3. Hometown travel fare
  4. Hangout/Shopping expenses
  5. Total monthly expense
  6. Exit
- Separate functions for each expense category.
- Electricity bill calculation includes:
  - Fixed charges (Electricity duty, PTV fee, Neelum Jehlum surcharge)
  - Unit slab rates
  - Due date and late-payment rules
  - Last month unpaid bill support
- Food bill in 3 batches (first 10 days, next 10 days, last 10 days).
- Travel fare for Lahore, Multan, Karachi, and custom city/fare.
- Apartment rent included in total monthly expense.
- Final check against father's monthly budget (Rs. 60,000).

## File Structure
- `main.cpp` -> source code
- `expense_calculator` -> compiled executable (generated after build)

## How to Run in Terminal (macOS/Linux)

### 1) Go to the project folder
```bash
cd /Users/prom1/Desktop/PROJ/expense_calculator
```

### 2) Compile
```bash
g++ -std=c++17 main.cpp -o expense_calculator
```

### 3) Run
```bash
./expense_calculator
```

## If `g++` is not installed
On macOS, install Apple Command Line Tools:
```bash
xcode-select --install
```

## Notes for Submission
- Put this folder inside the final submission folder named with group roll numbers.
- Zip the roll-number folder and submit as required.
- Keep code original (no plagiarism).
