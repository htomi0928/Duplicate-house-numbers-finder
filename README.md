# Duplicate House Numbers Finder

This console application is designed to identify and display the duplicate house numbers in a given dataset. The input data is loaded from a file named `network.mid`, and the output is printed to the standard output.

## Task Description

The task involves identifying house numbers that appear more than once in a given dataset. For example, if the Kossuth Street has house numbers 43–47 on one segment on the odd side and 47–49 on another segment on the even side, then the house number 47 is considered a duplicate. If there is an overlap with another range, such as 45–59, only the 45–49 range is considered a duplicate.

### Input Format
The input file (`network.mid`) contains various columns of data. For this task, only specific columns related to house numbers need to be processed. The algorithm should load this data into memory and work on the relevant columns.

### Output Format
The output should consist of lines indicating the street name, scheme (odd/even/mixed), and the range of duplicate house numbers. The format is as follows:

[Street Name]: [Scheme] [From] [To]

Kossuth Street: Odd 45 49

Kossuth Street: Even 12 12

### Implementation Guidelines

1. The algorithm should handle mixed and odd/even overlaps in a logical and efficient manner.
2. The loading of data into memory should be separate from the algorithm. Load only the necessary columns for processing.
3. The runtime of the solution should not depend on the numerical size of the house numbers. It should run in the same amount of time even if all numbers are multiplied by a constant factor.

### Usage

The application is written in C++ and should be executed as a console application. The input file is named `network.mid`, and the output is printed to the standard output.

```bash
./duplicate_house_numbers_finder