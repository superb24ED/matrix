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
//私有成员，仅内部和友元能够调用
void Matrix::__space_alloc() //初始化函数，根据行列分配矩阵的存储空间
{
	_matrix_head_pointer_ = new double* [_matrix_row_];
	for (int i = 0; i < _matrix_row_; ++i) {
		_matrix_head_pointer_[i] = new double[_matrix_column_];
	}
}
void Matrix::__fill(double val)			//矩阵空间填充
{
	for (int i = 0; i < _matrix_row_; i++)
	{
		for (int j = 0; j < _matrix_column_; j++)
		{
			_matrix_head_pointer_[i][j] = val;
		}
	}
}
void Matrix::Error(const char* error_message)		//检查出错时调用此函数输出错误信息
{
	std::cout << std::endl;
	fputs(error_message, stderr);			//输出错误信息至stderr
	abort();								//中止程序
}

//外部方法，可被其它类/对象或者外部函数调用

//构造方阵
Matrix::Matrix()							//构造1*1的零矩阵，即数值0
{
	_matrix_row_ = _matrix_column_ = 1;
	__space_alloc();
	**_matrix_head_pointer_ = 0;
}

Matrix::Matrix(double val)					//1*1，用双精度数值val初始化的方阵，即数值val.注意：后一个参数必须是双精度数
{
	//传入参数必须是浮点数，否则会调用Matrix(int &_order)而不是当前构造
	_matrix_row_ = _matrix_column_ = 1;
	__space_alloc();
	**_matrix_head_pointer_ = val;

}

Matrix::Matrix(int _order)					//阶数为_order的方阵，用0初始化
{
	if (_order <= 0)
	{
		Error("调用Matrix(int)构造矩阵时出现错误。请确认矩阵阶数是否正确.\n");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _matrix_column_ = _order;	//设置行列数
	__space_alloc();						//分配内存
	__fill(0.0);							//使用0填充

}

/*
//这个构造函数因为可能会与Matrix(int,int)发生混淆而被弃用
//要使用它，取消掉matrix.h和这里的注释即可
Matrix::Matrix(int _order, double val)
{
	if (_order <= 0)
	{
		fputs("调用Matrix(int,double)构造矩阵时出现错误。请确认矩阵阶数是否正确.\n", stderr);
		abort();
	}
	_matrix_row_ = _matrix_column_ = _order;	//设置行列数
	__space_alloc();						//分配内存
	__fill(val);							//使用val填充
}
*/
Matrix::Matrix(int _row, int _col)
{
	if (_row <= 0 || _col <= 0)
	{
		Error("调用Matrix(int,int)构造矩阵时出现错误。请确认行列数是否正确.\n");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _row;					//导入行数
	_matrix_column_ = _col;					//导入列数
	__space_alloc();						//分配内存
	__fill(0.0);							//以0填充
}

Matrix::Matrix(int _row, int _col, double val)
{
	if (_row <= 0 || _col <= 0)
	{
		Error("调用Matrix(int,int,double)构造矩阵时出现错误。请确认行列数是否正确.\n");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _row;					//导入行数
	_matrix_column_ = _col;					//导入列数
	__space_alloc();						//分配内存
	__fill(val);							//以val填充
}
Matrix::Matrix(int _row, int _col, int val)
{
	if (_row <= 0 || _col <= 0)
	{
		Error("调用Matrix(int,int,int)构造矩阵时出现错误。请确认行列数是否正确.\n");
		exit(EXIT_FAILURE);
	}
	_matrix_row_ = _row;					//导入行数
	_matrix_column_ = _col;					//导入列数
	__space_alloc();						//分配内存
	__fill(val);							//以val填充
}
Matrix::Matrix(int _row, int _col, double* _val_array)
{
	//以一维数组val_array来初始化数组,注意：val_array[]的成员数不能少于_row*_col个，否则将会越界访问
	//多维double数组的头指针，需要强制转换为double*再传入
	if (_row <= 0 || _col <= 0)
	{
		Error("调用Matrix(int,int,double*)构造矩阵时出现错误:请确认行列数是否正确.\n");
		exit(EXIT_FAILURE);
	}
	else if (_val_array == NULL)
	{
		Error("调用Matrix(int,int,double*)构造矩阵时出现错误:传入的指针是空指针");
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
	// 以一维数组val_array来初始化数组, 注意：val_array[]的成员数不能少于_row* _col个，否则将会越界访问
	//多维int数组的头指针，需要强制转换为int*再传入

	if (_row <= 0 || _col <= 0)
	{
		Error("调用Matrix(int,int,int*)构造矩阵时出现错误:请确认行列数是否正确.\n");
		exit(EXIT_FAILURE);
	}
	else if (_val_array == NULL)
	{
		Error("调用Matrix(int,int,int*)构造矩阵时出现错误:传入的指针是空指针.");
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
	//导入矩阵行列数
	_matrix_row_ = M._matrix_row_;
	_matrix_column_ = M._matrix_column_;
	//分配空间
	__space_alloc();
	//拷贝数值
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
	if (_matrix_row_ != M._matrix_row_ || _matrix_column_ != M._matrix_column_)		//尺寸不相同，需要重新分配空间
	{
		//释放当前存储空间
		for (int i = 0; i < _matrix_row_; i++)
		{
			delete[] _matrix_head_pointer_[i];
		}
		delete[] _matrix_head_pointer_;
		//导入新的行列数
		_matrix_row_ = M._matrix_row_;
		_matrix_column_ = M._matrix_column_;
		//重新分配空间
		__space_alloc();
		//将值拷贝至当前矩阵
	}
	for (int i = 0; i < _matrix_row_; i++)
	{
		for (int j = 0; j < _matrix_column_; j++)
		{
			_matrix_head_pointer_[i][j] = M._matrix_head_pointer_[i][j];
		}
	}
	// TODO: 在此处插入 return 语句
	//返回当前矩阵作为输出
	return *this;
}

Matrix& Matrix::operator=(double* _val_array)
{
	if (_val_array != NULL)		//在传入指针非空时才能操作
	{
		for (int i = 0; i < _matrix_row_; i++)
		{
			for (int j = 0; j < _matrix_column_; j++)
			{
				_matrix_head_pointer_[i][j] = *(_val_array + i * _matrix_column_ + j);		//	赋值值给当前矩阵
			}
		}
		return *this;
	}
	else
	{
		Error("在取等运算(=)时出现错误：传入的数组头指针有问题(空指针）");
		exit(EXIT_FAILURE);
	}
}

Matrix Matrix::operator*(const Matrix& M)
{
	if (_matrix_column_ == M._matrix_row_)		//只有前一个矩阵的列等于后一矩阵的行才能进行乘法操作
	{

		Matrix Temp(_matrix_row_, M._matrix_column_);	//乘积结果的矩阵规格：当前矩阵的行和后一个矩阵的列
		for (int i = 0; i < _matrix_row_; i++)
			for (int j = 0; j < M._matrix_column_; j++)//前两层循环表示“遍历结果矩阵Temp中的每一个元素”
			{
				for (int k = 0; k < _matrix_column_; k++)	//这一层循环表示“对前一矩阵第i行的列,和后一矩阵第j列的行，对应相乘后(用k递归)进行累加”
				{
					Temp._matrix_head_pointer_[i][j] += _matrix_head_pointer_[i][k] * M._matrix_head_pointer_[k][j];
				}
			}
		return Temp;	//输出计算结果Temp
	}
	Error("试图进行矩阵乘积出错：前一个矩阵的行不等于后一个矩阵的列.");
	exit(EXIT_FAILURE);
}

Matrix Matrix::operator*(double coef)
{
	Matrix Temp(*this);								//构造
	for (int i = 0; i < Temp._matrix_row_; i++)
	{
		for (int j = 0; j < Temp._matrix_column_; j++)
		{
			Temp._matrix_head_pointer_[i][j] *= coef;	//所有值乘以coef
		}
	}
	return Temp;
}

Matrix Matrix::operator+(const Matrix &M) const
{
	if (_matrix_row_ == M._matrix_row_ && _matrix_column_ == M._matrix_column_ )		//只有行列同时相等才能相加
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
		Error("尝试矩阵相加出错：两个矩阵的行列数必须一致.");
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
		Error("尝试矩阵相减出错：两个矩阵的行列数必须一致.");
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

	Matrix Temp(M);								//构造
	for (int i = 0; i < Temp._matrix_row_; i++)
	{
		for (int j = 0; j < Temp._matrix_column_; j++)
		{
			Temp._matrix_head_pointer_[i][j] *= coef;	//所有值乘以coef
		}
	}
	return Temp;
}

std::istream& operator>>(std::istream& _input_stream, const Matrix &M)		//从输入流初始化矩阵
{
	//清空缓冲区
	_input_stream.clear();
	_input_stream.sync();
	//从缓冲区读取数据
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
		Error("在尝试交换两行时出错:传入的行数不符合规范，请重新检查.");
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
		Error("在尝试交换两列时出错:传入的列数不符合规范，请重新检查.");
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
		Error("在尝试行加时出错：输入的行数应该是不超过最大行数的正整数，请重新检查");
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
		Error("在尝试列加时出错：输入的列数应该是不超过最大列数的正整数，请重新检查");
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
		Error("在尝试修改矩阵数值时出现错误：请输入正确的行数和列数");
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
		Error("尝试输出矩阵元素值时出现错误：请输入正确的行列数.");
		exit(EXIT_FAILURE);
	}
	_row--;
	_col--;
	return _matrix_head_pointer_[_row][_col];
}

void Matrix::Show() const
{
	std::cout.setf(std::ios::left);						//将输出左对齐
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
		Error("尝试显示矩阵的某行时出错：输入的行数不合法.");
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
		Error("尝试显示矩阵的某列时出错：输入的列数不合法.");
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
	//算法：全主元高斯消去法

	if (M._matrix_row_ != M._matrix_column_)
	{
		Error("无法求逆矩阵：不是方阵");
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
				if (abs(Temp._matrix_head_pointer_[i][j]) > abs(temp))		//第i+1列的那个值比fmax大
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
		Error("只有方阵能求逆矩阵");
		exit(EXIT_FAILURE);
	}
	double temp;
	Matrix Temp = Matrix(M._matrix_row_, M._matrix_column_);
	Temp = M;//为矩阵A做一个备份
	Matrix B = eye(M._matrix_row_);
	//将小于EPS的数全部置0
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
	//选择需要互换的两行选主元
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
				std::cout << "逆矩阵不存在\n";
				std::abort();
			}
		}
	}
	//通过初等行变换将A变为上三角矩阵
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
	//使对角元素均为1
	for (int i = 0; i < M._matrix_row_; i++)
	{
		temp = M._matrix_head_pointer_[i][i];
		for (int j = 0; j < M._matrix_column_; j++)
		{
			M._matrix_head_pointer_[i][j] /= temp;
			B._matrix_head_pointer_[i][j] /= temp;
		}
	}
	//将已经变为上三角矩阵的A，变为单位矩阵
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
	M = Temp;//还原A
	return B;//返回该矩阵的逆矩阵
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
		Error("无法作Hadmard乘积：请确认两个矩阵的尺寸规格相同.");
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
		Error("调用zero创建零方阵失败：请输入正确的阶数.");
		exit(EXIT_FAILURE);
	}
	return Matrix(_order);
}

Matrix Matrix::zeros(int _row, int _col)
{

	if (_row <= 0 || _col <= 0)
	{
		Error("调用zero创建零矩阵失败：请输入正确的行列数.");
		exit(EXIT_FAILURE);
	}
	return Matrix(_row, _col, 0.0);
}

Matrix Matrix::ones(int _order)
{

	if (_order <= 0)
	{
		Error("调用ones创建1方阵失败：请输入正确的阶数.");
		exit(EXIT_FAILURE);
	}
	return Matrix(_order, _order, 1.0);
}

Matrix Matrix::ones(int _row, int _col)
{

	if (_row <= 0 || _col <= 0)
	{
		Error("调用ones创建1矩阵失败：请输入正确的行列数.");
		exit(EXIT_FAILURE);
	}
	return Matrix(_row, _col, 1.0);
}

Matrix Matrix::diag(int _array_size, const double* _val_array)
{
	if (_array_size <= 0)
	{
		Error("调用diag出现错误：数组大小是非负的整数.");
		exit(EXIT_FAILURE);
	}
	else if (_val_array == NULL)
	{
		Error("调用diag出现错误：传入了空指针.");
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
		Error("调用diag出现错误：数组大小是非负的整数.");
		exit(EXIT_FAILURE);
	}
	else if (_val_array == NULL)
	{
		Error("调用diag出现错误：传入了空指针.");
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
		Error("尝试创建单位矩阵失败：请输入正确的阶数.");
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
		Error("构建随机矩阵失败：行列数必须是正整数.");
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
		Error("线性空间构造失败:线性空间的元素个数必须是正整数.");
		exit(EXIT_FAILURE);
	}
	else if (type == ROW_LINSPACE)
	{
		Matrix Temp1(linspace_nums, 1);
		Temp1._matrix_head_pointer_[linspace_nums - 1][0] = last_val;		//赋值最后一项
		for (int i = 0; i < linspace_nums - 1; i++)
		{
			Temp1._matrix_head_pointer_[i][0] = first_val + d * i;//赋值前n-1项
		}
		return Temp1;
	}
	else if (type == COL_LINSPACE)
	{
		Matrix Temp2(1, linspace_nums);
		Temp2._matrix_head_pointer_[0][linspace_nums - 1] = last_val;		//赋值最后一项
		for (int i = 0; i < linspace_nums - 1; i++)
		{
			Temp2._matrix_head_pointer_[0][i] = first_val + d * i;//赋值前n-1项
		}
		return Temp2;
	}
	Error("未知错误：无法构建所给类型的线性空间");
	exit(EXIT_FAILURE);
}

Matrix Matrix::getBlock(int _start_row, int _end_row, int _start_col, int _end_col)
{
	//让行和列按顺序排列，即保证起始行列不大于结束行列
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

	//判断输入的行列是否符合规范
	if (_start_row <= 0 || _start_col <= 0 || _end_row > _matrix_row_ || _end_col > _matrix_column_)
	{
		Error("不能获得子矩阵：输入的行数或列数有误");
		exit(EXIT_FAILURE);
	}
	//检查完成，开始截取矩阵
	int temp_row = abs(_end_row - _start_row) + 1;
	int temp_col = abs(_end_col - _start_col) + 1;
	Matrix Temp(temp_row, temp_col, 0.0);
	for (int i = 0; i < temp_row; i++)
	{
		for (int j = 0; j < temp_col; j++)
		{
			//这里注意：_start_row行，_start_col列的元是 M[_start_row-1][_start_col-1],数组下标要减一.或者可以直接调用Elem(_start_row,__start_col).
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
		Error("不能获得子矩阵：输入的行数有误.");
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
		Error("不能获得子矩阵：输入的列数有误");
		exit(EXIT_FAILURE);
	}
	//检查完成，开始截取矩阵
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
		Error("行插入位置错误：请输入正确的行数（或者0）");
			exit(EXIT_FAILURE);
	}
	else if (_matrix_to_link._matrix_column_ != _matrix_column_)
	{
		Error("矩阵粘连错误：行粘连时，两个矩阵的列数必须相等");
		exit(EXIT_FAILURE);
	}
	Matrix Temp(_matrix_row_ + _matrix_to_link._matrix_row_,_matrix_column_,0.0);//相加后，列数不变，行数加上被粘连的矩阵的行数
	//分三部分对Temp赋值
	for (int i = 0; i < Temp._matrix_row_; i++)
	{
		for (int j = 0; j < Temp._matrix_column_; j++)		
		{
			if (i < _row)//插入的上半部分，在Temp中行数对应1到_row
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_head_pointer_[i][j];
			}
			else if (i < _row + _matrix_to_link._matrix_row_)	//插入的矩阵，对应行号_row+1到_row + _matrix_to_link._matrix_row_
			{
				Temp._matrix_head_pointer_[i][j] = _matrix_to_link._matrix_head_pointer_[i-_row][j];
			}
			else //剩下的部分，是原矩阵里面的值，在M中行号对应	_row + _matrix_to_link._matrix_row_+1到Temp._matrix_row_	,在当前矩阵对应_row+1到	_matrix_row_
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
		Error("列插入位置错误：请输入正确的列数（或者0）");
		exit(EXIT_FAILURE);
	}
	else if (_matrix_to_link._matrix_row_ != _matrix_row_)
	{
		Error("矩阵粘连错误：列粘连时，两个矩阵的行数必须相等");
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

//cmath的一些函数重载
Matrix pow(const Matrix& X, int Y)
{
	if (X._matrix_row_ != X._matrix_column_)
	{
		Matrix::Error("矩阵乘方运算失败：不是方阵");
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

