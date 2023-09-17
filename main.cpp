#include <iostream>
#include <vector>

void forwardElim(std::vector<std::vector<double>>& matrix, int n) {
    for (int row = 0; row < n; ++row) {
        int pivot_row = row;
        for (int i = row + 1; i < n; ++i) {
            if (std::abs(matrix[i][row]) > std::abs(matrix[pivot_row][row])) {
                pivot_row = i;
            }
        }

        // Swap the pivot row with the current row (if necessary)
        if (pivot_row != row) {
            std::swap(matrix[row], matrix[pivot_row]);
        }

        // Make the diagonal element 1
        double pivot_element = matrix[row][row];
        for (int j = row; j <= n; ++j) {
            matrix[row][j] /= pivot_element;
        }

        // Eliminate other rows
        for (int i = row + 1; i < n; ++i) {
            double factor = matrix[i][row];
            for (int j = row; j <= n; ++j) {
                matrix[i][j] -= factor * matrix[row][j];
            }
        }
    }
}

std::vector<double> backSub(const std::vector<std::vector<double>>& matrix, int n) {
    std::vector<double> solution(n, 0.0);
    for (int row = n - 1; row >= 0; --row) {
        solution[row] = matrix[row][n];
        for (int j = row + 1; j < n; ++j) {
            solution[row] -= matrix[row][j] * solution[j];
        }
    }
    return solution;
}

std::vector<double> naiveGaussElim(std::vector<std::vector<double>>& matrix) {
    int n = matrix.size();
    forwardElim(matrix, n);
    return backSub(matrix, n);
}

std::vector<std::vector<double>> getUserInput() {
    int n;
    std::cout << "Enter the number of linear equations: ";
    std::cin >> n;

    std::vector<std::vector<double>> matrix(n, std::vector<double>(n + 1, 0.0));

    for (int i = 0; i < n; ++i) {
        std::cout << "\nEnter coefficients of equation " << i + 1 << ":\n [separated by spaces and followed by the constant value]\n For example: 3 2 -1 1.5\n >";
        for (int j = 0; j <= n; ++j) {
            std::cin >> matrix[i][j];
        }
    }

    return matrix;
}

std::string format_output(double value) {
    return std::to_string(value);
}

int main() {
    // Get user input for the system of equations
    std::vector<std::vector<double>> A = getUserInput();

    // Perform Gaussian elimination
    std::vector<double> solution = naiveGaussElim(A);

    // Print the solution
    std::cout << "\nSolution:\n";
    for (int i = 0; i < solution.size(); ++i) {
        std::string formatted_x = format_output(solution[i]);
        std::cout << "x" << i + 1 << " = " << formatted_x << "\n";
    }

    return 0;
}