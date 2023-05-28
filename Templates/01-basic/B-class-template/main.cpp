#include <iostream>
#include <optional>

using namespace std;


template<typename T = int, size_t WIDTH = 10, size_t HEIGHT = 10>
class Grid
{
public:
    Grid() = default;
    virtual ~Grid() = default;

    Grid(const Grid& src) = default;
    Grid& operator=(const Grid& rhs) = default;

    template<typename E, size_t WIDTH_E, size_t HEIGHT_E>
    Grid(const Grid<E, WIDTH_E, HEIGHT_E>& src);

    template<typename E, size_t WIDTH_E, size_t HEIGHT_E>
    Grid<T>& operator=(const Grid<E, WIDTH_E, HEIGHT_E>& rhs);

    std::optional<T>& at(size_t x, size_t y);
    const std::optional<T>& at(size_t x, size_t y) const;

    void swap(Grid& other) noexcept {
        std::swap(m_cells, other.m_cells);
    }

    size_t getHeight() const { return HEIGHT; }
    size_t getWidth() const { return WIDTH; }

private:
    void verifyCoordinate(size_t x, size_t y) const;

    std::optional<T> m_cells[WIDTH][HEIGHT];
};

template<typename T, size_t WIDTH, size_t HEIGHT>
template<typename E, size_t WIDTH_E, size_t HEIGHT_E>
Grid<T, WIDTH, HEIGHT>::Grid(const Grid<E, WIDTH_E, HEIGHT_E>& src)
{
    for (size_t i {0}; i < WIDTH; i++) {
        for (size_t j {0}; j < HEIGHT; j++) {
            if (i < WIDTH_E && j < HEIGHT_E) {
                m_cells[i][j] = src.at(i, j);
            } else {
                m_cells[i][j].reset();
            }
        }
    }
}

template<typename T, size_t WIDTH, size_t HEIGHT>
template<typename E, size_t WIDTH_E, size_t HEIGHT_E>
Grid<T>& Grid<T, WIDTH, HEIGHT>::operator=(const Grid<E, WIDTH_E, HEIGHT_E>& rhs)
{
    Grid<T, WIDTH, HEIGHT> tmp = rhs;
    swap(tmp);
    return *this;
}

template<typename T, size_t WIDTH, size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::verifyCoordinate(size_t x, size_t y) const {
    if (x >= WIDTH) {
        std::cout << x << " must be less than ", WIDTH;
    }
    if (y >= HEIGHT) {
        std::cout << y << " must be less than ", HEIGHT;
    }
}

template<typename T, size_t WIDTH, size_t HEIGHT>
std::optional<T>& Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y) {
    return const_cast<std::optional<T>&>(std::as_const(*this)).at(x, y);
}

template<typename T, size_t WIDTH, size_t HEIGHT>
const std::optional<T>& Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y) const {
    verifyCoordinate(x, y);
    return m_cells[x][y];
}

// 类模板的特化
template<>
class Grid<const char*>
{
public:
    Grid() = default;
    virtual ~Grid() = default;
};

template<typename T>
class SpreadsheetCell
{
public:
    SpreadsheetCell(const T& t)
        : m_content(t) {}

    const T& getContent() const {
        return m_content;
    }

    size_t getSize() const {
        return m_content.size();
    }
private:
    T m_content;
};

// 自定义推导原则
SpreadsheetCell(const char*) -> SpreadsheetCell<std::string>;

int main()
{
    // 1、类型参数可以使用默认值
    Grid<> myIntGrid;
    Grid<int> myGrid;
    Grid<int, 5> anotherGrid;
    Grid<int, 5, 5> aFourthGrid;

    // 2、类模板的实参推导
    std::pair<int, double> pair1 = {1, 2.0};
    auto pair2 = std::make_pair(1, 2.3);

    // 3、用户自定义推导类型
    std::string myString {"hello world"};
    SpreadsheetCell cell {myString}; // SpreadsheetCell<std::string>
    std::cout << cell.getSize() << std::endl;
    SpreadsheetCell cell2 {"xinze hua"}; // SpreadsheetCell<const char*>
    std::cout << cell2.getSize() << std::endl;

    Grid<int, 11, 11> grid1;
    Grid<double, 12, 12> grid2 = grid1;

    Grid<const char*, 10, 10> grid3;
    return 0;
}