// Aman Mathur 20710307
//       &&
// Jonathan Chen 20722167
//
// SYDE 223 Practice Assignment #1

#include <iostream>
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
            return true;
        } else {
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
            }
        }

        //Add to mySoldArtwork
        if (eraseArtwork) {
            mySoldArtwork.insert(mySoldArtwork.begin(), artworkInfo);
            return true;
        } else {
            return false;
        }

    }

    bool operator ==(const ArtCollection &target) {
        bool isEqual = true;
        isEqual = isEqual && (myArtwork == target.myArtwork);
        isEqual = isEqual && (mySoldArtwork == target.mySoldArtwork);
        return isEqual;
    }

    friend ArtCollection operator +(const ArtCollection &collection1, const ArtCollection &collection2) {
        ArtCollection combinedCollection;
        unsigned int long sizeOfCollection1Artwork = collection1.myArtwork.size();
        unsigned int long sizeOfCollection2Artwork = collection2.myArtwork.size();
        unsigned int long sizeOfCollection1SoldArtwork = collection1.mySoldArtwork.size();
        unsigned int long sizeOfCollection2SoldArtwork = collection2.mySoldArtwork.size();

        for (int i = 0; i < sizeOfCollection1Artwork; i++) {
            combinedCollection.myArtwork.push_back(collection1.myArtwork.at(i));
        }

        for (int i = 0; i < sizeOfCollection2Artwork; i++) {
            combinedCollection.myArtwork.push_back(collection2.myArtwork.at(i));
        }

        for (int i = 0; i < sizeOfCollection1SoldArtwork; i++) {
            combinedCollection.mySoldArtwork.push_back(collection1.mySoldArtwork.at(i));
        }

        for (int i = 0; i < sizeOfCollection2SoldArtwork; i++) {
            combinedCollection.mySoldArtwork.push_back(collection2.mySoldArtwork.at(i));
        }

        return combinedCollection;
    }
};

void test_insert_artwork(ArtCollection &myArt1, ArtCollection &myArt2) {

    Artwork art0;
    Artwork guernica("Picasso", "Guernica", 1937);
    Artwork theOldGuitarist("Picasso", "The Old Guitarist", 1903);
    Artwork theWeepingWoman("Picasso", "The Weeping Woman", 1937);
    Artwork theWeepingWomanCriesAgain("Picasso", "The Weeping Woman", 1937);

    Artwork sistineChapel("Michelangelo", "Sistine Chapel Ceiling", 1512);
    Artwork pieta("Michelangelo", "Pieta", 1499);
    Artwork david("Michelangelo", "David", 1504);

    if (theWeepingWoman == theWeepingWomanCriesAgain) {
        cout << "These paintings are the same!" << endl;
    }

    if (myArt1.insertArtwork(guernica)) {
        cout << "Inserted Guernica" << endl;
    }
    if (myArt1.insertArtwork(theOldGuitarist)) {
        cout << "Inserted The Old Guitarist" << endl;
    }
    if (myArt1.insertArtwork(theWeepingWoman)) {
        cout << "Inserted The Weeping Woman" << endl;
    }
    if (myArt1.insertArtwork(theWeepingWomanCriesAgain)) {
        cout << "Inserted The Weeping Woman Cries Again" << endl;
    } else {
        cout << "Duplicate of The Weeping Woman! Did not insert into collection" << endl;
    }

    myArt2.insertArtwork(sistineChapel);
    myArt2.insertArtwork(pieta);
    myArt2.insertArtwork(david);
}

void test_sell_artwork(ArtCollection &myArt1, ArtCollection &myArt2) {
    Artwork art10("money", "coolart1", 1999);

    SoldArtwork art0;
    SoldArtwork soldGuernica("John Smith", "111 Lester", 123456.789, "Picasso", "Guernica", 1937);
    SoldArtwork soldPieta("Johnson", "123 Lester", 127465, "Michelangelo", "Pieta", 1499);
    SoldArtwork soldDavid("Ericsson", "1000 sunview", 89.89, "Michelangelo", "David", 1504);
    SoldArtwork soldPietaCopy("Johnson", "123 Lester", 127465, "Michelangelo", "Pieta", 1499);

    if (soldPieta == soldPietaCopy) {
        cout << "Pieta Artworks are the Same!" << endl;
    }

    if (myArt1.sellArtwork(soldGuernica)) {
        cout << "Sold Guernica" << endl;
    }

    if (myArt2.sellArtwork(soldPieta)) {
        cout << "Sold Pieta" << endl;
    }

    if (myArt2.sellArtwork(soldDavid)) {
        cout << "Sold David" << endl;
    }

    if (myArt2.sellArtwork(soldPietaCopy)) {
        cout << "Sold Pieta Copy" << endl;
    } else {
        cout << "Cannot sell duplicate item!" << endl;
    }

}

void testEqualArtCollections() {
    ArtCollection myArt1;
    ArtCollection myArt2;

    Artwork art1("jon", "coolArt1", 1999);
    Artwork art2("jeff", "coolArt1", 2000);
    SoldArtwork art5("aman", "295 Lester", 123456.789, "jon", "coolArt1", 1999);

    myArt1.insertArtwork(art1);
    myArt1.insertArtwork(art2);

    myArt2.insertArtwork(art1);
    myArt2.insertArtwork(art2);

    myArt1.sellArtwork(art5);
    myArt2.sellArtwork(art5);

    if (myArt1 == myArt2) {
        cout << "The art collections are the same!" << endl;
    } else {
        cout << "Collections aren't the same!" << endl;
    }
}

void testAddCollections(ArtCollection myArt1, ArtCollection myArt2) {
    ArtCollection totalCollection;
    totalCollection = myArt1 + myArt2;
}

int main() {
    ArtCollection Picasso;
    ArtCollection Michelangelo;

    test_insert_artwork(Picasso, Michelangelo);
    test_sell_artwork(Picasso, Michelangelo);
    testEqualArtCollections();
    testAddCollections(Picasso, Michelangelo);

    return 0;
}

