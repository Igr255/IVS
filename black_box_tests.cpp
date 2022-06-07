//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     IGOR HANUS <xhanus19@stud.fit.vutbr.cz>
// $Date:       $2021-21-02
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author IGOR HANUS
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test{
    protected:
        BinaryTree bTree;
};

class NonEmptyTree : public ::testing::Test{
    virtual void SetUp() {
        int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };

        for(int i = 0; i < 14; ++i)
            bTree.InsertNode(values[i]);
    }
protected:
    BinaryTree bTree;
};

class TreeAxiom : public ::testing::Test{
    virtual void SetUp() {
        int values[15] = {5,3,2,2,1,7,8,1,1,2,2,5,5,8,8};

        for(int i = 0; i < 14; ++i)
            bTree.InsertNode(values[i]);
    }
protected:
    BinaryTree bTree;
};

// 0 is red, 1 is black

TEST_F(EmptyTree, InsertNode) { //todo add another value
    auto returnValue = bTree.InsertNode(100);
    EXPECT_TRUE(returnValue.first);
    EXPECT_TRUE(returnValue.second);

    returnValue = bTree.InsertNode(100);
    EXPECT_FALSE(returnValue.first);
    EXPECT_TRUE(returnValue.second);
}

TEST_F(NonEmptyTree, InsertNode) { //todo
    int keys[2] = {100, 10};

    auto returnValue = bTree.InsertNode(keys[0]);
    EXPECT_TRUE(returnValue.first);
    EXPECT_TRUE(returnValue.second);

    returnValue = bTree.InsertNode(keys[0]);
    EXPECT_FALSE(returnValue.first);
    EXPECT_TRUE(returnValue.second);

    returnValue = bTree.InsertNode(keys[1]);
    EXPECT_FALSE(returnValue.first);
    EXPECT_TRUE(returnValue.second);
}


TEST_F(EmptyTree, DeleteNode) {
    bool isDeleted = bTree.DeleteNode(100);
    EXPECT_FALSE(isDeleted);
}

TEST_F(NonEmptyTree, DeleteNode) {
    bool isDeleted = bTree.DeleteNode(10);
    EXPECT_TRUE(isDeleted);

    isDeleted = bTree.DeleteNode(7);
    EXPECT_FALSE(isDeleted);
}

TEST_F(EmptyTree, FindNode) {
    auto isFound = bTree.FindNode(10);
    EXPECT_EQ(isFound, nullptr);
}

TEST_F(NonEmptyTree, FindNode) {
    auto isFound = bTree.FindNode(100);
    EXPECT_FALSE(isFound);

    isFound = bTree.FindNode(90);
    EXPECT_TRUE(isFound);
}

TEST_F(TreeAxiom, Axiom1) {
    std::vector<Node_t *> vecArray(0);

    bTree.GetLeafNodes(vecArray);

    for (int i = 0; i < vecArray.capacity(); i++) {
        EXPECT_EQ(vecArray[i]->key, 0);
        EXPECT_EQ(vecArray[i]->color, 1);
    }
}

TEST_F(TreeAxiom, Axiom2) {
    std::vector<Node_t *> vecArray(0);

    bTree.GetNonLeafNodes(vecArray); // leaves are always black so they can be ignored

    for (int i = 0; i < vecArray.capacity(); i++) {

        if (vecArray[i]->color == 0) { // checking if children of "red" are "black"
            EXPECT_EQ(vecArray[i]->pLeft->color,1);
            EXPECT_EQ(vecArray[i]->pRight->color, 1);
        }
    }
}

TEST_F(TreeAxiom, Axiom3) {
    bool setRefLen = true;

    std::vector<Node_t *> vecArray(0);

    auto root = bTree.GetRoot();

    bTree.GetLeafNodes(vecArray);

    int len = 0;
    int refBlackNodes = -1; // reference amount of black nodes

    for(int i = 0; i < vecArray.capacity(); i++) {
        while(vecArray[i]->pParent != root ) { // iterating trough the tree until reaching the root
            if (vecArray[i]->pParent->color == 1) {
                len++;
            }
            vecArray[i] = vecArray[i]->pParent;
        }

        if (setRefLen) { // setting the reference count of black nodes after first time reaching the root
            refBlackNodes = len;
            setRefLen = false;
        }

        EXPECT_EQ(len, refBlackNodes); // checking the lenght for every leaf
        len = 0;
    }
}


/*** Konec souboru black_box_tests.cpp ***/
