#ifndef UBURU_RENDERENGINE_DETAIL_MATRIXSIZEADAPTER_H
#define UBURU_RENDERENGINE_DETAIL_MATRIXSIZEADAPTER_H

#include <mutex>

#include "../matrix.h"

namespace detail {
    template <size_t DIMENSION, typename T>
    class MatrixSizeAdapter {
    public:
        MatrixSizeAdapter(const Matrix<T> &matrix, bool restore_size_at_destruct = true)
        : matrix(const_cast<Matrix<T> &>(matrix)), 
        save_value(matrix.rows - DIMENSION), 
        restore_size_at_destruct(restore_size_at_destruct) {
            mutex.lock();
            this->matrix.rows      -= save_value;
            this->matrix.data_size -= save_value;
        }

        ~MatrixSizeAdapter() {
            if(restore_size_at_destruct) {
                matrix.rows      += save_value;
                matrix.data_size += save_value;
            }

            mutex.unlock();
        }

    private:
        Matrix<T> &matrix;
        size_t save_value;
        bool restore_size_at_destruct;
        std::mutex mutex;
    };
}

#endif // UBURU_RENDERENGINE_DETAIL_MATRIXSIZEADAPTER_H