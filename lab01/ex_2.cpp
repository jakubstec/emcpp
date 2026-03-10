#include <iostream>
class Matrix
{
private:
    int N, M;
    double *data;

public:
    Matrix(int _N, int _M) : N(_N), M(_M), data(new double[_N * _M]{})
    {
        std::cout << "constructor with dimensions in argument called\n"
                  << N << "x" << M << " matrix created\n";
    }

    ~Matrix()
    {
        std::cout << "destructor called\n";
        delete[] data;
    }

    Matrix(Matrix &&o) : N(o.N), M(o.M), data(o.data)
    {
        std::cout << "move constructor called\n";
        o.N = 0;
        o.M = 0;
        o.data = nullptr;
    }

    Matrix &operator=(Matrix &&o)
    {
        std::cout << "move assignment operator called\n";
        if (this == &o)
            return *this;
        delete[] data;
        N = o.N;
        M = o.M;
        data = o.data;
        o.N = 0;
        o.M = 0;
        o.data = nullptr;
        return *this;
    }

    Matrix operator-() const
    {
        std::cout << "unary operator - called\n";
        Matrix result(N, M);
        for (int i = 0; i < N * M; i++)
            result.data[i] = -data[i];
        return result;
    }

    double operator()(int i, int j) const
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
    std::cout << "Move semantics \n";
    Matrix m2(3, 4);
    Matrix m3(3, 4);
    Matrix m7 = std::move(m2);
    Matrix m4(3, 4);
    m4 = -m3;

    std::cout << "Copy elision \n";
    Matrix m6 = -m4;
    Matrix *pm = new Matrix(-m4);
    std::cout << m6(2, 1) << std::endl;
}