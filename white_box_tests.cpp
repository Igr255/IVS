//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     IGOR HANUS <xhanus19@stud.fit.vutbr.cz>
// $Date:       $2021-22-02
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author IGOR HANUS
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class MatrixTst : public ::testing::Test{
    Matrix m{};
};

TEST(BasicTests,MatrixPropertyTests) {
    Matrix M{};
    EXPECT_EQ(M.get(0,0), 0);
    M.set(0,0,1);
    EXPECT_EQ(M.get(0,0), 1);
    EXPECT_FALSE(M.set(0,-1,1));

}

TEST(BasicTests, Matrix_Set) {
    Matrix M{2,2};

    std::vector<double> row1 = {1.11,2.1};
    std::vector<double> row2 = {1.12,2.112};

    std::vector<std::vector<double>> values = {row1, row2};

    EXPECT_TRUE(M.set(values));

    values = {row1};

    EXPECT_FALSE(M.set(values));

}

TEST(AdvancedTests, Matrix_Create) {
    size_t rnd;

    for (int i = 0; i < 10; i++) {
        rnd = (size_t)rand() % 100 + 50;

        Matrix M {rnd,rnd};

        for (int j = 0; j < rnd; j++) {
            for (int k = 0; k < rnd; k++) {
                EXPECT_EQ(M.get(j,k), 0);
            }
        }

    }
}

TEST(ExceptionTests, Matrix_Create_InvalidMatrixSize) {

    EXPECT_THROW({
        try {
            auto M = new Matrix(1,0);
        }
        catch(const std::exception& e) {
            EXPECT_STREQ("Minimalni velikost matice je 1x1", e.what());
            throw;
        }
    }, std::exception);

}

TEST(ExceptionTests, Matrix_Get_InvalidMatrixSize) {
    Matrix M{1,1};

    EXPECT_THROW({
        try {
            M.get(0,1);
        }
        catch(const std::exception& e) {
            EXPECT_STREQ("Pristup k indexu mimo matici", e.what());
            throw;
        }
    }, std::exception);
}

TEST(BasicTests, Matrix_Compare_IdenticalMatrices) {
    Matrix M {1,1};
    Matrix M1 {1,1};

    EXPECT_TRUE(M == M1);
}

TEST(BasicTests, Matrix_Compare_DifferentValues) {
    Matrix M {1,1};
    Matrix M1 {1,1};
    M.set(0,0,1);
    EXPECT_FALSE(M == M1);
}

TEST(AdvancedTests, Matrix_Compare_DifferentValues) {

    size_t rnd;

    for (int i = 0; i < 10; i++) {
        rnd = (size_t)rand() % 100 + 50;

        Matrix M {rnd,rnd};
        Matrix M1 {rnd,rnd};

        for (int j = 0; j < rnd; j++) {
            for (int k = 0; k < rnd; k++) {
                M.set(j,k, rnd);
                M1.set(j,k,(double)(rnd + 1));
            }
        }

        EXPECT_FALSE(M==M1);

    }
}

TEST(ExceptionTests, Matrix_Compare_DifferentSizeMatrices) {
    Matrix M {1,1};
    Matrix M1 {2,2};

    EXPECT_THROW({
        try {
            M == M1;
        }
        catch(const std::exception& e) {
            EXPECT_STREQ("Matice musi mit stejnou velikost.", e.what());
            throw;
        }
    }, std::exception);
}

TEST(BasicTests, Matrix_Sum_IdenticalMatrices) {
    Matrix M {2,2};
    Matrix M1 {2,2};

    M.set(0,0,1);
    M.set(1,0,1);

    auto M3 = M+M1;

    EXPECT_EQ(M3.get(0,0), 1);
    EXPECT_EQ(M3.get(0,1), 0);
    EXPECT_EQ(M3.get(1,0), 1);
    EXPECT_EQ(M3.get(1,1), 0);
}

TEST(AdvancedTests, Matrix_Sum_IdenticalMatrices) {

    size_t rnd;

    for (int i = 0; i < 10; i++) {
        rnd = (size_t)rand() % 100 + 50;

        Matrix M {rnd,rnd};
        Matrix M1 {rnd,rnd};

        for (int j = 0; j < rnd; j++) {
            for (int k = 0; k < rnd; k++) {
                M.set(j,k, rnd);
                M1.set(j,k,(double)(rnd + 1));
            }
        }

        auto M3 = M+M1;

        for (int j = 0; j < rnd; j++) {
            for (int k = 0; k < rnd; k++) {
                EXPECT_EQ(M3.get(j,k), rnd * 2 +1);
            }
        }

    }
}

TEST(ExceptionTests, Matrix_Sum_DifferentMatrices) {
    Matrix M {2,2};
    Matrix M1 {1,1};

    EXPECT_THROW({
       try{
           auto M3 = M + M1;
       }
       catch(const std::exception& e) {
           EXPECT_STREQ("Matice musi mit stejnou velikost.", e.what());
           throw;
       }
    }, std::exception);
}

TEST(BasicTests, Matrix_Multiply_IdenticalSizeMatrices) {
    Matrix M {2,2};
    Matrix M1 {2,2};

    M.set(1,1,2);
    M1.set(1,1,4);

    auto M2 = M * M1;

    EXPECT_EQ(M2.get(1,1), 8);
}

TEST(ExceptionTests, Matrix_Multiply_DifferentSizeMatrices) {
    Matrix M {2,2};
    Matrix M1 {1,1};

    EXPECT_THROW({
        try{
            auto M3 = M * M1;
        }
        catch(const std::exception& e) {
            EXPECT_STREQ("Prvni matice musi stejny pocet sloupcu jako druha radku.", e.what());
            throw;
        }
    }, std::exception);
}

TEST(BasicTests, Matrix_Multiply_WithValue) {
    Matrix M {2,2};

    M.set(1,1,2);
    auto M2 = M * 3;

    EXPECT_EQ(M2.get(1,1), 6);
}

TEST(AdvancedTests, Matrix_Multiply_WithValue) {
    size_t rnd;

    for (int i = 0; i < 10; i++) {
        rnd = (size_t)rand() % 100 + 50;

        Matrix M {rnd,rnd};

        for (int j = 0; j < rnd; j++) {
            for (int k = 0; k < rnd; k++) {
                M.set(j,k, rnd);
            }
        }

        auto M3 = M*rnd;

        for (int j = 0; j < rnd; j++) {
            for (int k = 0; k < rnd; k++) {
                EXPECT_EQ(M3.get(j,k), rnd * rnd);
            }
        }

    }
}

TEST(BasicTests, Matrix_Solve_Equation_1x1) {
    Matrix M {1,1};
    M.set(0,0, 3);

    std::vector<double> values = {2};
    auto solution = M.solveEquation(values);

    EXPECT_EQ(solution.size(), 1);
    EXPECT_EQ(M.get(0,0), 3);
}

TEST(BasicTests, Matrix_Solve_Equation_2x2) {
    Matrix M {2,2};
    M.set(0,0, 3);
    M.set(1,0,2);
    M.set(0, 1, 2);
    M.set(1,1,4);

    std::vector<double> values = {2, 3};
    auto solution = M.solveEquation(values);

    EXPECT_EQ(solution.size(), 2);
    EXPECT_EQ(solution[0], 0.25);
    EXPECT_EQ(solution[1], 0.625);
}

TEST(BasicTests, Matrix_Solve_Equation_3x3) {
    Matrix M {3,3};
    M.set(0,0, 3);
    M.set(1,0,2);
    M.set(0, 1, 2);
    M.set(1,1,4);
    M.set(0,2,3);
    M.set(1,2,3);
    M.set(2,2,3);

    std::vector<double> values = {2, 3, 3};
    auto solution = M.solveEquation(values);

    EXPECT_EQ(solution.size(), 3);
    EXPECT_EQ(solution[0], -0.5);
    EXPECT_EQ(solution[1], 0.25);
    EXPECT_EQ(solution[1], 0.25);
}


TEST(ExceptionTests, Matrix_Solve_Equation_NotEqual) {
    Matrix M {2,2};
    std::vector<double> values = {2, 3, 4};


    EXPECT_THROW({
        try{
            auto solution = M.solveEquation(values);
        }
        catch(const std::exception& e) {
            EXPECT_STREQ("Pocet prvku prave strany rovnice musi odpovidat poctu radku matice.", e.what());
            throw;
        }
    }, std::exception);
}

TEST(ExceptionTests, Matrix_Solve_Equation_NotSquareMatrix) {
    Matrix M {1,2};
    std::vector<double> values = {2, 3};

    EXPECT_THROW({
        try{
            auto solution = M.solveEquation(values);
        }
        catch(const std::exception& e) {
            EXPECT_STREQ("Matice musi byt ctvercova.", e.what());
            throw;
        }
    }, std::exception);
}

TEST(ExceptionTests, Matrix_Solve_Equation_NotSingularMatrix) {
    Matrix M {4,4};
    std::vector<double> values = {2, 3, 1, 2};

    EXPECT_THROW({
        try{
            auto solution = M.solveEquation(values);
        }
        catch(const std::exception& e) {
            EXPECT_STREQ("Matice je singularni.", e.what());
            throw;
        }
    }, std::exception);
}

TEST(BasicTests, Matrix_Transpose_2x2) {
    Matrix M {2,2};
    M.set(0,0, 3);
    M.set(1,0,2);
    M.set(0, 1, 2);
    M.set(1,1,4);

    auto M1 = M.transpose();

    EXPECT_EQ(M1.get(0,0), 3);
    EXPECT_EQ(M1.get(0,1), 2);
    EXPECT_EQ(M1.get(1,0), 2);
    EXPECT_EQ(M1.get(1,1), 4);

}

TEST(BasicTests, Matrix_Transpose_3x3) {
    Matrix M {3,3};
    M.set(0,0, 3);
    M.set(2,0,2);
    M.set(1, 2, 2);
    M.set(1,1,4);

    auto M1 = M.transpose();

    EXPECT_EQ(M1.get(0,0), 3);
    EXPECT_EQ(M1.get(0,1), 0);
    EXPECT_EQ(M1.get(1,0), 0);
    EXPECT_EQ(M1.get(1,1), 4);
}

TEST(AdvancedTests, Matrix_Transpose_3x3) {
    size_t rnd;

    for (int i = 0; i < 10; i++) {
        rnd = (size_t)rand() % 100 + 50;

        Matrix M {rnd,rnd};

        for (int j = 0; j < rnd; j++) {
            for (int k = 0; k < rnd; k++) {
                M.set(j,k, rnd + k);
            }
        }

        auto M3 = M.transpose();

        for (int j = 0; j < rnd; j++) {
            for (int k = 0; k < rnd; k++) {
                EXPECT_EQ(M3.get(k,j), rnd + k);
            }
        }

    }
}


TEST(BasicTests, Inverse_Matrix_2x2) {
    Matrix M {2,2};
    M.set(0,0, 3);
    M.set(1,0,2);
    M.set(0, 1, 2);
    M.set(1,1,4);

    auto M1 = M.inverse();

    EXPECT_EQ(M1.get(0,0), 0.5);
    EXPECT_EQ(M1.get(0,1), -0.25);
    EXPECT_EQ(M1.get(1,0), -0.25);
    EXPECT_EQ(M1.get(1,1), 0.375);

}

TEST(BasicTests, Inverse_Matrix_3x3) {
    Matrix M {3,3};

    M.set(0,0, 3);
    M.set(1,0,2);
    M.set(0, 1, 2);
    M.set(1,1,4);
    M.set(0,2,3);
    M.set(1,2,3);
    M.set(2,2,3);

    auto M1 = M.inverse();

    EXPECT_EQ(M1.get(0,0), 0.5);
    EXPECT_EQ(M1.get(0,1), -0.25);
    EXPECT_EQ(M1.get(1,0), -0.25);
    EXPECT_EQ(M1.get(1,1), 0.375);
}

TEST(ExceptionTests, Inverse_Matrix_Singular) {
    Matrix M {3,3};
    M.set(0,0, 3);
    M.set(2,0,2);
    M.set(1, 2, 2);
    M.set(1,1,4);

    EXPECT_THROW({
        try{
            auto M1 = M.inverse();
        }
        catch(const std::exception& e) {
            EXPECT_STREQ("Matice je singularni.", e.what());
            throw;
        }
    }, std::exception);
}

TEST(ExceptionTests, Inverse_Matrix_NotCorrectSize) {
    Matrix M {4,4};

    EXPECT_THROW({
        try{
            auto M1 = M.inverse();
        }
        catch(const std::exception& e) {
            EXPECT_STREQ("Matice musi byt velikosti 2x2 nebo 3x3.", e.what());
            throw;
        }
    }, std::exception);
}

/*** Konec souboru white_box_tests.cpp ***/
