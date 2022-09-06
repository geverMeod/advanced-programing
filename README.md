# Advanced Programing - ass3
by: Omri Nitzan and Moshe Kalamaro


### We used unique_ptr, so please run the code in c++14.

## KNN
The k-nearest neighbors (KNN) algorithm is a data classification method for estimating the likelihood that a data point will become a member of one group or another based on what group the data points nearest to it belong to.

KNN works by finding the distances between a query and all the examples in the data, selecting the specified number examples (K) closest to the query, then votes for the most frequent label (in the case of classification) or averages the labels (in the case of regression).

## Explanation of the Algorithem
we implemented a client and server system using the TCP protocol, each client can uplode files and run the knn algorithem and other commands on them. most of the work is done on the server side, the server gets the raw files from the client and then manipulates them according to the clients' requstes, the client is used mostly to display server messages to the user.
in order to handle multiple clients the server opens a new thread for each one, threads are also opened for "heavy" functions like the classify command so that the client will not have to wait for them to finish.

## How to Run

There are three directories: Server, Client and testing.
in the server directory you will find the files used only for the server executble and in the client directory you will find the files used only for the client executble, files that are used for both are outside of the directories.
in the testing directory you will find example csv files we used to test the code.

we recommend you to compile this code using the included CMakeLists.txt file, it creates both the server and client executbles. then run the server and after that run the clients.


