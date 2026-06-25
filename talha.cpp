#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Abstract Base Class
class TaxPayer
{
protected:
    string PayerName;
    string PayerType;
    double taxRate;
    double propertyCost;

public:
    TaxPayer(string name, string type, double rate)
    {
        PayerName = name;
        PayerType = type;
        taxRate = rate;
        propertyCost = 0.0;
    }

    void setPropertyCost(double cost)
    {
        propertyCost = cost;
    }

    virtual double CalcWithHoldingTax() = 0;
    virtual void DetailInfo() = 0;

    virtual ~TaxPayer()
    {
    }
};

// Filer Tax Payer
class FilerTaxPayer : public TaxPayer
{
private:
    string ntn;
    int nFilerYears;

public:
    FilerTaxPayer(string name, string type, double rate,
                  string ntnNum, int years)
        : TaxPayer(name, type, rate)
    {
        ntn = ntnNum;
        nFilerYears = years;
    }

    double CalcWithHoldingTax()
    {
        return (taxRate / 100.0) * propertyCost;
    }

    void DetailInfo()
    {
        cout << "\n======== Filer Tax Payer =========" << endl;
        cout << "Payer Name : " << PayerName << endl;
        cout << "Payer Type : " << PayerType << endl;
        cout << "National Tax Number : " << ntn << endl;
        cout << "Property Cost : "
             << fixed << setprecision(2)
             << propertyCost << endl;

        cout << "Tax Rate : "
             << fixed << setprecision(2)
             << taxRate << "%" << endl;

        cout << "Withholding Tax : "
             << fixed << setprecision(2)
             << CalcWithHoldingTax() << endl;

        cout << "Number of Years from which the Payer is filer : "
             << nFilerYears << endl;

        cout << "***********************************************" << endl;
    }

    ~FilerTaxPayer()
    {
        cout << "\nDestructor of FilerTaxPayer called for "
             << PayerName << endl;
    }
};

// Non-Filer Tax Payer
class NonFilerTaxPayer : public TaxPayer
{
private:
    bool IsEligible;

public:
    NonFilerTaxPayer(string name, string type, double rate)
        : TaxPayer(name, type, rate)
    {
        IsEligible = true;
    }

    double CalcWithHoldingTax()
    {
        if (propertyCost <= 3000000)
        {
            IsEligible = true;
            return (taxRate / 100.0) * propertyCost;
        }
        else
        {
            IsEligible = false;
            return 0.0;
        }
    }

    void DetailInfo()
    {
        CalcWithHoldingTax();

        cout << "\n======== Non-Filer Tax Payer =========" << endl;
        cout << "Payer Name : " << PayerName << endl;
        cout << "Payer Type : " << PayerType << endl;

        if (IsEligible)
        {
            cout << "Eligible : YES" << endl;
            cout << "Property Cost : "
                 << fixed << setprecision(2)
                 << propertyCost << endl;

            cout << "Tax Rate : "
                 << fixed << setprecision(2)
                 << taxRate << "%" << endl;

            cout << "Withholding Tax : "
                 << fixed << setprecision(2)
                 << CalcWithHoldingTax() << endl;
        }
        else
        {
            cout << "Eligible : NO" << endl;
            cout << "Property Cost : "
                 << fixed << setprecision(2)
                 << propertyCost << endl;

            cout << "Tax Rate : "
                 << fixed << setprecision(2)
                 << taxRate << "%" << endl;

            cout << "Not eligible to buy property above 30 lac." << endl;
        }

        cout << "***********************************************" << endl;
    }

    ~NonFilerTaxPayer()
    {
        cout << "\nDestructor of NonFilerTaxPayer called for "
             << PayerName << endl;
    }
};

int main()
{
    double propertyCost;

    cout << "Enter the cost of property to buy: ";
    cin >> propertyCost;

    cout << "\n******** FBR Tax Paying Management System ********\n"
         << endl;

    TaxPayer *payer;

    payer = new FilerTaxPayer(
        "Umar",
        "Filer",
        2.5,
        "17301507",
        3);

    payer->setPropertyCost(propertyCost);
    payer->DetailInfo();
    delete payer;

    cout << endl;

    payer = new NonFilerTaxPayer(
        "Ahmed",
        "Non-Filer",
        5.0);

    payer->setPropertyCost(propertyCost);
    payer->DetailInfo();
    delete payer;

    return 0;
}
