//Aman Mathur 20710307 && Jonathan Chen 20722167

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Artwork {
    string artistName;
    string title;
    unsigned int year;

public:
    Artwork() {
        year = 0;
    }

    Artwork(string newArtistName, string newTitle, int newYear) {
        artistName = newArtistName;
        title = newTitle;
        year = newYear;
    }

    bool operator ==(const Artwork &target) const {
        bool isEqual = true;
        isEqual = isEqual && (artistName == target.artistName);
        isEqual = isEqual && (title == target.title);
        isEqual = isEqual && (year == target.year);

        return isEqual;
    }
};

class SoldArtwork : public Artwork {
    string customerName;
    string customerAddress;
    double saleAmount;

public:
    SoldArtwork() {
        saleAmount = 0.0;
    }

    SoldArtwork(string newCustomerName, string newCustomerAddress, double newSaleAmount, string newArtistName, string newTitle, int newYear)
            : Artwork(newArtistName, newTitle, newYear) {

        customerName = newCustomerName;
        customerAddress = newCustomerAddress;
        saleAmount = newSaleAmount;
    }

    bool operator ==(const SoldArtwork &target) const {
        bool isEqual = true;
        isEqual = isEqual && (customerName == target.customerName);
        isEqual = isEqual && (customerAddress == target.customerAddress);
        isEqual = isEqual && (saleAmount == target.saleAmount);
        isEqual = isEqual && (static_cast<Artwork>(*this) == static_cast<Artwork>(target));
        return isEqual;
    }
};

class ArtCollection {
    vector<Artwork> myArtwork;
    vector<SoldArtwork> mySoldArtwork;
public:
    bool insertArtwork(const Artwork &artworkInfo){
        bool isDuplicate = false;

        //Check for duplicate
        for (int i = 0; i < myArtwork.size(); i++) {
            if (myArtwork[i] == artworkInfo) {
                isDuplicate = true;
            }
        }

        //If Duplicate is found, cancel operation
        if (!isDuplicate) {
            myArtwork.insert(myArtwork.begin(), artworkInfo);
            //cout << "Not Duplicate";
            return true;
        } else {
            //cout << "Duplicate";
            return false;
        }
    }

    bool sellArtwork(const SoldArtwork &artworkInfo){
        bool eraseArtwork = false;
        static_cast<Artwork>(artworkInfo);
        //Delete from myArtwork
        for (int i = 0; i < myArtwork.size(); i++) {
            if (myArtwork[i] == artworkInfo) {
                myArtwork.erase(myArtwork.begin() + i);
                eraseArtwork = true;
                //cout << "Erased";
            }
        }

        //Add to mySoldArtwork
        if (eraseArtwork) {
            mySoldArtwork.insert(mySoldArtwork.begin(), artworkInfo);
            cout << "Added to mySoldArtwork" << endl;
            return true;
        } else {
            cout << "No art found" << endl;
            return false;
        }
    }

    bool operator ==(const ArtCollection &target) {
        bool isEqual = true;
        isEqual = isEqual && (myArtwork == target.myArtwork);
        isEqual = isEqual && (mySoldArtwork == target.mySoldArtwork);
        return isEqual;
    }
};

int main() {
    ArtCollection myArt;
    Artwork art1("jon", "coolArt1", 1999);
    Artwork art2("jon", "coolArt1", 2000);

    SoldArtwork art3("aman", "295 Lester", 4206969.0, "jon", "coolArt1", 1999);
    SoldArtwork art4("aman", "295 Lester", 4206969.0, "jon", "coolArt1", 2000);

    myArt.insertArtwork(art1);
    myArt.insertArtwork(art2);
    myArt.sellArtwork(art3);

//    if (art3 == art4){
//        cout << "they are equal";
//    } else {
//        cout << "no";
//    }
    return 0;
}

