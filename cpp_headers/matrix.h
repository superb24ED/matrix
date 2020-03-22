#ifndef __MATRIX_SUP_H__
#define __MATRIX_SUP_H__
/* A Matrix realization of superb24ed. Inspired by cclplus.
my email:2590889389@qq.com
cclplus's email:707101557@qq.com
For learning purpose only.
Warning:this realization  file is not insured to compatible with other header files related to matrix realization.
Do not include them in the same project.
*/  
#include "pch.h"
//define class matrix
class Matrix
{
private: 
	int row_nums,col_nums;	//row numbers and column numbers.
	double **p;
	void initialize();		//the initialization function of the matrix.
	
public:
	//constructor
	Matrix(int);				//square matrix.
	Matrix(int,int);
	Matrix(int,int,double);		//pre-alloced 
	Matrix(Matrix&);			//a new copy from existed matrix.
	
	//destructor
	virtual ~Matrix();
	
	//operator reload.
	Matrix& operator=(double *);			//matrix assignment.
	Matrix& operator=(double *);			//matrix assignment from an array. 
	Matrix& operator+=(const Matrix&);		
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);		
	Matrix operator*(const Matrix & m)const	//
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	bool _is_initlized;	//初始化标记.判断是否初始化，是则为true.
	public:
		//矩阵头 
		double **head;
		//行数和列数 
		int row;
		int col;
		//矩阵构造方法 
		matrix(int length,const double** head);	//导入方阵 
		matrix(int rows,int cols,const double** head);//导入普通矩阵 
		
		//矩阵析构方法 
		~matrix();
		//矩阵拷贝方法
		matrix(matrix& A);
			
		//运算符重载
		matrix& operator+(matrix& A);		//矩阵加法
		matrix& operator-(matrix& A);		//矩阵减法 
		matrix& operator*(matrix& A) ;   	//矩阵乘法
		matrix& operator*(double lamda);	//矩阵数乘
		matrix& operator=(matrix &A);		//矩阵赋值 
		
		//矩阵性质判断
		bool is_square();	//是否方阵
		bool is_sym();		//是否对称 
		bool is_odd();		//是否奇异
		
		//矩阵求值 
		double det();			//行列式
		matrix& inverse();		//矩阵求逆 
		double& envs();			//特征值 
		
		//矩阵输出
		void _print();			//打印矩阵 
		 
}; 

inline matrix::matrix(int rows,int cols,const double** head)
{
//对矩阵赋值，行数为rows,列数为cols,数据初始化位置为二维数组head[rows][cols]
	//行数和列数必须大于0！ 
	if (rows<=0||cols<=0)
	{
		this->_is_initlized=false;
		this->head=NULL;
		return ;
	}
	this->		row=rows;
	this->		col=cols;
	//为矩阵分配空间
	this->  	head=new double*[this->row];
	for (int i=0;i<this->row;i++)
		this->head[i] = new double[col];
	//初始化 
	//将数组的值转移到矩阵中 
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			this->head[i][j]=head[i][j];
	
	//初始化完成，将初始化标记设为true 
	this->_is_initlized = true; 
}

inline matrix::matrix(int length,const double** head)
{ 
//对矩阵赋值。该矩阵为方阵，长度为length,矩阵数据存储在一个二维数组head[length][length]中
	matrix(length,length,head);
	 
}
inline matrix::~matrix()
{
	for(int i=0;i<row;i++)
		delete []head;
	delete []head;
}

#endif __MATRIX_SUP_H__ 
