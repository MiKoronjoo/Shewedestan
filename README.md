# Shewedestan
**Design and Analysis of Algorithms Course Project**

## Definition
### Phase 1
Shewedestan is a country which has S states and the ith state has Ci cities ( C1 +C2 +...+ CS = C, so we have C cities).
The coordinates of each city are defined as (Xcity, Ycity, Statecity).
Shewed The Great wants to design roads between cities in a way that all the cities are reachable from each other, but due to lack of budget in each state, authorities enforced civil engineers to design at most one path between each two cities (a path consists of some roads which are connected by their cities).
The cost of constructing a road between any two cities is proportional to the distance of two.
Given the coordinates, we want to assist Shewed. What can we do in order to design paths for these cities?
* a. In order to solve the problem, you can apply popular algorithms such a **Prim** and **Kruskal**.
* b. Please try to present a **greedy algorithm**.(Because you may face a large amount of data, we recommend you to **apply a linear algorithm** in order to solve the problem [It may not be optimal but it should be **as optimal as it can be**.])
* c. Shewed’s authorities have decided to choose a capital for each state. In their opinion, each capital should have a predefined property: the maximum distance from all cities to the capital is minimum. Try to find a capital for each state of Shewedestan.

### Phase 2
Shewed participated in a meeting and after that, concluded that it is more sensible to assign each state’s road construction to that state and let each state construct its roads independently (though all previous conditions must still hold).
Each governor tries to minimize road construction cost, and after that Shewed tries to connect all the states.
Now, the “best solution” , which is a solution that has the least cost, to road construction problem of the whole country is defined as a road construction in which all the cities are reachable from each other with at most one path between them.
* a. Try to apply **Kruskal** or **Prim** algorithms for each state, and after connecting the states, compare the solution’s quality(the time and memory complexity and the total cost of construction) of your proposed algorithm with the “best” solutions found in previous steps **a** and **b** of phase 1.
* b. Try to plan a new greedy algorithm instead of the previous one in step **a**, and compare your results with the previous step **a**.

### Phase 3
Due to the fluctuations in authorities’ decisions, Shewed The Great attempts to connect capitals instead of connecting cities.
In authorities’ opinion, it is not necessary for cities to participate in road construction.
In other words, the important thing is to minimize road construction (while maintaining the reachability of all capitals from one another) in such a way that each non-capital city may or may not be present in the solution.
In order to solve this problem you have to consider phase 1 and find the capital of each state and after that, attempt to design a method to solve this phase.

#### Notes:
* 1. There are four datasets and you must perform your algorithms on all four. The first dataset contains 100 cities, second one contains 10,000 and third and fourth contain 1,000,000 cities.
* 2. Each phase has 1 point and it is graded on how well your algorithms perform on the datasets. The quality of your algorithm is determined by it’s execution speed and the quality of final answer
* 3. The amount of points that you will receive in each phase depends on the quality of your algorithms. The quality of each algorithm is determined competitively. That is, everyone’s algorithms will be ranked by their quality and the ones ranked higher will receive more points.
