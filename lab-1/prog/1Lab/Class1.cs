using System;

namespace Program
{
    public class ArrayOperations
    {
        // Функция 1: Произведение ненулевых компонентов по индексам
        public static double MultiplyNonZeroByIndices(double[] v, int[] ind)
        {
            if (v == null || ind == null)
                throw new ArgumentNullException("Массивы не могут быть null");

            if (v.Length == 0 || ind.Length == 0)
                throw new ArgumentException("Массивы не могут быть пустыми");

            double product = 1.0;
            bool hasNonZero = false;

            foreach (int index in ind)
            {
                if (index < 0 || index >= v.Length)
                    throw new IndexOutOfRangeException("Индекс выходит за границы массива");

                if (v[index] != 0)
                {
                    product *= v[index];
                    hasNonZero = true;
                }
            }

            if (!hasNonZero)
                return 0;

            return product;
        }

        // Функция 2: Минимальный элемент и его индекс
        public static (int minValue, int minIndex) FindMinElement(int[] array)
        {
            if (array == null)
                throw new ArgumentNullException("Массив не может быть null");

            if (array.Length == 0)
                throw new ArgumentException("Массив не может быть пустым");

            int minValue = array[0];
            int minIndex = 0;

            for (int i = 1; i < array.Length; i++)
            {
                if (array[i] < minValue)
                {
                    minValue = array[i];
                    minIndex = i;
                }
            }

            return (minValue, minIndex);
        }

        // Функция 3: Перестановка элементов в обратном порядке
        public static double[] ReverseArray(double[] array)
        {
            if (array == null)
                throw new ArgumentNullException("Массив не может быть null");

            if (array.Length == 0)
                return [];

            double[] reversed = new double[array.Length];

            for (int i = 0; i < array.Length; i++)
            {
                reversed[i] = array[array.Length - 1 - i];
            }

            return reversed;
        }
    }
}
