#ifndef SET_H
#define SET_H

#include <string>

class Set {
private:
    std::string *data;
    size_t pojemnosc;
    size_t rozmiar;

    void powieksz() {
        pojemnosc *= 2;
        std::string *nowyData = new std::string[pojemnosc];
        for (size_t i = 0; i < rozmiar; ++i) {
            nowyData[i] = std::move(data[i]);
        }
        delete[] data;
        data = nowyData;
    }

    void sort() {
        for (size_t i = 0; i < rozmiar - 1; ++i) {
            for (size_t j = 0; j < rozmiar - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::string temp = std::move(data[j]);
                    data[j] = std::move(data[j + 1]);
                    data[j + 1] = std::move(temp);
                }
            }
        }
        
    }

public:
    Set() : data(new std::string[2]), pojemnosc(2), rozmiar(0) {}

    Set(Set&& other) noexcept : data(other.data), pojemnosc(other.pojemnosc), rozmiar(other.rozmiar) {
        other.data = nullptr;
        other.pojemnosc = 0;
        other.rozmiar = 0;
    }

    Set& operator=(Set&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            pojemnosc = other.pojemnosc;
            rozmiar = other.rozmiar;
            other.data = nullptr;
            other.pojemnosc = 0;
            other.rozmiar = 0;
        }
        return *this;
    }

    void dodaj(const std::string& slowo) {
        if (!czyZawiera(slowo)) {
            if (rozmiar == pojemnosc) {
                powieksz();
            }
            data[rozmiar++] = slowo;
            sort();
        }
    }


    bool czyZawiera(const std::string& slowo) const {
        for (size_t i = 0; i < rozmiar; ++i) {
            if (data[i] == slowo) {
                return true;
            }
        }
        return false;
    }

    size_t zwrocRozmiar() const {
        return rozmiar;
    }

    std::string& operator[](size_t index) const {
        return data[index];
    }

    void sortuj() {
        sort();
    }

    ~Set() {
        delete[] data;
    }

};

#endif // SET_H