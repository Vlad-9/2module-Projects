//M3108-Влад.Ч
#include <iostream>
#include <fstream>

using namespace std ;

class Matrix {
    
    private :
    int ** values ;
    
    public :
    int n , m ;
    
    Matrix() {
        n = 0 ;
        m = 0 ;
        values = 0 ;
    }
    
    Matrix(int lines , int columns) {
        if (lines < 0 ) n = lines * -1; 
        else n = lines ;
        if (columns < 0) m = columns * -1;
        else m = columns ;
        values = new int*[n] ;
        for(int i = 0 ; i < n ; i++)
            values[i] = new int[m] ;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < m ; j++)
                values[i][j] = 0 ;
    }
    
    Matrix(Matrix const& mtrx) {
        n = mtrx.n ;
        m = mtrx.m ;
        values = new int*[n] ;
        for(int i = 0 ; i < n ; i++)
            values[i] = new int[m] ;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < m ; j++)
                values[i][j] = mtrx.values[i][j] ;
    }

    ~Matrix() {
        if(values != 0) {
            for(int i = 0 ; i < n ; i++)
                delete[] values[i] ;
            delete[] values ;
        }
    }
//---
    Matrix const operator+(Matrix const& mtrx) const {
        Matrix result(n , m) ;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < m ; j++)
                result.values[i][j] = values[i][j] + mtrx.values[i][j] ;
        return result ;
    }
    
    Matrix const operator+=(Matrix const& mtrx) const {
        Matrix result(n , m) ;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < m ; j++)
                values[i][j]+=mtrx.values[i][j];
        return *this ;
    }
    
    Matrix const operator-(Matrix const& mtrx) const {
        Matrix result(n , m) ;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < m ; j++)
                result.values[i][j] = values[i][j] - mtrx.values[i][j] ;
        return result ;
    }

    Matrix const operator-=(Matrix const& mtrx) const {
        Matrix result(n , m) ;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < m ; j++)
                values[i][j]-=mtrx.values[i][j];
        return *this ;
    }
    
    Matrix const operator*(Matrix const& mtrx) const {
        Matrix result(n , mtrx.m) ;
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < mtrx.m ; j++) {
                for(int k = 0 ; k < m ; k++)
                    result.values[i][j] = result.values[i][j] + values[i][k] * mtrx.values[k][j] ;
            }
        }
        return result ;
    }
    
    Matrix const operator*(int o) const {
        Matrix result(n , m) ;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < m ; j++)
                result.values[i][j] = values[i][j] * o ;
        return result ;
    }
    
    Matrix const operator*=(int o) const {
        Matrix result(n , m) ;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < m ; j++)
                values[i][j]*=o;
        return *this ;
    }
    
    void operator=(Matrix const& mtrx) {
        if(values==mtrx.values);
        else {
        if(values != 0) {
            for(int i = 0 ; i < n ; i++)
                delete[] values[i] ;
            delete[] values ;
        }
        n = mtrx.n ;
        m = mtrx.m ;
        values = new int*[n] ;
        for(int i = 0 ; i < n ; i++)
            values[i] = new int[m] ;
        for(int i = 0 ; i < n ; i++)
            for(int j = 0 ; j < m ; j++)
                values[i][j] = mtrx.values[i][j] ;
        }
    }
    
    int& operator()(int i , int j) {
        return values[i][j] ;
    }
    //---
    Matrix transpose()
    {
        Matrix result(m , n) ;
        for(int i = 0 ; i < m ; i++)
            for(int j = 0 ; j < n ; j++)
                result.values[i][j] = values[j][i] ;
        return result ;
    }
    
    Matrix DOT(Matrix const& mtrx)
    {
        Matrix result(n , mtrx.m) ;
        for(int i = 0 ; i < n ; i++) {
            for(int j = 0 ; j < mtrx.m ; j++) {
                for(int k = 0 ; k < m ; k++)
                    result.values[i][j] = result.values[i][j] + values[i][k] * mtrx.values[k][j] ;
            }
        }
        return result ;
    }

} ;

ostream& operator<<(ostream& os, Matrix& mtrx)
{
    for(int i = 0 ; i < mtrx.n ; i++){
        
        for(int j = 0 ; j < mtrx.m ; j++)
            os << mtrx(i,j) << " ";
        os << "\n";
    }
    return os;
}

ifstream& operator>> ( ifstream& ifs, Matrix& mtrx )
{
    for(int i = 0 ; i < mtrx.n ; i++)
        
        for(int j = 0 ; j < mtrx.m ; j++)
            ifs >> mtrx(i,j);
    return ifs;
}


int main() {

    int n,m;
 
    ifstream file;
    file.open("1.txt");
    file >> m >> n;
    Matrix mt(m,n);
    file >> mt;
    file.close();
    //mt=mt.transpose();
    cout << mt;
    return 0;
}
