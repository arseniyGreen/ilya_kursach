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

    int NumberOfItems;
    int WeightOfBag;

    std::vector<std::vector<Cell>> field; /* field array X*Y */

    std::vector<std::vector<int>> A;
    std::vector<int> ans;
    std::vector<int> weights;
    std::vector<int> prices;

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

        A = std::vector<std::vector<int>>(NumberOfItems + 1), std::vector<int>(WeightOfBag + 1));
        ans = std::vector<int>(NumberOfItems);
        for (int k = 1; k <= NumberOfItems; k++)
            for (int s = 1; s <= WeightOfBag; s++)
                if (s >= weights[k - 1])
                    A[k][s] = std::max(A[k - 1][s], A[k - 1][s - weights[k - 1]] + prices[k - 1]);
                else
                    A[k][s] = A[k - 1][s];

    };
    ~Field() {};

    size_t getCellCount() { return cellCount; }

    void setVectors()
    {
        for (size_t i = 0; i < field[0].size(); i++)
            for (size_t j = 0; j < field.size(); j++)
            {
                prices.push_back(field[i][j].getIncome());
                weights.push_back(field[i][j].getCost());
            }
    }

    void printVectors()
    {
        std::cout << "Income vector : ";
        for (size_t i = 0; i < prices.size(); i++) std::cout << prices[i];
        std::cout << std::endl << "Cost vector : ";
        for (size_t i = 0; i < weights.size(); i++) std::cout << weights[i];
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

    void findAns(int NumberOfItems, int WeightOfBag) 
    {
        if (A[NumberOfItems][WeightOfBag] == 0)
            return;
        if (A[NumberOfItems - 1][WeightOfBag] == A[NumberOfItems][WeightOfBag])
        {
            findAns(NumberOfItems - 1, WeightOfBag);
        }
        else
        {
            findAns(NumberOfItems - 1, WeightOfBag - weights[NumberOfItems -1]);
            ans[NumberOfItems - 1] = 1;
        }
    }

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
