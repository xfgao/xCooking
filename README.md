# xCooking
Code for the collaborative cooking game in the RO-MAN 2020 paper "Joint Mind Modeling for Explanation Generation in Complex Human-Robot Collaborative Tasks".
To run the code please compile with Unreal Engine 4.23. 

We provide the source code for the gaming environment and you can implement the agent and the XAI module:
- "STAOG.h" defines all the data structures and some utilites;
- "TaskPawn" class is the main workhorse of the game. It defines how the agent interact with the environment. AIActionPlan queues all the plans planner makes.


# Binary
For a binary which is playable under Windows:

https://drive.google.com/file/d/1Jqv3hKOQNeHiIgDZ1ra2Ns0LJB9-a6xO/view?usp=sharing

It contains both the cooking game, an collaborative agent and the XAI module. The user can control the agent using keyboard. Explanations would be displayed via the user interface. After the task has been finished, the time to completion each dish would be recorded.
