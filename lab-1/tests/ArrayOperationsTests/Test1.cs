using Microsoft.VisualStudio.TestTools.UnitTesting;
using Program;

namespace ArrayOperationsTests
{
    [TestClass]
    public class ArrayOperationsTests
    {
        // Тесты для MultiplyNonZeroByIndices
        [TestMethod]
        public void MultiplyNonZeroByIndices_ValidData_ReturnsCorrectProduct()
        {
            // Arrange
            double[] v = { 2.0, 3.0, 0.0, 4.0, 5.0 };
            int[] ind = { 0, 1, 3, 4 };

            // Act
            double result = ArrayOperations.MultiplyNonZeroByIndices(v, ind);

            // Assert
            Assert.AreEqual(2.0 * 3.0 * 4.0 * 5.0, result);
        }

        [TestMethod]
        public void MultiplyNonZeroByIndices_WithZeroValues_IgnoresZeros()
        {
            // Arrange
            double[] v = { 2.0, 0.0, 3.0, 0.0 };
            int[] ind = { 0, 1, 2, 3 };

            // Act
            double result = ArrayOperations.MultiplyNonZeroByIndices(v, ind);

            // Assert
            Assert.AreEqual(2.0 * 3.0, result);
        }

        [TestMethod]
        public void MultiplyNonZeroByIndices_AllZeros_ReturnsZero()
        {
            // Arrange
            double[] v = { 0.0, 0.0, 0.0 };
            int[] ind = { 0, 1, 2 };

            // Act
            double result = ArrayOperations.MultiplyNonZeroByIndices(v, ind);

            // Assert
            Assert.AreEqual(0.0, result);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentNullException))]
        public void MultiplyNonZeroByIndices_NullArrayV_ThrowsException()
        {
            // Arrange
            double[] v = null;
            int[] ind = { 0, 1 };

            // Act
            ArrayOperations.MultiplyNonZeroByIndices(v, ind);
        }

        // Тесты для FindMinElement
        [TestMethod]
        public void FindMinElement_ValidArray_ReturnsCorrectMinAndIndex()
        {
            // Arrange
            int[] array = { 5, 2, 8, 1, 9 };

            // Act
            var result = ArrayOperations.FindMinElement(array);

            // Assert
            Assert.AreEqual(1, result.minValue);
            Assert.AreEqual(3, result.minIndex);
        }

        [TestMethod]
        public void FindMinElement_FirstElementIsMin_ReturnsCorrectIndex()
        {
            // Arrange
            int[] array = { -5, 2, 8, 1, 9 };

            // Act
            var result = ArrayOperations.FindMinElement(array);

            // Assert
            Assert.AreEqual(-5, result.minValue);
            Assert.AreEqual(0, result.minIndex);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentNullException))]
        public void FindMinElement_NullArray_ThrowsException()
        {
            // Arrange
            int[] array = null;

            // Act
            ArrayOperations.FindMinElement(array);
        }

        // Тесты для ReverseArray
        [TestMethod]
        public void ReverseArray_ValidArray_ReturnsReversedArray()
        {
            // Arrange
            double[] array = { 1.1, 2.2, 3.3, 4.4 };

            // Act
            double[] result = ArrayOperations.ReverseArray(array);

            // Assert
            CollectionAssert.AreEqual(new double[] { 4.4, 3.3, 2.2, 1.1 }, result);
        }

        [TestMethod]
        public void ReverseArray_SingleElement_ReturnsSameArray()
        {
            // Arrange
            double[] array = { 5.5 };

            // Act
            double[] result = ArrayOperations.ReverseArray(array);

            // Assert
            CollectionAssert.AreEqual(new double[] { 5.5 }, result);
        }

        [TestMethod]
        public void ReverseArray_EmptyArray_ReturnsEmptyArray()
        {
            // Arrange
            double[] array = new double[0];

            // Act
            double[] result = ArrayOperations.ReverseArray(array);

            // Assert
            Assert.AreEqual(0, result.Length);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentNullException))]
        public void ReverseArray_NullArray_ThrowsException()
        {
            // Arrange
            double[] array = null;

            // Act
            ArrayOperations.ReverseArray(array);
        }
    }
}