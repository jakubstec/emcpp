#include <iostream>
#include <initializer_list>
#include <algorithm>
class Matrix
{
private:
    int N, M;
    double *data;

public:
    Matrix() : N(0), M(0), data(nullptr)
    {
        std::cout << "default constructor called\n";
    }
    Matrix(int _N, int _M) : N(_N), M(_M), data(new double[N * M]{})
    {
        std::cout << "constructor with dimensions in argument called\n"
                  << N << "x" << M << " matrix created\n";
    }

    Matrix(std::initializer_list<std::initializer_list<double>> l) : N(0), M(0)
    {
        std::cout << "constructor with initializer list in argument called\n";
        N = l.size();
        for (const auto &r : l)
        {
            M = std::max(M, (int)r.size());
        }
        data = new double[M * N]{};

        int i = 0;

        for (const auto &r : l)
        {
            int j = 0;
            for (const auto &val : r)
            {
                data[i * M + j] = val;
                j++;
            }
            i++;
        }
    }

    Matrix(const Matrix &o) : N(o.N), M(o.M), data(new double[N * M]{})
    {
        std::cout << "copy constructor called\n";
        for (int i = 0; i < N * M; i++)
            data[i] = o.data[i];
    }
    ~Matrix()
    {
        std::cout << "destructor called\n";
        delete[] data;
    }

    Matrix &operator=(const Matrix &o)
    {
        std::cout << "copy assignment operator called\n";
        if (this == &o)
            return *this;
        delete[] data;
        N = o.N;
        M = o.M;
        data = new double[N * M]{};
        for (int i = 0; i < N * M; i++)
        {
            data[i] = o.data[i];
        }
        return *this;
    }

    const double &operator()(int i, int j) const
    {
        return data[(i - 1) * M + (j - 1)];
    }
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
};

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    for (int i = 0; i < m.N; i++)
    {
        for (int j = 0; j < m.M; j++)
        {
            os << m.data[i * m.M + j] << " ";
        }
        os << '\n';
    }
    return os;
}

int main()
{
    Matrix m1;
    Matrix m2(3, 4);
    Matrix m3({{1, 2, 3}, {32, 23, 22}, {3, 234, 23, 44}});
    std::cout << m2(1, 1) << std::endl; // 0
    std::cout << m3(2, 2) << std::endl; // 23
    std::cout << m3;

    std::cout << "Copy semantics \n";
    Matrix m4 = m2;
    m4 = m3;
}