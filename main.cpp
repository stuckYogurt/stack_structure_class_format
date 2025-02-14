#include <iostream>
using namespace std;

struct subvector {
    unsigned int top;
    unsigned int capacity;
    int* mas;
};

class Stack {
public:
    Stack() {
        qv = new subvector;
        qv->top = 0;
        qv->capacity = 0;
        qv->mas = nullptr;
    }

    ~Stack() {
        delete[] qv->mas;

        delete this->qv;
    }

    bool push_back(int d); // добавление элемента в конец с выделением дополнительной памяти при необходимости

    int pop_back(); // удаление элемента с конца, значение удаленного элемента вернуть (если пустой, вернуть ноль)

    bool resize(unsigned int new_capacity); // увеличить емкость (можно использовать и для уменьшения - тогда, в рамках данной реализации, если top меньше новой capacity, то копируем только то, что влезает, и уменьшаем top до capacity)

    void shrink_to_fit(); // очистить неиспользуемую память, переехав на новое место с уменьшением capacity до top

    void clear(); // очистить содержимое , занимаемое место при этом не меняется

private:
    subvector *qv;
};


bool Stack::push_back(int d) {
    if (qv->top + 1 > qv->capacity) {
        resize(qv->capacity + 1);
    }
    qv->mas[qv->top] = d;
    qv->top++;
    return true;
}

int Stack::pop_back() {
    if (qv->top == 0) return 0;

    qv->top--;
    return qv->mas[qv->top];
}

bool Stack::resize(unsigned int new_capacity) {
    if (qv->capacity == new_capacity) return true;

    int* _n_arr = new int[new_capacity];
    for (int i = 0; i< (int)std::min(qv->top, new_capacity); i++) {
        _n_arr[i] = qv->mas[i];
    }
    delete[] qv->mas;

    qv->mas = _n_arr;
    qv->capacity = new_capacity;
    qv->top = std::min(new_capacity, qv->top);
    return true;
}

void Stack::shrink_to_fit() {
    resize(qv->top);
}

void Stack::clear() {
    qv->top = 0;
}


int main() {
    Stack sb;
    sb.push_back(3);
    sb.push_back(4);
    sb.push_back(5);
    cout<<sb.pop_back()<<endl;
}