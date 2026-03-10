#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <string>

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
            M = std::max(M, (int)r.size());
        data = new double[N * M]{};
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
            data[i] = o.data[i];
        return *this;
    }

    const double &operator()(int i, int j) const
    {
        return data[(i - 1) * M + (j - 1)];
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &m)
    {
        for (int i = 0; i < m.N; i++)
        {
            for (int j = 0; j < m.M; j++)
                os << m.data[i * m.M + j] << " ";
            os << '\n';
        }
        return os;
    }
};

class MatrixWithLabel : public Matrix
{
private:
    std::string label = "A";

public:
    MatrixWithLabel(std::string label, int N, int M)
        : Matrix(N, M), label(label)
    {
        std::cout << "MatrixWithLabel constructor called\n";
    }

    MatrixWithLabel(std::initializer_list<std::initializer_list<double>> l)
        : Matrix(l), label(label)
    {
        std::cout << "MatrixWithLabel initializer list constructor called\n";
    }

    std::string getLabel() const
    {
        return label;
    }

    void setLabel(std::string label)
    {
        this->label = label;
    }
};

int main()
{
    std::cout << "Inheritance \n";
    MatrixWithLabel l0("B", 3, 4);
    MatrixWithLabel l1({{1, 2}, {4, 5}});
    l1.setLabel("A");
    MatrixWithLabel l2 = l1;
    MatrixWithLabel l3 = std::move(l1);
    std::cout << l2.getLabel() << " " << l3.getLabel() << std::endl;
    std::cout << l1.getLabel() << std::endl;
}