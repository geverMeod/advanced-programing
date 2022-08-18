# Advanced Programing - ass2
by: Omri Nitzan and Moshe Kalamaro


## KNN
The k-nearest neighbors (KNN) algorithm is a data classification method for estimating the likelihood that a data point will become a member of one group or another based on what group the data points nearest to it belong to.

KNN works by finding the distances between a query and all the examples in the data, selecting the specified number examples (K) closest to the query, then votes for the most frequent label (in the case of classification) or averages the labels (in the case of regression).

## Explanation of the Algorithem

In our code, the client and the server communicate in a way that the client sends the server a string line representing the unclassified iris,
the server classifieds the iris with the KNN algorithem(that was used in ass1) and returns the iris's type to the client.

The client classifieds all the irises in the unclassified file by sending all of them one by one to the server.

We added comments in the code if more clarification is requierd.

## How to Run

There are four files, Flower.h, Flower.cpp, tcp_client.cpp and tcp_server.cpp.

since we can't put a direct path to the input file, the classified.csv and Unclassifies.csv files should be in the same directory as the program.

When executing the server, it should be with Flower.cpp.

  we give a example on what to write in the make file:
         add_executable(Server tcp_server.cpp Flower.cpp)
         add_executable(Client tcp_client.cpp
         
When running the client in the terminal there should be a command line with the name of the unclassified file and the name of the desired output file

  example: ./Client Unclassified.csv Output.csv
 
