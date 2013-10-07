#ifndef MATRIX_H_
#define MATRIX_H_

#define MATRIX_MAX_ROWS 4
#define MATRIX_MAX_COLS 4

class Matrix {
  public:
    float mat[MATRIX_MAX_ROWS][MATRIX_MAX_COLS];
  
    Matrix() {
      // initialize all entries in the matrix to zero
      mat = {0};
    }
	bool operator==(const Matrix& m) const {
      for(int i = 0; i < MATRIX_MAX_ROWS; i++) {
        for(int j = 0; j < MATRIX_MAX_ROWS; j++) {
          if(mat[i][j] != m.mat[i][j])
            return false;
        }
      }
      return true;
	}

    Matrix scalerMultiply(float scaler) {
      Matrix m;
      for(int i = 0; i < MATRIX_MAX_ROWS; i++) {
        for(int j = 0; j < MATRIX_MAX_ROWS; j++) {
          m[i][j] = m.mat[i][j] * scaler;
        }
      }

      return m;
    }

    Matrix scalerDivide(float scaler) {
      Matrix m;
      for(int i = 0; i < MATRIX_MAX_ROWS; i++) {
        for(int j = 0; j < MATRIX_MAX_ROWS; j++) {
          m[i][j] = m.mat[i][j] / scaler;
        }
      }

      return m;
    }

    Matrix scalerAdd(float scaler) {
      Matrix m;
      for(int i = 0; i < MATRIX_MAX_ROWS; i++) {
        for(int j = 0; j < MATRIX_MAX_ROWS; j++) {
          m[i][j] = m.mat[i][j] + scaler;
        }
      }

      return m;
    }

    Matrix scalerSubtract(float scaler) {
      Matrix m;
      for(int i = 0; i < MATRIX_MAX_ROWS; i++) {
        for(int j = 0; j < MATRIX_MAX_ROWS; j++) {
          m[i][j] = m.mat[i][j] - scaler;
        }
      }

      return m;
    }

	Matrix operator*(const Matrix& v) {
      Matrix m;
      for(int i = 0; i < MATRIX_MAX_ROWS; i++) {
        for(int j = 0; j < MATRIX_MAX_ROWS; j++) {
          for(int k = 0; k < MATRIX_MAX_ROWS; k++) {
            m[i][j] = m.mat[i][j] + v.mat[i][j];
          }
        }
      }

      return m;
	}

	Matrix operator+(const Matrix& v) {
      Matrix m;
      for(int i = 0; i < MATRIX_MAX_ROWS; i++) {
        for(int j = 0; j < MATRIX_MAX_ROWS; j++) {
          m[i][j] = m.mat[i][j] + v.mat[i][j];
        }
      }

      return m;
	}

	Matrix operator-() {
		return scalerMultiply(-1);
	}

	Matrix operator-(const Matrix& v) {
      Matrix m;
      for(int i = 0; i < MATRIX_MAX_ROWS; i++) {
        for(int j = 0; j < MATRIX_MAX_ROWS; j++) {
          m[i][j] = m.mat[i][j] - v.mat[i][j];
        }
      }

      return m;
	}

};

#endif
