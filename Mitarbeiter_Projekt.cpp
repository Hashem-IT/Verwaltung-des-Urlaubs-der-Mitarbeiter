
#include <iostream>     // Ein- und Ausgabe
#include <string>       // Zeichenkettenverarbeitung

using namespace std;    // Verwende den Standard-Namespace

// Funktion Jahr von Strin zu int umzuwendeln
int stringToInt(const string &str)
{
    int result = 0;
    for (char c: str) {
        // Bedienung: Zeichen zwischen 0 und 9 setzt die Zahl zwischen 0 und 9 gemäß ASCII-Tabelle.
        if (c >= '0' && c <= '9')
        {
            result = result * 10 + (c - '0');
        } else {
            break;
        }
    }
    return result;
}

// Definition der Mitarbeiter-Klasse
class Mitarbeiter
{
private:
    string nachname;        // Name des Mitarbeiters
    string vorname;         // Vorname des Mitarbeiters
    string geburtsdatum;    // Geburtsdatum des Mitarbeiters
    int behinderungsgrad;   // Grad der Behinderung des Mitarbeiters
    int genommenUrlaub;     // Anzahl der genommenen Urlaubstage

public:
    // Konstruktor der Klasse Mitarbeiter
    Mitarbeiter(const string& nachname, const string& vorname, const string& gebDatum, int behindGrad)
            : nachname(nachname), vorname(vorname), geburtsdatum(gebDatum), behinderungsgrad(behindGrad), genommenUrlaub(0) {}

    // Getter  für NachName
    const string& getNachName() const { return nachname; }

    // Getter  für Vorname
    const string& getVorname() const { return vorname; }

    // Berechnung und Verwaltung des Urlaubs
    int UrlaubstageRechnen() const
    {
        int basisUrlaub = 30;                                                   // Basisurlaubstage
        int currentJahr = 2024;                                                 // Aktuelles Jahr
        int geburtsjahr = stringToInt (geburtsdatum.substr(0, 4));   // Extrahiere Geburtsjahr aus dem Geburtsdatum

        // Bedienung: Wenn der Mitarbeiter 50 Jahre oder älter ist, Zusätzliche 2 Urlaubstage hinzufügen
        if (currentJahr - geburtsjahr >= 50)
        { basisUrlaub += 2;}
        // Bedienung: Wenn der Behinderungsgrad 50% oder mehr beträgt,Zusätzliche 5 Urlaubstage hinzufügen
        if (behinderungsgrad >= 50)
        { basisUrlaub += 5;}
        return basisUrlaub;
    }

    // Methode zum Eintragen von Urlaub
    void urlaubNehmen(int tage) { genommenUrlaub += tage; }

    // Berechnung des restUrlaubs
    int restUrlaub() const { return UrlaubstageRechnen() - genommenUrlaub; }

    // Anzeige der Mitarbeiterinfo
    void anzeigen() const
    {
        cout << "Name: " << nachname << ", " <<  vorname << "\n"
             << "Geburtsdatum: " << geburtsdatum << "\n"
             << "Grad der Behinderung: " << behinderungsgrad << "%\n"
             << "Genommener Urlaub: " << genommenUrlaub << " Tage\n"
             << "RestUrlaub: " << restUrlaub() << " Tage\n";
    }
};

// Definition der Verwaltung-Klasse
class Verwaltung
{
private:
    Mitarbeiter* mitarbeiterListe[500];                                   // Array von Zeigern auf Mitarbeiter
public:
    int anzahlMitarbeiter;                                              // Anzahl der Mitarbeiter

public:
    // Konstruktor der Klasse Verwaltung
    Verwaltung() : anzahlMitarbeiter(0) {}

    // Methode zum Hinzufügen eines Mitarbeiters
    void mitarbeiterHinzufugen(const Mitarbeiter& m)
    {                                                                   // Überprüfen, ob die maximale Anzahl erreicht ist
        mitarbeiterListe[anzahlMitarbeiter] = new Mitarbeiter(m);   // Mitarbeiter hinzufügen
        anzahlMitarbeiter++;                                        // Anzahl der Mitarbeiter erhöhen
    }

    // Methode zum Eintragen von Urlaub
    void urlaubEintragen(const string& nachname, const string& vorname, int tage)
    {
        for (int i = 0; i < anzahlMitarbeiter; i++)
        {
            // Bedienung: Wenn der die Name und Vorname stimmen, beantragen für Urlaubtagen
            if (mitarbeiterListe[i]->getNachName() == nachname && mitarbeiterListe[i]->getVorname() == vorname)
            {
                mitarbeiterListe[i]->urlaubNehmen(tage);                // Urlaub eintragen
                mitarbeiterListe[i]->anzeigen();                        // Mitarbeiterinformationen anzeigen
                return;
            }
        }
        cout << "Mitarbeiter nicht gefunden.\n";
        cout << endl;
    }

    // Methode zum Suchen eines Mitarbeiters
    void mitarbeiterSuchen(const string& nachname, const string& vorname)
    {
        for (int i = 0; i < anzahlMitarbeiter; i++)
        {
            // Bedienung: Wenn der die Name und Vorname stimmen, gib die Info über den Mitarbeiter zurück
            if (mitarbeiterListe[i]->getNachName() == nachname && mitarbeiterListe[i]->getVorname() == vorname)
            {
                mitarbeiterListe[i]->anzeigen();                        // Mitarbeiterinformationen anzeigen
                return;
            }
        }
        cout << "Mitarbeiter nicht gefunden.\n";
        cout << endl;
    }

    // Methode zum Anzeigen aller Mitarbeiter
    void alleMitarbeiterAnzeigen()
    {
        for (int i = 0; i < anzahlMitarbeiter; i++)
        {
            mitarbeiterListe[i]->anzeigen();                              // Mitarbeiterinformationen anzeigen
            cout << endl;
        }
    }

    // Methode zum Löschen eines Mitarbeiters
    void mitarbeiterLoschen(const string& nachname, const string& vorname)
    {
        for (int i = 0; i < anzahlMitarbeiter; i++)
        {
            if (mitarbeiterListe[i]->getNachName() == nachname && mitarbeiterListe[i]->getVorname() == vorname)
            {
                mitarbeiterListe[i] = NULL;                             // Mitarbeiter löschen

                for (int j = i; j < anzahlMitarbeiter - 1; j++) {
                    mitarbeiterListe[j] = mitarbeiterListe[j + 1];      // Array neu organisieren
                }
                anzahlMitarbeiter--;                                    // Anzahl der Mitarbeiter verringern
                cout << "Mitarbeiter erfolgreich geloscht.\n";
                return;
            }
        }
        cout << "Mitarbeiter nicht gefunden.\n";
    }

};

// Hauptprogramm Main()
int main()
{
    // Verwaltung Definition und Methoden zu benutzen
    Verwaltung verwaltung;

    // nachname, vorname, geburtsdatum und behinderungsgrad  Definition
    string nachname, vorname, geburtsdatum;
    int behinderungsgrad;

    // Hinzufügen von Mitarbeitern
    verwaltung.mitarbeiterHinzufugen(Mitarbeiter("Hashem"   , "MohamadYassin", "1996-12-02", 0));               // Normaler Mitarbeiter
    verwaltung.mitarbeiterHinzufugen(Mitarbeiter("Schueeger", "Lukas"        , "1960-01-01", 0));               // Er ist 50 Jahre alt
    verwaltung.mitarbeiterHinzufugen(Mitarbeiter("Master"   , "Max"          , "1990-01-01", 60));              // Er hat mehr als 50 Behinderungsgrad
    verwaltung.mitarbeiterHinzufugen(Mitarbeiter("Therisa"  , "Lisa"         , "1960-01-01", 60));              // Sie ist 50 und hat mehr als 50 Behinderungsgrad


    // Benutzereingaben für neuen Mitarbeiter
    // Test Eingabe 4 Mitarbeiter
    for (int i = 0; i < 4; ++i)
    {
        // Bedienung nicht mehr als 500 Mitarbeiter hinzufügen dürfen
        if (verwaltung.anzahlMitarbeiter >= 500)
        {
            cout << "Maximale Anzahl von Mitarbeitern erreicht. => "<< verwaltung.anzahlMitarbeiter <<" \n"; break;}

        // Eingabe für den Nachnamen
        cout << "Geben Sie den Nachnamen ein: " << endl;
        cin >> nachname;

        // Eingabe für den Vornamen
        cout << "Geben Sie den Vornamen ein: " << endl;
        cin >> vorname;

        // Eingabe für das Geburtsdatum
        cout << "Geben Sie das Geburtsdatum ein (YYYY-MM-DD): " << endl;
        cin >> geburtsdatum;

        // Eingabe für den Grad der Behinderung
        cout << "Geben Sie den Grad der Behinderung ein (0-100): " << endl;
        cin >> behinderungsgrad;

        // Manuelles Hinzufügen von Mitarbeitern
        verwaltung.mitarbeiterHinzufugen(Mitarbeiter(nachname, vorname, geburtsdatum, behinderungsgrad));
    }

    // Alle Mitarbeiter anzeigen
    cout << endl;
    cout << "Alle Mitarbeiter" << endl;
    cout << " -------------------------" << endl;
    // alleMitarbeiterAnzeigen Methode aufrufen
    verwaltung.alleMitarbeiterAnzeigen();
    cout << " -------------------------" << endl;

    // Urlaub eintragen
    // nachnameUE, vornameLE und urlaubsTagen  Definition
    string nachnameUE, vornameLE;
    int urlaubsTagen;
    // Eingabe für den Nachnamen
    cout << "Geben Sie den Nachnamen zum Urlaubseintragen ein: " << endl;
    cin >> nachnameUE;

    // Eingabe für den Vornamen
    cout << "Geben Sie den Vornamen zum Urlaubseintragen ein: " << endl;
    cin >> vornameLE;


    // Eingabe für die Anzahl der Urlaubstage
    cout << "Geben Sie die Anzahl der Urlaubstage zum Urlaubseintragen ein: " << endl;
    cin >> urlaubsTagen;

    // urlaubEintragen Methode aufrufen
    verwaltung.urlaubEintragen(nachnameUE, vornameLE, urlaubsTagen);

    // bestimmten Mitarbeiter suchen
    // nachnamebM und vornamebM  Definition
    string nachnamebM, vornamebM;
    cout << endl;
    cout << "Suchen Sie bestimmte Mitarbeiter?" << endl;
    // Eingabe für den Nachnamen
    cout << "Geben Sie den Nachnamen zum Suchen ein: " << endl;
    cin >> nachnamebM ;

    // Eingabe für den Vornamen
    cout << "Geben Sie den Vornamen zum Suchen ein: " << endl;
    cin >> vornamebM;

    cout << endl;
    // mitarbeiterSuchen Methode aufrufen
    cout << "Mitarbeiter gefunden" << endl;
    cout << " -------------------------" << endl;
    // mitarbeiterSuchen Methode aufrufen
    verwaltung.mitarbeiterSuchen(nachnamebM, vornamebM);
    cout << " -------------------------" << endl;

    // Löschen
    // nachnameL und vornameL  Definition
    string nachnameL, vornameL;
    // Eingabe für den Nachnamen
    cout << "Geben Sie den Nachnamen zum Loschen ein: " << endl;
    cin >> nachnameL;

    // Eingabe für den Vornamen
    cout << "Geben Sie den Vornamen zum Loschen ein: " << endl;
    cin >> vornameL;

    // mitarbeiterLoschen Methode aufrufen
    verwaltung.mitarbeiterLoschen(nachnameL, vornameL);
    cout << endl;
    cout << "Alle Mitarbeiter" << endl;
    cout << " -------------------------" << endl;
    // alleMitarbeiterAnzeigen Methode aufrufen
    verwaltung.alleMitarbeiterAnzeigen();
    cout << " -------------------------" << endl;

    return 0;
}


/*
 * Info:
- const vor den Datentyp, so kann eine Variable nur gelesen werden,
- stringToInt: Wandelt einen String in eine Ganzzahl um. Betrachtet dabei nur die Zeichen, die Ziffern ('0'-'9') sind
- Mitarbeiter-Klasse : Initialisiert ein neues Mitarbeiter-Objekt mit Nachname, Vorname, Geburtsdatum und Behinderungsgrad.
- getNachName : Gibt den Nachnamen des Mitarbeiters zurück.
- getVorname : Gibt den Vornamen des Mitarbeiters zurück.
- UrlaubstageRechnen : Berechnet die jährlichen Urlaubstage des Mitarbeiters basierend auf Alter und Behinderungsgrad.
- urlaubNehmen : Erhöht die Anzahl der genommenen Urlaubstage um die angegebene Anzahl.
- restUrlaub : Berechnet die verbleibenden Urlaubstage des Mitarbeiters.
- anzeigen : Zeigt die Informationen des Mitarbeiters auf der Konsole an.
- Verwaltung-Konstruktor:  Initialisiert ein neues Verwaltung-Objekt mit leerer Mitarbeiterliste.
- mitarbeiterHinzufugen : Fügt einen neuen Mitarbeiter zur Verwaltung hinzu
- urlaubEintragen : Trägt für einen bestimmten Mitarbeiter Urlaubstage ein.
- mitarbeiterSuchen : Sucht und zeigt die Informationen eines bestimmten Mitarbeiters an.
- alleMitarbeiterAnzeigen : Zeigt die Informationen aller Mitarbeiter an.
- mitarbeiterLoschen : Löscht einen bestimmten Mitarbeiter aus der Verwaltung.



Ausgabe:
 Geben Sie den Nachnamen ein:
Muster
Geben Sie den Vornamen ein:
Max
Geben Sie das Geburtsdatum ein (YYYY-MM-DD):
2001-01-01
Geben Sie den Grad der Behinderung ein (0-100):
0
Maximale Anzahl von Mitarbeitern erreicht => 500 .

Alle Mitarbeiter
 -------------------------
Name: Hashem, MohamadYassin
Geburtsdatum: 1996-12-02
Grad der Behinderung: 0%
Genommener Urlaub: 0 Tage
RestUrlaub: 30 Tage

Name: Schueeger, Lukas
Geburtsdatum: 1960-01-01
Grad der Behinderung: 0%
Genommener Urlaub: 0 Tage
RestUrlaub: 32 Tage

Name: Master, Max
Geburtsdatum: 1990-01-01
Grad der Behinderung: 60%
Genommener Urlaub: 0 Tage
RestUrlaub: 35 Tage

Name: Therisa, Lisa
Geburtsdatum: 1960-01-01
Grad der Behinderung: 60%
Genommener Urlaub: 0 Tage
RestUrlaub: 37 Tage

Name: Muster, Max
Geburtsdatum: 2001-01-01
Grad der Behinderung: 0%
Genommener Urlaub: 0 Tage
RestUrlaub: 30 Tage

 -------------------------
Geben Sie den Nachnamen zum Urlaubseintragen ein:
Hashem
Geben Sie den Vornamen zum Urlaubseintragen ein:
MohamadYassin
Geben Sie die Anzahl der Urlaubstage zum Urlaubseintragen ein:
10
Name: Hashem, MohamadYassin
Geburtsdatum: 1996-12-02
Grad der Behinderung: 0%
Genommener Urlaub: 10 Tage
RestUrlaub: 20 Tage

Suchen Sie bestimmte Mitarbeiter?
Geben Sie den Nachnamen zum Suchen ein:
Schueeger
Geben Sie den Vornamen zum Suchen ein:
Lukas

Mitarbeiter gefunden
 -------------------------
Name: Schueeger, Lukas
Geburtsdatum: 1960-01-01
Grad der Behinderung: 0%
Genommener Urlaub: 0 Tage
RestUrlaub: 32 Tage
 -------------------------
Geben Sie den Nachnamen zum Loschen ein:
Therisa
Geben Sie den Vornamen zum Loschen ein:
Lisa
Mitarbeiter erfolgreich geloscht.

Alle Mitarbeiter
 -------------------------
Name: Hashem, MohamadYassin
Geburtsdatum: 1996-12-02
Grad der Behinderung: 0%
Genommener Urlaub: 10 Tage
RestUrlaub: 20 Tage

Name: Schueeger, Lukas
Geburtsdatum: 1960-01-01
Grad der Behinderung: 0%
Genommener Urlaub: 0 Tage
RestUrlaub: 32 Tage

Name: Master, Max
Geburtsdatum: 1990-01-01
Grad der Behinderung: 60%
Genommener Urlaub: 0 Tage
RestUrlaub: 35 Tage

Name: Muster, Max
Geburtsdatum: 2001-01-01
Grad der Behinderung: 0%
Genommener Urlaub: 0 Tage
RestUrlaub: 30 Tage

 -------------------------

 */
