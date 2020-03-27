#pragma once
/*
@file name:	matrix.h
@author:	superb24ed
@version:	1.0
@date:		2020.03.27
@copyright:	Anyone can use and modify this source code in any way without authorization.
@email:		yuchao.xu@outlook.com
@github:	superb24ed
*/

#include <cmath>
#include <iostream>
#include <time.h>		

typedef bool linspace_type;
const linspace_type  ROW_LINSPACE = 0;	
const linspace_type	 COL_LINSPACE = 1;


//矩阵类的一个C++实现.请勿与其它实现类似功能代码混用
//构造矩阵时,数值建议使用double.以防整数值(int)与矩阵维度(int)混淆
class Matrix
{
protected:
	//数据成员
						//矩阵行数
			int			_matrix_row_;
						//矩阵列数
			int			_matrix_column_;
						//矩阵头指针，用于矩阵存储空间读取
			double**	_matrix_head_pointer_;								
	//只能被内部和友元调用
						//矩阵初始化，根据矩阵行数和列数内存分配内存空间
			void		__space_alloc();	
						//矩阵空间填充，用一个double值填充所有矩阵空位
			void		__fill(double);

						//参数调用出错时输出错误信息,并中止程序
	static	void		Error(const char*);	
public:
	
	//构造方阵

						//默认构造1*1的零矩阵.
						Matrix();
						//构造1*1矩阵，并用双精度数值val初始化.
						Matrix(double val);
						//构造维度为_dim的方阵
						Matrix(int);										
						//构造维度为_dim的方阵，并使用双精度数值val初始化.
						//这个构造函数因为可能会与Matrix(int,int)发生混淆而被弃用。重新使用它，取消这里和matrix.cpp里面的注释
						//Matrix(int _dim, double val);


	
	//构造普通矩阵

						//构造零矩阵
						Matrix(int _row, int _col);
						//构造矩阵，并使用双精度数值val初始化
						Matrix(int _row, int _col, double val );
						//构造矩阵，并使用整型数值val初始化.
						Matrix(int _row, int _col, int val );

	
	//通过数组构造矩阵

						//以一维数组val_array来初始化数组
						//注意1：val_array[]的成员数不能少于_row*_col个，否则将会越界访问.
						//注意2:double型数组不能强制转换为int*,否则矩阵赋值将会出现错误.
						Matrix(int _row, int _col, double* _val_array);
						//以一维数组val_array来初始化数组
						//注意1：val_array[]的成员数不能少于_row*_col个，否则将会越界访问.
						//注意2:int型数组不能强制转换为double*,否则矩阵赋值将会出现错误.
						Matrix(int _row, int _col, int* _val_array);

	//矩阵析构
	virtual				~Matrix();			//析构函数应当是虚函数，除非此类不用做基类

	//拷贝函数
	Matrix(const Matrix&);

	//运算符重载

			//矩阵的赋值操作
			Matrix&		operator=(const Matrix&);
			//将数组的值传给矩阵.可传入int或者double型的数组
			//维度需要预先定义
			Matrix&		operator=(double*);
			//矩阵乘法
			Matrix		operator*(const Matrix&);
			//矩阵数乘:Matrix*int
			Matrix		operator*(double coef);
			//矩阵数乘: int*Matrix
	friend	Matrix		operator*(double coef, const Matrix&);
			//矩阵加法
			Matrix		operator+(const Matrix&)const;
			//矩阵减法
			Matrix		operator-(const Matrix&)const;
			//取相反矩阵,或者负矩阵
			Matrix		operator-()const;
			//支持使用cin>>Matrix & 来输入矩阵（矩阵维度需要预先设置好），但是分隔符只能用空格，tab或者回车。
friend std::istream&	operator>>(std::istream&, const Matrix&);
			//支持使用cout<<Matrix &来显示矩阵.
friend std::ostream&	operator<<(std::ostream&, const Matrix&);

	//初等变换

			//行交换
			void		swapRows(int _row1, int row2);
			//列交换
			void		swapCols(int _col1, int _col2);
			//某一行乘以一个系数
			void		mulRow(int _row,double coef);
			//某一行乘以一个系数
			void		mulCol(int _col, double coef);
			//src_row这一行乘以系数coef加到dst_row这一行上
			void		addtoRow(int src_row, int dst_row, double coef);
			//src_col这一列乘以系数coef加到dst_col这一行上
			void		addtoCol(int _src_column, int _dst_column, double coef);	

	//修改矩阵元素

			//修改某个矩阵元素的值
			void		Modify(int _target_row, int _target_column, double modified_value);	
			//矩阵重置，将所有元素重置为0	
			void		Reset();
				
	//矩阵输出函数

			//输出行数
			int			Row()const;
			//输出列数
			int			Col()const;
			//输出_row行，_col列的值
			double		Elem(int _row, int _col)const;
			//显示矩阵
			void		Show()const;
			//显示行
			void		ShowRow(int _row)const;
			//显示列
			void		ShowCol(int _col)const;
			//求特征值，并将所有特征值输出至一个n*1维的矩阵.(会保留重复的特征值)
			Matrix		EigenValues(const Matrix&);
			//求某个矩阵的逆矩阵
	static  Matrix		inv(Matrix);
			//输出当前矩阵的逆矩阵
			Matrix		inv()const;
			//输出当前矩阵的转置
			Matrix		T()const;
			//计算当前矩阵的行列式
			double		Det()const;
			//解方程Ax=B
	static	Matrix		Solve(const Matrix& A, const Matrix& B);
			//输出两个矩阵的Hadmard乘积
	static	Matrix		Hadamard(const Matrix&, const Matrix&);	


	//快速构造特殊矩阵

	//构造长度为_dim的零方阵
	static	Matrix		zeros(int _dim);
	//构造_row*col的零矩阵
	static	Matrix		zeros(int _row, int _col);
	//构造维度为_dim的1方阵
	static	Matrix		ones(int _dim);
	//构造_row*col的1矩阵	
	static	Matrix		ones(int _row, int _col);
	//将一个double数组_valarray作为对角元，构造对角阵.
	//_val_array[]的长度不能小于_array_size,否则可能会发生越界访问.
	static	Matrix		diag(int _array_size_, const double* _val_array );
	//由一个int数组，构造对角阵
	//_val_array[]的长度不能小于_array_size,否则可能会发生越界访问.
	static	Matrix		diag(int _array_size_, const int* _val_array);
	//构造维度为_dim的单位矩阵 
	static	Matrix		eye(int _dim);
	//构造元素取值范围在(0,1),维度为_row*_col的随机矩阵
	static	Matrix		rand(int _row, int _col);
	//构造维度为linspace_dim的线性空间.type=ROW_LINSPACE返回行向量;type=COL_LINSPACE返回列向量.
	static	Matrix		linspace(double first_val, double last_val, int linspace_dim,linspace_type type);
				

	//通过矩阵分块与粘合得到新矩阵 (不会改变当前矩阵）

			//获取矩阵分块,前两个参数写起始终止行，后两个为起始终止列.
			Matrix		getBlock(int _start_row, int _end_row, int start_col, int _end_col);
			//根据行获取分块(保留全列）
			Matrix		getBlock_byRow(int _start_row, int _end_row);
			//根据列获取分块（保留全行)
			Matrix		getBlock_byCol(int _start_col, int _end_col);
			//在某行_row的下面插入矩阵._row=0则插入在最上面.
			Matrix		linkRow(int _row, const Matrix& _matrix_to_link);
			//在某列_column右侧插入矩阵. _column=0则在最左侧插入.
			Matrix		linkCol(int _column, const Matrix& _matrix_to_link);

			//cmath函数的重载
			
			//求矩阵X的Y次方，其中Y是整数
			friend	Matrix pow(const Matrix& X, int Y);
};

class SquareMatrix :public Matrix
{
public:
	SquareMatrix();
	SquareMatrix(double val);
	SquareMatrix(int _dim);
	SquareMatrix(int _dim, double val);


};