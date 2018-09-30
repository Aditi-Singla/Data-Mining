# Summary of the papers for the Research Survey

## 1. Outlier Detection in data streams
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
+ The reduced dimension computation takes place as y<sub>id</sub>[i] += Sigma<sub>i</sub> h<sub>i</sub>(f) delta where *(id, f, delta)* belongs to the data stream
+ The hash functions are constructed to maintain the probability distribution of a sparse random vectors, as discussed above

## 2. Outlier Detection for High Dimensional Data
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

## 3. Outlier Ensembles
#### Link:
* [Outlier Ensembles](./EnsembleMethods/OutlierEnsembles/p49-aggarwal.pdf)

#### Key Ideas:
* Employing ensemble analysis for the task of outlier detection
* Ensemble analysis has been used in a widespread fashion, for classification and clustering tasks
* Useful in streaming scenarios for training multiple models for the task
* Ensemble algorithms can be classified on 
	* *Component Independence* - Whether the subset of attributes are independent or dependent
	* *Component Type* - Whether the algorithm makes a choice on the data attributes or model
* Components in outlier ensembles:
	* *Model Creation* - Model to run on the dataset for outlier detection
	* *Model Normalisation* - Normalise the outlier scores output by the different models
	* *Model Combination* - Combining the scores of different models to output a single outlier score

#### Key Components of the solution
##### Categorisation by the component independence
* Sequential ensembles
	* Set of outlier detection algorithms applied sequentially to incorporate the output of the previously applied algorithm
	* Output is either a weighted combination of all the sequential algorithms or just the output of the final algorithm
    * Eg. Two phase algorithms to construct refined models for outlier detection in two phases
    * Eg. Recursive exploration of subspaces of data based on the discriminating capabilities of predecessor subspaces 
* Independent ensembles
	* Different algorithms applied on the dataset or a subset of it
    * Can choose different models or construct different datasets out of the given dataset, independent of other models or datasets respectively

##### Categorisation by constituent components
* Model centered ensembles
    - Train multiple models on the same dataset and combine the scores
    - Challenges in normalisation and combination of scores
    - Particular example where same model trained with different model parameters
        + LOF method - kNN based, run for different values of *k* and combined using a *best fit* approach
        + LOCI method - makes use of a sampled neighbourhood to check for outlier behaviour, over a different granularity of samples every time and combines using *best fit*
* Data centered ensembles
    - Explore multiple samples of the dataset
        + Subset of data
        + Subspace of data
    - Eg. Feature bagging
        + Sample multiple subspaces and compute LOF score over each
        + Combination using averaging or softmax
        + Subspace selection using statistical methods
    - Eg. Iterative removal of outliers to refine data in subsequent iterations

##### Normalisation and Combination
* Normalisation
    - Need to convert outlier scores into probablities
        + Model the data and outlier as coming from same or multiple probability distributions
        + Learn the parameters using Expectation Maximisation
* Choice of combination function
    - Functions like max, min, average, damped average, pruned average or simple the last ensemble's output
    - Arguments against averaging as it dilutes the outlier scores from models which might be irrelevant, unless model choice is carefully made

## 4. Fast Anomaly Detection for Streaming Data
#### Link:
* [Fast Anomaly Detection for Streaming Data](./StreamingMethods/Partitioning/3229-15879-1-PB.pdf)

#### Key Ideas:
* Outlier detection in streams has challenges:
    - Infinite length of streams
    - Mostly non-outlier samples (rarity of outliers)
    - Evolving data over time
* Propose Streaming Half Space Chains to 
    - Processing data in one pass, opposed to offline outlier detection algorithms
    - Semi-supervised one class anomaly detection to detect rare instances of outliers
    - Efficient model update to incorporate for time varying data
* Tree structure constructed independent of data samples, prior to stream processing
* Constant order time and space

#### Challenges
* Issues with offline training and continuous feature spaces
* Supervised methods perform better but training data for rare outliers not available

#### Key Components of the solution
##### Half Space Trees construction:
- Set of nodes forms a tree
- Each node captures a mass in a subspace of the stream
- Segment the input data stream into contiguous windows of the same size
- In particular, two consecutive windows, the *reference* and the *latest* windows are considered 
    + Helps to capture the time varying data profile

##### Anomaly score computation:
- Compute a score based on the path traversed in the half space tree, T
    + *Node.r x 2^Node.k* where *r* is the mass in the *reference* window and *k* is the depth of the node
- Final score is the sum of scores output by every tree in the ensemble
