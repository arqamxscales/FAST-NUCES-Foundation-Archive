#include <iostream>
#include <iomanip>
#include <limits>
#include <map>
#include <string>

using namespace std;

const double FATHER_MONTHLY_AMOUNT = 60000.0;
const double APARTMENT_RENT = 20000.0;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int getIntInput(const string &prompt, int minValue = 0) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue) {
            return value;
        }
        cout << "Invalid input. Please enter a value >= " << minValue << ".\n";
        clearInput();
    }
}

double getDoubleInput(const string &prompt, double minValue = 0.0) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue) {
            return value;
        }
        cout << "Invalid input. Please enter a value >= " << minValue << ".\n";
        clearInput();
    }
}

void printStartPattern() {
    cout << "===============================================\n";
    cout << "          N . U .  F A S T  (in dots)         \n";
    cout << "===============================================\n";
    cout << ".N....N.  .U....U.  .F.F.F.  .A....A.  .S.S.S.  .T.T.T.\n";
    cout << ".NN...N.  .U....U.  .F.....  .A....A.  .S...... .T.T.T.\n";
    cout << ".N.N..N.  .U....U.  .F.F.F.  .AAAAAA.  .S.S.S.  ...T...\n";
    cout << ".N..N.N.  .U....U.  .F.....  .A....A.  .....S.  ...T...\n";
    cout << ".N...NN.  ..UUUU..  .F.....  .A....A.  .S.S.S.  ...T...\n";
    cout << "===============================================\n\n";
}

double calculateElectricityUnitsCost(int units) {
    if (units <= 100) {
        return units * 10.0;
    } else if (units <= 200) {
        return (100 * 10.0) + (units - 100) * 15.0;
    } else if (units <= 300) {
        return (100 * 10.0) + (100 * 15.0) + (units - 200) * 20.0;
    }
    return (100 * 10.0) + (100 * 15.0) + (100 * 20.0) + (units - 300) * 22.0;
}

double calculateElectricityBill() {
    const long long electricityDuty = 30;
    const long long ptvFee = 25;
    const long long neelumJehlumSurcharge = 22;

    string referenceNo;
    cout << "Enter Reference No. (16 digits): ";
    cin >> referenceNo;

    int inquiryDate = getIntInput("Enter today's date (1-31): ", 1);
    while (inquiryDate > 31) {
        cout << "Date cannot exceed 31.\n";
        inquiryDate = getIntInput("Enter today's date (1-31): ", 1);
    }

    int consumedUnits = getIntInput("Enter total consumed units: ", 0);

    char paidLastMonth;
    cout << "Was last month's bill paid? (y/n): ";
    cin >> paidLastMonth;

    double pendingAmount = 0.0;
    if (paidLastMonth == 'n' || paidLastMonth == 'N') {
        pendingAmount = getDoubleInput("Enter pending amount of last month bill: Rs. ", 0.0);
    }

    double unitCost = calculateElectricityUnitsCost(consumedUnits);
    double fixedCharges = electricityDuty + ptvFee + neelumJehlumSurcharge;

    int lateDays = 0;
    double lateBillCharges = 0.0;

    if (inquiryDate > 17 && inquiryDate <= 27) {
        lateDays = inquiryDate - 17;
        lateBillCharges = lateDays * 10.0;
    } else if (inquiryDate > 27) {
        cout << "\nDue date as well as late bill payment date has been passed.\n";
        cout << "Now you can pay the bill of this month with the next month.\n";
        lateBillCharges = 1000.0;
    }

    double totalBill = unitCost + fixedCharges + lateBillCharges + pendingAmount;

    cout << "\n========== Electricity Bill ==========" << "\n";
    cout << "Reference No.: " << referenceNo << "\n";
    cout << "Sub-Division: H-11\n";
    cout << "Electricity duty: Rs. " << electricityDuty << "\n";
    cout << "PTV fee: Rs. " << ptvFee << "\n";
    cout << "Neelum Jehlum surcharge: Rs. " << neelumJehlumSurcharge << "\n";
    cout << "Consumed units: " << consumedUnits << "\n";
    cout << "Due Date: 17th\n";
    cout << "Date of Inquiry: " << inquiryDate << "\n";
    cout << "Late bill charges: Rs. " << lateBillCharges << "\n";
    if (pendingAmount > 0) {
        cout << "Previous pending bill: Rs. " << pendingAmount << "\n";
    }
    cout << fixed << setprecision(2);
    cout << "Total Bill: Rs. " << totalBill << "\n";
    cout << "=====================================\n\n";

    return totalBill;
}

double calculateTenDayFoodBill(const string &label) {
    cout << "\n" << label << "\n";

    int breakfast = getIntInput("No. of breakfast: ", 0);
    int lunch = getIntInput("No. of lunch: ", 0);
    int dinner = getIntInput("No. of dinner: ", 0);
    int teaCoffee = getIntInput("No. extra tea/coffee: ", 0);

    cout << "Special ordered food options:\n";
    cout << "1. Pizza (Rs. 300 each)\n";
    cout << "2. Chinese item (Rs. 200 each)\n";
    cout << "3. Sandwich/Burger (Rs. 300 each)\n";
    cout << "4. None\n";

    int pizzaCount = 0, chineseCount = 0, sandwichCount = 0;

    int specialChoice;
    while (true) {
        specialChoice = getIntInput("Choose special item (1-4): ", 1);
        if (specialChoice >= 1 && specialChoice <= 4) {
            break;
        }
        cout << "Please enter a valid choice (1-4).\n";
    }

    if (specialChoice == 1) {
        pizzaCount = getIntInput("No. of Pizza orders/persons: ", 0);
    } else if (specialChoice == 2) {
        chineseCount = getIntInput("No. of Chinese food items: ", 0);
    } else if (specialChoice == 3) {
        sandwichCount = getIntInput("No. of Sandwich/Burger orders: ", 0);
    }

    double bill = breakfast * 50.0 + lunch * 100.0 + dinner * 70.0 + teaCoffee * 20.0 +
                  pizzaCount * 300.0 + chineseCount * 200.0 + sandwichCount * 300.0;

    cout << fixed << setprecision(2);
    cout << "Special ordered food cost: Rs. "
         << (pizzaCount * 300.0 + chineseCount * 200.0 + sandwichCount * 300.0) << "\n";
    cout << "10-day Bill: Rs. " << bill << "\n";

    return bill;
}

double calculateFoodBill() {
    double first10 = calculateTenDayFoodBill("Bill for first 10 days");
    double next10 = calculateTenDayFoodBill("Bill for next 10 days");
    double last10 = calculateTenDayFoodBill("Bill for last 10 days");

    double total = first10 + next10 + last10;

    cout << "\n========== Food Bill Summary ==========" << "\n";
    cout << fixed << setprecision(2);
    cout << "Bill for first 10 days: Rs. " << first10 << "\n";
    cout << "Bill for next 10 days: Rs. " << next10 << "\n";
    cout << "Bill for last 10 days: Rs. " << last10 << "\n";
    cout << "Total bill of the month: Rs. " << total << "\n";
    cout << "======================================\n\n";

    return total;
}

double calculateTravelFare() {
    char visited;
    cout << "Did you visit your hometown this month? (y/n): ";
    cin >> visited;

    if (!(visited == 'y' || visited == 'Y')) {
        cout << "No hometown travel expense this month.\n\n";
        return 0.0;
    }

    map<string, double> fareMap;
    fareMap["lahore"] = 1000.0;
    fareMap["multan"] = 1500.0;
    fareMap["karachi"] = 3000.0;

    cout << "Available cities and one-side fare:\n";
    cout << "- Lahore: Rs. 1000\n";
    cout << "- Multan: Rs. 1500\n";
    cout << "- Karachi: Rs. 3000\n";
    cout << "(You can also enter your own city and fare.)\n";

    string city;
    cout << "Enter hometown city name: ";
    cin >> city;

    string cityLower = city;
    for (char &c : cityLower) c = static_cast<char>(tolower(c));

    double farePerVisit;
    if (fareMap.find(cityLower) != fareMap.end()) {
        farePerVisit = fareMap[cityLower];
    } else {
        farePerVisit = getDoubleInput("City not in default list. Enter fare per visit: Rs. ", 0.0);
    }

    int visits = getIntInput("How many times did you visit this month? ", 0);

    double totalFare = farePerVisit * visits;

    cout << fixed << setprecision(2);
    cout << "Total hometown travel fare: Rs. " << totalFare << "\n\n";

    return totalFare;
}

double calculateHangoutShopping() {
    char spent;
    cout << "Did you spend on hangout/shopping this month? (y/n): ";
    cin >> spent;

    if (!(spent == 'y' || spent == 'Y')) {
        cout << "No hangout/shopping expense this month.\n\n";
        return 0.0;
    }

    double amount = getDoubleInput("Enter hangout/shopping amount: Rs. ", 0.0);

    cout << fixed << setprecision(2);
    cout << "Hangout/Shopping expense: Rs. " << amount << "\n\n";

    return amount;
}

void showMenu() {
    cout << "Choose expense type:\n";
    cout << "1. Utility bill - Electricity\n";
    cout << "2. Food items\n";
    cout << "3. Hometown travel fare\n";
    cout << "4. Hangout/Shopping expenses\n";
    cout << "5. Total monthly expense\n";
    cout << "6. Exit\n";
}

int main() {
    printStartPattern();

    double electricityBill = 0.0;
    double foodBill = 0.0;
    double travelBill = 0.0;
    double hangoutShoppingBill = 0.0;

    bool electricityDone = false;
    bool foodDone = false;
    bool travelDone = false;
    bool hangoutDone = false;

    while (true) {
        showMenu();
        int choice = getIntInput("Enter your choice: ", 1);
        cout << "\n";

        switch (choice) {
            case 1:
                electricityBill = calculateElectricityBill();
                electricityDone = true;
                break;

            case 2:
                foodBill = calculateFoodBill();
                foodDone = true;
                break;

            case 3:
                travelBill = calculateTravelFare();
                travelDone = true;
                break;

            case 4:
                hangoutShoppingBill = calculateHangoutShopping();
                hangoutDone = true;
                break;

            case 5: {
                if (!electricityDone) electricityBill = calculateElectricityBill();
                if (!foodDone) foodBill = calculateFoodBill();
                if (!travelDone) travelBill = calculateTravelFare();
                if (!hangoutDone) hangoutShoppingBill = calculateHangoutShopping();

                double totalMonthlyExpense = electricityBill + foodBill + travelBill +
                                             hangoutShoppingBill + APARTMENT_RENT;

                cout << "\n============= Monthly Expense Summary =============\n";
                cout << fixed << setprecision(2);
                cout << "Electricity Bill: Rs. " << electricityBill << "\n";
                cout << "Food Bill: Rs. " << foodBill << "\n";
                cout << "Hometown Travel Fare: Rs. " << travelBill << "\n";
                cout << "Hangout/Shopping Expense: Rs. " << hangoutShoppingBill << "\n";
                cout << "Apartment Rent: Rs. " << APARTMENT_RENT << "\n";
                cout << "---------------------------------------------------\n";
                cout << "Total Monthly Expense: Rs. " << totalMonthlyExpense << "\n";
                cout << "Father's Monthly Amount: Rs. " << FATHER_MONTHLY_AMOUNT << "\n";

                if (totalMonthlyExpense <= FATHER_MONTHLY_AMOUNT) {
                    cout << "Status: Expenses are manageable within father's amount.\n";
                    cout << "Savings: Rs. " << (FATHER_MONTHLY_AMOUNT - totalMonthlyExpense) << "\n";
                } else {
                    cout << "Status: You need extra money from your elder sister.\n";
                    cout << "Extra amount required: Rs. " << (totalMonthlyExpense - FATHER_MONTHLY_AMOUNT) << "\n";
                }

                cout << "===================================================\n\n";
                break;
            }

            case 6:
                cout << "Thank you for using the Expense Calculator.\n";
                return 0;

            default:
                cout << "Invalid choice. Please enter 1 to 6.\n\n";
                break;
        }
    }

    return 0;
}
