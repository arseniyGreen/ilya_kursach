#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <utility>

class Cell
{
private:
    int cost, income;
    int cordX, cordY;
public:
    Cell(int cost_, int income_, int cordX_, int cordY_) : cost(cost_), income(income_), cordX(cordX_), cordY(cordY_) {};
    ~Cell() {};

    friend std::ostream& operator<<(std::ostream&, Cell cell);

    void getData() { std::cout << "Income : " << income << " Cost : " << cost; }
    int getCost() { return cost; }
    int getIncome() { return income; }
    void setCost(int cost_) { cost = cost_; }
    void setIncome(int income_) { income = income_; }

};

class Field
{
private:
    friend class Cell;
    size_t x, y, cellCount;

    int totalBudget;

    std::vector<std::vector<Cell>> field; /* field array X*Y */
    std::vector<std::vector<int>> A;
    std::vector<int> ans;
    std::vector<int> costVec;
    std::vector<int> incomeVec;

public:
    Field() {};
    Field(size_t x_, size_t y_, int totalBudget_) /* Init field here */
    {
        this->totalBudget = totalBudget_;
        this->x = x_;
        this->y = y_;
        cellCount = 0;
        for (int i = 0; i < x; i++) {
            // Vector to store column elements
            std::vector<Cell> v1;

            for (int j = 0; j < y; j++)
            {
                Cell temp(0, 0, i, j);
                v1.push_back(temp);
                cellCount++;
            }
            field.push_back(v1);
        }

        std::cout << "Method invoked\n";

        std::cout << "Cell count = " << cellCount << std::endl;
        std::cout << "Total budget = " << totalBudget << std::endl;

        std::cout << "A initialized\n";

        for (size_t i = 0; i < cellCount + 1; i++)
        {
            std::vector<int> v1;
            //std::cout << "Inner vector initialized\n";
            for (size_t j = 0; j < totalBudget; j++)
            {
                // std::cout << "Appended\n";
                v1.push_back(0);
            }
            A.push_back(v1);
        }

    };
    ~Field() {};

    size_t getCellCount() { return cellCount; }

    void setVectors()
    {
        for (size_t i = 0; i < field[0].size(); i++)
            for (size_t j = 0; j < field.size(); j++)
            {
                incomeVec.push_back(field[i][j].getIncome());
                costVec.push_back(field[i][j].getCost());
            }
    }

    void printVectors()
    {
        std::cout << "Income vector : ";
        for (size_t i = 0; i < incomeVec.size(); i++) std::cout << incomeVec[i];
        std::cout << std::endl << "Cost vector : ";
        for (size_t i = 0; i < costVec.size(); i++) std::cout << costVec[i];
    }

    void setData(size_t X, size_t Y, int cost_, int income_)
    {
        field[X][Y].setCost(cost_);
        field[X][Y].setIncome(income_);
    }

    void print()
    {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++)
                std::cout << field[i][j] << "\t";
            std::cout << std::endl;
        }
    }

    void genRandom()
    {
        srand(time(NULL));
        for (size_t i = 0; i < x; i++) {
            for (size_t j = 0; j < y; j++)
            {
                field[i][j].setCost(rand() % 100 + 1);
                field[i][j].setIncome(rand() % 100 + 1);
            }
        }
    }
    int getFieldSize()
    {
        return field.size() * field[0].size();
    }

    /*
    totalBudget = s = W - вместимость(максимальная масса)
    field[i][j] = k - количество возможных элементов
    масса предмета =  = Cell.cost
    ценность = Pk = Cell.income
    A = field
    A(k,s) = field(cellcnt, totalBudget)
    */

    void findAns(int k, int s)
    {
        if(A[k - 1][s] == A[k][s])
            findAns(k - 1, s);
        else
        {
            findAns(k - 1, s - costVec[k]);
            ans.push_back(k);
        }
    }

    void calculate()
    {
        std::cout << "Setting vectors...\n";
        setVectors();
        std::cout << "Vectors set\n";

        for (int i = 0; i < cellCount + 1; i++) {
            for (int j = 0; j < totalBudget; j++)
                std::cout << A[i][j] << "\t";
            std::cout << std::endl;
        }

        for (int k = 1; k <= cellCount; k++)
            for (int s = 1; s <= totalBudget; s++)
                if (s >= costVec[k])
                    A[k][s] = std::max(A[k - 1][s], A[k - 1][s - costVec[k]] + incomeVec[k]);
                else
                    A[k][s] = A[k - 1][s];

        std::cout << "Calculated!\n";

        for (int i = 0; i < cellCount + 1; i++) {
            for (int j = 0; j < totalBudget; j++)
                std::cout << A[i][j] << "\t";
            std::cout << std::endl;
        }

        findAns(1, 1);

    }
};

std::ostream& operator<<(std::ostream& out, Cell cell) { return out << "Income : " << cell.getIncome() << " Cost : " << cell.getCost(); }

int main(int argc, char const* argv[])
{
    std::cout << "Running..." << std::endl;
    Field test(2, 2, 13);
    test.setData(0, 0, 3, 1);
    test.setData(0, 1, 4, 6);
    test.setData(1, 0, 5, 4);
    test.setData(1, 1, 8, 7);
    test.print();
    //test.genRandom();
    //test.print();
    //test.calculate();
    test.calculate();

    return 0;
}
