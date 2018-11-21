## COL 761 - Assignment 3

| Aditi Singla | Ankush Phulia | Vaibhav Bhagee |
| ------------ | ------------- | -------------- |
| 2014CS50277  | 2014CS50279   | 2014CS50297    |


#### Project Structure

* C++ code - *include/* (headers) and *src/*
  * *main.cpp* - driver program
* Makefile
* Scripts - 
  * *install.sh*
  * *format.py*
  * *plot.py*
  * *compile.sh*
  * *classify.sh*


#### Running the code

1. To compile -

   ```bash
   ./scripts/compile.sh
   ```

2. To run -

   1. Comparison between gSpan, FSG and Gaston

      ```bash
      python scripts/plot.py <input-data> --supports <list of frequency thresholds>
      ```

   2. Generation of train/test set for classification

      ```bash
      ./scripts/classify.sh <train-data> <active-ids> <inactive-ids> <test-data>
      ```

#### Graphs

Comparision for execution time for `gSpan`, `fsg` and `gaston` at support thresholds 5, 10, 25, 50, 95:

![Execution time vs Support Threshold](plots/comparison.png)
![Execution time vs Support Threshold on log scale](plots/comparison_log.png)

##### Observations

* The running time increases with decrease in support threshold.

* This increase is greater for gSpan and FSG than for Gaston. The former two show an almost exponential increase, for the latter, it is very less.

* Gaston performs the best out of the three - requiring the minimum running time. FSG does the worst on the aido99_all dataset

##### Exlpanation

* Lowered support thresholds results in more frequent subgrahps being mined, and this increases exopnentially.

* FSG follows a breadth-first strategy - generates all possible candidates at each level and prunes. This is generally slower than gSpan and Gaston, which follow a depth-first strategy - remove infrequent edges and avoid generating all candidates/pruning.

* Gaston works the best as it improves the depth-first approach of gSpan by first mining frequent paths and trees, followed by trees with cycles and then the others. 
  * It follows a global order on cycle-closing edges and only generates those cycles that are bigger than the previous one

  * Duplicate detection is carried out efficiently - first is hashing to perform a pre-sort and then an isomorphism test for final duplicate detection. This makes for very fast pattern

 