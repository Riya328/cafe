#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <limits>

using namespace std;

// Structure for menu item
struct MenuItem
{
    string name;
    double price;
    int stock;
};

// Structure for order
struct Order
{
    string customerName;
    map<string, int> items; // item name -> quantity
    double total;
};

// Structure for review
struct Review
{
    string customerName;
    string reviewText;
    int rating;
};

class CafeManagementSystem
{
private:
    map<string, MenuItem> menu;
    vector<Order> orders;
    vector<Review> reviews;
    double totalSales;

public:
    // Constructor
    CafeManagementSystem()
    {
        totalSales = 0.0;

        // Initialize the menu
        menu["Coffee"] = {"Coffee", 3.0, 50};
        menu["Tea"] = {"Tea", 2.5, 40};
        menu["Sandwich"] = {"Sandwich", 5.0, 30};
        menu["Cake"] = {"Cake", 4.0, 20};
    }

    // Display the menu
    void displayMenu()
    {
        cout << "\n--- Menu ---\n";
        cout << setw(15) << left << "Item" << setw(10) << "Price" << setw(10) << "Stock" << endl;
        for (auto &item : menu)
        {
            cout << setw(15) << left << item.second.name
                 << "$" << setw(9) << fixed << setprecision(2) << item.second.price
                 << item.second.stock << endl;
        }
    }

    // Take an order
    void takeOrder()
    {
        string customerName;
        cout << "\nEnter customer name: ";
        cin.ignore(); // To ignore any leftover newline character in the input buffer
        getline(cin, customerName);

        double totalBill = 0.0;
        map<string, int> orderItems;

        while (true)
        {
            displayMenu();
            cout << "Enter the item name (or type 'done' to finish): ";
            string itemName;
            getline(cin, itemName);

            if (itemName == "done")
                break;

            auto it = menu.find(itemName);
            if (it == menu.end())
            {
                cout << "Invalid item. Please choose again.\n";
                continue;
            }

            cout << "Enter quantity for " << itemName << ": ";
            int quantity;
            cin >> quantity;

            // Clear the newline character left in the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (quantity > it->second.stock)
            {
                cout << "Insufficient stock for " << itemName << ". Available stock: " << it->second.stock << endl;
                continue;
            }

            // Process order
            double itemTotal = quantity * it->second.price;
            totalBill += itemTotal;
            it->second.stock -= quantity;
            orderItems[itemName] += quantity;

            cout << quantity << " x " << itemName << " added to the order. Subtotal: $" << itemTotal << endl;
        }

        if (totalBill > 0)
        {
            cout << "\nThank you for your order, " << customerName << "! Your total bill is: $" << totalBill << endl;
            totalSales += totalBill;
            orders.push_back({customerName, orderItems, totalBill});
        }
        else
        {
            cout << "No items ordered. Thank you!\n";
        }
    }

    // Leave a review
    void leaveReview()
    {
        string customerName, reviewText;
        int rating;

        cout << "\nEnter your name: ";
        cin.ignore();
        getline(cin, customerName);

        cout << "Write your review: ";
        getline(cin, reviewText);

        cout << "Rate us (1 to 5): ";
        cin >> rating;
        while (rating < 1 || rating > 5)
        {
            cout << "Invalid rating. Please rate between 1 and 5: ";
            cin >> rating;
        }

        reviews.push_back({customerName, reviewText, rating});
        cout << "Thank you for your feedback, " << customerName << "!\n";
    }

    // View total sales
    void viewTotalSales()
    {
        cout << "\n--- Total Sales ---\n";
        cout << "Total Sales: $" << fixed << setprecision(2) << totalSales << endl;
    }

    // View all orders
    void viewOrders()
    {
        cout << "\n--- Orders ---\n";
        if (orders.empty())
        {
            cout << "No orders have been placed yet.\n";
            return;
        }

        for (const auto &order : orders)
        {
            cout << "Customer: " << order.customerName << "\nItems:\n";
            for (const auto &item : order.items)
            {
                cout << "  " << item.first << " x " << item.second << "\n";
            }
            cout << "Total: $" << order.total << "\n\n";
        }
    }

    // View all reviews
    void viewReviews()
    {
        cout << "\n--- Customer Reviews ---\n";
        if (reviews.empty())
        {
            cout << "No reviews available.\n";
            return;
        }

        for (const auto &review : reviews)
        {
            cout << review.customerName << " (Rating: " << review.rating << "/5): " << review.reviewText << endl;
        }
    }

    // Main menu
    void run()
    {
        while (true)
        {
            cout << "\n--- Café Management System ---\n";
            cout << "1. Display Menu\n";
            cout << "2. Place an Order\n";
            cout << "3. Leave a Review\n";
            cout << "4. View Total Sales\n";
            cout << "5. View Orders\n";
            cout << "6. View Reviews\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
                displayMenu();
                break;
            case 2:
                takeOrder();
                break;
            case 3:
                leaveReview();
                break;
            case 4:
                viewTotalSales();
                break;
            case 5:
                viewOrders();
                break;
            case 6:
                viewReviews();
                break;
            case 7:
                cout << "Thank you for visiting the café! Goodbye!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main()
{
    CafeManagementSystem cafeSystem;
    cafeSystem.run();
    return 0;
}
