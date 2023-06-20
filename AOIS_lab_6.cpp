#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
class Cell
{
public:
	Cell();
	Cell(std::string key, std::string value);
	Cell(const Cell& cell);
	std::string key, value;
	Cell* next_element;
};

class Hash_table
{
public:
	Hash_table();
	~Hash_table();
	void add_element(std::string key, std::string value);
	void del_element(std::string key);
	Cell get_element(std::string key);
	void print_table();
	void increase();
private:

	bool need_increase();
	std::vector<Cell*> cells;
	int hash_function(std::string key);

};


Hash_table::Hash_table()
{
	for (int i = 0; i < 20; i++)
	{
		this->cells.push_back(NULL);
	}
}

Hash_table::~Hash_table()
{
	while (this->cells.size())
	{
		this->cells.pop_back();
	}
}

void Hash_table::add_element(std::string key, std::string value)
{
	Cell* buffer_cell = new Cell(key, value), * temp;
	int hash_id = this->hash_function(key);
	if (this->cells[hash_id] == NULL)
	{
		this->cells[hash_id] = buffer_cell;
		if (this->need_increase())
		{
			this->increase();
		}
		return;
	}
	temp = this->cells[hash_id];
	if (temp->key == key)
	{
		throw "KeyError";
	}
	while (temp->next_element != NULL)
	{
		if (temp->key == key)
		{
			throw "KeyError";
		}
		temp = temp->next_element;
	}
	temp->next_element = buffer_cell;
	if (this->need_increase())
	{
		this->increase();
	}
	return;
}

void Hash_table::del_element(std::string key)
{
	Cell* temp, * prev_temp = NULL;
	int hash_id = this->hash_function(key);
	if (this->cells[hash_id] == NULL)
	{
		throw "KeyError";
	}
	temp = this->cells[hash_id];
	if (temp->key == key)
	{
		cells[hash_id] = (temp->next_element);
		delete temp;
		return;
	}

	while (temp->next_element != NULL)
	{
		if (temp->key == key)
		{
			prev_temp->next_element = temp->next_element;
			delete temp;
			return;
		}
		prev_temp = temp;
		temp = temp->next_element;
	}
	throw "KeyError";
}

Cell Hash_table::get_element(std::string key)
{
	Cell* temp;
	int hash_id = this->hash_function(key);
	if (this->cells[hash_id] == NULL)
	{
		throw "KeyError";
	}
	temp = this->cells[hash_id];
	if (temp->key == key)
	{
		Cell gettet_cell(temp->key, temp->value);
		return gettet_cell;
	}
	while (temp->next_element != NULL)
	{
		if (temp->key == key)
		{
			Cell gettet_cell(temp->key, temp->value);
			return gettet_cell;
		}
		temp = temp->next_element;
	}
	throw "KeyError";
}

void Hash_table::print_table()
{
	std::cout << "id\t key\t value\n";
	for (int i = 0; i < this->cells.size(); i++)
	{
		if (this->cells[i] == NULL)
		{
			std::cout << i + 1 << ": \n";
			continue;
		}
		Cell* temp = this->cells[i];
		std::cout << i + 1 << ": \t";
		while (temp != NULL)
		{
			std::cout << temp->key << ":\t" << temp->value << ";\t";
			temp = temp->next_element;
		}
		std::cout << "\n";
	}
}

void Hash_table::increase()
{
	std::vector<Cell*> old_vector = cells;
	this->cells.clear();
	for (int i = 0; i < old_vector.size() + 10; i++)
	{
		this->cells.push_back(NULL);
	}
	for (int i = 0; i < old_vector.size(); i++)
	{
		if (old_vector.at(i) == NULL)
		{
			continue;
		}
		Cell* buffer_current_cell = old_vector.at(i);
		this->add_element(buffer_current_cell->key, buffer_current_cell->value);
		while (buffer_current_cell->next_element != NULL)
		{
			buffer_current_cell = buffer_current_cell->next_element;
			this->add_element(buffer_current_cell->key, buffer_current_cell->value);

		}
	}
}

bool Hash_table::need_increase()
{
	int count_of_not_empty = 0;
	for (int i = 0; i < this->cells.size(); i++)
	{
		if (cells.at(i) != NULL)
		{
			count_of_not_empty++;
		}
	}
	if (count_of_not_empty * 100 / this->cells.size() < 75)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int Hash_table::hash_function(std::string key)
{
	int hash_id = 0;
	for (int i = 0; i < key.size(); i++)
	{
		hash_id += (-1 * key[i]);
	}
	hash_id %= this->cells.size();
	return hash_id;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	Hash_table my_hach_table;
	std::ifstream fin("test.txt");

	while (!fin.eof())
	{
		std::string buffer_key = "", buffer_value = "", buffer_cell_str;
		getline(fin, buffer_cell_str);
		bool first_space = false;
		int counter = 0;
		while (!first_space)
		{
			if (buffer_cell_str[counter] == ' ')
			{
				first_space = true;
				break;
			}
			buffer_key += buffer_cell_str[counter];
			counter++;
		}
		for (int i = counter + 1; i < buffer_cell_str.size(); i++)
		{
			buffer_value += buffer_cell_str[i];
		}
		my_hach_table.add_element(buffer_key, buffer_value);
	}
	my_hach_table.print_table();
	std::cout << (int)("С") << ' ' << (int)("о") << ' ' << (int)("ю") << ' ' << (int)("з") << '\n';
	int case_key;

	while (true)
	{
		std::string input_key, input_value, buffer;
		std::cout << "1 - add element, 2 - search element, 3 - delete element, 4 - view table: ";
		std::cin >> case_key;
		switch (case_key)
		{
		case 1:
		{
			std::cout << "Input key: ";
			std::cin >> input_key;
			std::cout << "Input value: ";
			std::cin >> input_value;
			getline(std::cin, buffer);
			input_value += buffer;
			try
			{
				my_hach_table.add_element(input_key, input_value);
			}
			catch (...)
			{
				std::cout << "Key is already used\n";
			}
			break;
		}
		case 2:
		{
			std::cout << "Input key: ";
			std::cin >> input_key;
			Cell gettet_cell;
			try
			{
				gettet_cell = my_hach_table.get_element(input_key);
			}
			catch (...)
			{
				std::cout << "Key not found\n";
			}
			std::cout << gettet_cell.key << " " << gettet_cell.value << " ";
			break;
		}
		case 3:
		{
			std::cout << "Input key: ";
			std::cin >> input_key;
			try
			{
				my_hach_table.del_element(input_key);
			}
			catch (...)
			{
				std::cout << "Key not found\n";
			}
			break;
		}
		case 4:
		{
			my_hach_table.print_table();
			break;
		}
		case 5:
		{
			my_hach_table.increase();
			break;
		}
		default:
			std::cout << "Invalid input";
		}
	}
	my_hach_table.~Hash_table();
}

Cell::Cell()
{
	this->value = "";
	this->key = "";
}

Cell::Cell(std::string key, std::string value)
{
	this->key = key;
	this->value = value;
	this->next_element = NULL;
}

Cell::Cell(const Cell& cell)
{
	this->key = cell.key;
	this->value = cell.value;
}

