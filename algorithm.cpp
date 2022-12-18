#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>


using namespace std;



class Matrix
{
private:
	int size_row;
	int size_column;
	int potential_i;
	int potential_j;
	int func;
	bool way = false;
	char symbol = '-';
	vector <int> min_vec;
	int minimal_element;
	vector <vector <int>> matrix;


	vector <vector <int>> price_matrix;
	vector <vector <int>> free_matrix;
	vector <vector <char>> matrix_plus_minus;

public:
	vector <int> resources;
	vector <int> consumers;

	void set_resources(vector <int> tmp) {
		this->resources = tmp;
	}

	void set_consumers(vector <int> tmp) {
		this->consumers = tmp;
	}

	Matrix(int size_row, int size_column)
	{
		this->size_row = size_row;
		this->size_column = size_column;
	}

	void mininmumCost()
	{
		vector <int> resources = { 70, 80, 90, 80 };
		vector <int> consumers = { 60, 40, 120, 100 };
		while(IsItEmpty(resources) || IsItEmpty(consumers))
		{
			for(int point = 1; point < 6; point++)
			{
				for (int i = 0; i < size_row; i++)
				{
					for (int j = 0; j < size_column; j++)
					{
						if(price_matrix[i][j] == point)
						{
							if (resources.at(i) < consumers.at(j) && resources.at(i) != 0 && consumers.at(j) !=0)
							{
								matrix[i][j] += resources[i];
								consumers[j] -= resources[i];
								resources[i] -= resources[i];
							}
							else if (resources.at(i) == consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
							{
								matrix[i][j] = consumers[j];
								resources[i] -= consumers[j];
								consumers.erase(consumers.begin() + i);
							}
							else if(resources.at(i) > consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
							{
								matrix[i][j] += resources.at(i) - (resources.at(i) - consumers.at(j));
								resources[i] -= consumers[j];
								consumers[j] -= consumers[j];
							}
						}
					}
				}
			}
		}
	}

	bool IsItEmpty(vector<int> &vec)
	{
		for (auto c : vec)
		{
			if (c > 0)
			{
				return 1;
			}
		}
		return 0;
	}

	void northwestCorner()
	{
		vector <int> resources = this->resources;
		vector <int> consumers = this->consumers;
		
		for (int i = 0; i < this->size_row; i++) 
		{
			for (int j = 0; j < this->size_column; j++) 
			{
				if (resources.at(i) < consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
				{
					matrix[i][j] += resources[i];
					consumers[j] -= resources[i];
					resources[i] -= resources[i];
				}
				else if (resources.at(i) == consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
				{
					matrix[i][j] = consumers[j];
					resources[i] -= consumers[j];
					consumers.erase(consumers.begin() + i);
				}
				else if (resources.at(i) > consumers.at(j) && resources.at(i) != 0 && consumers.at(j) != 0)
				{
					matrix[i][j] += resources.at(i) - (resources.at(i) - consumers.at(j));
					resources[i] -= consumers[j];
					consumers[j] -= consumers[j];
				}
			}
		}
	}
	

	void fillMatrix(vector <int> matrix)
	{
		int z = 0;
		for (int i = 0; i < this->size_row; i++) {
			vector <int> tmp_vec;
			for (int j = 0; j < this->size_column; j++) {
				tmp_vec.push_back(matrix[z++]);
			}
			this->matrix.push_back(tmp_vec);
		}
	}

	void printMatrix()
	{
		for (int i = 0; i < size_row; i++) {
			for (int j = 0; j < size_column; j++) {
				cout << right << setw(4) << this->matrix[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	void printPriceMatrix()
	{
		for (int i = 0; i < size_row; i++) {
			for (int j = 0; j < size_column; j++) {
				cout << right << setw(4) << this->price_matrix[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}

	bool potentials() // метод потенциалов
	{
		vector <bool> boolU = { true, false, false, false };
		vector <bool> boolV = { false, false, false, false };
		vector <int> u_vec = { 0, 0, 0, 0 };
		vector <int> v_vec = { 0, 0, 0, 0 };

		while (IsItTrue(boolU) || IsItTrue(boolV))
		{
			for (int i = 0; i < size_row; i++)
			{
				for (int j = 0; j < size_column; j++)
				{
					if(matrix[i][j] != 0)
					{
						if(boolU[i] != false)
						{
							v_vec[j] = price_matrix[i][j] - u_vec[i];
							boolV[j] = true;
						}
						if(boolV[j] != false)
						{
							u_vec[i] = price_matrix[i][j] - v_vec[j];
							boolU[i] = true;
						}
					}
				}
			}
		}
		if(delta(u_vec, v_vec))
		{
			return 1;
		}
		return 0;
	}

	bool delta(vector<int> u_vec, vector<int> v_vec)
	{
		int negative = 0;
		for(int i = 0; i < size_row; i++)
		{
			for( int j = 0; j < size_column; j++)
			{
				if(matrix[i][j] == 0)
				{
					this->free_matrix[i][j] = price_matrix[i][j] - (u_vec[i] + v_vec[j]);
					//нахождение наибольшего отрицательного значения
					if(free_matrix[i][j]<0 && free_matrix[i][j] < negative)
					{
						negative = free_matrix[i][j];
					}
				}
			}
		}
		// проверка существование отрицательных значений
		if(negative<0)
		{
			//vector <int> ::iterator it = min_element(negative_vec.begin(), negative_vec.end());
			for (int i = 0; i < size_row; i++)
			{
				for (int j = 0; j < size_column; j++)
				{
					if(negative == free_matrix[i][j])
					{
						//cout <<setw(10) <<negative<<endl;
						this->potential_i = i;
						this->potential_j = j;
						return 1;
					}
				}
			}
		}
		return 0;
	}

	bool IsItTrue(vector<bool> &bool_vec)
	{
		for(auto c : bool_vec)
		{
			if(c == false)
			{
				return 1;
			}
		}
		return 0;
	}

	void target_func() // подсчёт целевой функции
	{
		this->func = 0;
		for(int i = 0; i <size_row; i++)
		{
			for (int j = 0; j < size_column; j++)
			{
				if(matrix[i][j] != 0)
				{
					this->func += matrix[i][j] * price_matrix[i][j];
				}
			}
		}
		cout << " F = " << this->func<<endl;
	}

	void min_func() // нахождение минимального элемента
	{
		for (int i = 0; i < size_row; i++)
		{
			for (int j = 0; j < size_column; j++)
			{
				if(matrix_plus_minus[i][j] == '-')
				{
					this->min_vec.push_back(matrix[i][j]);
				}
			}
		}
		vector <int> ::iterator it = min_element(min_vec.begin(), min_vec.end());
		minimal_element = *it;
		min_vec.clear();
	}

	void searchLoop(int i, int j) // поиск цикла
	{
		matrix_plus_minus[i][j] = '+';
		if ((j != 0) && !way)
		{
			go_left(i, j - 1);
		}
		if ((j != size_column - 1) && !way) 
		{
			go_right(i, j + 1);
		}
		if ((i != 0) && !way) {
			go_up(i - 1, j);
		}
		if ((i != size_row - 1) && !way) 
		{
			go_down(i + 1, j);
		}
		way = false;
		symbol = '-';
	}

	void go_down(int i, int j)
	{
		if ((i == potential_i) && (j == potential_j)) 
		{
			way = true;
		}
		if ((i != this->size_column - 1) && !way) 
		{
			go_down(i + 1, j);
		}
		if ((j != 0) && (matrix[i][j] != 0) && !way) 
		{
			go_left(i, j - 1);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
		if ((j != this->size_row - 1) && (matrix[i][j] != 0) && !way) 
		{
			go_right(i, j + 1);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
	}

	void go_up(int i, int j)
	{
		if ((i == potential_i) && (j == potential_j))
		{
			way = true;
		}
		if ((i != 0) && !way) 
		{
			go_up(i - 1, j);
		}
		if ((j != 0) && (matrix[i][j] != 0) && !way) 
		{
			go_left(i, j - 1);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
		if ((j != this->size_row - 1) && (matrix[i][j] != 0) && !way) 
		{
			go_right(i, j + 1);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
	}

	void go_right(int i, int j)
	{
		if ((i == potential_i) && (j == potential_j)) 
		{
			way = true;
		}
		if ((j != this->size_row - 1) && !way) 
		{
			go_right(i, j + 1);
		}
		if ((i != 0) && (matrix[i][j] != 0) && !way) 
		{
			go_up(i - 1, j);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
		if ((i != this->size_row - 1) && (matrix[i][j] != 0) && !way) 
		{
			go_down(i + 1, j);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
	}

	void go_left(int i, int j)
	{
		if ((i == potential_i) && (j == potential_j)) 
		{
			way = true;
		}
		if ((j != 0) && !way) 
		{
			go_left(i, j - 1);
		}
		if ((i != 0) && (matrix[i][j] != 0) && !way) 
		{
			go_up(i - 1, j);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
		if ((i != this->size_row - 1) && (matrix[i][j] != 0) && !way) 
		{
			go_down(i + 1, j);
			if (way and matrix[i][j] != '0') 
			{
				matrix_plus_minus[i][j] = symbol;
				if (symbol == '+') { symbol = '-'; }
				else { symbol = '+'; }
			}
		}
	}

	void calculating()
	{
		for (int i = 0; i < size_row; i++) 
		{
			for (int j = 0; j < size_column; j++) 
			{
				if (matrix_plus_minus[i][j] == '-') 
				{
					matrix[i][j] -= minimal_element;
				}
				else if (matrix_plus_minus[i][j] == '+') 
				{
					matrix[i][j] += minimal_element;
				}
			}
		}
		minimal_element = 0;
	}

	void start()
	{
		while (potentials())
		{
			matrix_plus_minus = { {'0', '0', '0', '0'},
									{'0', '0', '0','0'},
									{'0', '0', '0', '0'},
									{'0', '0', '0', '0'} };
			searchLoop(potential_i, potential_j);
			min_func();
			calculating();
			printMatrix();
		}
	}
	int getSize_row() { return this->size_row; }

	int getSize_column() { return this->size_column; }

	vector <vector <int>> getMatrix() { return this->matrix; }
		
};



