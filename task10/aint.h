#include <mutex>

class pseudo_atomic_int{
public:
pseudo_atomic_int() : data(0) {busy = new std::mutex();}
pseudo_atomic_int(int _data) : data(_data) {busy = new std::mutex();}

pseudo_atomic_int &operator=(const pseudo_atomic_int& _rhs){
    data = _rhs.data;
}

pseudo_atomic_int operator++(int _unused){
    busy->lock();
    pseudo_atomic_int _tmp = data;
    data++;
    busy->unlock();

    return _tmp;
}
pseudo_atomic_int operator--(int _unused){
    busy->lock();
    pseudo_atomic_int _tmp = data;
    data--;
    busy->unlock();

    return _tmp;
}

pseudo_atomic_int operator+(const pseudo_atomic_int &_rhs){
   busy->lock();
    pseudo_atomic_int _tmp = data + _rhs.data;
    busy->unlock();
    return _tmp;
}

inline operator int() const { busy->lock(); return data; busy->unlock();}

private:
    int data;
    std::mutex * busy;
    
};
