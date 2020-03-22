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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	bool _is_initlized;	//��ʼ�����.�ж��Ƿ��ʼ��������Ϊtrue.
	public:
		//����ͷ 
		double **head;
		//���������� 
		int row;
		int col;
		//�����췽�� 
		matrix(int length,const double** head);	//���뷽�� 
		matrix(int rows,int cols,const double** head);//������ͨ���� 
		
		//������������ 
		~matrix();
		//���󿽱�����
		matrix(matrix& A);
			
		//���������
		matrix& operator+(matrix& A);		//����ӷ�
		matrix& operator-(matrix& A);		//������� 
		matrix& operator*(matrix& A) ;   	//����˷�
		matrix& operator*(double lamda);	//��������
		matrix& operator=(matrix &A);		//����ֵ 
		
		//���������ж�
		bool is_square();	//�Ƿ���
		bool is_sym();		//�Ƿ�Գ� 
		bool is_odd();		//�Ƿ�����
		
		//������ֵ 
		double det();			//����ʽ
		matrix& inverse();		//�������� 
		double& envs();			//����ֵ 
		
		//�������
		void _print();			//��ӡ���� 
		 
}; 

inline matrix::matrix(int rows,int cols,const double** head)
{
//�Ծ���ֵ������Ϊrows,����Ϊcols,���ݳ�ʼ��λ��Ϊ��ά����head[rows][cols]
	//�����������������0�� 
	if (rows<=0||cols<=0)
	{
		this->_is_initlized=false;
		this->head=NULL;
		return ;
	}
	this->		row=rows;
	this->		col=cols;
	//Ϊ�������ռ�
	this->  	head=new double*[this->row];
	for (int i=0;i<this->row;i++)
		this->head[i] = new double[col];
	//��ʼ�� 
	//�������ֵת�Ƶ������� 
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			this->head[i][j]=head[i][j];
	
	//��ʼ����ɣ�����ʼ�������Ϊtrue 
	this->_is_initlized = true; 
}

inline matrix::matrix(int length,const double** head)
{ 
//�Ծ���ֵ���þ���Ϊ���󣬳���Ϊlength,�������ݴ洢��һ����ά����head[length][length]��
	matrix(length,length,head);
	 
}
inline matrix::~matrix()
{
	for(int i=0;i<row;i++)
		delete []head;
	delete []head;
}

#endif __MATRIX_SUP_H__ 
