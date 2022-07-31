# Advanced Programing
by: Omri Nitzan and Moshe Kalamaro


# KNN
The k-nearest neighbors (KNN) algorithm is a data classification method for estimating the likelihood that a data point will become a member of one group or another based on what group the data points nearest to it belong to.

KNN works by finding the distances between a query and all the examples in the data, selecting the specified number examples (K) closest to the query, then votes for the most frequent label (in the case of classification) or averages the labels (in the case of regression).

In our code we will search for the most frequent label.

# Explanation of the Algorithem

Firstly we put all the classified irises in a vector of flowers.
We want to classify each point in the Unclassified file, so we calculate the distance from each flower in the flower vector to the iris we want classify.
We then sort the vector (and now know that the KNN are the first k elements in the vector).
we count the number of instances of each flower type and the type with the most instances is the solution to our problem.
