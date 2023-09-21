///
/// @file   mat.cpp
/// @author 
/// @date   Fri Sep 12 14:06:47 2008
/// 
/// @brief  Header of the Matrix class
/// 
/// 
///

#include "myspice.h"
#include <algorithm>

#define FREE_AND_SET_NULL(ptr) if(ptr){free(ptr);ptr=NULL;}


/// \class Mat 
///
/// \brief the matrix class
///
/// This is an empty class. You have to design you own Matrix class by
/// adding necessary data and public functions. \n
///
/// To facilliate the stamping process, the matrix class needs to satisfy 
/// the following condition:
/// - Dynamic allocation of the memory according to the size of the circuit.
/// - Expandable. Each time we stamp an element, the entries of the matrix may grow.
/// - Flexible and efficient. Most of the entries in the matrix would be zero and we don't need to store them. 
///
/// My advice is: Using orthogonal list data structure. \n
///
/// Currently, this class is designed as a C++ template. If you're not familliar with 
/// the concept of template. Just define a non-template class and do the same thing.


/// \brief Constructor
/// \param nrow #rows
/// \param ncol #columns
///
/// \todo Allocate the memory with given size of the matrix
template<class T>
Mat<T>::Mat(int nrow, int ncol) : _row(nrow), _col(ncol), _nnz(0) {

    _row_pointer = (int *)malloc( (nrow+1) * sizeof(int) );

    _tmp_index = (int **)malloc( nrow * sizeof(int *) );
    for(int i = 0; i < nrow; ++i){
        _tmp_index[i] = (int *)malloc( 8 * sizeof(int) );
    }

    _tmp_value = (T **)malloc( nrow * sizeof(T *) );
    for(int i = 0; i < nrow; ++i){
        _tmp_value[i] = (T *)malloc( 8 * sizeof(T) );
    }

    _tmp_len = (int *)malloc( nrow * sizeof(int) );
    memset(_tmp_len, 0, nrow * sizeof(int));

    _tmp_size = (int *)malloc( nrow * sizeof(int) );
    memset(_tmp_size, 8, nrow * sizeof(int));
}


/// \brief Destructor
///
/// \todo release the allocated memory
template<class T>
Mat<T>::~Mat(){
    FREE_AND_SET_NULL(_row_pointer);
    FREE_AND_SET_NULL(_tmp_len);
    FREE_AND_SET_NULL(_tmp_size);
    for(int i = 0; i < _row; ++i){
        FREE_AND_SET_NULL(_tmp_index[i]);
        FREE_AND_SET_NULL(_tmp_value[i]);
    }
    FREE_AND_SET_NULL(_tmp_index);
    FREE_AND_SET_NULL(_tmp_value);
}


/// \brief insert nonezeros
template<class T>
void Mat<T>::insert(int row, int col, REAL value){  // 0-based

    // wrong input
    if( row < 0 || row >= _row || col < 0 || col >= _col )
        return;

    // too long for this row, reallocate memory
    if( _tmp_len[row] == _tmp_size[row] ){

        int* _tmp_index_new = (int*)malloc( (_tmp_size[row]*2) * sizeof(int) );
        memcpy(_tmp_index_new, _tmp_index[row], sizeof(_tmp_index[row]));
        FREE_AND_SET_NULL(_tmp_index[row]);
        _tmp_index[row] = _tmp_index_new;

        T* _tmp_value_new = (T*)malloc( (_tmp_size[row]*2) * sizeof(T) );
        memcpy(_tmp_value_new, _tmp_value[row], sizeof(_tmp_value[row]));
        FREE_AND_SET_NULL(_tmp_index[row]);
        _tmp_value[row] = _tmp_value_new;

        _tmp_size[row] *= 2;
    }

    // add entry
    _tmp_index[row][_tmp_len[row]] = col;
    _tmp_value[row][_tmp_len[row]] = value;
    _tmp_len[row]++;
    
};


/// \brief form CSR format
template<class T>
void Mat<T>::csr() {

    _row_pointer[0] = 0;

    T *_tmp_row_value = (T *)malloc( _col * sizeof(T) );
    vector<int> nz_idx; 

    for(int i = 0; i < _row; ++i){  // row i

        // intialize
        memset(_tmp_row_value, 0, _col * sizeof(T));
        nz_idx.clear();

        // caculate indexes and values
        for(int j = 0; j < _tmp_len[i]; ++j){
            int col_idx = _tmp_index[i][j];
            T value = _tmp_value[i][j];
            _tmp_row_value[col_idx] += value;
            nz_idx.push_back(col_idx);
        }
        sort(nz_idx.begin(), nz_idx.end());
        nz_idx.erase(unique(nz_idx.begin(), nz_idx.end()), nz_idx.end());

        // row i in CSR
        _row_pointer[i+1] = _row_pointer[i] + nz_idx.size();
        for(int j = 0; j < nz_idx.size(); ++j){
            _col_index.push_back(nz_idx[j]);
            _csr_value.push_back(_tmp_row_value[nz_idx[j]]);
        }
    }

    _nnz = _row_pointer[_row];

    FREE_AND_SET_NULL(_tmp_row_value);
};


template<class T>
void Mat<T>::print_csr(FILE* out, int setting){
    
    if (setting == 0) {  // text
        for(int i = 0; i <= _row; ++i) fprintf(out, "%d ", _row_pointer[i]); fprintf(out, "\n"); 
        for(int i = 0; i < _nnz; ++i) fprintf(out, "%d ", _col_index[i]); fprintf(out, "\n"); 
        for(int i = 0; i < _nnz; ++i) fprintf(out, "%lf ", _csr_value[i]); fprintf(out, "\n"); 
    }

    else if (setting == 1) { // binary
        // need binary format
    }

    else if (setting == 2) { // command
        for(int i = 0; i <= _row; ++i) printf("%d ", _row_pointer[i]); printf("\n"); 
        for(int i = 0; i < _nnz; ++i) printf("%d ", _col_index[i]); printf("\n"); 
        for(int i = 0; i < _nnz; ++i) printf("%lf ", _csr_value[i]); printf("\n"); 
    }

}


template class Mat<double>;
template class Mat<float>;