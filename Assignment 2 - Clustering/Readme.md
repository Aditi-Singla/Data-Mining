## COL 761 - Assignment 2

| Aditi Singla | Ankush Phulia | Vaibhav Bhagee |
| ------------ | ------------- | -------------- |
| 2014CS50277  | 2014CS50279   | 2014CS50297    |


#### Project Structure

* C++ code - *include/* (headers) and *src/*
  * *io.cpp* - C style I/O for speed
  * *main.cpp* - driver program
* Makefile
* Scripts - 
  * *compile.sh*
  * *run.sh*

#### Running the code

1. To compile -

   ```bash
   ./scripts/compile.sh
   ```

2. To run - 

3. * k-means

     ```bash
     ./scripts/run.sh -kmeans <k> <input file>
     ```

   * dbscan/optics

     ```bash
     ./scripts/run.sh -<dbscan/optics> -<minPts> <epsilon> <input file> 
     ```


