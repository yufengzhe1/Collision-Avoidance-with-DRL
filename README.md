# Collision-Avoidance-with-DRL
Decentralized Non-communicating Multiagent Collision Avoidance with Deep Reinforcement Learning

## 1. Generate training data
  利用[ORCA](http://www.meltycriss.com/2017/01/14/paper-orca/)算法进行轨迹数据集的生成。ORCA是经典的避障算法，只要双方都采用ORCA，那么双方无需通信，即可分布式的求出各自保证不会发生碰撞的速度。简单来说，就是在已知自身和其他agents的速度情况下，将未来 δ 时间内有可能发生碰撞的速度完全排除在外，得到v(ORCA),vnewA=argminv∈ORCAτA∥v−voptA∥

### 进行训练
