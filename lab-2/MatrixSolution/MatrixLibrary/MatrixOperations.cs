using System;

namespace MatrixLibrary
{
    public static class MatrixOperations
    {
        public static double SumElementsWithEvenIndexSum(double[,] A)
        {
            if (A is null) throw new ArgumentNullException(nameof(A));

            int rows = A.GetLength(0);
            int cols = A.GetLength(1);

            if (rows == 0 || cols == 0)
                return 0.0; // сумма по пустому множеству = 0

            double sum = 0.0;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (((i + j) & 1) == 0) // проверяем чётность суммы индексов
                        sum += A[i, j];
                }
            }

            return sum;
        }

        public static double MaxOnAndBelowMainDiagonal(double[,] A)
        {
            if (A is null) throw new ArgumentNullException(nameof(A));

            int rows = A.GetLength(0);
            int cols = A.GetLength(1);

            if (rows == 0 || cols == 0)
                throw new ArgumentException("Array must contain at least one element.", nameof(A));

            bool found = false;
            double max = double.NegativeInfinity;

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (i >= j) // на диагонали и ниже
                    {
                        if (!found)
                        {
                            max = A[i, j];
                            found = true;
                        }
                        else if (A[i, j] > max)
                        {
                            max = A[i, j];
                        }
                    }
                }
            }

            return max;
        }
    }
}
