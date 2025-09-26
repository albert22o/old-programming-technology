using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using MatrixLibrary;

namespace MatrixLibrary.Tests
{
    [TestClass]
    public class MatrixOperationsTests
    {
        private void AreEqualDouble(double expected, double actual, double tol = 1e-9)
        {
            Assert.AreEqual(expected, actual, tol);
        }

        #region SumElementsWithEvenIndexSum tests

        [TestMethod]
        public void SumEven_SingleElement_ReturnsElement()
        {
            double[,] A = { { 5.5 } };
            double result = MatrixOperations.SumElementsWithEvenIndexSum(A);
            AreEqualDouble(5.5, result);
        }

        [TestMethod]
        public void SumEven_2x2Matrix_ReturnsCorrectSum()
        {
            double[,] A = { { 1.0, 2.0 }, { 3.0, 4.0 } };
            AreEqualDouble(5.0, MatrixOperations.SumElementsWithEvenIndexSum(A));
        }

        [TestMethod]
        public void SumEven_3x3NegativeValues_ReturnsCorrectSum()
        {
            double[,] A = {
                { -1.0, -2.0, -3.0 },
                { -4.0, -5.0, -6.0 },
                { -7.0, -8.0, -9.0 }
            };
            AreEqualDouble(-25.0, MatrixOperations.SumElementsWithEvenIndexSum(A));
        }

        [TestMethod]
        public void SumEven_Rectangular2x3_ReturnsCorrectSum()
        {
            double[,] A = { { 1, 2, 3 }, { 4, 5, 6 } };
            AreEqualDouble(9.0, MatrixOperations.SumElementsWithEvenIndexSum(A));
        }

        [TestMethod]
        public void SumEven_EmptyArray_ReturnsZero()
        {
            double[,] A = new double[0, 0];
            AreEqualDouble(0.0, MatrixOperations.SumElementsWithEvenIndexSum(A));
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentNullException))]
        public void SumEven_Null_ThrowsArgumentNullException()
        {
            MatrixOperations.SumElementsWithEvenIndexSum(null);
        }

        #endregion

        #region MaxOnAndBelowMainDiagonal tests

        [TestMethod]
        public void MaxOnDiag_SingleElement_ReturnsElement()
        {
            double[,] A = { { 5.5 } };
            AreEqualDouble(5.5, MatrixOperations.MaxOnAndBelowMainDiagonal(A));
        }

        [TestMethod]
        public void MaxOnDiag_2x2Matrix_ReturnsMaxBelowDiagonal()
        {
            double[,] A = { { 1.0, 2.0 }, { 3.0, 4.0 } };
            AreEqualDouble(4.0, MatrixOperations.MaxOnAndBelowMainDiagonal(A));
        }

        [TestMethod]
        public void MaxOnDiag_3x3NegativeValues_ReturnsCorrectMax()
        {
            double[,] A = {
                { -1.0, -2.0, -3.0 },
                { -4.0, -5.0, -6.0 },
                { -7.0, -8.0, -9.0 }
            };
            AreEqualDouble(-1.0, MatrixOperations.MaxOnAndBelowMainDiagonal(A));
        }

        [TestMethod]
        public void MaxOnDiag_Rectangular2x3_ReturnsCorrectMax()
        {
            double[,] A = { { 1, 2, 3 }, { 4, 5, 6 } };
            AreEqualDouble(5.0, MatrixOperations.MaxOnAndBelowMainDiagonal(A));
        }

        [TestMethod]
        public void MaxOnDiag_Rectangular3x2_ReturnsCorrectMax()
        {
            double[,] A = { { 1, 2 }, { 3, 4 }, { 0, 10 } };
            AreEqualDouble(10.0, MatrixOperations.MaxOnAndBelowMainDiagonal(A));
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentNullException))]
        public void MaxOnDiag_Null_ThrowsArgumentNullException()
        {
            MatrixOperations.MaxOnAndBelowMainDiagonal(null);
        }

        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void MaxOnDiag_EmptyArray_ThrowsArgumentException()
        {
            double[,] A = new double[0, 0];
            MatrixOperations.MaxOnAndBelowMainDiagonal(A);
        }

        #endregion
    }
}
