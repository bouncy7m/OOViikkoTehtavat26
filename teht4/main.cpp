#include <iostream>
#include <string>

using namespace std;

class Pankkitili {
protected:
    string omistaja;
    double saldo;

public:
    Pankkitili(const string& nimi) : omistaja(nimi), saldo(0.0) {
        cout << "Pankkitili luotu " << omistaja << ":lle\n";
    }

    virtual ~Pankkitili() = default;

    double getBalance() const {
        return saldo;
    }

    virtual bool deposit(double maara) {
        if (maara <= 0) return false;
        saldo += maara;
        cout << "Pankkitili: talletus " << maara << " tehty\n";
        return true;
    }

    virtual bool withdraw(double maara) {
        if (maara <= 0) return false;
        if (maara > saldo) return false;
        saldo -= maara;
        cout << "Pankkitili: nosto " << maara << " tehty\n";
        return true;
    }
};

class Luottotili : public Pankkitili {
private:
    double luottoRaja;

public:
    Luottotili(const string& nimi, double luottoraja)
        : Pankkitili(nimi), luottoRaja(luottoraja) {
        saldo = luottoraja;
        cout << "Luottotili luotu " << omistaja << ":lle, luottoraja " << luottoraja << "\n";
    }

    bool deposit(double maara) override {
        if (maara <= 0) return false;
        saldo += maara;
        if (saldo > luottoRaja) saldo = luottoRaja;
        cout << "Luottotili: talletus " << maara << " tehty\n";
        return true;
    }

    bool withdraw(double maara) override {
        if (maara <= 0) return false;
        if (saldo - maara < 0) return false;
        saldo -= maara;
        double luottoaJaljella = saldo;
        cout << "Luottotili: nosto " << maara << " tehty, luottoa jaljella " << luottoaJaljella << "\n";
        return true;
    }
};

class Asiakas {
private:
    string nimi;
    Pankkitili* kayttoiti;
    Luottotili* luottotili;

public:
    Asiakas(const string& nimi, double luottoraja) : nimi(nimi) {
        kayttoiti = new Pankkitili(nimi);
        luottotili = new Luottotili(nimi, luottoraja);
        cout << "Asiakkuus luotu " << nimi << "\n";
    }

    ~Asiakas() {
        delete kayttoiti;
        delete luottotili;
    }

    string getNimi() const { return nimi; }

    void showSaldo() const {
        cout << nimi << "\n";
        cout << "Kayttotilin saldo " << kayttoiti->getBalance() << "\n";
        cout << "Luottotilin saldo " << luottotili->getBalance() << "\n\n";
    }

    bool talletus(double maara) { return kayttoiti->deposit(maara); }
    bool nosto(double maara) { return kayttoiti->withdraw(maara); }
    bool luotonMaksu(double maara) { return luottotili->deposit(maara); }
    bool luotonNosto(double maara) { return luottotili->withdraw(maara); }

    bool tiliSiirto(double maara, Asiakas& kohdeAsiakas) {
        if (maara <= 0) return false;
        if (kayttoiti->getBalance() < maara) return false;

        cout << "Pankkitili: " << nimi << " siirtaa " << maara
             << " " << kohdeAsiakas.getNimi() << ":lle\n";

        if (!kayttoiti->withdraw(maara)) return false;
        if (!kohdeAsiakas.talletus(maara)) {
            kayttoiti->deposit(maara);
            return false;
        }

        return true;
    }
};

int main() {
    Asiakas aapeli("Aapeli", 1000);
    aapeli.showSaldo();

    aapeli.talletus(250);
    aapeli.luotonNosto(150);
    aapeli.showSaldo();

    Asiakas bertta("Bertta", 1000);
    bertta.showSaldo();

    cout << "Aapeli\n";
    aapeli.showSaldo();

    if (aapeli.tiliSiirto(50, bertta)) {
        cout << "Siirto onnistui!\n";
    } else {
        cout << "Siirto epäonnistui!\n";
    }

    cout << "Bertta\n";
    bertta.showSaldo();

    cout << "\nPress <RETURN> to close this window.\n";
    cin.get();

    return 0;
}
