#include <iostream>
template<typename type>
class vector
{

};

template<>
class vector<bool> 
{
private:
    size_t length{0};
    char* boolMas = new char[0];
public:

    // Конструктор
    vector<bool>() = default;

    // Метод добавления элемента в конец вектора
    void push_back(bool value)
    {
        if (length % 8 == 0)
        {
            char* temp = new char[(length / 8) + 1];
            for (int i = 0; i < length; i++)
            {
                temp[i] = boolMas[i];
            }
            delete[] boolMas;
            boolMas = temp;
            edit(length, value);
        }
        else {
            edit(length, value);
        }
        length++;
    }

    // Оператор получения элемента по индексу
    bool operator[](unsigned int index) const
    {
        return static_cast<bool>(((boolMas[index / 8]) >> index) & 0b00000001);
    }

    // Метод изменения элемента по индексу
    void edit(size_t index, bool value)
    {
        char degree = 1;
        for (int i = 0; i < index; i++) 
        {
            degree *= 2;
        }
        if (value)
        {
            boolMas[index / 8] |= degree;
        }
        else
        {
            boolMas[index / 8] &= ~degree;
        }
    }
    
    // Метод size
    size_t size() const
    {
        return length;
    }

    // Метод insert (добавляет элемент в вектор)
    void insert(size_t index, bool  value)
    {
        this->push_back(operator[](length - 1));
        for (size_t i = length; i != index; i--)
            edit(i, operator[](i - 1));

        edit(index, value);
    }

    // Метод erase (удаляет один или несколько идущих подряд элементов)
    void erase(size_t firstIndex, size_t lastIndex) 
    {
        for (size_t i = lastIndex; i < length; i++)
        {
            edit(i - (lastIndex - firstIndex), operator[](i));
        }
        length -= lastIndex - firstIndex;
    }
    void erase(size_t index) {
        for (size_t i = index; i < length - 1; i++) {
            edit(i, operator[](i + 1));
        }
        length--;
    }
};

int main() {
    vector<bool> bv;
    bv.push_back(true);
    bv.push_back(false);
    bv.push_back(true);
    bv.push_back(false);
    bv.push_back(false);
    bv.push_back(false);
    bv.push_back(true);
    bv.push_back(true);
    for (int i = 0; i < bv.size(); i++) {
        std::cout << bv[i] << " ";
    }

    bv.insert(3, true);
    std::cout << "\n";
    for (int i = 0; i < bv.size(); i++) {
        std::cout << bv[i] << " ";
    }

    bv.edit(1, true);
    std::cout << "\n";
    for (int i = 0; i < bv.size(); i++) {
        std::cout << bv[i] << " ";
    }

    bv.erase(3);
    std::cout << "\n";
    for (int i = 0; i < bv.size(); i++) {
        std::cout << bv[i] << " ";
    }

    bv.erase(1, 4);
    std::cout << "\n";
    for (int i = 0; i < bv.size(); i++) {
        std::cout << bv[i] << " ";
    }
    std::cout << " - size of vector: " << bv.size();
    return 0;
}