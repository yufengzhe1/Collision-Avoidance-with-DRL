# Collision-Avoidance-with-DRL
Decentralized Non-communicating Multiagent Collision Avoidance with Deep Reinforcement Learning

## 1. Generate training data
  利用[ORCA](http://www.meltycriss.com/2017/01/14/paper-orca/)算法进行轨迹数据集的生成。ORCA是经典的避障算法，只要双方都采用ORCA，那么双方无需通信，即可分布式的求出各自保证不会发生碰撞的速度。简单来说，就是在已知自身和其他agents的速度情况下，将未来 δ 时间内有可能发生碰撞的速度完全排除在外，得到v(ORCA),然后在其中选择一个与自身的偏好速度最接近的速度，Vnew=argmin ||V-Vopt ||,其中	V属于V(ORCA)。
  
  代码位于Project1文件夹。运行环境：win10+vs2017+openGL库。运行即可输出动态演示图，各个agents的轨迹坐标集。

## 2. training the model
  CADRL算法，利用神经网络来估计状态值函数，将连续的动作离散化为35个可选的动作空间，通过最大化 即时奖励与下一个状态的价值和 来选取下一个动作。CADRL引入了价值网络（value network），该价值网络利用agent自身状态与其相邻agent的联合状态来训练模型。CADRL包含两部分，Deep V-Learning训练模型，CADRL利用训练好的模型进行防碰撞路径规划。
### 2.1 reward
  奖励函数的设计。由于是两个物体防碰撞路径规划情景，奖励函数设计成距离越远奖励越大，到达目的地奖励为1，彭改装奖励为-0.25，其他情况根据距离远近奖励范围在（-0.2，-0.1）。

### 2.2 Deep V-Learning（training the value network）
  算法输入：ORCA生成的轨迹集
  算法输出：value network
  
  首先，将输入的轨迹集处理成“状态-价值”对，初始化value network，并将其复制一份；然后在每一次迭代训练中利用CADRL算法来最大化 即时奖励与下一个状态的价值和（此时利用的是初始化的value network的复制版本）得到下一个状态值，然后利用新的状态值更新value network；最后输出讲过训练的value network。
  
### 2.3 CADRL
  算法输入：value network，利用value network 生成的model中的参数
  算法输出：最大化即时奖励与下一状态 所选择的动作，根据所选择的动作生成下一时刻状态。
  
  首先进行速度滤波（便于后面计算中包含的求积分运算）；然后用估计的动作计算下一个近似状态，计算奖励，利用ε-贪心算法在动作空间中选择动作最大化即时奖励与下一状态 。
  
### 2.4 代码
  代码在CADRL-master文件夹，环境Ubuntu16.04+Python3.7+pycharm+Pytorch。
  执行train model：python train.py --config=configs/model.config --gpu（GPU版本）
                   python train.py --config=configs/model.config（CPU版本）
                   
                   
  执行可视化动态展示，利用matplotlib.pyplot：python visualize.py
  
