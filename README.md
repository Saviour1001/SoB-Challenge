# SoB-Challenge

This is my submission for the SoB Challenge. 

The challenge was fun. Its basically the classical 0-1 Knapsack problem. We are given a list of transactions along with their IDs, their fees and their weights. We need to collect transactions such that their combined weight is less than the block weight i.e. 4 million. The fees attribute of the transactions should be maximized. 

# Solution Approach

The approach to find the optimum solution is via Dynammic programming as we could simply keep the track of all the solutions and finding the best approach. But there is a problem in this approach as some of the transactions have parent transactions and for a transaction with parent transactions to be included in the block, all the parent transactions will also be required to include in the block. And thus this will create too many parameters to keep check of while conducting Dynammic Programming. 

Thus I approached it greedily. I sorted the complete list of the transactions based on their fees and am including each and every transaction which can be included such that the current weight of the Block + the next transaction is lesser than the maximum weight. 

I did enjoy the challenge and would continue trying to code the optimum solution.  

