#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include <algorithm>

template <typename T>
class Repository {
private:
    std::vector<T> items;

public:
    void add(const T& item) {
        items.push_back(item);
    }

    // Șterge din colecție toate elementele care 
    // îndeplinesc condiția specificată de predicat.
    //   |
    // Predicatul este o funcție care primește un element 
    // și returnează true dacă trebuie șters.
    //   |
    template <typename Predicate>
    inline void remove(Predicate predicate) {
        auto it = std::remove_if(items.begin(), items.end(), predicate);
        items.erase(it, items.end());
    }



    // Caută primul element care îndeplinește condiția specificată de predicat.
    //  |
    // Returnează un pointer către acel element, sau nullptr dacă nu a fost găsit.
    //  |
    template <typename Predicate>
    T* find(Predicate predicate) {
        auto it = std::find_if(items.begin(), items.end(), predicate);
        return (it != items.end()) ? &(*it) : nullptr;
    }


    // Returnează o referință constantă la vectorul intern cu toate elementele din repository.
    //  |
    // Permite accesul read-only la întreaga colecție.
    //  |
    const std::vector<T>& getAll() const {
        return items;
    }

    // Funcție dependentă de T
    // _____________________________
    // Returnează toate elementele care îndeplinesc o condiție specificată de un predicat cu doi parametri.
    //   |
    // Predicatul primește un element și o valoare suplimentară, și decide dacă acel element se potrivește.
    //   |
    template <typename U, typename Predicate>
    std::vector<T> filter(Predicate predicate, U value) {
        std::vector<T> result;
        std::copy_if(items.begin(), items.end(), std::back_inserter(result),
            [&](const T& item) { return predicate(item, value); });
        return result;
    }
    


};
#endif // REPOSITORY_H