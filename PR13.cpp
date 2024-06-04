#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Клас Product
class Product {
private:
    string name;
    double price;
    int stock;

public:
    // Конструктор
    Product(string name, double price, int stock) 
        : name(name), price(price), stock(stock) {}

    // Геттери
    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getStock() const {
        return stock;
    }

    // Сеттери
    void setPrice(double newPrice) {
        price = newPrice;
    }

    void setStock(int newStock) {
        stock = newStock;
    }

    // Метод для зменшення кількості товару на складі
    bool reduceStock(int amount) {
        if (amount > stock) {
            return false;
        }
        stock -= amount;
        return true;
    }
};

// Клас Customer
class Customer {
private:
    string name;
    string email;

public:
    // Конструктор
    Customer(string name, string email) 
        : name(name), email(email) {}

    // Геттери
    string getName() const {
        return name;
    }

    string getEmail() const {
        return email;
    }

    // Сеттери
    void setEmail(string newEmail) {
        email = newEmail;
    }
};

// Клас Order
class Order {
private:
    Customer customer;
    vector<Product> products;
    double totalPrice;

    // Приватний метод для оновлення загальної ціни замовлення
    void updateTotalPrice() {
        totalPrice = 0;
        for (const auto& product : products) {
            totalPrice += product.getPrice();
        }
    }

public:
    // Конструктор
    Order(Customer customer) 
        : customer(customer), totalPrice(0) {}

    // Додавання товару до замовлення
    bool addProduct(Product& product, int amount) {
        if (product.reduceStock(amount)) {
            for (int i = 0; i < amount; ++i) {
                products.push_back(product);
            }
            updateTotalPrice();
            return true;
        }
        return false;
    }

    // Виведення інформації про замовлення
    void printOrder() const {
        cout << "Customer: " << customer.getName() << " (" << customer.getEmail() << ")" << endl;
        cout << "Products:" << endl;
        for (const auto& product : products) {
            cout << "- " << product.getName() << " $" << product.getPrice() << endl;
        }
        cout << "Total Price: $" << totalPrice << endl;
    }
};

// Основна функція
int main() {
    // Створення товарів
    Product product1("Laptop", 999.99, 10);
    Product product2("Smartphone", 499.99, 20);

    // Створення покупця
    Customer customer("John Doe", "john.doe@example.com");

    // Створення замовлення
    Order order(customer);

    // Додавання товарів до замовлення
    if (!order.addProduct(product1, 1)) {
        cout << "Not enough stock for " << product1.getName() << endl;
    }
    if (!order.addProduct(product2, 2)) {
        cout << "Not enough stock for " << product2.getName() << endl;
    }

    // Виведення інформації про замовлення
    order.printOrder();

    return 0;
}
