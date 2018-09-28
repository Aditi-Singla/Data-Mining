## Summary of the papers for the Research Survey

### 1. Outlier Detection in data streams
#### Link:
* [Outlier Detection in Feature-Evolving Data Streams](./p1963-manzoor.pdf)

#### Key Ideas:
* First to address outlier detection problem for streams where:
    - Feature values of data points, evolve with time
    - New features occur with time
* The updates are considered to be a tuple of *(id, f, delta)* where the *id* or the *f* might or might not have been encountered before

#### Challenges
* The set of points needs to be maintained in memory and can't be processed one at a time, as the points already encountered could evolve in ways discussed above
* Since the number *n* and the dimension *d* of points is unknown, allocation of space for point storage is challenging
* The updates need to be processed in a fast and efficient manner

#### Problem Specification
* Given a data stream D of updates of the form as discussed above, we need to maintain an outlier score such that at any temporal instant, the outliers are scored higher that the non outlier points

#### Key components of the solution
##### StreamHash
+ Distance preserving dimensionality reduction using Random Projections
+ Outliers might be difficult to detect in high dimensional data as we have many irrelevant features
+ Traditional approach involves coming up with sparse projection vectors where only a third of the feature values are non zero, thus ignoring two thirds of the feature space
+ We don't have the dimension of the feature space known a-priori
+ *StreamHash* overcomes this problem by maintaining a set of *K* hash functions, which map feature names to a hash value (Here, *K* is the reduced dimension)
+ The reduced dimension computation takes place as `y <sub>id</sub>[i] += \sum h <sub>i</sub>(f) * delta` where *(id, f, delta)* belongs to the data stream
+ The hash functions are constructed to maintain the probability distribution of a sparse random vectors, as discussed above

### 2. Outlier Detection for High Dimensional Data
#### Link:
* [Outlier Detection in High Dimensional Data](./Surveys/p37-aggarwal.pdf)

#### Key Ideas:
* Outlier detection algorithms in high dimensional data, based on proximity, face issues due to sparsity and curse of dimensionality
	* Identify outliers while trying to cluster the data
	* Take into account, the mutual distance of points
* Propose exact and approximate algorithms based on projetion of data onto smaller dimensions
* Projection onto smaller dimensions gives better results for clustering

#### Challenges:
* Need to formulate algorithms to overcome the issues caused due to the sparsity of the data, in the higher dimensions
* Thee algorithms should define the meaning of a point being an outlier, in a subspace of the original dataset
* Should be computationally efficient

#### Key Components of the solution
##### Definition of outliers in low dimensional projections
* Divide each attribute in the dataset into equi-depth ranges. This divides the complete space into cubes of different dimensions.
* We consider the cubes of k-dimensions, created by picking the ranges from k different dimensions, to identify the expected number of points in them, assuming a uniform distribution of points.
* Define a metric to identify how off is the actual number from the probabilistic estimate, called the *sparsity coefficient*.
* Wish to identify, most sparse k-dimensional cubes, in the dataset.

##### Evolutionary algorithms for Outlier Detection
* Encode the grid range for the dimension *i* as a value between *1* and *phi* (number of ranges) or a *star* (don't care), for all the dimensions.
* Can use the *sparsity coefficient* as the fitness function.
* Selection
	* Biasing the population towards fitter strings. Sampling probability proportional to how negative is the *sparsity coefficient*.
* Crossover
	* Two point crossover - Randomly choose a crossover point and make a crossover of the part towards the right. Need to be careful to keep the dimensions constant.
	* Can optimise the crossover
* Mutation
	* Mutating the genes, based on their existing quality, to ensure that the program was contined our and run explicitly
