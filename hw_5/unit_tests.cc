#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "utilities.h"
#include "gtest/gtest.h"


using namespace std;


// sort_by_magnitude
TEST(Magnitude, TestMagnitude) {
    // Test case 1: Mixed positive and negative numbers
    {
        vector<double> vec = {3.0, -1.0, -2.0, 4.0};
        sort_by_magnitude(vec);
        EXPECT_EQ(vec[0], -1.0);
        EXPECT_EQ(vec[1], -2.0);
        EXPECT_EQ(vec[2], 3.0);
        EXPECT_EQ(vec[3], 4.0);

    }

    // Test case 2: Zero values
    {
        vector<double> vec = {0.0, -0.0, 0.0};
        sort_by_magnitude(vec);
        EXPECT_EQ(vec[0], 0);
        EXPECT_EQ(vec[1], 0);
        EXPECT_EQ(vec[2], 0);

    }

    // Test case 3: Empty vector
    {
        vector<double> vec = {};
        sort_by_magnitude(vec);
        EXPECT_EQ(vec, vector<double>{});

    }
}

// generate csv file
TEST(Matrix, GenerateAndReadCSV) {
    string filename = "test_matrix.csv";

    // Create a sample matrix file
    ofstream file(filename);
    ASSERT_TRUE(file.is_open());

    file << "1.1,2.2,3.3\n";
    file << "4.4,5.5,6.6\n";
    file << "7.7,8.8,9.9\n";

    file.close();

    // Now read the matrix using the function
    TypedArray<TypedArray<double>> matrix = read_matrix_csv(filename);

    // Verify the dimensions
    EXPECT_EQ(matrix.size(), 3);
    EXPECT_EQ(matrix.get(0).size(), 3);

    // Verify specific values
    EXPECT_DOUBLE_EQ(matrix.get(0).get(0), 1.1);
    EXPECT_DOUBLE_EQ(matrix.get(1).get(1), 5.5);
    EXPECT_DOUBLE_EQ(matrix.get(2).get(2), 9.9);
}

// test read_matrix_csv and write_matrix_csv
TEST(Matrix, ReadAndWriteCSV) {
    string filename = "test_matrix.csv";

    // Create a matrix
    TypedArray<TypedArray<double>> matrix;
    for (int i = 0; i < 3; ++i) {
        TypedArray<double> row;
        for (int j = 0; j < 2; ++j) {
            row.set(j, i * 2 + j + 1);
        }
        matrix.set(i, row);
    }

    // Write to CSV
    write_matrix_csv(matrix, filename);

    // Read back
    TypedArray<TypedArray<double>> loaded_matrix = read_matrix_csv(filename);

    // Compare
    EXPECT_EQ(matrix.size(), loaded_matrix.size());
    for (int i = 0; i < matrix.size(); ++i) {
        EXPECT_EQ(matrix.get(i).size(), loaded_matrix.get(i).size());
        for (int j = 0; j < matrix.get(i).size(); ++j) {
            EXPECT_DOUBLE_EQ(matrix.get(i).get(j), loaded_matrix.get(i).get(j));
        }
    }
}

// test occurence_map
// example 1
TEST(TextProcessing, OccurrenceMap1) {
    string filename = "test_example1.txt";

    // Create a sample text file
    std::ofstream file(filename);
    file << "This is a sentence. Don't think of wier_d strings as words. Really, 123 is a nice number.";
    file.close();

    // Read occurrences
    map<string, int> result = occurrence_map(filename);

    // Verify word counts
    EXPECT_EQ(result["is"], 2);
    EXPECT_EQ(result["this"], 1);
    EXPECT_EQ(result["123"], 1);

    // invalid word
    EXPECT_EQ(result.count("wier_d"), 0);
}

// example 2
TEST(TextProcessing, OccurrenceMap2) {
    string filename = "test_example2.txt";

    // Create a sample text file
    std::ofstream file(filename);
    file << "'I should use double quotes'";
    file.close();

    // Read occurrences
    map<string, int> result = occurrence_map(filename);

    // Verify word counts
    EXPECT_EQ(result["'i"], 1);
    EXPECT_EQ(result["should"], 1);
    EXPECT_EQ(result["quotes'"], 1);

    // invalid word
    // EXPECT_EQ(result.count("wier_d"), 0);
}

// example 3
TEST(TextProcessing, OccurrenceMap3) {
    string filename = "test_example3.txt";

    // Create a sample text file
    std::ofstream file(filename);
    file << "George Mallory's famous quote: \"My mind is in a state of constant rebellion.\"";
    file.close();

    // Read occurrences
    map<string, int> result = occurrence_map(filename);

    // Verify word counts
    EXPECT_EQ(result["george"], 1);
    EXPECT_EQ(result["mallory's"], 1);
    EXPECT_EQ(result["my"], 1);
    EXPECT_EQ(result["rebellion"], 1);

    // invalid word
    // EXPECT_EQ(result.count("wier_d"), 0);
}

TEST(TextProcessing, OccurrenceMap4) {
    string filename = "test_example4.txt";

    // Create a sample text file
    std::ofstream file(filename);
    file << "10XGenomics (a biotech company) is quoted as saying \"blah blah blah.\"";
    file.close();

    // Read occurrences
    map<string, int> result = occurrence_map(filename);

    // Verify word counts
    EXPECT_EQ(result["10xgenomics"], 1);
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["company"], 1);
    EXPECT_EQ(result["blah"], 3);

    // invalid word
    // EXPECT_EQ(result.count("wier_d"), 0);
}

TEST(TextProcessing, OccurrenceMap5) {
    string filename = "test_example5.txt";

    // Create a sample text file
    std::ofstream file(filename);
    file << "the)s are no%y6 wo!e4";
    file.close();

    // Read occurrences
    map<string, int> result = occurrence_map(filename);

    // Verify word counts
    EXPECT_EQ(result["are"], 1);
    // EXPECT_EQ(result["a"], 1);
    // EXPECT_EQ(result["company"], 1);
    // EXPECT_EQ(result["blah'"], 3);

    // invalid word
    EXPECT_EQ(result.count("the)s"), 0);
    EXPECT_EQ(result.count("no%y6"), 0);
    EXPECT_EQ(result.count("wo!e4"), 0);

}