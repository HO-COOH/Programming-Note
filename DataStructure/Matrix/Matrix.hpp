template<typename T>
class Matrix
{
private:
    //dimension of the Matrix
    int rows;
    int columns;
    T* elements;
public:
    Matrix(int theRows=0, int theColumns=0);
    Matrix(const Matrix<T>& );
    ~Matrix() {delete[] elements;}
    int Rows() const {return rows;}
    int Columns() const {return columns;}
    T& operator(int row, int columns);
    Matrix<T>& operator=(const Matrix<T>&);
    Matrix<T> operator+() const;
    Matrix<T> operator+(const Matrix<T>&) const;
    Matrix<T> operator-() const;
    Matrix<T> operator-(const Matrix<T>&) const;
    Matrix<T> operator*(const Matrix<T>&) const;
    Matrix<T>& operator+=(const Matrix<T>&);
    Matrix<T> operator~(const Matrix<T>&);

};