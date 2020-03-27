/*
@file name:	matrix.h
@author:	superb24ed
@version:	1.0
@date:		2020.03.27
@copyright:	Anyone can use and modify this source code in any way without authorization.
@email:		yuchao.xu@outlook.com
@github:	superb24ed
*/

#include "matrix.h"


const double EPS = 1e-10;
//˽�г�Ա�����ڲ�����Ԫ�ܹ�����
void Matrix::__space_alloc() //��ʼ���������������з������Ĵ洢�ռ�
{
	_matrix_head_pointer_ = new double* [_matrix_row_];
	for (int i = 0; i < _matrix_row_; ++i) {
		_matrix_head_pointer_[i] = new double[_matrix_column_];
	}
}
void Matrix::__fill(double val)			//����ռ����
{
	for (int i = 0; i < _matrix_row_; i++)
	{
		for (int j = 0; j < _matrix_column_; j++)
		{
			_matrix_head_pointer_[i][j] = val;
		}
	}
}
void Matrix::Error(const char* error_message)		//������ʱ���ô˺������������Ϣ
{
	std::cout << std::endl;
	fputs(error_message, stderr);			//���������Ϣ��stderr
	abort();								//��ֹ����
}

//�ⲿ�������ɱ�������/��������ⲿ��������

//���췽��
Matrix::Matrix()							//����1*1������󣬼���ֵ0
{
	_matrix_row_ = _matrix_column_ = 1;
	__space_alloc();
	**_matrix_head_pointer_ = 0;
}

Matrix::Matrix(double val)					//1*1����˫������ֵval��ʼ���ķ��󣬼���ֵval.ע�⣺��һ������������˫������
{
	//������������Ǹ���������������Matrix(int &_order)�����ǵ�ǰ����
	_matrix_row_ = _matrix_column_ = 1;
	__space_alloc();
	**_matrix_head_pointer_ = val;

}

Matrix::Matrix(int _order)					//����Ϊ_order�ķ�����0��ʼ��
{
	if (_order <= 0)
	{
		Error("����Matrix(int)�������ʱ���ִ�����ȷ�Ͼ�������Ƿ���ȷ.\n");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _matrix_column_ = _order;	//����������
	__space_alloc();						//�����ڴ�
	__fill(0.0);							//ʹ��0���

}

/*
//������캯����Ϊ���ܻ���Matrix(int,int)����������������
//Ҫʹ������ȡ����matrix.h�������ע�ͼ���
Matrix::Matrix(int _order, double val)
{
	if (_order <= 0)
	{
		fputs("����Matrix(int,double)�������ʱ���ִ�����ȷ�Ͼ�������Ƿ���ȷ.\n", stderr);
		abort();
	}
	_matrix_row_ = _matrix_column_ = _order;	//����������
	__space_alloc();						//�����ڴ�
	__fill(val);							//ʹ��val���
}
*/
Matrix::Matrix(int _row, int _col)
{
	if (_row <= 0 || _col <= 0)
	{
		Error("����Matrix(int,int)�������ʱ���ִ�����ȷ���������Ƿ���ȷ.\n");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _row;					//��������
	_matrix_column_ = _col;					//��������
	__space_alloc();						//�����ڴ�
	__fill(0.0);							//��0���
}

Matrix::Matrix(int _row, int _col, double val)
{
	if (_row <= 0 || _col <= 0)
	{
		Error("����Matrix(int,int,double)�������ʱ���ִ�����ȷ���������Ƿ���ȷ.\n");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _row;					//��������
	_matrix_column_ = _col;					//��������
	__space_alloc();						//�����ڴ�
	__fill(val);							//��val���
}
Matrix::Matrix(int _row, int _col, int val)
{
	if (_row <= 0 || _col <= 0)
	{
		Error("����Matrix(int,int,int)�������ʱ���ִ�����ȷ���������Ƿ���ȷ.\n");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _row;					//��������
	_matrix_column_ = _col;					//��������
	__space_alloc();						//�����ڴ�
	__fill(val);							//��val���
}
Matrix::Matrix(int _row, int _col, double* _val_array)
{
	//��һά����val_array����ʼ������,ע�⣺val_array[]�ĳ�Ա����������_row*_col�������򽫻�Խ�����
	//��άdouble�����ͷָ�룬��Ҫǿ��ת��Ϊdouble*�ٴ���
	if (_row <= 0 || _col <= 0)
	{
		Error("����Matrix(int,int,double*)�������ʱ���ִ���:��ȷ���������Ƿ���ȷ.\n");
		exit(EXIT_FAILURE);
	}
	else if (_val_array == NULL)
	{
		Error("����Matrix(int,int,double*)�������ʱ���ִ���:�����ָ���ǿ�ָ��");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _row;
	_matrix_column_ = _col;
	__space_alloc();
	for (int i = 0; i < _matrix_row_; i++)
	{
		for (int j = 0; j < _matrix_column_; j++)
		{
			if (_val_array != 0)
			{
				_matrix_head_pointer_[i][j] = *(_val_array + i * _matrix_column_ + j);
			}

		}
	}
}

Matrix::Matrix(int _row, int _col, int* _val_array)
{
	// ��һά����val_array����ʼ������, ע�⣺val_array[]�ĳ�Ա����������_row* _col�������򽫻�Խ�����
	//��άint�����ͷָ�룬��Ҫǿ��ת��Ϊint*�ٴ���

	if (_row <= 0 || _col <= 0)
	{
		Error("����Matrix(int,int,int*)�������ʱ���ִ���:��ȷ���������Ƿ���ȷ.\n");
		exit(EXIT_FAILURE);
	}
	else if (_val_array == NULL)
	{
		Error("����Matrix(int,int,int*)�������ʱ���ִ���:�����ָ���ǿ�ָ��.");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _row;
	_matrix_column_ = _col;
	__space_alloc();
	for (int i = 0; i < _matrix_row_; i++)
	{
		for (int j = 0; j < _matrix_column_; j++)
		{
			if (_val_array != 0)
			{
				_matrix_head_pointer_[i][j] = (double)*(_val_array + i * _matrix_column_ + j);
			}
		}
	}
}


Matrix::~Matrix()
{
	for (int i = 0; i < _matrix_row_; i++)
	{
		delete[] _matrix_head_pointer_[i];
	}
	delete[] _matrix_head_pointer_;
}

Matrix::Matrix(const Matrix& M)
{
	//�������������
	_matrix_row_ = M._matrix_row_;
	_matrix_column_ = M._matrix_column_;
	//����ռ�
	__space_alloc();
	//������ֵ
	for (int i = 0; i < _matrix_row_; i++)
	{
		for (int j = 0; j < _matrix_column_; j++)
		{
			_matrix_head_pointer_[i][j] = M._matrix_head_pointer_[i][j];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& M)
{
	Matrix Temp(*this);
	if (this == &M)
	{
		return *this;
	}
	if (_matrix_row_ != M._matrix_row_ || _matrix_column_ != M._matrix_column_)		//�ߴ粻��ͬ����Ҫ���·���ռ�
	{
		//�ͷŵ�ǰ�洢�ռ�
		for (int i = 0; i < _matrix_row_; i++)
		{
			delete[] _matrix_head_pointer_[i];
		}
		delete[] _matrix_head_pointer_;
		//�����µ�������
		_matrix_row_ = M._matrix_row_;
		_matrix_column_ = M._matrix_column_;
		//���·���ռ�
		__space_alloc();
		//��ֵ��������ǰ����
	}
	for (int i = 0; i < _matrix_row_; i++)
	{
		for (int j = 0; j < _matrix_column_; j++)
		{
			_matrix_head_pointer_[i][j] = M._matrix_head_pointer_[i][j];
		}
	}
	// TODO: �ڴ˴����� return ���
	//���ص�ǰ������Ϊ���
	return *this;
}

Matrix& Matrix::operator=(double* _val_array)
{
	if (_val_array != NULL)		//�ڴ���ָ��ǿ�ʱ���ܲ���
	{
		for (int i = 0; i < _matrix_row_; i++)
		{
			for (int j = 0; j < _matrix_column_; j++)
			{
				_matrix_head_pointer_[i][j] = *(_val_array + i * _matrix_column_ + j);		//	��ֵֵ����ǰ����
			}
		}
		return *this;
	}
	else
	{
		Error("��ȡ������(=)ʱ���ִ��󣺴��������ͷָ��������(��ָ�룩");
		exit(EXIT_FAILURE);
	}
}

Matrix Matrix::operator*(const Matrix& M)
{
	if (_matrix_column_ == M._matrix_row_)		//ֻ��ǰһ��������е��ں�һ������в��ܽ��г˷�����
	{

		Matrix Temp(_matrix_row_, M._matrix_column_);	//�˻�����ľ����񣺵�ǰ������кͺ�һ���������
		for (int i = 0; i < _matrix_row_; i++)
			for (int j = 0; j < M._matrix_column_; j++)//ǰ����ѭ����ʾ�������������Temp�е�ÿһ��Ԫ�ء�
			{
				for (int k = 0; k < _matrix_column_; k++)	//��һ��ѭ����ʾ����ǰһ�����i�е���,�ͺ�һ�����j�е��У���Ӧ��˺�(��k�ݹ�)�����ۼӡ�
				{
					Temp._matrix_head_pointer_[i][j] += _matrix_head_pointer_[i][k] * M._matrix_head_pointer_[k][j];
				}
			}
		return Temp;	//���������Temp
	}
	Error("��ͼ���о���˻�����ǰһ��������в����ں�һ���������.");
	exit(EXIT_FAILURE);
}

Matrix Matrix::operator*(double coef)
{
	Matrix Temp(*this);								//����
	for (int i = 0; i < Temp._matrix_row_; i++)
	{
		for (int j = 0; j < Temp._matrix_column_; j++)
		{
			Temp._matrix_head_pointer_[i][j] *= coef;	//����ֵ����coef
		}
	}
	return Temp;
}

Matrix Matrix::operator+(const Matrix &M) const
{
	if (_matrix_row_ == M._matrix_row_ && _matrix_column_ == M._matrix_column_ )		//ֻ������ͬʱ��Ȳ������
	{
		Matrix Temp(_matrix_row_, _matrix_column_, 0.0);
		for (int i = 0; i < _matrix_row_; i++)
		{
			for (int j = 0; j < _matrix_column_; j++)
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[i][j] + M._matrix_head_pointer_[i][j];
			}
		}
		return Temp;
	}
	else
	{
		Error("���Ծ�����ӳ����������������������һ��.");
		exit(EXIT_FAILURE);
	}
}

Matrix Matrix::operator-(const Matrix &M) const
{
	if (_matrix_row_ == M._matrix_row_ && _matrix_column_ == M._matrix_column_)
	{
		Matrix Temp(_matrix_row_, _matrix_column_, 0.0);
		for (int i = 0; i < _matrix_row_; i++)
		{
			for (int j = 0; j < _matrix_column_; j++)
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[i][j] - M._matrix_head_pointer_[i][j];
			}
		}
		return Temp;
	}
	else
	{
		Error("���Ծ�����������������������������һ��.");
		exit(EXIT_FAILURE);
	}
}

Matrix Matrix::operator-() const
{
		Matrix Temp(_matrix_row_, _matrix_column_, 0.0);
		for (int i = 0; i < _matrix_row_; i++)
		{
			for (int j = 0; j < _matrix_column_; j++)
			{
				Temp._matrix_head_pointer_[i][j] = -_matrix_head_pointer_[i][j];
			}
		}
		return Temp;
}

Matrix operator*(double coef, const Matrix& M)
{

	Matrix Temp(M);								//����
	for (int i = 0; i < Temp._matrix_row_; i++)
	{
		for (int j = 0; j < Temp._matrix_column_; j++)
		{
			Temp._matrix_head_pointer_[i][j] *= coef;	//����ֵ����coef
		}
	}
	return Temp;
}

std::istream& operator>>(std::istream& _input_stream, const Matrix &M)		//����������ʼ������
{
	//��ջ�����
	_input_stream.clear();
	_input_stream.sync();
	//�ӻ�������ȡ����
	for (int i = 0; i < M._matrix_row_; i++)
	{
		for (int j = 0; j < M._matrix_column_; j++)
		{

			_input_stream >> M._matrix_head_pointer_[i][j];
		}
	}
	return _input_stream;
}

std::ostream& operator<<(std::ostream &_output_stream, const Matrix &M)
{
	for (int i = 0; i < M._matrix_row_; i++)
	{
		for (int j = 0; j < M._matrix_column_; j++)
		{
			_output_stream << M._matrix_head_pointer_[i][j]<<"\t";
		}
		_output_stream << std::endl;
	}
	return _output_stream;
}


void Matrix::swapRows(int _row1, int _row2)
{
	if (_row1 > _matrix_row_ || _row2 > _matrix_row_ || _row1 <= 0 || _row2 <= 0)
	{
		Error("�ڳ��Խ�������ʱ����:��������������Ϲ淶�������¼��.");
		exit(EXIT_FAILURE);
	}
	else if (_row1 == _row2)
	{
		return;
	}
	_row1--;
	_row2--;
	double* temp = _matrix_head_pointer_[_row1];
	_matrix_head_pointer_[_row1] = _matrix_head_pointer_[_row2];
	_matrix_head_pointer_[_row2] = temp;
}

void Matrix::swapCols(int _column1, int _column2)
{
	if (_column1 > _matrix_column_ || _column2 > _matrix_column_ || _column1 <= 0 || _column2 <= 0)
	{
		Error("�ڳ��Խ�������ʱ����:��������������Ϲ淶�������¼��.");
		exit(EXIT_FAILURE);
	}
	else if (_column1 == _column2)
	{
		return;
	}
	_column1--;
	_column2--;
	double temp = 0;
	for (int i = 0; i < _matrix_row_; i++)
	{
		temp = _matrix_head_pointer_[i][_column1];
		_matrix_head_pointer_[i][_column1] = _matrix_head_pointer_[i][_column2];
		_matrix_head_pointer_[i][_column2] = temp;
	}
}

void Matrix::mulRow(int _row, double coef)
{
	--_row;
	for (int i = 0; i < _matrix_column_; i++)
	{
		_matrix_head_pointer_[_row][i] *= coef;
	}
}

void Matrix::mulCol(int _col, double coef)
{
	--_col;
	for (int i = 0; i < _matrix_row_; i++)
	{
		_matrix_head_pointer_[i][_col] *= coef;
	}
}

void Matrix::addtoRow(int _src_row, int _dst_row, double coef)
{
	if (_src_row > _matrix_row_ || _dst_row > _matrix_row_ || _src_row <= 0 || _dst_row <= 0)
	{
		Error("�ڳ����м�ʱ�������������Ӧ���ǲ���������������������������¼��");
		exit(EXIT_FAILURE);
	}
	_src_row--;
	_dst_row--;
	for (int i = 0; i < _matrix_column_; i++)
	{
		_matrix_head_pointer_[_dst_row][i] += coef * _matrix_head_pointer_[_src_row][i];
	}
}

void Matrix::addtoCol(int _src_column, int _dst_column, double coef)
{

	if (_src_column > _matrix_column_ || _dst_column > _matrix_column_ || _src_column <= 0 || _dst_column <= 0)
	{
		Error("�ڳ����м�ʱ�������������Ӧ���ǲ���������������������������¼��");
		exit(EXIT_FAILURE);
	}
	_src_column--;
	_dst_column--;
	for (int i = 0; i < _matrix_row_; i++)
	{
		_matrix_head_pointer_[i][_dst_column] += coef * _matrix_head_pointer_[i][_src_column];
	}
}

void Matrix::Modify(int _target_row, int _target_column, double modified_value)
{
	if (_target_row > _matrix_row_ || _target_column > _matrix_column_ || _target_row <= 0 || _target_column <= 0)
	{
		Error("�ڳ����޸ľ�����ֵʱ���ִ�����������ȷ������������");
		exit(EXIT_FAILURE);
	}
	_target_row--;
	_target_column--;
	_matrix_head_pointer_[_target_row][_target_column] = modified_value;

}

void Matrix::Reset()
{
	__fill(0.0);
}

int Matrix::Row()const
{
	return _matrix_row_;
}

int Matrix::Col()const
{
	return _matrix_column_;
}

double Matrix::Elem(int _row, int _col) const
{
	if (_row > _matrix_row_ || _col > _matrix_column_ || _row <= 0 || _col <= 0)
	{
		Error("�����������Ԫ��ֵʱ���ִ�����������ȷ��������.");
		exit(EXIT_FAILURE);
	}
	_row--;
	_col--;
	return _matrix_head_pointer_[_row][_col];
}

void Matrix::Show() const
{
	std::cout.setf(std::ios::left);						//����������
	for (int i = 0; i < _matrix_row_; i++)
	{
		for (int j = 0; j < _matrix_column_; j++)
		{
			std::cout << _matrix_head_pointer_[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void Matrix::ShowRow(int _row)const
{
	if (_row > _matrix_row_ || _row <= 0)
	{
		Error("������ʾ�����ĳ��ʱ����������������Ϸ�.");
		exit(EXIT_FAILURE);
	}
	_row--;
	for (int i = 0; i < _matrix_column_; i++)
	{
		std::cout << _matrix_head_pointer_[_row][i] << "\t";
	}
	std::cout << std::endl;
}

void Matrix::ShowCol(int _col)const
{
	if (_col > _matrix_column_ || _col <= 0)
	{
		Error("������ʾ�����ĳ��ʱ����������������Ϸ�.");
		exit(EXIT_FAILURE);
	}
	_col--;
	for (int i = 0; i < _matrix_column_; i++)
	{
		std::cout << _matrix_head_pointer_[i][_col] << std::endl;
	}
	std::cout << std::endl;
}

/*
Matrix Matrix::inv(const Matrix &M)
{
	//�㷨��ȫ��Ԫ��˹��ȥ��

	if (M._matrix_row_ != M._matrix_column_)
	{
		Error("�޷�������󣺲��Ƿ���");
		exit(EXIT_FAILURE);
	}
	Matrix Temp(M);
	Matrix E(eye(M._matrix_row_));
	int(*rec)[2] = new int[Temp._matrix_row_ + 1 ][2]{};
	double temp=0.0f;
	for (int k = 0; k < Temp._matrix_row_; k++)
	{
		temp = Temp._matrix_head_pointer_[k][k];
		std::cout << std::endl << "init fmax=" << temp << std::endl;
		rec[k][0] = k;
		rec[k][1] = k;
		for (int i = k; i < Temp._matrix_row_; i++)
		{
			for (int j = k; j < Temp._matrix_column_; j++)
			{
				if (abs(Temp._matrix_head_pointer_[i][j]) > abs(temp))		//��i+1�е��Ǹ�ֵ��fmax��
				{
					rec[k][0] = i ;
					rec[k][1] = j ;
					temp = Temp._matrix_head_pointer_[i][j];
					std::cout << std::endl<<"fmax=" << temp << std::endl;
				}
			}
		}
		std::cout << std::endl << "k=" << k<<std::endl;
		std::cout << rec[k][0] + 1 << "\t" << rec[k][1] + 1 << std::endl;
		Temp.swapRows(k + 1, rec[k][0] + 1);
		Temp.swapCols(k + 1, rec[k][1] + 1);
		E.swapRows(k + 1, rec[k][0] + 1);
		E.swapCols(k + 1, rec[k][1] + 1);
		std::cout << "Temp = " << std::endl << Temp << std::endl;
		std::cout << "E = " << std::endl << E << std::endl<<std::endl;
	}
	for (int k = 1; k <= Temp._matrix_row_; k++)
	{
		temp = -1 / Temp.Elem(k, k);
		for (int i = k+1; i <= Temp._matrix_row_; i++)
		{
			Temp.mulRow(k,temp);
			E.mulRow(k, temp);
			Temp.addtoCol(k, i, temp * Temp.Elem(k, i));
			E.addtoCol(k, i, temp * Temp.Elem(k, i));
			Temp.addtoRow(k, i, temp * Temp.Elem(i, k));
			E.addtoRow(k, i, temp * Temp.Elem(i, k));

			std::cout << "Temp:" << std::endl << Temp << std::endl<<std::endl;
			std::cout << "E:" << std::endl << E << std::endl << std::endl<<std::endl;
		}
	}
	std::cout << "Temp = " << std::endl << Temp;
	
	return Temp;
}
*/

Matrix Matrix::inv(Matrix M) {
	if (M._matrix_row_ != M._matrix_column_) 
	{
		Error("ֻ�з������������");
		exit(EXIT_FAILURE);
	}
	double temp;
	Matrix Temp = Matrix(M._matrix_row_, M._matrix_column_);
	Temp = M;//Ϊ����A��һ������
	Matrix B = eye(M._matrix_row_);
	//��С��EPS����ȫ����0
	for (int i = 0; i < M._matrix_row_; i++)
	{
		for (int j = 0; j < M._matrix_column_; j++)
		{
			if (abs(M._matrix_head_pointer_[i][j]) <= EPS)
			{
				M._matrix_head_pointer_[i][j] = 0;
			}
		}
	}
	//ѡ����Ҫ����������ѡ��Ԫ
	for (int i = 0; i < M._matrix_row_; i++)
	{
		if (abs(M._matrix_head_pointer_[i][i]) <= EPS)
		{
			bool flag = false;
			for (int j = 0; (j < M._matrix_row_) && (!flag); j++)
			{
				if ((abs(M._matrix_head_pointer_[i][j]) > EPS) && (abs(M._matrix_head_pointer_[j][i]) > EPS))
				{
					flag = true;
					for (int k = 0; k < M._matrix_column_; k++)
					{
						temp = M._matrix_head_pointer_[i][k];
						M._matrix_head_pointer_[i][k] = M._matrix_head_pointer_[j][k];
						M._matrix_head_pointer_[j][k] = temp;
						temp = B._matrix_head_pointer_[i][k];
						B._matrix_head_pointer_[i][k] = B._matrix_head_pointer_[j][k];
						B._matrix_head_pointer_[j][k] = temp;
					}
				}
			}
			if (!flag) 
			{
				std::cout << "����󲻴���\n";
				std::abort();
			}
		}
	}
	//ͨ�������б任��A��Ϊ�����Ǿ���
	double temp_rate;
	for (int i = 0; i < M._matrix_row_; i++)
	{
		for (int j = i + 1; j < M._matrix_row_; j++)
		{
			temp_rate = M._matrix_head_pointer_[j][i] / M._matrix_head_pointer_[i][i];
			for (int k = 0; k < M._matrix_column_; k++) 
			{
				M._matrix_head_pointer_[j][k] -= M._matrix_head_pointer_[i][k] * temp_rate;
				B._matrix_head_pointer_[j][k] -= B._matrix_head_pointer_[i][k] * temp_rate;
			}
			M._matrix_head_pointer_[j][i] = 0;
		}
	}
	//ʹ�Խ�Ԫ�ؾ�Ϊ1
	for (int i = 0; i < M._matrix_row_; i++)
	{
		temp = M._matrix_head_pointer_[i][i];
		for (int j = 0; j < M._matrix_column_; j++)
		{
			M._matrix_head_pointer_[i][j] /= temp;
			B._matrix_head_pointer_[i][j] /= temp;
		}
	}
	//���Ѿ���Ϊ�����Ǿ����A����Ϊ��λ����
	for (int i = M._matrix_row_ - 1; i >= 1; i--) 
	{
		for (int j = i - 1; j >= 0; j--) 
		{
			temp = M._matrix_head_pointer_[j][i];
			for (int k = 0; k < M._matrix_column_; k++) 
			{
				M._matrix_head_pointer_[j][k] -= M._matrix_head_pointer_[i][k] * temp;
				B._matrix_head_pointer_[j][k] -= B._matrix_head_pointer_[i][k] * temp;
			}
		}
	}
	M = Temp;//��ԭA
	return B;//���ظþ���������
}
Matrix Matrix::inv() const
{
	return inv(*this);
}

Matrix Matrix::T() const
{
	Matrix Temp(_matrix_column_, _matrix_row_);
	for (int i = 0; i < _matrix_column_; i++)
	{
		for (int j = 0; j < _matrix_row_; j++)
		{
			Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[j][i];
		}
	}
	return Temp;
}

Matrix Matrix::Hadamard(const Matrix& M, const Matrix& N)
{
	if ((M._matrix_column_ != N._matrix_column_) || (M._matrix_row_ != N._matrix_row_))
	{
		Error("�޷���Hadmard�˻�����ȷ����������ĳߴ�����ͬ.");
		exit(EXIT_FAILURE);
	}
	Matrix temp(M._matrix_row_, M._matrix_column_, 0);
	for (int i = 0; i < M._matrix_row_; i++) {
		for (int j = 0; j < M._matrix_column_; j++) {
			temp._matrix_head_pointer_[i][j] = M._matrix_head_pointer_[i][j] * N._matrix_head_pointer_[i][j];
		}
	}
	return temp;
}

Matrix Matrix::zeros(int _order)
{
	if (_order <= 0)
	{
		Error("����zero�����㷽��ʧ�ܣ���������ȷ�Ľ���.");
		exit(EXIT_FAILURE);
	}
	return Matrix(_order);
}

Matrix Matrix::zeros(int _row, int _col)
{

	if (_row <= 0 || _col <= 0)
	{
		Error("����zero���������ʧ�ܣ���������ȷ��������.");
		exit(EXIT_FAILURE);
	}
	return Matrix(_row, _col, 0.0);
}

Matrix Matrix::ones(int _order)
{

	if (_order <= 0)
	{
		Error("����ones����1����ʧ�ܣ���������ȷ�Ľ���.");
		exit(EXIT_FAILURE);
	}
	return Matrix(_order, _order, 1.0);
}

Matrix Matrix::ones(int _row, int _col)
{

	if (_row <= 0 || _col <= 0)
	{
		Error("����ones����1����ʧ�ܣ���������ȷ��������.");
		exit(EXIT_FAILURE);
	}
	return Matrix(_row, _col, 1.0);
}

Matrix Matrix::diag(int _array_size, const double* _val_array)
{
	if (_array_size <= 0)
	{
		Error("����diag���ִ��������С�ǷǸ�������.");
		exit(EXIT_FAILURE);
	}
	else if (_val_array == NULL)
	{
		Error("����diag���ִ��󣺴����˿�ָ��.");
		exit(EXIT_FAILURE);
	}
	Matrix Temp(_array_size);
	for (int i = 0; i < _array_size; i++)
	{
		if (_val_array != 0)
		{
			Temp._matrix_head_pointer_[i][i] = _val_array[i];
		}
	}
	return Temp;
}

Matrix Matrix::diag(int _array_size, const int* _val_array)
{
	if (_array_size <= 0)
	{
		Error("����diag���ִ��������С�ǷǸ�������.");
		exit(EXIT_FAILURE);
	}
	else if (_val_array == NULL)
	{
		Error("����diag���ִ��󣺴����˿�ָ��.");
		exit(EXIT_FAILURE);
	}
	Matrix Temp(_array_size);
	for (int i = 0; i < _array_size; i++)
	{
		if (_val_array != 0)
		{
			Temp._matrix_head_pointer_[i][i] = _val_array[i];
		}
	}
	return Temp;
}

Matrix Matrix::eye(int _order)
{
	if (_order <= 0)
	{
		Error("���Դ�����λ����ʧ�ܣ���������ȷ�Ľ���.");
		exit(EXIT_FAILURE);
	}
	Matrix Temp(_order, _order, 0);
	for (int i = 0; i < _order; i++)
	{
		Temp._matrix_head_pointer_[i][i] = 1;
	}
	return Temp;
}

Matrix Matrix::rand(int _row, int _col)
{
	if (_row <= 0 || _col <= 0)
	{
		Error("�����������ʧ�ܣ�������������������.");
		exit(EXIT_FAILURE);
	}
	srand((unsigned int)time(NULL));
	Matrix Temp(_row, _col, 0.0);
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			Temp._matrix_head_pointer_[i][j] = (RAND_MAX - (double)::rand()) / RAND_MAX;
		}
	}
	return Temp;
}

Matrix Matrix::linspace(double first_val, double last_val, int linspace_nums, linspace_type type)
{
	double d = (last_val - first_val) / (double)linspace_nums;
	if (linspace_nums <= 0)
	{
		Error("���Կռ乹��ʧ��:���Կռ��Ԫ�ظ���������������.");
		exit(EXIT_FAILURE);
	}
	else if (type == ROW_LINSPACE)
	{
		Matrix Temp1(linspace_nums, 1);
		Temp1._matrix_head_pointer_[linspace_nums - 1][0] = last_val;		//��ֵ���һ��
		for (int i = 0; i < linspace_nums - 1; i++)
		{
			Temp1._matrix_head_pointer_[i][0] = first_val + d * i;//��ֵǰn-1��
		}
		return Temp1;
	}
	else if (type == COL_LINSPACE)
	{
		Matrix Temp2(1, linspace_nums);
		Temp2._matrix_head_pointer_[0][linspace_nums - 1] = last_val;		//��ֵ���һ��
		for (int i = 0; i < linspace_nums - 1; i++)
		{
			Temp2._matrix_head_pointer_[0][i] = first_val + d * i;//��ֵǰn-1��
		}
		return Temp2;
	}
	Error("δ֪�����޷������������͵����Կռ�");
	exit(EXIT_FAILURE);
}

Matrix Matrix::getBlock(int _start_row, int _end_row, int _start_col, int _end_col)
{
	//���к��а�˳�����У�����֤��ʼ���в����ڽ�������
	int swap_var = 0;
	if (_start_row > _end_row)
	{
		swap_var = _start_row;
		_start_row = _end_row;
		_end_row = swap_var;

	}

	if (_start_col > _end_col)
	{
		swap_var = _start_col;
		_start_col = _end_col;
		_end_col = swap_var;
	}

	//�ж�����������Ƿ���Ϲ淶
	if (_start_row <= 0 || _start_col <= 0 || _end_row > _matrix_row_ || _end_col > _matrix_column_)
	{
		Error("���ܻ���Ӿ����������������������");
		exit(EXIT_FAILURE);
	}
	//�����ɣ���ʼ��ȡ����
	int temp_row = abs(_end_row - _start_row) + 1;
	int temp_col = abs(_end_col - _start_col) + 1;
	Matrix Temp(temp_row, temp_col, 0.0);
	for (int i = 0; i < temp_row; i++)
	{
		for (int j = 0; j < temp_col; j++)
		{
			//����ע�⣺_start_row�У�_start_col�е�Ԫ�� M[_start_row-1][_start_col-1],�����±�Ҫ��һ.���߿���ֱ�ӵ���Elem(_start_row,__start_col).
			Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[_start_row - 1 + i][_start_col - 1 + j];
		}
	}

	return Temp;
}

Matrix Matrix::getBlock_byRow(int _start_row, int _end_row)
{
	int swap_var = 0;
	if (_start_row > _end_row)
	{
		swap_var = _start_row;
		_start_row = _end_row;
		_end_row = swap_var;

	}
	if (_start_row <= 0 || _end_row > _matrix_row_ )
	{
		Error("���ܻ���Ӿ����������������.");
		exit(EXIT_FAILURE);
	}
	int temp_row = abs(_end_row - _start_row) + 1;
	int temp_col = _matrix_column_;
	Matrix Temp(temp_row, temp_col, 0.0);
	for (int i = 0; i < temp_row; i++)
	{
		for (int j = 0; j < temp_col; j++)
		{
			Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[_start_row - 1 + i][j];
		}
	}

	return Temp;
}

Matrix Matrix::getBlock_byCol(int _start_col, int _end_col)
{
	int swap_var = 0;
	if (_start_col > _end_col)
	{
		swap_var = _start_col;
		_start_col = _end_col;
		_end_col = swap_var;
	}

	if (_start_col <= 0 || _end_col > _matrix_column_)
	{
		Error("���ܻ���Ӿ����������������");
		exit(EXIT_FAILURE);
	}
	//�����ɣ���ʼ��ȡ����
	int temp_row = _matrix_row_;
	int temp_col = abs(_end_col - _start_col) + 1;
	Matrix Temp(temp_row, temp_col, 0.0);
	for (int i = 0; i < temp_row; i++)
	{
		for (int j = 0; j < temp_col; j++)
		{
			Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[i][_start_col - 1 + j];
		}
	}

	return Temp;
}

Matrix Matrix::linkRow(int _row, const Matrix& _matrix_to_link)
{
	if (_row<0 || _row>_matrix_row_)
	{
		Error("�в���λ�ô�����������ȷ������������0��");
			exit(EXIT_FAILURE);
	}
	else if (_matrix_to_link._matrix_column_ != _matrix_column_)
	{
		Error("����ճ��������ճ��ʱ����������������������");
		exit(EXIT_FAILURE);
	}
	Matrix Temp(_matrix_row_ + _matrix_to_link._matrix_row_,_matrix_column_,0.0);//��Ӻ��������䣬�������ϱ�ճ���ľ��������
	//�������ֶ�Temp��ֵ
	for (int i = 0; i < Temp._matrix_row_; i++)
	{
		for (int j = 0; j < Temp._matrix_column_; j++)		
		{
			if (i < _row)//������ϰ벿�֣���Temp��������Ӧ1��_row
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[i][j];
			}
			else if (i < _row + _matrix_to_link._matrix_row_)	//����ľ��󣬶�Ӧ�к�_row+1��_row + _matrix_to_link._matrix_row_
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_to_link._matrix_head_pointer_[i-_row][j];
			}
			else //ʣ�µĲ��֣���ԭ���������ֵ����M���кŶ�Ӧ	_row + _matrix_to_link._matrix_row_+1��Temp._matrix_row_	,�ڵ�ǰ�����Ӧ_row+1��	_matrix_row_
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[i - _matrix_to_link._matrix_row_][j];
			}
		}
	}

	return Temp;
}

Matrix Matrix::linkCol(int _column, const Matrix& _matrix_to_link)
{
	if (_column < 0 || _column > _matrix_column_)
	{
		Error("�в���λ�ô�����������ȷ������������0��");
		exit(EXIT_FAILURE);
	}
	else if (_matrix_to_link._matrix_row_ != _matrix_row_)
	{
		Error("����ճ��������ճ��ʱ����������������������");
		exit(EXIT_FAILURE);
	}
	Matrix Temp(_matrix_row_, _matrix_column_ + _matrix_to_link._matrix_column_, 0.0);

	for (int i = 0; i < Temp._matrix_row_; i++)
	{
		for (int j = 0; j < Temp._matrix_column_; j++)
		{
			if (j < _column)
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[i][j];
			}
			else if (j < _column + _matrix_to_link._matrix_column_)	
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_to_link._matrix_head_pointer_[i][j - _column];
			}
			else
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[i][j - _matrix_to_link._matrix_column_];
			}
		}
	}

	return Temp;
}

//cmath��һЩ��������
Matrix pow(const Matrix& X, int Y)
{
	if (X._matrix_row_ != X._matrix_column_)
	{
		Matrix::Error("����˷�����ʧ�ܣ����Ƿ���");
	}
	if (Y == 0)
	{
		return Matrix::eye(X._matrix_row_);
	}
	else if (Y > 0)
	{
		Matrix Temp = X;
		while (Y > 1)
		{
			Temp = Temp * X;
			Y--;
		}
		return Temp;
	}
	else
	{
		Matrix Temp = X.inv();
		while (Y < -1)
		{
			Temp = Temp * Temp;
			Y++;
		}
		return Temp;
	}
}

