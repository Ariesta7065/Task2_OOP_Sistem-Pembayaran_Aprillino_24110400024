#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Payment {
protected:
    int id;
    double amount;
    string date;
    string status;
public:
    Payment(int id, double amount, string date)
        : id(id), amount(amount), date(date), status("Pending") {
    }

    virtual void processPayment() = 0;
    virtual bool validatePayment() = 0;
    virtual void refundPayment() = 0;
    virtual ~Payment() {}

    string getStatus() const {
        return status;
    }
};

class CreditCardPayment : public Payment {
private:
    string cardNumber;
    string expiryDate;
    int cvv;
public:
    CreditCardPayment(int id, double amount, string date, string cardNumber, string expiryDate, int cvv)
        : Payment(id, amount, date), cardNumber(cardNumber), expiryDate(expiryDate), cvv(cvv) {
    }

    void processPayment() override {
        if (validatePayment()) {
            status = "Success";
            cout << "Credit Card Payment processed successfully.\n";
        }
        else {
            status = "Failed";
            cout << "Credit Card Payment failed.\n";
        }
    }

    bool validatePayment() override {
        return cardNumber.length() == 16 && cvv > 99 && cvv < 1000;
    }

    void refundPayment() override {
        cout << "Refund processed for Credit Card Payment.\n";
    }

    ~CreditCardPayment() override {}
};

bool isNumber(const string& s) {
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

class BankTransfer : public Payment {
private:
    string accountNumber;
    string bankName;
    string transferCode;
public:
    BankTransfer(int id, double amount, string date, string accountNumber, string bankName, string transferCode)
        : Payment(id, amount, date), accountNumber(accountNumber), bankName(bankName), transferCode(transferCode) {
    }

    void processPayment() override {
        if (validatePayment()) {
            status = "Success";
            cout << "Bank Transfer Payment processed successfully.\n";
        }
        else {
            status = "Failed";
            cout << "Bank Transfer Payment failed.\n";
        }
    }

    bool validatePayment() override {
        return isNumber(accountNumber) && !transferCode.empty();
    }

    void refundPayment() override {
        cout << "Refund processed for Bank Transfer Payment.\n";
    }

    ~BankTransfer() override {}
};

class DigitalWallet : public Payment {
private:
    string walletId;
    string provider;
    string phoneNumber;
public:
    DigitalWallet(int id, double amount, string date, string walletId, string provider, string phoneNumber)
        : Payment(id, amount, date), walletId(walletId), provider(provider), phoneNumber(phoneNumber) {
    }

    void processPayment() override {
        if (validatePayment()) {
            status = "Success";
            cout << "Digital Wallet Payment processed successfully.\n";
        }
        else {
            status = "Failed";
            cout << "Digital Wallet Payment failed.\n";
        }
    }

    bool validatePayment() override {
        return !walletId.empty() && phoneNumber.length() >= 10;
    }

    void refundPayment() override {
        cout << "Refund processed for Digital Wallet Payment.\n";
    }

    ~DigitalWallet() override {}
};

int main() {
    CreditCardPayment cc(1, 500.0, "2025-03-17", "1234567812345678", "12/27", 123);
    BankTransfer bt(2, 1000.0, "2025-03-17", "9876543210", "Bank ABC", "TRF123");
    DigitalWallet dw(3, 250.0, "2025-03-17", "WALLET123", "GoPay", "0812345678");

    cc.processPayment();
    bt.processPayment();
    dw.processPayment();

    cout << "Credit Card Status: " << cc.getStatus() << endl;
    cout << "Bank Transfer Status: " << bt.getStatus() << endl;
    cout << "Digital Wallet Status: " << dw.getStatus() << endl;

    cc.refundPayment();
    bt.refundPayment();
    dw.refundPayment();

    return 0;
}
