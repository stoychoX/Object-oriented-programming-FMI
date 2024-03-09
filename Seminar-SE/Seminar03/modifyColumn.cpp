#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

#pragma warning(disable : 4996)

namespace GlobalConstants
{
	constexpr int FIELD_MAX_SIZE = 30;
	constexpr int MAX_FIELDS_ROW = 10;
	constexpr int ROWS_MAX_SIZE = 300;
	constexpr int BUFFER_SIZE = 1024;
	constexpr char SEP = ',';
}

typedef char Field[GlobalConstants::FIELD_MAX_SIZE];

struct Row
{
	Field fields[GlobalConstants::MAX_FIELDS_ROW];
};

struct CsvTable
{
	Row rows[GlobalConstants::ROWS_MAX_SIZE];
	size_t rowsCount = 0;
	size_t collsCount = 0;
};

size_t parseRow(const char *row, Row &toReturn)
{
	std::stringstream ss(row);

	size_t currentColumnCount = 0;
	while (!ss.eof())
	{
		ss.getline(toReturn.fields[currentColumnCount++],
				   GlobalConstants::FIELD_MAX_SIZE,
				   GlobalConstants::SEP);
	}
	return currentColumnCount;
}
CsvTable parseFromFile(std::istream &ifs)
{
	CsvTable result;
	char buff[GlobalConstants::BUFFER_SIZE];
	while (!ifs.eof())
	{
		ifs.getline(buff, GlobalConstants::BUFFER_SIZE);
		result.collsCount = parseRow(buff, result.rows[result.rowsCount++]);
	}
	return result;
}
CsvTable parseFromFile(const char *fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return {};
	}

	return parseFromFile(ifs);
}

void printTable(const CsvTable &table)
{
	for (int i = 0; i < table.rowsCount; i++)
	{
		for (int j = 0; j < table.collsCount; j++)
		{
			std::cout << table.rows[i].fields[j] << "          ";
		}
		std::cout << std::endl;
	}
}

void saveRowToFile(std::ostream &ofs, const Row &row, size_t collsCount)
{
	for (int i = 0; i < collsCount; i++)
	{
		ofs << row.fields[i];
		if (i != collsCount - 1)
		{
			ofs << GlobalConstants::SEP;
		}
	}
}

void saveToFile(std::ostream &ofs, const CsvTable &table)
{
	for (int i = 0; i < table.rowsCount; i++)
	{
		saveRowToFile(ofs, table.rows[i], table.collsCount);
		if (i != table.rowsCount - 1)
		{
			ofs << std::endl;
		}
	}
}

void saveToFile(const char *fileName, const CsvTable &table)
{
	std::ofstream ofs(fileName);
	saveToFile(ofs, table);
	ofs.close();
}

const char *getColumnAtIndex(const CsvTable &table, size_t index)
{
	if (index >= table.collsCount)
		return nullptr;
	return table.rows[0].fields[index];
}

int findColumnIndex(const CsvTable &table, const char *columnName)
{
	for (size_t i = 0; i < table.collsCount; i++)
	{
		if (strcmp(getColumnAtIndex(table, i), columnName) == 0)
			return (int)i;
	}
	return -1;
}

void setValue(CsvTable &table, size_t colIndex, size_t rowIndex, const char *value)
{
	strcpy(table.rows[rowIndex].fields[colIndex], value);
}

void modifyColumn(CsvTable &table, size_t columnIndex, const char *values, char separator)
{
	std::stringstream ss(values);
	char buff[GlobalConstants::FIELD_MAX_SIZE];
	size_t currentRow = 1;

	while (!ss.eof())
	{
		ss.getline(buff, GlobalConstants::FIELD_MAX_SIZE, separator);
		setValue(table, columnIndex, currentRow++, buff);

		if (currentRow >= table.rowsCount)
			break;
	}
}

void modifyColumn(const char *filePath, const char *columnName, const char *values, char separator)
{
	CsvTable table = parseFromFile(filePath);

	int index = findColumnIndex(table, columnName);

	if (index == -1)
		return;

	modifyColumn(table, index, values, separator);
	saveToFile(filePath, table);
}

int main()
{
	modifyColumn(
		"table.csv",
		"C1",
		"a1#b1#c1#d1#e1",
		'#');
}