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


//�������һ��C++ʵ��.����������ʵ�����ƹ��ܴ������
//�������ʱ,��ֵ����ʹ��double.�Է�����ֵ(int)�����ά��(int)����
class Matrix
{
protected:
	//���ݳ�Ա
						//��������
			int			_matrix_row_;
						//��������
			int			_matrix_column_;
						//����ͷָ�룬���ھ���洢�ռ��ȡ
			double**	_matrix_head_pointer_;								
	//ֻ�ܱ��ڲ�����Ԫ����
						//�����ʼ�������ݾ��������������ڴ�����ڴ�ռ�
			void		__space_alloc();	
						//����ռ���䣬��һ��doubleֵ������о����λ
			void		__fill(double);

						//�������ó���ʱ���������Ϣ,����ֹ����
	static	void		Error(const char*);	
public:
	
	//���췽��

						//Ĭ�Ϲ���1*1�������.
						Matrix();
						//����1*1���󣬲���˫������ֵval��ʼ��.
						Matrix(double val);
						//����ά��Ϊ_dim�ķ���
						Matrix(int);										
						//����ά��Ϊ_dim�ķ��󣬲�ʹ��˫������ֵval��ʼ��.
						//������캯����Ϊ���ܻ���Matrix(int,int)���������������á�����ʹ������ȡ�������matrix.cpp�����ע��
						//Matrix(int _dim, double val);


	
	//������ͨ����

						//���������
						Matrix(int _row, int _col);
						//������󣬲�ʹ��˫������ֵval��ʼ��
						Matrix(int _row, int _col, double val );
						//������󣬲�ʹ��������ֵval��ʼ��.
						Matrix(int _row, int _col, int val );

	
	//ͨ�����鹹�����

						//��һά����val_array����ʼ������
						//ע��1��val_array[]�ĳ�Ա����������_row*_col�������򽫻�Խ�����.
						//ע��2:double�����鲻��ǿ��ת��Ϊint*,�������ֵ������ִ���.
						Matrix(int _row, int _col, double* _val_array);
						//��һά����val_array����ʼ������
						//ע��1��val_array[]�ĳ�Ա����������_row*_col�������򽫻�Խ�����.
						//ע��2:int�����鲻��ǿ��ת��Ϊdouble*,�������ֵ������ִ���.
						Matrix(int _row, int _col, int* _val_array);

	//��������
	virtual				~Matrix();			//��������Ӧ�����麯�������Ǵ��಻��������

	//��������
	Matrix(const Matrix&);

	//���������

			//����ĸ�ֵ����
			Matrix&		operator=(const Matrix&);
			//�������ֵ��������.�ɴ���int����double�͵�����
			//ά����ҪԤ�ȶ���
			Matrix&		operator=(double*);
			//����˷�
			Matrix		operator*(const Matrix&);
			//��������:Matrix*int
			Matrix		operator*(double coef);
			//��������: int*Matrix
	friend	Matrix		operator*(double coef, const Matrix&);
			//����ӷ�
			Matrix		operator+(const Matrix&)const;
			//�������
			Matrix		operator-(const Matrix&)const;
			//ȡ�෴����,���߸�����
			Matrix		operator-()const;
			//֧��ʹ��cin>>Matrix & ��������󣨾���ά����ҪԤ�����úã������Ƿָ���ֻ���ÿո�tab���߻س���
friend std::istream&	operator>>(std::istream&, const Matrix&);
			//֧��ʹ��cout<<Matrix &����ʾ����.
friend std::ostream&	operator<<(std::ostream&, const Matrix&);

	//���ȱ任

			//�н���
			void		swapRows(int _row1, int row2);
			//�н���
			void		swapCols(int _col1, int _col2);
			//ĳһ�г���һ��ϵ��
			void		mulRow(int _row,double coef);
			//ĳһ�г���һ��ϵ��
			void		mulCol(int _col, double coef);
			//src_row��һ�г���ϵ��coef�ӵ�dst_row��һ����
			void		addtoRow(int src_row, int dst_row, double coef);
			//src_col��һ�г���ϵ��coef�ӵ�dst_col��һ����
			void		addtoCol(int _src_column, int _dst_column, double coef);	

	//�޸ľ���Ԫ��

			//�޸�ĳ������Ԫ�ص�ֵ
			void		Modify(int _target_row, int _target_column, double modified_value);	
			//�������ã�������Ԫ������Ϊ0	
			void		Reset();
				
	//�����������

			//�������
			int			Row()const;
			//�������
			int			Col()const;
			//���_row�У�_col�е�ֵ
			double		Elem(int _row, int _col)const;
			//��ʾ����
			void		Show()const;
			//��ʾ��
			void		ShowRow(int _row)const;
			//��ʾ��
			void		ShowCol(int _col)const;
			//������ֵ��������������ֵ�����һ��n*1ά�ľ���.(�ᱣ���ظ�������ֵ)
			Matrix		EigenValues(const Matrix&);
			//��ĳ������������
	static  Matrix		inv(Matrix);
			//�����ǰ����������
			Matrix		inv()const;
			//�����ǰ�����ת��
			Matrix		T()const;
			//���㵱ǰ���������ʽ
			double		Det()const;
			//�ⷽ��Ax=B
	static	Matrix		Solve(const Matrix& A, const Matrix& B);
			//������������Hadmard�˻�
	static	Matrix		Hadamard(const Matrix&, const Matrix&);	


	//���ٹ����������

	//���쳤��Ϊ_dim���㷽��
	static	Matrix		zeros(int _dim);
	//����_row*col�������
	static	Matrix		zeros(int _row, int _col);
	//����ά��Ϊ_dim��1����
	static	Matrix		ones(int _dim);
	//����_row*col��1����	
	static	Matrix		ones(int _row, int _col);
	//��һ��double����_valarray��Ϊ�Խ�Ԫ������Խ���.
	//_val_array[]�ĳ��Ȳ���С��_array_size,������ܻᷢ��Խ�����.
	static	Matrix		diag(int _array_size_, const double* _val_array );
	//��һ��int���飬����Խ���
	//_val_array[]�ĳ��Ȳ���С��_array_size,������ܻᷢ��Խ�����.
	static	Matrix		diag(int _array_size_, const int* _val_array);
	//����ά��Ϊ_dim�ĵ�λ���� 
	static	Matrix		eye(int _dim);
	//����Ԫ��ȡֵ��Χ��(0,1),ά��Ϊ_row*_col���������
	static	Matrix		rand(int _row, int _col);
	//����ά��Ϊlinspace_dim�����Կռ�.type=ROW_LINSPACE����������;type=COL_LINSPACE����������.
	static	Matrix		linspace(double first_val, double last_val, int linspace_dim,linspace_type type);
				

	//ͨ������ֿ���ճ�ϵõ��¾��� (����ı䵱ǰ����

			//��ȡ����ֿ�,ǰ��������д��ʼ��ֹ�У�������Ϊ��ʼ��ֹ��.
			Matrix		getBlock(int _start_row, int _end_row, int start_col, int _end_col);
			//�����л�ȡ�ֿ�(����ȫ�У�
			Matrix		getBlock_byRow(int _start_row, int _end_row);
			//�����л�ȡ�ֿ飨����ȫ��)
			Matrix		getBlock_byCol(int _start_col, int _end_col);
			//��ĳ��_row������������._row=0�������������.
			Matrix		linkRow(int _row, const Matrix& _matrix_to_link);
			//��ĳ��_column�Ҳ�������. _column=0������������.
			Matrix		linkCol(int _column, const Matrix& _matrix_to_link);

			//cmath����������
			
			//�����X��Y�η�������Y������
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