#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

#include "set.h"

std::vector<std::string> tokenizacjaPliku(const std::string& nazwapliku) {
    std::ifstream plik(nazwapliku);
    std::vector<std::string> slowa;

    if (plik.is_open()) {
        std::string linia;
        while (std::getline(plik, linia)) {
            std::istringstream iss(linia);
            std::string slowo;
            while (iss >> slowo) {
                std::string slowo_oczyszczone;
                for (char& c : slowo) {
                    if (std::isalpha(c)) {
                        slowo_oczyszczone += std::tolower(c);
                    }
                }
                if (!slowo_oczyszczone.empty()) {
                    slowa.push_back(slowo_oczyszczone);
                }
            }
        }
        plik.close();
    } else {
        std::cerr << "Nie mozna otworzyc pliku: " << nazwapliku << std::endl;
    }

    return slowa;
}

Set znajdzWspolneSlowa(const Set& set1, const Set& set2) {
    Set wspolneSlowa;
    for (size_t i = 0; i < set1.zwrocRozmiar(); ++i) {
        if (set2.czyZawiera(set1[i])) {
            wspolneSlowa.dodaj(set1[i]);
        }
    }
    return wspolneSlowa;
}

Set znajdzUnikatoweSlowa(const Set& set1, const Set& set2) {
    Set unikatoweSlowa1, unikatoweSlowa2;
    for (size_t i = 0; i < set1.zwrocRozmiar(); ++i) {
        if (!set2.czyZawiera(set1[i])) {
            unikatoweSlowa1.dodaj(set1[i]);
        }
    }
    for (size_t i = 0; i < set2.zwrocRozmiar(); ++i) {
        if (!set1.czyZawiera(set2[i])) {
            unikatoweSlowa2.dodaj(set2[i]);
        }
    }

    std::cout << "1.txt:" << std::endl;
    for (size_t i = 0; i < unikatoweSlowa1.zwrocRozmiar(); ++i) {
        std::cout << unikatoweSlowa1[i] << std::endl;
    }

    std::cout << "2.txt:" << std::endl;
    for (size_t i = 0; i < unikatoweSlowa2.zwrocRozmiar(); ++i) {
        std::cout << unikatoweSlowa2[i] << std::endl;
    }

    return unikatoweSlowa1;
}

Set znajdzWszystkieSlowa(const Set& set1, const Set& set2) {
    Set wszystkieSlowa;
    for (size_t i = 0; i < set1.zwrocRozmiar(); ++i) {
        //std::cout << set1[i] << " ";
        wszystkieSlowa.dodaj(set1[i]);
    }
    for (size_t i = 0; i < set2.zwrocRozmiar(); ++i) {
        //std::cout << set2[i] << " ";
        wszystkieSlowa.dodaj(set2[i]);
    }

    return wszystkieSlowa;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uzycie: " << argv[0] << " <komenda> <plik1> <plik2>" << std::endl;
        return 1;
    }

    std::string komenda = argv[1];
    std::vector<std::string> nazwypliku;

    for (int i = 2; i < argc; ++i) {
        nazwypliku.push_back(argv[i]);
    }


    std::vector<std::string> slowa1 = tokenizacjaPliku(nazwypliku[0]);
    std::vector<std::string> slowa2 = tokenizacjaPliku(nazwypliku[1]);

    Set set1, set2;
    for (const auto& slowo : slowa1) {
        //std::cout << slowo;
        set1.dodaj(slowo);
    }
    for (const auto& slowo : slowa2) {
        //std::cout << slowo;
        set2.dodaj(slowo);
    }

    if (komenda == "common_words") {
        Set wspolneSlowa = znajdzWspolneSlowa(set1, set2);
        for (size_t i = 0; i < wspolneSlowa.zwrocRozmiar(); ++i) {
            std::cout << wspolneSlowa[i] << std::endl;
        }
    } else if (komenda == "unique_words") {
        znajdzUnikatoweSlowa(set1, set2);
    } else if (komenda == "all_words") {
        Set wszystkieSlowa = znajdzWszystkieSlowa(set1, set2);
        for (size_t i = 0; i < wszystkieSlowa.zwrocRozmiar(); ++i) {
            std::cout << wszystkieSlowa[i] << std::endl;
        }
    } else {
        std::cerr << "Nieznana komenda." << std::endl;
        return 1;
    }
}


