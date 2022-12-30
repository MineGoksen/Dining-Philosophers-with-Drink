# Dining-Philosophers-with-Drink

## Run program
`gcc dining_philosophers.c -lpthread` <br />
`./a.out [filozof_sayisi] `

## Explanation
In this version of Dining Philosophers problem, we can also have a beverage service. The process has 3 stages: taking drink, eating rice and thinking.
Let not every philosopher go to the dinner table without a glass of drink in his hand and drink all the drink during the meal. However, let there be only one jug around, and only one philosopher at a time can take a drink from that jug. Let's call the number of philosophers N. As the waiter finishes, he puts K cup (a random value between 1<=K<=5N) of beverage into the jug. Let's call the time until the pitcher runs out one lap. A philosopher may eat more than one serving per turn.
