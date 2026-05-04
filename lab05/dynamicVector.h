#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H
#include "staticVector.h"  

class VectorException : public std::runtime_error {
public:
    VectorException(const std::string& msg) : std::runtime_error(msg) {}
};

struct artificialType{};

template <typename U, size_t M> class Vector;

template <typename T>
class Vector<T,0> {
    unique_ptr<T[]> data;
    size_t current_size;

    Vector(artificialType, std::size_t n) : data(std::make_unique<T[]>(n)), current_size(n) {}

public:
    typedef T value_type;
    typedef std::size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    Vector(size_type n) : data(std::make_unique<T[]>(n)), current_size(n) {
        std::fill(data.get(),data.get() + current_size, T{}); 
    }
    Vector(const Vector & v) : data(std::make_unique<T[]>(v.current_size)), current_size(v.current_size) {
        std::copy(v.data.get(), v.data.get() + current_size, data.get()); 
    }
    Vector &operator=(Vector m) {
        std::swap(data, m.data);
        std::swap(current_size,m.current_size);
        return *this;
    }
    Vector(const std::initializer_list<T> &list) 
        : data(std::make_unique<T[]>(list.size())), current_size(list.size()) {
        std::copy(list.begin(), list.end(), data.get());
    }

    friend Vector operator+ (const  Vector & u, const Vector & v ){
        if (u.current_size != v.current_size)
            throw VectorException("incompatible sizes error");
        
        Vector res(artificialType{}, u.current_size);
        for(size_type i = 0; i < u.current_size; i++) {
            res[i] = u[i] + v[i];
        }
        return res;
    }

    void resize(size_type newSize) {
        if (newSize == current_size) return;

        auto newData = std::make_unique<T[]>(newSize);
        size_type copySize = std::min(current_size, newSize);
        
        std::move(data.get(), data.get() + copySize, newData.get());
        
        if (newSize > current_size) {
            std::fill(newData.get() + current_size, newData.get() + newSize, T{});
        }

        data = std::move(newData);
        current_size = newSize;
    }

    Vector(Vector&& v) : data(std::move(v.data)), current_size(v.current_size) {
        v.current_size = 0;
    }

    Vector& operator=(Vector&& v) {
        data = std::move(v.data);
        current_size = v.current_size;
        v.current_size = 0;
        return *this;
    }

    template <size_t N>
    Vector(const Vector<T, N>& stat) 
        : data(std::make_unique<T[]>(N)), current_size(N) {
        for(size_t i = 0; i < N; ++i) data[i] = stat[i];
    }

    constexpr size_type size() const {
        return current_size;
    }

    const_reference get(size_type index) const {
        return data[index];
    }

    void set(size_type index, const_reference value) {
        data[index] = value;
    }

    reference operator[](size_type index){
        return data[index];
    }
    const_reference operator[](size_type index) const{
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
        for(size_t i = 0; i < v.size(); i++) {
            out << v.data[i] << " ";
        }
        return out;
    }

    template <typename U, size_t M> friend class Vector;

};

#endif // DYNAMIC_VECTOR_H