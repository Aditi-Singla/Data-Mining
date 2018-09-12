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
