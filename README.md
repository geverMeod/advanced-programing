# Advanced Programing - ass2
by: Omri Nitzan and Moshe Kalamaro


## KNN
The k-nearest neighbors (KNN) algorithm is a data classification method for estimating the likelihood that a data point will become a member of one group or another based on what group the data points nearest to it belong to.

KNN works by finding the distances between a query and all the examples in the data, selecting the specified number examples (K) closest to the query, then votes for the most frequent label (in the case of classification) or averages the labels (in the case of regression).

## Explanation of the Algorithem

The client sends the server the unclassified iris file one line at a time, the server classifies the iris from the line with the KNN algorithem (that was used in ass1) and sends the type of the classified iris back to the client.

The client classifies all the irises in the unclassified file by sending all of them one by one to the server.

We added comments in the code if more clarification is requierd.

## How to Run

There are four files, Flower.hpp, Flower.cpp, tcp_client.cpp and tcp_server.cpp.

since we can't put a direct path to the input file, the classified.csv and Unclassified.csv files should be in the same directory as the program.

we recommend you to write these instructions in the cmake file:
add_executable(Server tcp_server.cpp Flower.cpp)
add_executable(Client tcp_client.cpp
         
the client recieves the path to the input and output files from the command line arguments, the first argument should be the input file (contains the uncalssified flowers) and the second argument will be the place whare the output file will be created.

  example: ./Client Unclassified.csv Output.csv
 
