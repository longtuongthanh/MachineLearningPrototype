# MachineLearningPrototype
This project is started in 2018, before I used Github.

This is my first attempt at venturing into the Machine Learning field. I used the genetic algorithm in order to solve 10 bit a+b with only bitwise AND, OR, SHL, SHR and NOT. 
The bots are scored based on how many bits they got right.
From this project, it turns out that genetic algorithms are not that good. Especially when coupled with the fact that I have no idea how to steer the AI towards the correct answer without outright giving the answer away. You generally have to have some good idea on how the end AI works, but then making machine learning is kind of redundant if you do. The best they could do is tweak numbers over time as user preference changes. Even then, a normal AI without machine learning, or a non-random learning mechanism, would probably serve that purpose better.
There is significant trouble in defining the 'small mutation' that happen between each generation when it comes to machine learning, because depending on how this 'small mutation' is implemented, there could be large bias in the answer, which makes machine learning more suitable for finding one of many answers instead of the only answer.

Machine learning also requires a simulation space that may need to be specifically implemented outside of the target program, which may cause desync in expected performance.
